#include <iostream>
#include <conio.h>
#include <string>
#include <windows.h>
#define UP 72
#define DOWN 80
#define select 13
using namespace std;
int server(){
    system("cls");
    system("g++ -o main  ..\\main.cpp -lws2_32");
    system("start ..\\main.exe");
}
int client(){
    system("cls");
    system("g++ -o client  ..\\client.cpp -lws2_32");
    system("start ..\\client.exe");
}
int about(){
    system("cls");
    cout<<"Thundernet is a simple console-based chat application that allows users to communicate over a local network. It consists of a server and a client component, both implemented in C++. The server listens for incoming connections, while the client connects to the server and facilitates message exchange between users. Thundernet is designed for educational purposes and demonstrates basic socket programming concepts in C++."<<endl;
    cout<<"Made by : MUHAMMAD TALHA ASIF"<<endl<<"University ID : SP26-BSE-064"<<endl;
    cout<<"\nPress any key to return to the main menu..."<<endl;
    _getch();
    return 0;
}
int main() {
    int pointer = 0;
    bool selected = false; 
    char in;
    string title = R"(
  _______ _                     _               _   _      _   
 |__   __| |                   | |             | \ | |    | |  
    | |  | |__  _   _ _ __   __| | ___ _ __    |  \| | ___| |_ 
    | |  | '_ \| | | | '_ \ / _` |/ _ \ '__|   | . ` |/ _ \ __|
    | |  | | | | |_| | | | | (_| |  __/ |      | |\  |  __/ |_ 
    |_|  |_| |_|\__,_|_| |_|\__,_|\___|_|      |_| \_|\___|\__|
                                                               
    )";
    start:
    while(1){
    system("cls");
    cout << title << std::endl;
    cout<<"\t Use arrow keys to navigate"<<endl;
		if (pointer == 0){
			cout<<"[ ";
		}
		cout << "- Server";
        if (pointer == 0){
		    cout << "]";
        }
		cout << "\n";
		if (pointer == 1){
			cout<<"[ ";
		}
		cout << "- Client";
        if (pointer == 1){
		    cout << "]";
        }
		cout << "\n";
		if (pointer == 2){
			cout<<"[ ";
		}
		cout << "- About";
        if (pointer == 2){
		    cout << "]";
        }
		cout << "\n";
		if (pointer == 3){
			cout<<"[ ";
		}
		cout << "- Exit";
        if (pointer == 3){
		    cout << "]";
        }
        in = _getch();
        if (in == UP){
            pointer--;
        }
		if (in == DOWN)
		{
			pointer++;
		}
		if (in == select)
		{
			selected = 1;
		}
		if (pointer == 4)
		{
			pointer = 0;
		}
		if (pointer == -1)
		{
			pointer = 3;
		}
		system("cls");
		if (selected)
		{
			if (pointer == 0)
			{
				goto o1;
			}
			else if (pointer == 1)
			{
				goto o2;
			}
			else if (pointer == 2)
			{
				goto o3;
			}
			else if (pointer == 3)
			{
				cout<<"Exiting..."<<endl;
                break;

			}
	}
	if (0)
	{
	o1:
		server();
		pointer = 0;
		selected = 0;
		goto start;

	o2:
		client();
		pointer = 0;
		selected = 0;
		goto start;

	o3:
		about();
		pointer = 0;
		selected = 0;
		goto start;
    }
}
    return 0;
}