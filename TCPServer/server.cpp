#include <iostream>
#include <ctime>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

std::string make_daytime_string() {
	using namespace std;
	time_t now = time(0);
	return "good";
}

int main() {
	try {
		boost::asio::io_context io;
		tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 13)); //Port 13, IP version 4


		for (;;) {
			tcp::socket socket(io);
			acceptor.accept(socket);

			std::string message = make_daytime_string();

			boost::system::error_code ignored_error;
			boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
		}
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}