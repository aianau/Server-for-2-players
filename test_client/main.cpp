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
	int result_send, result_recv1, result_recv2;
    char inp[512];
    char recv1[512], recv2[512];
	do{
		cin>>inp;

		result_send = send(client, inp, (int)strlen(inp), 0);

		result_recv1 = recv(client, recv1, 511, 0);
		result_recv2 = recv(client, recv2, 511, 0);

		recv1[result_recv1] = '\0';
		recv2[result_recv2] = '\0';

		cout<<"Recv1: "<<recv1<<endl;
		cout<<"Recv2: "<<recv2<<endl;
		cout<<"\n";

	}while(strcmp(inp, strdup("exit")) != 0 &&
            strcmp(recv1, strdup("exit")) != 0 &&
            strcmp(recv2, strdup("exit")) != 0 &&
            result_send > 0 &&
            result_recv1 > 0 && result_recv2 > 0);
	return 0;
}
