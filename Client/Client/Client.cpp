
#include <Networking/client/TcpClient.h>
#include <iostream>
#include <thread>


using namespace Tcp;

int main(int argc, char* argv[]) {

    std::cout << "I am a client" << std::endl;
    TCPClient client{ "localhost", 1337 };

    client.OnMessage = [](const std::string& message) {
        std::cout << message;
    };

    std::thread t{ [&client]() { client.Run(); } };

    while (true) {
        std::string message;
        getline(std::cin, message);

        if (message == "\\q") break;
        message += "\n";

        client.Post(message);
    }

    client.Stop();
    t.join();
    return 0;
}