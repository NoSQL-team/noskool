//
// Created by amartery on 08.11.2020.
//

#ifndef NOSKOOL_SERVER_POSTS_CONNECTION_H
#define NOSKOOL_SERVER_POSTS_CONNECTION_H

#include <string>
#include "utilty.h"


namespace tcp_server {

    class Connection {
    public:
        friend class TCPServer;

        explicit Connection() = default;
        Connection(std::string& ip, uint16_t port);
        explicit Connection(const Socket& fd) {}
        Connection(Connection&& con) noexcept;
        virtual ~Connection() noexcept;

        size_t write(const std::string& message);
        void connect(const std::string& addr, uint16_t port);
        size_t read(const std::string& message);
        void close();
        bool is_opened() const;
        void set_timeout(int time);
        void send_size(const size_t size);
        size_t recv_size();
        void set_serv_name(const std::string& serv_name);
        std::string get_serv_name() const;
        int get_connnection() const;

    private:

        Socket sock_fd_;
        bool is_readable_ = false;
        std::string server_name_;
    };

}


#endif  // NOSKOOL_SERVER_POSTS_CONNECTION_H