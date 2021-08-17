#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char* argv[]) {
	try {
		if (argc != 2) { //실행 시 서버의 ip 를 같이 넣을 수 있도록 없다면 에러처리
			std::cerr << "Usage: client <host>" << std::endl;
			return 1;

		}

		boost::asio::io_context io_context;
		tcp::resolver resolver(io_context); // 서버를 지목하기 위함
		tcp::resolver::results_type endpoints = resolver.resolve(argv[1], "daytime"); // daytime 서버 ip를 가진 endpoints 생성

		// 소켓 통신을 위한 소켓 생성
		tcp::socket socket(io_context);
		boost::asio::connect(socket, endpoints); // 연결 시도

		for (;;) {
			boost::array<char, 128> buf; // 데이터를 받기 위한 buf 변수
			boost::system::error_code error;

			size_t len = socket.read_some(boost::asio::buffer(buf), error);  //boost::asio::buffer 함수로 buf에 대해 크기를 유동적으로 조절 가능 (넘을 경우 추가적으로 메모리 할당)
			// 해당 함수는 읽은 데이터의 길이를 반환
			if (error == boost::asio::error::eof)
				break;
			else if (error)
				throw boost::system::system_error(error);
			std::cout.write(buf.data(), len);
		}
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	
}