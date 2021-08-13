#include "Printer.h"

void print(const boost::system::error_code& e, boost::asio::steady_timer* t ,int* count) {
	if (*count < 5) {
		std::cout << *count << std::endl;
		++(*count);
		t->expires_at(t->expiry() + boost::asio::chrono::seconds(1));
		t->async_wait(boost::bind(print, boost::asio::placeholders::error, t, count));
	}
}
/*
int main()
{
	boost::asio::io_context io;
	p::Printer printer(io);
	io.run();
	return 0;
}
*/