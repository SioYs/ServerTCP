#include <boost/asio.hpp>
#include <string>

namespace tcp {
	using boost::asio::ip::tcp;

	class TcpConnection {

	public:
		tcp::socket& Socket() {

			return _socket;
		}
		void Start();


	private:
		TcpConnection(boost::asio::io_context& ioContext);	
	private:
		tcp::socket _socket;
		std::string _message{ "Hello beautiful client \n" };
	};
}