#include "Printer.h"

namespace p {

	Printer::Printer(boost::asio::io_context& io):timer_(io, boost::asio::chrono::seconds(1)), count_(0) {
		timer_.async_wait(boost::bind(&p::Printer::print, this));
	}

	Printer::~Printer() {
		std::cout << "Final count is " << count_ << std::endl;
	}
	void Printer::print() {
		if (count_ < 5) {
			std::cout << count_ << std::endl;
			++count_;

			timer_.expires_at(timer_.expiry() + boost::asio::chrono::seconds(1));
			timer_.async_wait(boost::bind(&Printer::print, this));
		}
	}
}