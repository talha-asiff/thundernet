#include <iostream>
#include <string>
#include <winsock2.h>
#include <conio.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;
int main(){
    string msg;
    char in;
    char buffer[1024] = {0};
    WSADATA ws;
	cout<<"Searching server..."<<endl;
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
    ser.sin_addr.s_addr = inet_addr("127.0.0.1");
	cout<<"Connecting..."<<endl;
    if(connect(sock, (sockaddr*)&ser, sizeof(ser)) == SOCKET_ERROR){
        cout<<"Error : "<<WSAGetLastError();
        closesocket(sock);
        WSACleanup();
        return 1;
    }
    else {
        cout << "Connected to the server! Reference ID: " << sock << std::endl;
    }

    cout<<"Enter a message (ENTER 0 TO SEND A NEW MESSAGE): \n";
    while(1)
    {
        cout<<"You : ";
        getline(cin, msg);
        send(sock, msg.c_str(), msg.length(), 0);
        msg = "";
        recv(sock, buffer, sizeof(buffer), 0);
        cout<<"Server : "<<buffer<<endl;
        buffer[0] = '\0';
    }

    
    closesocket(sock);
    WSACleanup();
    _getch();
    return 0;
}