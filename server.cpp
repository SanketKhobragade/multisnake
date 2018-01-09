#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>

using namespace std;
int client, server;
int portNum = 3000;
bool isExit = false;
char buffer1[2];
char buffer2[60*80];

int con()
{
    struct sockaddr_in server_addr;
    socklen_t size;

    client = socket(AF_INET, SOCK_STREAM, 0);

    if (client < 0) 
    {
        cout << "\nError establishing socket..." << endl;
        exit(1);
    }

    cout << "\n=> Socket server has been created..." << endl;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(portNum);


    if ((bind(client, (struct sockaddr*)&server_addr,sizeof(server_addr))) < 0) 
    {
        cout << "=> Error binding connection, the socket has already been established..." << endl;
        return -1;
    }

    size = sizeof(server_addr);
    cout << "=> Looking for clients..." << endl;

    /* ------------- LISTENING CALL ------------- */
    /* ---------------- listen() ---------------- */

    listen(client, 1);

    int clientCount = 1;
    server = accept(client,(struct sockaddr *)&server_addr,&size);

    if (server < 0) 
        cout << "=> Error on accepting..." << endl;

    if(server > 0) 
    {
        strcpy(buffer2, "=> Server connected...\n");
        send(server, buffer2,60*80 , 0);
        cout << "=> Connected with the client #" << clientCount << ", you are good to go..." << endl;
        cout << "\n=> Enter # to end the connection\n" << endl;
    }
    return 0;
}

void send_sig(int change[1000], int change_ct){
	int32_t temp;
	char *data;
	int left;
	for(int i = 0; i<change_ct; i++){
		temp = htonl(change[i]);
		data = (char*)&temp;
		left = sizeof(temp);
		int rc;
		do{
        		rc = write(server, data, left);
        		if (rc < 0) {
            			if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
				// use select() or epoll() to wait for the socket to be writable again
				}
				else if (errno != EINTR) {
					return ;
				}
			}
			else {
			    data += rc;
			    left -= rc;
			}
		}
		while (left > 0);
	}		
}
void send_ct(int ct){
	cout << "E3" << endl;
	char *tem = new char[5];
	tem[0] = (char)(ct/10 + 48);
	tem[1] = (char)(ct % 10 + 48);
	cout << tem << endl;
	send(server, tem, 5, 0);
	delete(tem);
}
void recieve_sig(int *input){
	//int * input =
	cout << "E4" << endl;
	char *b = new char[5];
	recv(server, b, 5, 0);
	cout << (int)(b[0] - 48) << endl;
	input[0] = (int)( b[0] - 48);
	input[1] = (int)( b[1] - 48);
	delete(b);
}
