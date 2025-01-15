#pragma once


#include <boost/asio.hpp>
#include <string>
#include <iostream>
#include <memory>
#include <queue>


namespace Tcp {
    using boost::asio::ip::tcp;
    namespace io = boost::asio;

    using MessageHandler = std::function<void(std::string)>;
    using ErrorHandler = std::function<void()>;

    class TcpConnection : public std::enable_shared_from_this<TcpConnection> {
    public:
        using pointer = std::shared_ptr<TcpConnection>;

        static pointer Create(io::ip::tcp::socket&& socket) {
            return pointer(new TcpConnection(std::move(socket)));
        }

        inline const std::string& GetUsername() const {
            return _username;
        }

        tcp::socket& Socket() {
            return _socket;
        }

        void Start(MessageHandler&& messageHandler, ErrorHandler&& errorHandler);
        void Post(const std::string& message);

    private:
        explicit TcpConnection(io::ip::tcp::socket&& socket);

        // Wait for a new message from client
        void asyncRead();
        void onRead(boost::system::error_code ec, size_t bytesTranferred);

        void asyncWrite();
        void onWrite(boost::system::error_code ec, size_t bytesTransferred);

    private:
        tcp::socket _socket;
        std::string _username;

        std::queue<std::string> _outgoingMessages;
        io::streambuf _streamBuf{ 65536 };

        MessageHandler _messageHandler;
        ErrorHandler _errorHandler;
    };
}




//AI explanation :

/*	The std::shared_ptr uses a reference count internally to track how many shared_ptr instances are pointing to the object."
		"When the resence count drops to zero, the memory is automatically freed."*/

		//auto strongThis = shared_from_this();

				//this factory function is responsible for the creation of a new TcpConnection object and wraps is it in a shared pointer
				//The idea of the shared pointer is the following:
				//by using a shared pointer the lifetime of the object is automatically mananged and until all the shared_pointer are not used the object will stay alive
				//If all the shared pointers are not used it will be deleted. This way we are managing memory leaks. And we are not deleting the object too early becasue 
				//some other part of our app might still be using this object


				// |
				// |
				// |
				// |
				// v


		//static pointer Create(boost::asio::io_context& ioContext) {
		//
		//	return pointer(new TcpConnection(ioContext));
		//}