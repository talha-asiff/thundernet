#include <iostream>
#include <winsock2.h>
#include <conio.h>
#include <string>
#include <windows.h>
#include <fstream>
#pragma comment(lib, "ws2_32.lib")
using namespace std;
int server(){
	system("cls");
	ofstream logFile("export/server_log.html");
	logFile << "<!DOCTYPE html><html><head><title>Server Chat Log</title><link rel=\"stylesheet\" href=\"style.css\"></head>" << endl;
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
		cout << "A friend has connected! Reference ID: " << acceptsock <<endl;
	}
	cout<<"Messages "<<endl;
	cout<<"Enter a message (SEND \"exit\" to quit):\n ";
    while(1)
    {
		 memset(buffer, 0, sizeof(buffer));
		recv(acceptsock, buffer, sizeof(buffer), 0);
		 logFile << "<h2 class = \"client\"><strong>Client:</strong> " << buffer << "</h2>" <<endl;
         cout<<"Client : "<<buffer<<endl;
		 cout<<"You : ";
         getline(cin, msg);
		 send(acceptsock, msg.c_str(), msg.length(), 0);
		 if(msg == "exit"){
			cout<<"Exiting..."<<endl;
			break;
		 }
		 logFile << "<h2 class = \"server\"><strong>Server:</strong> " << msg << "</h2>" << endl;
    }
	logFile.close();
	WSACleanup();
	_getch();
	return 0;
}

int main(){
	server();
}
