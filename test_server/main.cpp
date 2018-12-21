#define _WIN32_WINNT 0x501
#define PORT "1338"

#include "functii_socket.cpp"
#include <cstring>

///SERVER


int main(){
	initSockLibrary();
	SOCKET serverSocket, client1, client2;

	serverSocketBind(serverSocket, INADDR_ANY, PORT);

	serverSocketListen(serverSocket, 2);
	cout<<"Listening activated"<<endl;

	acceptClient(serverSocket, client1);
	cout<<"Client1 accepted!"<<endl;

	acceptClient(serverSocket, client2);
	cout<<"Client2 accepted!"<<endl;

	char inp[512];
	inp[511] = '\0';
	int result_send1, result_recv1;
	int result_send2, result_recv2;
	int clientNo=0;
	do{
		result_recv1 = recv(client1, inp, 512, 0);
		inp[result_recv1] = '\0';
		result_send1 = send(client1, inp, (int)strlen(inp), 0);
		cout<<"Client "<<clientNo%2<<" :"<<inp<<endl;
		inp[511] = '\0';
	}while(strcmp(inp, strdup("exit")) != 0 &&
            result_send1 > 0 && result_recv1 > 0);
	return 0;
}
