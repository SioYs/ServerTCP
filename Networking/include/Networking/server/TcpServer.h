

//C:\Users\bhari\source\repos\ServerTCP\Networking\include\Networking\Base.h
#pragma once	

#include<boost/asio.hpp>
#include"TcpConnection.h"
#include <functional>
#include <optional>
#include <unordered_set>


namespace Tcp {
    namespace io = boost::asio;

    enum class IPV {
        V4,
        V6
    };

    class TcpServer {
        using OnJoinHandler = std::function<void(TcpConnection::pointer)>;
        using OnLeaveHandler = std::function<void(TcpConnection::pointer)>;
        using OnClientMessageHandler = std::function<void(std::string)>;

    public:
        TcpServer(IPV ipv, int port);

        int Run();
        void Broadcast(const std::string& message);
    private:
        void startAccept();

    public:
        OnJoinHandler OnJoin;
        OnLeaveHandler OnLeave;
        OnClientMessageHandler OnClientMessage;

    private:
        IPV _ipVersion;
        int _port;

        io::io_context _ioContext;
        io::ip::tcp::acceptor  _acceptor;
        std::optional<io::ip::tcp::socket> _socket;
        std::unordered_set<TcpConnection::pointer> _connections{};
    };

}
