

//C:\Users\bhari\source\repos\ServerTCP\Networking\include\Networking\Base.h
#pragma once	

#include<boost/asio.hpp>



namespace tcp {

	enum class IPV {
		V4,
		V6
	};

	class TcpServer {

	public:
		TcpServer(IPV ipv, int port);
		int Run();
		
	private:
		void startAccept();
		IPV _ipVersion;
		int _port;

		boost::asio::io_context _ioContext;
		boost::asio::ip::tcp::acceptor _acceptor;


	};
}
