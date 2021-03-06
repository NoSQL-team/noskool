//
// Created by steve on 15.12.2020.
//

#ifndef MAIN_TP_SESSION_H
#define MAIN_TP_SESSION_H

#include <boost/system/error_code.hpp>
#include "../include/types.h"

class Session : public std::enable_shared_from_this<Session> {
public:

    Session(tcp::socket&& socket,
            std::map<std::string, dispatcher_entry> const& dispatcher,
            std::map<std::string, dispatcher_entry_with_body> const& dispatcher_with_body)
            : socket    (std::move(socket))
            , dispatcher(dispatcher)
            , dispatcher_with_body(dispatcher_with_body) {}

    void start();

private:
    static void send_response(std::string& response);
    void read();
    void on_read(error_code error, std::size_t bytes_transferred);

// Находим соответствующий обработчик команд, применяем его,
// если он найден, отправляем ответ обратно.
    std::string dispatch(std::string const& line);


    tcp::socket socket;
    // сохраняем диспетчер внутри объекта сервера и передаем ссылку на него в сеанс
    std::map<std::string, dispatcher_entry> const& dispatcher;
    std::map<std::string, dispatcher_entry_with_body> const& dispatcher_with_body;
    io::streambuf incoming;
    std::queue<std::string> outgoing;

};

#endif //MAIN_TP_SESSION_H
