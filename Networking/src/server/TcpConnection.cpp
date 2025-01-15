#include "Networking/server/TcpConnection.h"

#include <boost/asio.hpp>
#include <iostream>
using std::cout;

namespace Tcp {
    TcpConnection::TcpConnection(io::ip::tcp::socket&& socket) : _socket(std::move(socket)) {
        boost::system::error_code ec;

        std::stringstream name;
        name << _socket.remote_endpoint();

        _username = name.str();
    }

    void TcpConnection::Start(MessageHandler&& messageHandler, ErrorHandler&& errorHandler) {
        _messageHandler = std::move(messageHandler);
        _errorHandler = std::move(errorHandler);

        asyncRead();
    }

    void TcpConnection::Post(const std::string& message) {
        bool queueIdle = _outgoingMessages.empty();
        _outgoingMessages.push(message);

        if (queueIdle) {
            asyncWrite();
        }
    }

    void TcpConnection::asyncRead() {
        io::async_read_until(_socket, _streamBuf, "\n", [self = shared_from_this()]
        (boost::system::error_code ec, size_t bytesTransferred) {
            self->onRead(ec, bytesTransferred);
        });
    }

    void TcpConnection::onRead(boost::system::error_code ec, size_t bytesTranferred) {
        if (ec) {
            _socket.close(ec);

            _errorHandler();
            return;
        }

        std::stringstream message;
        message << _username << ": " << std::istream(&_streamBuf).rdbuf();
        _streamBuf.consume(bytesTranferred);

        _messageHandler(message.str());
        asyncRead();
    }

    void TcpConnection::asyncWrite() {
        io::async_write(_socket, io::buffer(_outgoingMessages.front()), [self = shared_from_this()]
        (boost::system::error_code ec, size_t bytesTransferred) {
            self->onWrite(ec, bytesTransferred);
        });
    }

    void TcpConnection::onWrite(boost::system::error_code ec, size_t bytesTransferred) {
        if (ec) {
            _socket.close(ec);

            _errorHandler();
            return;
        }

        _outgoingMessages.pop();

        if (!_outgoingMessages.empty()) {
            asyncWrite();
        }
    }
}
