#include "Networking/TcpConnection.h"
#include <boost/asio.hpp>
#include <iostream>
namespace Tcp {




	TcpConnection::TcpConnection(boost::asio::io_context& ioContext) : _socket(ioContext) {
	
	
	}


	void TcpConnection::Start() {
		auto strongThis = shared_from_this();

		boost::asio::async_write(_socket, boost::asio::buffer(_message),
			[strongThis](const boost::system::error_code& error, size_t bytesTransffered) {
			if (error) {

				std::cout << "Failed to send a message!\n";
			}
			else {

				std::cout << "Sent " << bytesTransffered << "bytes of data \n";
			}

		}
		);


		boost::asio::streambuf buffer;
		_socket.async_receive(buffer.prepare(512), [this](const boost::system::error_code& error, size_t bytesTransferred) {


			if (error == boost::asio::error::eof) {
				//clean connection cut

				std::cout << "Client disconneted properly!";




			}

			else if (error) {

				std::cout << "Client disconneted in a bad way!";
			}
		});

	}
 
}
