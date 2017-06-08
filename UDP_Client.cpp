#include <iostream>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable : 4996)
#define SERVER "192.168.1.46"
#define PORT 8888

int main()
{
	struct sockaddr_in si_other;
	int s, slen = sizeof(si_other);
	char buf[1024];
	char message[1024];
	WSADATA wsa;

	std::cout << "\nInitializing winsock...\n";
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		std::cout << "Failed";
		
	}
	std::cout << "Initialized\n";
	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		std::cout << "Socket() failed\n";
		exit(EXIT_FAILURE);
	}
	memset((char*)&si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);
	si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);
	while (1)
	{
		std::cout << "\nEnter message: \n";
		std::cin >> message;
		if (sendto(s, message, strlen(message), 0, (struct sockaddr*) &si_other, slen) == SOCKET_ERROR)
		{
			std::cout << "sendto() failed";
			exit(EXIT_FAILURE);
		}
		memset(buf, '\0', 1024);
		if (recvfrom(s, buf, 1024, 0, (struct sockaddr*) &si_other, &slen) == SOCKET_ERROR)
		{
			std::cout << "recvfrom() faled";
			exit(EXIT_FAILURE);
		}
		std::cout << "Message: " << buf << '\n';
		system("PAUSE");
	}
	closesocket(s);
	WSACleanup();

}