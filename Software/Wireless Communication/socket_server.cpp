//The Raspberry Pi will act as a server to send the collected data to the client.
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std; 
#define USEPORT 1234

int main()
{
//Create socket
	int serverSock = socket(AF_INET, SOCK_STREAM, 0); 
	if (serverSock < 0)
	{
		cout << "socket creation failed" << endl; 
		exit(-1); 
	}
	cout << "socket creation successfully" << endl; 
//Bind ip and port
	struct sockaddr_in serverAddr; 
	memset(&serverAddr, 0, sizeof(serverAddr)); 
	serverAddr.sin_family = AF_INET; 
	serverAddr.sin_port = htons(USEPORT); 
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); //INADDR_ANY used to bind any ip
//Bind socket
	if (bind(serverSock, 
		(struct sockaddr*)&serverAddr, 
		sizeof(struct sockaddr)) == -1)
	{
		cout << "Bind error, Port["<< USEPORT << "]" << endl; 
	       exit(-1); 
    }
	cout << "Bind successfully" << endl; 
	
//Listen
	if (listen(serverSock, 10) == -1)
	{
		cout << "Listen error!" << endl; 
	}
	cout << "Listening on port[" << USEPORT << "]" << endl; 

//Start accept()
	struct sockaddr clientAddr; 
	int size = sizeof(struct sockaddr); 

	int clientSock = accept(serverSock, (struct sockaddr*)&clientAddr, (socklen_t*)&size); 

	cout << "****NEW client touched****" << endl; 

//Communication
	while (1)
	{
		string input; 
		cout << "input something ('quit' to shutdown)" << endl; 
		cin >> input; 
		send(clientSock, input.c_str(), input.length(), 0); 
		if (input == "quit")
		{
			cout << "shutdown"<<endl;
			break; 
		}
	}
	
	close(serverSock); 
	return 0; 
} 
