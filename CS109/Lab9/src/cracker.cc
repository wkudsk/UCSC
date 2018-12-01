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
Message makeMessage(unsigned int num_passwds, unsigned int port)
{
    Message message;
    strcpy(message.cruzid, "wkudskthor");        // Who this datagram is for
    bzero(message.passwds, MAX_HASHES);
    message.num_passwds = htonl(num_passwds);// Number of plain text passwords or password  hases in PASSWDS
    strcpy(message.hostname, "thor"); 	 	 // Host to return decrypted passwords to over TCP
    message.port = htons(port);              // Port to return decrypted passwords to
    return message;
}
void crackAndStore(char passwd[HASH_LENGTH+1])
{
	char buffer[4];
	crack(passwd, buffer);
	//cout << buffer << endl;
	strcpy(passwd, buffer);
}

Message runThreads(Message message)
{
	//From Lab5/Lab6
	vector<thread> threads;
	//cout << "num_passwds: " << ntohl(message.num_passwds) << endl;
	for(unsigned int i = 0; i < ntohl(message.num_passwds); i++)
	{
		//cout << message.passwds[i] << endl;
		threads.push_back(thread(crackAndStore, message.passwds[i]));
		if(threads.size() == 24)
		{	
			while(threads.size() == 24)
            {
                for(unsigned int j = 0; j < threads.size(); j++)
                {
                    if(threads[j].joinable())
                    {
                        threads[j].join();
                        threads.erase(threads.begin() + j);
                    }
                }
            }
            
    	}
	}
	for(auto& th : threads) th.join();
	threads.clear();
	//cout << "cracked message" << endl;
	return message;
}

Message read(unsigned int flag)
{
	//cout << "reading" << endl;
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) 
		cout << "open" << endl;
	
	struct sockaddr_in server_addr;
	bzero((char *) &server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(get_multicast_port());
	if (bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
		cout << "bind" << endl;
	
	struct ip_mreq multicastRequest;
	multicastRequest.imr_multiaddr.s_addr = get_multicast_address(); 
	multicastRequest.imr_interface.s_addr = htonl(INADDR_ANY);
	if (setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *) &multicastRequest, sizeof(multicastRequest)) < 0)
		cout << "setsockopt ";

	if(flag == 1)
	{
		struct timeval tv;
		tv.tv_sec = 0;
		tv.tv_usec = 600000;
		if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv)) < 0)
		{
			cout << "error" << endl;
		}
	}
	
	Message message;
	strcpy(message.cruzid, "nope");
	int n = recvfrom(sockfd, (void*)&message, sizeof(Message), 0, NULL, 0);
  	if(n < 0)
 	{
 		//cout << "read" << endl;
 	}
 	cout << message.cruzid << endl;
 	//else cout << "got something" << endl;		
	//cout << message.cruzid << endl;
	close(sockfd);
	return message;
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
	//cout << "sending message: " << message.cruzid << endl;
	/*for(unsigned int i = 0; i < ntohl(message.num_passwds); i++)
	{
		cout << message.passwds[i] << endl;
	}*/
	int n = sendto(sockfd,(void*)&message, sizeof(Message), 0, (struct sockaddr *) &multicastAddr, sizeof(multicastAddr));
	if (n < 0)
		cout << "write" << endl;    			
	close(sockfd);
}

void write(Message message)
{
	//https://classes.soe.ucsc.edu/cmps109/Spring18/SECURE/12.Distributed2.pdf
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) throw "open";
    
    struct hostent *server = gethostbyname(message.hostname);
	if (server == NULL)
    {
        cout << "Exiting because it cant find server" << endl;
        exit(-1);      
    }

    struct sockaddr_in serv_addr;
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = (message.port);

    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
    {
        cout << "Exiting because it cant connect" << endl;
        exit(-1);
    }
    send(sockfd, (void*)&message, sizeof(message), 0);
    
	close(sockfd);
}

