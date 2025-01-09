// Client.cpp : Defines the entry point for the application.
//
#include <boost/asio.hpp>
#include "Client.h"
#include <Networking/Base.h>
#include <array>
using namespace std;
#include <iostream>
using boost::asio::ip::tcp;



int main(int argc, char*argv[])
{

	
	try {

		boost::asio::io_context ioContext;

		tcp::resolver resolver{ ioContext };

		auto endpoints = resolver.resolve("127.0.0.1", "1337");

		tcp::socket socket{ ioContext };

		boost::asio::connect(socket, endpoints);


		while (true) {
			array<char, 128>buf{};
			boost::system::error_code error;

			size_t length = socket.read_some(boost::asio::buffer(buf), error);

			if (error == boost::asio::error::eof) {
				//clean connection cut

				break;



			}

			else if(error){

				throw boost::system::system_error(error);
			}

			cout.write(buf.data(), length);



		}

	}
	catch (const std::exception& e) {
		cerr << e.what() << endl;
	}
	cout << "Hello CMake." << endl;
	return 0;
}
