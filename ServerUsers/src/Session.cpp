//
// Created by lerakry on 03.12.2020.
//

#include "Session.h"
#include "HandlerUser.h"
#include <iostream>

using boost::asio::ip::tcp;

tcp::socket& Session::socket()
{
    return socket_;
}

void Session::send_answer(std::string& answer)
{
    boost::asio::io_service service;
    tcp::endpoint end(boost::asio::ip::address::from_string("127.0.0.1"), 9999);
    tcp::socket socket(service);
    socket.async_connect(end, [&socket, this, &answer] (const boost::system::error_code& err) {
        if(!err) {
            boost::asio::write(socket, boost::asio::buffer(answer));
        }
    });
    service.run();
}

void Session::start()
{
    for (size_t i = 0; i < max_length; i++) {
        data_[i] = '\0';
    }
	socket_.async_read_some(boost::asio::buffer(data_, max_length),
							boost::bind(&Session::handle_read, this,shared_from_this(),
										boost::asio::placeholders::error));
}

void Session::handle_read(std::shared_ptr<Session> session, const boost::system::error_code& error)
{
    if (!error) {
        auto handler = std::make_shared<HandlerUser>(io_service_, *session.get(), data_base_);
        auto str = std::string(data_);
        handler->handle_request(str);
    }
    else {
		session.reset();
    }
}