int main(int argc, char *argv[])
{
	char master[7] = "thor";
	if(strcmp(argv[1], master) == 0)
	{
		Message message;
		char cruzid[7] = "wkudsk"; 	
		while(1)
		{
			message = read(0);
			if(strcmp(message.cruzid, cruzid) == 0)
			{
				//cout << "right message" << endl;
				break;
			}
			//else cout << "wrong message" << endl;
		}
		
		unsigned int n = ntohl(message.num_passwds)/4;
		//cout << n << endl;
		unsigned int port = get_unicast_port();
		
		Message messageThor = makeMessage(n, port);
		Message messageOlaf = makeMessage(n, port);
		Message messageGraculus = makeMessage(n, port);
		Message messageGrolliffe = makeMessage(n, port);
		strcpy(messageOlaf.cruzid, "wkudskolaf");
		strcpy(messageGraculus.cruzid, "wkudskgraculus");  
		strcpy(messageGrolliffe.cruzid, "wkudskgrolliffe");  
		unsigned int numLast = 0;
		for(unsigned int i = 0; i < ntohl(message.num_passwds); i++)
		{
			sleep(.1);
			if(i >= 0 && i < n)
			{
				strcpy(messageThor.passwds[i], message.passwds[i]);
				//cout << messageThor.passwds[i%n] << " " << message.passwds[i] << endl;
			}
			else if(i >= n && i < n*2)
			{
				strcpy(messageOlaf.passwds[i%n], message.passwds[i]);
				//cout << messageOlaf.passwds[i%n] << " " << message.passwds[i] << endl;
				if(i == (n*2) - 1)
				{
					send(messageOlaf);
					send(messageOlaf);
					send(messageOlaf);
					send(messageOlaf);
					send(messageOlaf);
					send(messageOlaf);
					send(messageOlaf);
					send(messageOlaf);
					send(messageOlaf);
					send(messageOlaf);
					sleep(.1);
				}
			}
			else if(i >= n*2 && i < n*3)
			{
				strcpy(messageGraculus.passwds[i%n], message.passwds[i]);
				//cout << i%n << ": " << messageGraculus.passwds[i%n] << " " << message.passwds[i] << endl;
				if(i == (n*3) - 1 )
				{
					send(messageGraculus);	
					send(messageGraculus);	
					send(messageGraculus);
					send(messageGraculus);
					send(messageGraculus);
					send(messageGraculus);
					send(messageGraculus);
					send(messageGraculus);	
					send(messageGraculus);
					send(messageGraculus);	
					sleep(.1);
				}
			}
			else if(i >= n*3 && i < ntohl(message.num_passwds))
			{
				strcpy(messageGrolliffe.passwds[numLast], message.passwds[i]);
				numLast++;
				//cout << messageGrolliffe.passwds[i%n] << " " << message.passwds[i] << endl;
			}
		}
		messageGrolliffe.num_passwds = htonl(numLast);
		send(messageGrolliffe);
		send(messageGrolliffe);
		send(messageGrolliffe);
		send(messageGrolliffe);
		send(messageGrolliffe);
		send(messageGrolliffe);
		send(messageGrolliffe);
		send(messageGrolliffe);
		send(messageGrolliffe);
		send(messageGrolliffe);
				


		messageThor = runThreads(messageThor);

		bool foundOlaf, foundGraculus, foundGrolliffe = false;
		while(!foundOlaf || !foundGraculus || !foundGrolliffe)
		{
			Message tempMessage = read(1);
			if(strcmp(tempMessage.cruzid, "wkudskolaf") == 0 && !foundOlaf)
			{
				messageOlaf = tempMessage;
				foundOlaf = true;
				send(messageOlaf);
				send(messageOlaf);
				send(messageOlaf);
				
				//cout << "found olaf" << endl;
				/*for(unsigned int i = 0; i < n; i++)
				{
					cout << messageOlaf.passwds[i] << endl;
				}*/
			}
			else if(strcmp(tempMessage.cruzid, "wkudskgraculus") == 0 && !foundGraculus)
			{
				messageGraculus = tempMessage;
				foundGraculus = true;
				send(messageGraculus);
				send(messageGraculus);
				send(messageGraculus);
				
				//cout << "found graculus" << endl;
				/*for(unsigned int i = 0; i < n; i++)
				{
					cout << messageGraculus.passwds[i] << endl;
				}*/
			}
			else if(strcmp(tempMessage.cruzid, "wkudskgrolliffe") == 0 && !foundGrolliffe)
			{ 
				messageGrolliffe = tempMessage;
				foundGrolliffe = true;
				send(messageGrolliffe);
				send(messageGrolliffe);
				send(messageGrolliffe);
				
				//cout << "found grolliffe" << endl;
				/*for(unsigned int i = 0; i < n; i++)
				{
					cout << messageGrolliffe.passwds[i] << endl;
				}*/
			}
		}
		unsigned int throuLast = 0;
		for(unsigned int i = 0; i < ntohl(message.num_passwds); i++)
		{
			if(i >= 0 && i < n)
			{
				strcpy(message.passwds[i], messageThor.passwds[i%n]);
				cout << i%n << ": "<< messageThor.passwds[i] << " " << i << ": " << message.passwds[i] << endl;
			}
			else if(i >= n && i < n*2)
			{
				strcpy(message.passwds[i], messageOlaf.passwds[i%n]);
				cout << i%n << ": "<< messageOlaf.passwds[i%n] << " " << i << ": " << message.passwds[i] << endl;
			}
			else if(i >= n*2 && i < n*3)
			{
				strcpy(message.passwds[i], messageGraculus.passwds[i%n]);
				cout << i%n << ": "<< messageGraculus.passwds[i%n] << " " << i << ": " << message.passwds[i] << endl;
			}
			else if(i >= n*3 && i < ntohl(message.num_passwds))
			{
				strcpy(message.passwds[i], messageGrolliffe.passwds[throuLast]);
				cout << i%numLast << ": "<< messageGrolliffe.passwds[throuLast] << " " << i << ": " << message.passwds[i] << endl;
				throuLast++;
			}
		}
		write(message);
	}
	else
	{
		Message message;
		bool youreDone = false;
		while(!youreDone)
		{
			message = read(0);
			if(strcmp(message.cruzid, argv[1]) == 0)
			{
				//cout << "right message" << endl;
				message = runThreads(message);
				Message stopMessage;
				while(!youreDone)
				{
					send(message);
					stopMessage = read(1);
					if(strcmp(stopMessage.cruzid, message.cruzid) == 0)
					{
						//cout << "recieved termination" << endl;
						youreDone = true;
					}
				}
				break;
			}
		}
	}	
	return 0;
}