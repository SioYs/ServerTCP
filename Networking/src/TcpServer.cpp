
#include <iostream>
#include "Networking/TcpServer.h"
#pragma once


namespace tcp {
	using boost::asio::ip::tcp;





	TcpServer::TcpServer(IPV ipv, int port) : _ipVersion(ipv), _port(std::move(port)),
		_acceptor(_ioContext, tcp::endpoint(ipv == IPV::V4 ? tcp::v4() : tcp::v6(), port)) {





	};

	int TcpServer::Run() {

		try {
			startAccept();
			_ioContext.run();
			

		}

		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
			return -1;
		}
		return 0;

	}

	void TcpServer::startAccept() {
		//create a connection 


		//asynchronously accept the connection

	}


	//Not a good practice to assing in ctor body especially for complex types like _acceptor. It is better to use the constructor initialization list where we do member initialization and it is better for complex types like the _acceptor
//TcpServer::TcpServer( IPV ipv, int port)  {
//	_ipVersion = ipv;
//	_port = port;
//	_acceptor = tcp::acceptor(_ioContext, tcp::endpoint(ipv == IPV::V4 ? tcp::v4() : tcp::v6(), port));



//};

}