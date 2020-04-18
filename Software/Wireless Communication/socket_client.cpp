//Computer PC will be used as a client to receive and display data sent by the server
#include <iostream>
#include <string>
#include <WinSock2.h> 
using namespace std;
#pragma comment(lib, "ws2_32.lib") 
#pragma warning(disable:4996)

int main()
{
//Initialization
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);		
	
//Creat Socket
	SOCKET sock = socket(PF_INET, SOCK_STREAM, 0);

//Creat sockAddr Structure
	sockaddr_in sockAddr;						
	memset(&sockAddr, 0, sizeof(sockAddr));	
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_port = htons(1234);
	sockAddr.sin_addr.s_addr = inet_addr(RASPI_IP); //RASPI_IP is the IP of raspberry pi

//Build connection
	connect(sock, (SOCKADDR*)& sockAddr, sizeof(SOCKADDR));		
	cout << "Client sends a link request" << endl;

//Receive data from the server
	while (1)
	{
		cout << "Wait for the server to send information.." << endl;
		
		char tack[MAXBYTE] = { 0 };
		recv(sock, tack, MAXBYTE, NULL); 
		
		//Output received data
		cout << "Server: " << tack << endl;
		
		if (strcmp(tack, "quit") == 0)
		{
			cout << "shutdown" << endl; 
			break;
		}
	}

	//Close socket and terminate DLL
	closesocket(sock);
	WSACleanup();

	return 0;
}
