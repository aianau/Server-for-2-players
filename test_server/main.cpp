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

	char inp1[512];
	char inp2[512];
	inp1[511] = '\0';
	inp2[511] = '\0';
	int result_send11, result_send12, result_recv1;
	int result_send21, result_send22, result_recv2;

	do{
		result_recv1 = recv(client1, inp1, 512, 0);
		result_recv2 = recv(client2, inp2, 512, 0);

		inp1[result_recv1] = '\0';
		inp2[result_recv2] = '\0';

		//trimit ce am primit fie de la client1 /client 2 catre amandoi
		//trimit catre client 1 ce am primit de la amandoi
		result_send11 = send(client1, inp1, (int)strlen(inp1), 0);
		result_send12 = send(client1, inp2, (int)strlen(inp2), 0);

		//trimit catre client 2 ce am primit de la amandoi
		result_send21 = send(client2, inp1, (int)strlen(inp1), 0);
		result_send22 = send(client2, inp2, (int)strlen(inp2), 0);

		cout<<"Client1:"<<inp1<<endl;
		cout<<"Client2:"<<inp2<<endl;
		cout<<"\n";
		inp1[511] = '\0';
		inp2[511] = '\0';


	}while(strcmp(inp1, strdup("exit")) != 0 &&
            strcmp(inp2, strdup("exit")) != 0 &&
            result_send11 > 0 && result_send12 > 0 && result_recv1 > 0 &&
            result_send21 > 0 && result_send22 > 0 && result_recv2 > 0);
	return 0;
}
