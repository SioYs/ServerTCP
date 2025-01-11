

//C:\Users\bhari\source\repos\ServerTCP\Networking\include\Networking\Base.h
#pragma once	

#include<boost/asio.hpp>
#include"TcpConnection.h"
#include <functional>

namespace Tcp {

	enum class IPV {
		V4,
		V6
	};

	class TcpServer {

	public:
		TcpServer(IPV ipv, int port);
		int Run();


		template <typename T>
		void WriteConnection(int connectionIndex, const T& message);
		
		template <typename T>
		using ListenCallback = std::function<void(int, const T&)>;


		template<typename T>
		void RegisterListenCallback(ListenCallback<T> callback);


	private:
		void startAccept();
		IPV _ipVersion;
		int _port;

		boost::asio::io_context _ioContext;
		boost::asio::ip::tcp::acceptor _acceptor;

		std::vector<TcpConnection::pointer> _connections {};

	};
}
