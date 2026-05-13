#include <iostream>
#include <string>
#include <winsock2.h>
#include <conio.h>
#include <fstream>
#include <windows.h>
#include <ctime>
#pragma comment(lib, "ws2_32.lib")
using namespace std;
int main(){
    time_t now = time(0);
    time(&now);
    string start = "";
    string stop = "";
    ofstream logFile("export/client_log.html");
	logFile << "<!DOCTYPE html><html><head><title>Client Chat Log</title><link rel=\"stylesheet\" href=\"style.css\"></head>" << endl;
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
        start = ctime(&now);
        logFile << "<h1 style = \"background-color: blue; color:white;\">Chat started at: " << start << "</h1><br>" << endl;
    }
    system("cls");
    cout<<"Enter a message (TYPE \"exit\" to quit): \n";
    while(1)
    {
        cout<<"You : ";
        getline(cin, msg);
        send(sock, msg.c_str(), msg.length(), 0);
        if(msg == "exit"){
            cout<<"Exiting..."<<endl;
            Sleep(2000);
            time(&now);
            stop = ctime(&now);
            logFile << "<h1 style = \"background-color: blue; color:white;\">Chat ended at: " << stop << "</h1><br>" << endl; 
            break;
        }
        logFile << "<h2 class = \"client\"><strong>client:</strong> " << msg << "</h2>" << endl;
        memset(buffer, 0, sizeof(buffer));
        recv(sock, buffer, sizeof(buffer), 0);
        logFile << "<h2 class = \"server\"><strong>server:</strong> " << buffer << "</h2>" << endl;
        cout<<"Server : "<<buffer<<endl;
        
    }

    logFile.close();
    closesocket(sock);
    WSACleanup();
    system("cls");
    cout<<"Disconnected from server."<<endl;
    cout<<"Chat log saved to export/client_log.html"<<endl;
    cout<<"connection started at : "<<start<<endl;
    cout<<"connection ended at : "<<stop<<endl;
    cout<<"Press any key to exit..."<<endl;
    _getch();
    return 0;
}
