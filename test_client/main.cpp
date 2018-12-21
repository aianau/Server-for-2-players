#define _WIN32_WINNT 0x501
#define PORT "1338"
#define HOST "192.168.0.1"

#include "functii_socket.cpp"
#include <cstring>

///CLIENT


int main(){
	initSockLibrary();
	SOCKET client;

	clientSocketConnect(client, HOST, PORT);
	int result_send, result_recv;
    char inp[512];
	do{
		cin>>inp;
		result_send = send(client, inp, (int)strlen(inp), 0);
		result_recv = recv(client, inp, 511, 0);
		inp[result_recv] = '\0';
		cout<<"Server: "<<inp<<endl;
	}while(strcmp(inp, strdup("exit")) != 0 &&
            result_send > 0 && result_recv > 0);
	return 0;
}
