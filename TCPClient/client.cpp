#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char* argv[]) {
	try {
		if (argc != 2) { //���� �� ������ ip �� ���� ���� �� �ֵ��� ���ٸ� ����ó��
			std::cerr << "Usage: client <host>" << std::endl;
			return 1;

		}

		boost::asio::io_context io_context;
		tcp::resolver resolver(io_context); // ������ �����ϱ� ����
		tcp::resolver::results_type endpoints = resolver.resolve(argv[1], "daytime"); // daytime ���� ip�� ���� endpoints ����

		// ���� ����� ���� ���� ����
		tcp::socket socket(io_context);
		boost::asio::connect(socket, endpoints); // ���� �õ�

		for (;;) {
			boost::array<char, 128> buf; // �����͸� �ޱ� ���� buf ����
			boost::system::error_code error;

			size_t len = socket.read_some(boost::asio::buffer(buf), error);  //boost::asio::buffer �Լ��� buf�� ���� ũ�⸦ ���������� ���� ���� (���� ��� �߰������� �޸� �Ҵ�)
			// �ش� �Լ��� ���� �������� ���̸� ��ȯ
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