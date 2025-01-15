#include <boost/asio.hpp>
#include <iostream>
#include "ServerTcp.h"
#include <Networking/server/TcpServer.h>
#include <Networking/server/TcpConnection.h>


using namespace std;

using Tcp::TcpServer;
using boost::asio::ip::tcp;

int main(int argc, char* argv[]) {

	TcpServer server = TcpServer(Tcp::IPV::V4, 1337);


	server.OnJoin = [](Tcp::TcpConnection::pointer server) {
		cout << "User has joined the server: " << server->GetUsername() << endl;
	

	};
	server.OnLeave = [](Tcp::TcpConnection::pointer server) {

		cout << "User has left the server: " << server->GetUsername() << endl;

	};

	server.OnClientMessage = [&server](const std::string& message) {


		cout << "User has sent a message " << message << endl;
		server.Broadcast(message);

	};

 
	server.Run();


	return 0;
}


//Cheat sheat for boost asio tcp accepto, and boost asio functions and stuff

//acceptor.local_endpoint().port() - get the port of the created acceptor
//The acceptor listens on a specific port and ip adress\
//after it is set to listen it will accept connection and provides a socket that represents the connection to the client:

//acceptor.accept(socket);




//boost::asio::write(socket, boost::asio::buffer(hello_message), error);
/*

socket: This is the tcp::socket object that represents the connection to the client.It is used for communication between the server and the client.
boost::asio::buffer(hello_message) : This converts the hello_message(a string or a byte array) into a buffer that can be sent over the network.
boost::asio::write : This function writes data from the buffer to the socket.It sends the data over the network to the connected client.

*/