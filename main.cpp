#include <iostream>
#include <winsock2.h>
#include <conio.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;
int server(){
	char in;
	string msg;
	char buffer[1024] = {0};
	WSADATA ws;
	cout<<"Initializing..."<<endl;
	if(WSAStartup(MAKEWORD(2,2), &ws) != 0){
		cout<<"Error : " <<WSAGetLastError();
		return 1;
	}
	SOCKET sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == INVALID_SOCKET){
		cout<<"Error : "<<WSAGetLastError();
		WSACleanup();
		return 1;
	}
	cout<<"reference ID : "<<sock<<endl;
	sockaddr_in ser;
	ser.sin_family = AF_INET;
	ser.sin_port = htons(5555);
	ser.sin_addr.s_addr = INADDR_ANY;
	cout<<"Server started!\n";
	bind(sock, (sockaddr*)&ser, sizeof(ser));
	if(listen(sock, 1) == SOCKET_ERROR){
		cout<<"Error : "<<WSAGetLastError();
		closesocket(sock);
		WSACleanup();
		return 1;
	}
	else {
    	cout << "Server is listening... waiting for a friend to connect!\n" << std::endl;
	}
	SOCKET acceptsock;
	acceptsock = accept(sock, NULL, NULL);
	if(acceptsock == INVALID_SOCKET){
		cout<<"Error : "<<WSAGetLastError();
		closesocket(sock);
		WSACleanup();
		return 1;
	}
	else {
		cout << "A friend has connected! Reference ID: " << acceptsock << std::endl;
	}
	cout<<"Messages "<<endl;
	/*
	while(1)
	{
		recv(acceptsock, buffer, sizeof(buffer), 0);
		cout<<"Client : "<<buffer<<endl;
		if(buffer == ""){
			cout<<"Client has disconnected!"<<endl;
			break;
		}
	}
	*/
	cout<<"Enter a message (ENTER 0 TO SEND A NEW MESSAGE): ";
    while(1)
    {
		 recv(acceptsock, buffer, sizeof(buffer), 0);
         cout<<"Server : "<<buffer<<endl;
         getline(cin, msg);
		 send(acceptsock, msg.c_str(), msg.length(), 0);
		 msg = "";
		 buffer[0] = '\0';
		 
    }
	WSACleanup();
	_getch();
	return 0;
}
int client(){
	WSADATA ws;
	cout<<"Searching..."<<endl;
	if(WSAStartup(MAKEWORD(2,2), &ws) != 0){
		cout<<"Error : " <<WSAGetLastError();
		return 1;
	}
	SOCKET sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == INVALID_SOCKET){
		cout<<"Error : "<<WSAGetLastError();
		WSACleanup();
		return 1;
	}
	cout<<"reference ID : "<<sock<<endl;
	cout<<"COnnecting..."<<endl;
	WSACleanup();
	_getch();
	return 0;
}
using namespace std;
int main(){
	server();
}
