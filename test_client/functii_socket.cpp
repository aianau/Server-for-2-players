#define _WIN32_WINNT 0x501

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <iostream>
using namespace std;

void initSockLibrary(){
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,2), &wsaData);
}

bool serverSocketBind(SOCKET &Server, const char* host, const char* port){
	Server = INVALID_SOCKET;

	addrinfo *ppResult = NULL, pHints;
	ZeroMemory(&pHints, sizeof(pHints));
	pHints.ai_family = AF_INET;
	pHints.ai_socktype = SOCK_STREAM;
	pHints.ai_protocol = IPPROTO_TCP;
	pHints.ai_flags = AI_PASSIVE;

	if(getaddrinfo(host, port, &pHints, &ppResult) != 0){
		cout<<"Eroare la convertirea datelor din ANSI in adresa! Host-ul sau port-ul selectat ar putea avea valori gresite!"<<endl;
		return false;
	}

	Server = socket(ppResult->ai_family, ppResult->ai_socktype, ppResult->ai_protocol);

	if(Server == INVALID_SOCKET){
		cout<<"Eroare la generarea socket-ului, verifica daca ai drepturile necesare!"<<endl;
		return false;
	}

	///nu stiu exact daca am apelat bine, intrucat documentatia de pe docs.windows.com e de:
	///U+1F4A9 U+1F4A9 U+1F4A9 U+1F4A9 U+1F4A9 U+1F4A9 U+1F4A9 U+1F4A9 U+1F4A9 U+1F4A9 U+1F4A9
	if(setsockopt(Server, SOL_SOCKET, SO_REUSEADDR, "TRUE", 4) != 0){
		cout<<"Eroare la setarea optiunii de reutilizare a adresei"<<endl;
		cout<<"Ar putea cauza probleme daca a mai fost folosit recent acelasi port!"<<endl;
	}

	if(bind(Server, ppResult->ai_addr, (int)ppResult->ai_addrlen) == SOCKET_ERROR){
		cout<<"Eroare la bind! Verifica daca ai drepturile necesare!"<<endl;
		return false;
	}
	return true;
}

bool serverSocketListen(SOCKET &Server, unsigned int max_backlog_connections = SOMAXCONN){
	if(listen(Server, max_backlog_connections) == SOCKET_ERROR){
		cout<<"Eroare la listen!"<<endl;
		return false;
	}
	return true;
}

bool acceptClient(SOCKET &Server, SOCKET &Client){
	Client = INVALID_SOCKET;
	Client = accept(Server, NULL, NULL);
	if(Client == INVALID_SOCKET){
		cout<<"Un computer nu a reusit sa se conecteze!"<<endl;
		return false;
	}
	return true;
}

bool clientSocketConnect(SOCKET &Client, const char* host, const char* port, bool try_everything = true){
	Client = INVALID_SOCKET;

	addrinfo *ppResult = NULL, pHints;
	ZeroMemory(&pHints, sizeof(pHints));
	pHints.ai_family = AF_UNSPEC;
	pHints.ai_socktype = SOCK_STREAM;
	pHints.ai_protocol = IPPROTO_TCP;

	if(getaddrinfo(host, port, &pHints, &ppResult) != 0){
		cout<<"Eroare la convertirea datelor din ANSI in adresa! Host-ul sau port-ul selectat ar putea avea valori gresite!"<<endl;
		return false;
	}
	do{
		Client = socket(ppResult->ai_family, ppResult->ai_socktype, ppResult->ai_protocol);
		if(Client == INVALID_SOCKET){
			cout<<"Eroare la generarea socket-ului!"<<endl;
		}

		if(connect(Client, ppResult->ai_addr, (int)ppResult->ai_addrlen) == SOCKET_ERROR){
			cout<<"Eroare la conectarea socket-ului!"<<endl;
			Client = INVALID_SOCKET;
		}
		ppResult = ppResult->ai_next;
	}while(try_everything && ppResult != NULL);
	if(Client != INVALID_SOCKET)
		return true;
	return false;
}
