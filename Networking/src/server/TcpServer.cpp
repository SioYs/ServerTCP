
#include <iostream>
#include "Networking/server/TcpServer.h"
#include "Networking/server/TcpConnection.h"


namespace Tcp {
    using boost::asio::ip::tcp;
    TcpServer::TcpServer(IPV ipv, int port) : _ipVersion(ipv), _port(port),
        _acceptor(_ioContext, tcp::endpoint(_ipVersion == IPV::V4 ? tcp::v4() : tcp::v6(), _port)) {
    }

    int TcpServer::Run() {
        try {
            startAccept();
            _ioContext.run();
        }
        catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            return -1;
        }
        return 0;
    }

    void TcpServer::Broadcast(const std::string& message) {
        for (auto& connection : _connections) {
            connection->Post(message);
        }
    }

    void TcpServer::startAccept() {
        _socket.emplace(_ioContext);

        // asynchronously accept the connection
        _acceptor.async_accept(*_socket, [this](const boost::system::error_code& error) {
            auto connection = TcpConnection::Create(std::move(*_socket));

            if (OnJoin) {
                OnJoin(connection);
            }

            _connections.insert(connection);
            if (!error) {
                connection->Start(
                    [this](const std::string& message) { if (OnClientMessage) OnClientMessage(message); },
                    [&, weak = std::weak_ptr(connection)] {
                    if (auto shared = weak.lock(); shared && _connections.erase(shared)) {
                        if (OnLeave) OnLeave(shared);
                    }
                }
                );
            }

            startAccept();
        });
    }



	//Not a good practice to assing in ctor body especially for complex types like _acceptor. It is better to use the constructor initialization list where we do member initialization and it is better for complex types like the _acceptor
//TcpServer::TcpServer( IPV ipv, int port)  {
//	_ipVersion = ipv;
//	_port = port;
//	_acceptor = tcp::acceptor(_ioContext, tcp::endpoint(ipv == IPV::V4 ? tcp::v4() : tcp::v6(), port));



//};

}