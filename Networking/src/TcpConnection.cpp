#include "Networking/TcpConnection.h"
#include <boost/asio.hpp>
#include <iostream>
namespace tcp {
	TcpConnection::TcpConnection(boost::asio::io_context& ioContext) : _socket(ioContext) {
	
	
	}


	void TcpConnection::Start() {
		boost::asio::async_write(_socket, boost::asio::buffer(_message),
			[this](const boost::system::error_code& error, size_t bytesTransffered) {
			if (error) {

				std::cout << "Failed to send a message!\n";
			}
			else {

				std::cout << "Sent " << bytesTransffered << "bytes of data";
			}

		}
		);


	}
 
}
