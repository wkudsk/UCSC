#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <thread>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <crypt.h>
#include "crack.h"

using namespace std;
Message makeMessage(char* passwd, unsigned int num_passwds, unsigned int port)
{
    Message message;
    strcpy(message.cruzid, "wkudsk");        // Who this datagram is for
    for(int i = 0; i < MAX_HASHES; i++)
    {
    	strcpy(message.passwds[i], passwd);  // NUM_PASSWD plain text passwords or password hashess
    }
    message.num_passwds = htonl(num_passwds);// Number of plain text passwords or password  hases in PASSWDS
    strcpy(message.hostname, "thor"); 	 	 // Host to return decrypted passwords to over TCP
    message.port = htons(port);              // Port to return decrypted passwords to
    return message;
}

void read(unsigned int port)
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
    { 
        cout << "Exit because of connection error" << endl;
        exit(-1);
    }
	struct sockaddr_in server_addr;
	bzero((char *) &server_addr, sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(port);

	if (bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
	{
        cout << "Exit because of bind error" << endl;
        exit(-1);
    }
	listen(sockfd,1);
    
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);

    int newsockfd = accept(sockfd, (struct sockaddr *) &client_addr, &len);
    if (newsockfd < 0)
    {
        cout << "Exit because cant connect to client?" << endl;
        exit(-1);
    }
    struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 600000;
	if (setsockopt(newsockfd, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv)) < 0)
	{
		cout << "error" << endl;
	}

    Message message;
    unsigned int p = recv(newsockfd, (void*)&message, sizeof(message), 0);
    if(p < 0)
    {
        cout << "couldnt recieve value" << endl;
        exit(-1);
    }
    else
    {
    	for(unsigned int i = 0; i < ntohl(message.num_passwds); i++)
    		cout << "recieved message: " << message.passwds[i] << endl;
    }
    close(newsockfd);
    close(sockfd);
}

void send(Message message)
{
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0)
		cout << "open" << endl;
	int ttl = 1;
	if (setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_TTL, (void *) &ttl, sizeof(ttl)) < 0)
		cout << "setsockopt" << endl;
	struct sockaddr_in multicastAddr;
	memset(&multicastAddr, 0, sizeof(multicastAddr));
	multicastAddr.sin_family = AF_INET;
	multicastAddr.sin_addr.s_addr = get_multicast_address();
	multicastAddr.sin_port = htons(get_multicast_port());
	
	//for (;;)
	//{
		printf("Sending: %s\n", message.cruzid);
		int n = sendto(sockfd,(void*)&message, sizeof(Message), 0, (struct sockaddr *) &multicastAddr, sizeof(multicastAddr));
		if (n < 0)
			cout << "write" << endl;    			
	//}
	close(sockfd);
}

int main(int argc, char *argv[])
{
	char string[HASH_LENGTH+1];
	strcpy(string, "00Pp9Oy0VWmn2");
	unsigned int port = get_unicast_port();
	Message message = makeMessage(string, 60, port);	
	send(message);
	//while(1)
	//{
	read(port);
	//}
	return 0;
}

/*int workingCode()
{
	Message message;
	char cruzid[7] = "wkudsk"; 	
	while(1)
	{
		message = read(0);
		if(strcmp(message.cruzid, cruzid) == 0)
		{
			cout << "right message" << endl;
			message = runThreads(message);
			write(message);
			break;
		}
	}
}*/