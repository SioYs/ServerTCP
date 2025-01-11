#include <boost/asio.hpp>
#include <string>
#include <iostream>
#include <memory>

namespace Tcp {
	using boost::asio::ip::tcp;

	//std::enable_shared_from_this is crucial when we want to pass a reference to the current object in a callback function for exmaple
	//It allowes the object to safely create a shared_pointer to itself
	class TcpConnection : public std::enable_shared_from_this<TcpConnection> {

	public:
		using pointer = std::shared_ptr<TcpConnection>;

		//AI explanation :

	/*	The std::shared_ptr uses a reference count internally to track how many shared_ptr instances are pointing to the object."
			"When the resence count drops to zero, the memory is automatically freed."*/


		//this factory function is responsible for the creation of a new TcpConnection object and wraps is it in a shared pointer
		//The idea of the shared pointer is the following:
		//by using a shared pointer the lifetime of the object is automatically mananged and until all the shared_pointer are not used the object will stay alive
		//If all the shared pointers are not used it will be deleted. This way we are managing memory leaks. And we are not deleting the object too early becasue 
		//some other part of our app might still be using this object
		static pointer Create(boost::asio::io_context& ioContext) {

			return pointer(new TcpConnection(ioContext));
		}


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