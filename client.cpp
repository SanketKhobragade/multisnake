#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

using namespace std;
int client;
int portNum; // NOTE that the port number is same for both client and server
bool isExit = false;
int bufsize = 2;
char buffer1[2];
char buffer2[60*80];
struct sockaddr_in server_addr;
char *ip;
int32_t *change;
void con(char *c, int p){
	ip = c;
	portNum = p;
	cout << ip << " " << portNum << endl;
	client = socket(AF_INET, SOCK_STREAM, 0);

    	if (client < 0) 
	{
        	cout << "\nError establishing socket..." << endl;
        	exit(1);
    	}

    	cout << "\n=> Socket client has been created..." << endl;
  
 	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(portNum);
    	//server_addr.sin_addr.s_addr=inet_addr(ip);

    	if (connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr)) == 0)
   	     cout << "=> Connection to the server port number: " << portNum << endl;

   	 cout << "=> Awaiting confirmation from the server..." << endl; //line 40
   	 recv(client, buffer2, bufsize, 0);
   	 cout << "=> Connection confirmed, you are good to go...";

   	 cout << "\n\n=> Enter # to end the connection\n" << endl;

   	 // Once it reaches here, the client can send a message first.
}

void send_sig(int dir, int speed_up){
	cout << "E2" << endl;
	char *b = new char[5];
	b[0] = (char)(dir + 48);
	b[1] = (char)(speed_up + 48);
	//cout << b[0] << endl;
	send(client, b, 5, 0);
	delete(b);
	/*buffer1[0] = 48 + dir;
	buffer1[1] = 48 + speed_up;
	cout << buffer1[0] << endl;
	send(client,buffer1,2,0);*/
}
int recieve_ct(){
	//int * input =
	cout << "E1" << endl;
	char *b = new char[5];
	int len = 0;
	recv(client, b, 5, 0);
	//cout << b << endl;//" " << len << endl;
	//cout << (int)( b[0] - 49) << " " << (int)( b[1] - 49) <<  endl;//" " << (int)( b[2] - 48) << endl;
	int ch = (int)( b[0] - 48) * 10 + (int)( b[1] - 48);
	delete(b);
	cout << ch << endl;
	/*if(change < 3 || change > 10)
		return recieve_ct();
	else
		return change;*/
	//return 1;
}
void recieve_sig(int ct){
	change = new int32_t[ct];
	for(int i=0; i<ct; i++){
		int32_t ret;
	    	char *data = (char*)&ret;
	    	int left = sizeof(ret);
	    	int rc;
	    	do {
			rc = read(client, data, left);
	       		if (ret <= 0) {
		    		if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
		        // use select() or epoll() to wait for the socket to be readable again
		    		}
		    		else if (errno != EINTR) {
		        		return;
		    		}
			}
			else {
		    		data += rc;
		    		left -= rc;
	       		}
	    	}
	    	while (left > 0);
	    	change[i] = ntohl(ret);
    	}
}
