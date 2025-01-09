#include <boost/asio.hpp>
#include <iostream>
#include "ServerTcp.h"
#include <Networking/Base.h>
using namespace std;
using boost::asio::ip::tcp;

int main(int argc, char* argv[]) {
    try {
        boost::asio::io_context io_context;

        // Create an acceptor and bind to port 1337
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 1337));

        // Retrieve and display the port dynamically
        cout << "Server is listening on port: "
            << acceptor.local_endpoint().port()
            << endl;

        while (true) {
            cout << "Accepting connections..." << endl;

            tcp::socket socket(io_context);
            acceptor.accept(socket);

            cout << "Client connected! Sending message..." << endl;

            string hello_message = "Hello beautiful client \n";
            boost::system::error_code error;

            boost::asio::write(socket, boost::asio::buffer(hello_message), error);
        }
    }
    catch (const std::exception& e) {
        cerr << e.what() << endl;
    }

    return 0;
}
