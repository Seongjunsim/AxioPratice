#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#pragma once

namespace p {
	class Printer
	{
	public:
		Printer(boost::asio::io_context& io);
		~Printer();
		void print();

	private:
		boost::asio::steady_timer timer_;
		int count_;
	};
}


