#include <iostream>
#include <winsock2.h>
#include <conio.h>
#include <string>
#include <windows.h>
#include <fstream>
#include <ctime>
#pragma comment(lib, "ws2_32.lib") //Required for GCC compiler to link the Winsock library
using namespace std;
class networkInfo {
	public:
		string platform;
		int port;
		string stime;
		string etime;
		void txtlog(string platform, int port, string stime, string etime);
		networkInfo(string live, int p, string s, string e){
			this->platform = live;
			this->port = p;
			this->stime = s;
			this->etime = e;
	}
};
void networkInfo :: txtlog(string platform, int port, string stime, string etime){
	ofstream logFile("export/network_log.txt", ios::app);
	logFile << "Network logs are only stored on server side (administrator) \nPlatform: " << platform << "\nPort: " << port << "\nStart Time: " << stime << "\nEnd Time: " << etime << "\n-------------------------\n";
	logFile.close();
}
struct connectionInfo {
	SOCKET connectid;
	SOCKET acceptid;
	string ipAddress;
	int port;
};
string serverStart(){
	time_t now = time(0);
	time(&now);
	string start = ctime(&now);
	return start;
}
string serverStop(){
	time_t now = time(0);
	time(&now);
	string stop = ctime(&now);
	return stop;
}
bool clientexit(char *buffer){
	if(strcmp(buffer, "exit") == 0){
		return true;
	}
	else {
		return false;
	}
}

int main(){
	string start = "";
	string stop = "";
	char exitin;
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
	start = serverStart();
	logFile << "<h1 style = \"background-color: blue; color:white;\">Chat started at: " << start << "</h1><br>" << endl;
	Sleep(3000);
	system("cls");
	cout<<"Enter a message (SEND \"exit\" to quit):\n ";
    while(1)
    {
		 memset(buffer, 0, sizeof(buffer));
		recv(acceptsock, buffer, sizeof(buffer), 0);
		 logFile << "<h2 class = \"client\"><strong>Client:</strong> " << buffer << "</h2>" <<endl;
         cout<<"Client : "<<buffer<<endl;
		 if(clientexit(buffer)){
			cout<<"NOTICE : Client has disconnected."<<endl;
		 }
		 cout<<"You : ";
         getline(cin, msg);
		 send(acceptsock, msg.c_str(), msg.length(), 0);
		 if(msg == "exit"){
			cout<<"Exiting..."<<endl;
			stop = serverStop();
			logFile << "<h1 style = \"background-color: blue; color:white;\">Chat ended at: " << stop << "</h1><br>" << endl;	
			break;
		 }
		 logFile << "<h2 class = \"server\"><strong>Server:</strong> " << msg << "</h2>" << endl;
    }
	logFile.close();
	WSACleanup();
	system("cls");
	cout<<"Disconnected from client."<<endl;
	cout<<"Chat log saved to export/server_log.html"<<endl;
	cout<<"connection started at : "<<start<<endl;
	cout<<"connection ended at : "<<stop<<endl;
	cout<<"Press 0 to get connection info, Press any key to exit..."<<endl;
	exitin = _getch();
	if(exitin == '0'){
		connectionInfo info;
		info.connectid = sock;
		info.acceptid = acceptsock;
		info.ipAddress = "127.0.0.1";
		info.port = ntohs(ser.sin_port);
		cout<<"Connection Info:\n";
		cout<<"MOde : TCP\n Computer Type : Server\n Data mode : Stream\n";
		cout<<"Listening socket Reference ID: "<<info.connectid<<endl;
		cout<<"Accepting socket Reference ID: "<<info.acceptid<<endl;
		cout<<"Live at: "<<info.ipAddress<<endl;
		cout<<"Port: "<<info.port<<endl;
		cout<<"Press any key to exit..."<<endl;
		_getch();
		networkInfo netinfo(info.ipAddress, info.port, start, stop);
		netinfo.txtlog(netinfo.platform, netinfo.port, netinfo.stime, netinfo.etime);
	}
	return 0;
}
