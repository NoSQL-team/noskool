//
// Created by steve on 15.12.2020.
//

#include "../include/session.h"
#include "../include/utility_for_lib.h"


void Session::start() {
    read();
}

void Session::read() {
    io::async_read_until(
            socket,
            incoming,
            "\r",
            std::bind(&Session::on_read, shared_from_this(), std::placeholders::_1,  std::placeholders::_2));
}


void Session::send_response(std::string& response) {
    io::io_service service;
    // указать порт http сервера
    ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 9999);
    ip::tcp::socket sock(service);

    sock.async_connect(ep, [&sock, &response](const error_code& error) {
        if (!error) {
            boost::asio::write(sock, boost::asio::buffer(response, response.size()));
        } else {
            std::cerr << error.message() << std::endl;
        }
    });
    service.run();
}

void Session::on_read(error_code error, std::size_t bytes_transferred) {
    
    if(!error) {
        std::istream stream(&incoming);
        std::string line;
        std::string full_line = "";
        while(std::getline(stream, line)) {
            full_line += line + "\n";
        }
        incoming.consume(bytes_transferred);
        std::string trim_full_line = reduce(full_line);
        if(!line.empty()) {
            std::string response = dispatch(trim_full_line) + "\n\r";
            send_response(response);
        }
        read();
    }
}

// Находим соответствующий обработчик команд, применяем его,
// если он найден, отправляем ответ обратно.
std::string Session::dispatch(std::string const& line) {
    std::string response; // строка ответа

    auto end_main_command = line.find("\n\n");

    std::string main_command;
    std::copy(line.begin(), line.begin() + end_main_command, std::back_inserter(main_command));
    auto parameters_request = split(main_command, "\n");

    auto start_body = line.find('{');
    auto end_body = line.rfind('}');
    std::string body;
    std::copy(line.begin() + start_body, line.begin() + end_body + 1, std::back_inserter(body));

    // если есть боди добавляем
    if (body.size() > 1) {
        parameters_request.push_back(body);
    }

    if (parameters_request.size() == 3) { // боди нет
        try {
            RequestWithoutBody result = parse_without_body(parameters_request);
            // поиск хендлера
            if(auto it = dispatcher.find(result.command); it != dispatcher.cend()) {
                auto const& entry = it->second;
                // проверяем количество параметров из url и авторизирован ли пользователь
                //if(entry.args == result.args.size() && check_access(entry.required_auth, result.is_authorized)) {
                    try {
                        // вызов хендлера
                        response =  entry.handler(result.id_request, result.args);
                    } catch(std::exception const& e) {
                        response = parameters_request[0] + "\n\n{\"error\": \"handler execution error\"}";
                    }
                // } else {
                //     response = parameters_request[0] + "\n\n{\"error\": \"bad args or not authorized\"}";
                // }
            } else {
                response = parameters_request[0] + "\n\n{\"error\": \"handler not found\"}";
            }
        } catch(boost::bad_lexical_cast &) {
            response = parameters_request[0] + "\n\n{\"error\": \"parse request error\"}";
        }

    } else if (parameters_request.size() == 4) {  // боди есть
        try {
            RequestWithBody result = parse_with_body(parameters_request);
            // поиск хендлера
            if(auto it = dispatcher_with_body.find(result.command); it != dispatcher_with_body.cend()) {
                auto const& entry = it->second;
                // проверяем количество параметров из url и авторизирован ли пользователь
                // if(entry.args == result.args.size() && check_access(entry.required_auth, result.is_authorized)) {
                    try {
                        // вызов хендлера
                        response = entry.handler(result.id_request, result.args, result.body);
                    } catch(std::exception const& e) {
                        response = parameters_request[0] + "\n\n{\"error\": \"handler execution error\"}";
                    }
                // } else {
                //     response = parameters_request[0] + "\n\n{\"error\": \"bad args or not authorized\"}";
                // }
            } else {
                response = parameters_request[0] + "\n\n{\"error\": \"handler not found\"}";
            }
        } catch(boost::bad_lexical_cast &) {
            response = parameters_request[0] + "\n\n{\"error\": \"parse request error\"}";
        }
    } else {
        response = parameters_request[0] + "\n\n{\"error\": \"too many arguments (" +
                        std::to_string(parameters_request.size())
                        + ")\"}";
    }
    return response;
}

