#include <iostream>
#include <WinSock2.h>
#include <string.h>
#pragma warning(disable : 4996)
#pragma comment (lib, "Ws2_32.lib")

int main()
{
	WSADATA wsd;
	SOCKET serv = NULL;
	int recv_len;
	char buf[1024];
	struct sockaddr_in serv_name, si_other;
	int slen = sizeof(si_other);
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		std::cout << "Failed startup\n";
		system("PAUSE");
		exit(EXIT_FAILURE);
	}
	std::cout << "Initialized \n";
	if ((serv = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	{
		std::cout << "Failed socket\n";
		system("PAUSE");
		exit(EXIT_FAILURE);
	}
	serv_name.sin_family = AF_INET;
	serv_name.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	serv_name.sin_port = htons(8888);
	if (bind(serv, (struct sockaddr*)&serv_name, sizeof(serv_name)) == SOCKET_ERROR)
	{
		std::cout << "Failed \n";
		system("PAUSE");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		std::cout << "Waiting... \n";
		memset(buf, '\0', 1024);
		if ((recv_len = recvfrom(serv, buf, 1024, 0, (struct sockaddr*) & si_other, &slen)) == SOCKET_ERROR)
		{
			std::cout << "Failed \n";
			system("PAUSE");
			exit(EXIT_FAILURE);
		}
		std::cout << "Received packet:\n" << inet_ntoa(si_other.sin_addr) << "\n" << ntohs(si_other.sin_port) << '\n';
		if (sendto(serv, buf, recv_len, 0, (struct sockaddr*)&si_other, slen) == SOCKET_ERROR)
		{
			std::cout << "Failed \n";
			system("PAUSE");
			exit(EXIT_FAILURE);
		}
	}
	closesocket(serv);
	WSACleanup();
}