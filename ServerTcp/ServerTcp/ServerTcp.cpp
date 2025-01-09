// ServerTcp.cpp : Defines the entry point for the application.
//
#include <boost/asio.hpp>
#include <iostream>
#include "ServerTcp.h"
#include <Networking/Base.h>
using namespace std;

using boost::asio::ip::tcp;

int main()
{

	try {

		boost::asio::io_context io_context;


		tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 13));

		while (true) {

			tcp::socket socket(io_context);
			acceptor.accept(socket);


			std::string hello_message = "Hello beautiful client \n";
			boost::system::error_code error;

			boost::asio::write(socket, boost::asio::buffer(hello_message), error);

		}

	}
	catch (const std::exception& e) {
		cerr << e.what() << endl;
	}
	



	return 0;
}
