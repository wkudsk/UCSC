/*
 * Copyright (C) 2018 David C. Harrison. All right reserved.
 *
 * You may not use, distribute, publish, or modify this code without 
 * the express written permission of the copyright holder.
 */
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
#include <netdb.h>
#include "radix.h"


using namespace std;
//http://www.cplusplus.com/reference/algorithm/sort/
bool compareTo(unsigned int i, unsigned int j)
{
	
	string i_toString = to_string(i);
	string j_toString = to_string(j);
	//http://www.cplusplus.com/reference/string/string/compare/
	return (i_toString.compare(j_toString) <= 0); 
}

void sortList(std::vector<unsigned int>* list)
{
	//http://www.cplusplus.com/reference/algorithm/sort/
	sort(list->begin(), list->end(), compareTo);
}

Message makeMessage(unsigned int size, unsigned int sequence, unsigned int flag)
{
    Message message;
    message.num_values = size;
    message.sequence = sequence;
    message.flag = flag;
    return message;
}

/*
 * Start a UDP listener on PORT and accept lists of unsiged integers from
 * clients to be MSD RAdix sorted using no more that CORES cpu cores. After
 * sorting the lists are to be retiurned to the client.
 */
void RadixServer::start(const int port, const unsigned int cores) {
    //https://classes.soe.ucsc.edu/cmps109/Spring18/SECURE/15.Distributed5.pdf
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) exit(-1);

	struct sockaddr_in server_addr;
	bzero((char *) &server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(port);

	if (bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
	exit(-1);
	
	struct sockaddr_in remote_addr;
	socklen_t len = sizeof(remote_addr);

	while(1)
	{
		vector<Message> sentMessages;
    	vector<Message> recvMessages;
    	
    	bool foundLast = false;
    	while(!foundLast)
    	{
    		Message message;
            
            //https://stackoverflow.com/questions/13547721/udp-socket-set-timeout
            struct timeval tv;
			tv.tv_sec = 0;
			tv.tv_usec = 600000;
			if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv)) < 0) {
    			cout << "error" << endl;
			}
            else
            {
            	int n = recvfrom(sockfd, (void*)&message, sizeof(Message), 0,(struct sockaddr *)&remote_addr, &len);
            	if(n < 0)
     			{
     				unsigned int lastSeq = ntohl(recvMessages[recvMessages.size() - 1].sequence);
	    			Message resend = makeMessage(htonl(1), htonl(0), htonl(RESEND));
					resend.values[0] = htonl(lastSeq);
					int n = sendto(sockfd, (void*)&resend, sizeof(Message), 0, (struct sockaddr *)&remote_addr,len);
	    			if(n < 0)
						cout << "Failed Send!" << endl;
	    			n = recvfrom(sockfd, (void*)&resend, sizeof(Message), 0,(struct sockaddr *)&remote_addr, &len);
	        		if(n < 0)
	        			cout << "Failed recieving" << endl;
	        		recvMessages.push_back(resend);
	        		n = recvfrom(sockfd, (void*)&resend, sizeof(Message), 0,(struct sockaddr *)&remote_addr, &len);
	        		if(n < 0)
	        			cout << "Failed recieving" << endl;
	        		foundLast = true;
     			}       	
	            //cout << "recieved! sequence: " << ntohl(message.sequence) << endl;
	  			recvMessages.push_back(message);
	  			if(ntohl(message.flag) == LAST)
            	{
            		foundLast = true;
            	}
            }

    	}

    	while(ntohl(recvMessages[recvMessages.size() - 1].sequence) > recvMessages.size() - 1)
    	{
    		for(unsigned int i = 0; i < recvMessages.size(); i++)
    		{
    			if(i != ntohl(recvMessages[i].sequence))
    			{
    				Message resend = makeMessage(htonl(1), htonl(0), htonl(RESEND));
    				resend.values[0] = htonl(i);
    				int n = sendto(sockfd, (void*)&resend, sizeof(Message), 0, (struct sockaddr *)&remote_addr,len);
	    			if(n < 0)
	    				cout << "Failed Send!" << endl;
	    			n = recvfrom(sockfd, (void*)&resend, sizeof(Message), 0,(struct sockaddr *)&remote_addr, &len);
            		if(n < 0)
            			cout << "Failed recieving" << endl;
            		recvMessages.insert(recvMessages.begin() + i, resend);
            		n = recvfrom(sockfd, (void*)&resend, sizeof(Message), 0,(struct sockaddr *)&remote_addr, &len);
            		if(n < 0)
            			cout << "Failed recieving" << endl;
            		
    			}
    		}
    	}

    	vector<unsigned int> list;
    	for(Message message : recvMessages)
    	{
    		for(unsigned int i = 0; i < ntohl(message.num_values); i++)
	        {
	            unsigned int onwire = message.values[i];
	            unsigned int local = ntohl(onwire);
	            //cout << "recieved: " << local << endl;
	            list.push_back(local);
	        }
    	}

    	sortList(&list);
    	
    	Message message = makeMessage(0, 0, NONE);
 		for(unsigned int i = 0; i < list.size(); i++)
    	{	
    		//cout << "Value: " << list[i] << endl;
            unsigned int onwire = htonl(list[i]);
            message.values[message.num_values] = onwire; 
            message.num_values++;
    		if(message.num_values == MAX_VALUES)
    		{
    			message.sequence = htonl(message.sequence);
    			message.flag = htonl(message.flag);
    			message.num_values = htonl(message.num_values);
    			//cout << "Sending Message: " << message.sequence << endl;
    			sentMessages.push_back(message);
    			int n = sendto(sockfd, (void*)&message, sizeof(Message), 0, (struct sockaddr *)&remote_addr,len);
    			if(n < 0)
    				cout << "Failed Send!" << endl;

    			message.sequence = ntohl(message.sequence) + 1;
    			message.num_values = 0;
    			message.flag = ntohl(message.flag);
    		}
   
    	}
    	//cout << "Sending Last: " << message.sequence << endl;
    	message.flag = LAST;
    	message.sequence = htonl(message.sequence);
		message.flag = htonl(message.flag);
		message.num_values = htonl(message.num_values);    			
    	sentMessages.push_back(message);
    	int n = sendto(sockfd, (void*)&message, sizeof(Message), 0, (struct sockaddr *)&remote_addr,len);
		if(n < 0)
			cout << "Failed Send!" << endl;

    	list.clear();
    	recvMessages.clear();
    	sentMessages.clear();

	}
	close(sockfd);
}

/*
 * Shutdown the server. Typically this will involve closing the server socket.
 */
void RadixServer::stop() {
   	
}

/*
 * Send the contents of the lists contained with LISTS to the server on HIOSTNAME
 * listening on PORT in datagrams containing batches of unsigned integers. These
 * will be returned to you MSD Radix sorted and should be retied to the caller
 * via LISTS.
 */
void RadixClient::msd(const char *hostname, const int port, std::vector<std::reference_wrapper<std::vector<unsigned int>>> &lists) { 
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) exit(-1);

    struct hostent *server = gethostbyname(hostname);
	if (server == NULL) exit(-1);

	struct sockaddr_in remote_addr;
	bzero((char *) &remote_addr, sizeof(remote_addr));
	remote_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&remote_addr.sin_addr.s_addr, server->h_length);
	remote_addr.sin_port = htons(port);

	socklen_t len = sizeof(remote_addr);
	for(vector<unsigned int> &list : lists)
    {
    	vector<Message> sentMessages;
    	Message message = makeMessage(0, 0, NONE);
 		
 		for(unsigned int i = 0; i < list.size(); i++)
    	{	
    		//cout << "Value: " << list[i] << endl;
            unsigned int onwire = htonl(list[i]);
            message.values[message.num_values] = onwire; 
            message.num_values++;
    		if(message.num_values == MAX_VALUES)
    		{
    			message.sequence = htonl(message.sequence);
    			message.flag = htonl(message.flag);
    			message.num_values = htonl(message.num_values);
    			//cout << "Sending Message: " << message.sequence << endl;
    			sentMessages.push_back(message);
    			int n = sendto(sockfd, (void*)&message, sizeof(Message), 0, (struct sockaddr *)&remote_addr,len);
    			if(n < 0)
    				cout << "Failed Send!" << endl;

    			message.sequence = ntohl(message.sequence) + 1;
    			message.num_values = 0;
    			message.flag = ntohl(message.flag);
    		}
   
    	}
    	//cout << "Sending Last: " << message.sequence << endl;
    	message.flag = LAST;
    	message.sequence = htonl(message.sequence);
		message.flag = htonl(message.flag);
		message.num_values = htonl(message.num_values);    			
    	sentMessages.push_back(message);
    	int n = sendto(sockfd, (void*)&message, sizeof(Message), 0, (struct sockaddr *)&remote_addr,len);
		if(n < 0)
			cout << "Failed Send!" << endl;

    	list.clear();
        vector<Message> recvMessages;
        bool foundLast = false;
        while(!foundLast)
    	{
    		//cout << "waiting for recieving" << endl;
            Message message;
            
			//https://stackoverflow.com/questions/13547721/udp-socket-set-timeout
            struct timeval tv;
			tv.tv_sec = 1;
			tv.tv_usec = 100000;
			if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv)) < 0) {
    			cout << "error" << endl;
			}
			else
			{
	            int n = recvfrom(sockfd, (void*)&message, sizeof(Message), 0,(struct sockaddr *)&remote_addr, &len);
	            if(n < 0)
	            {
	            	unsigned int lastSeq = ntohl(sentMessages[sentMessages.size() - 1].sequence);
	    			Message resend = makeMessage(htonl(1), htonl(0), htonl(RESEND));
					resend.values[0] = htonl(lastSeq);
					int n = sendto(sockfd, (void*)&resend, sizeof(Message), 0, (struct sockaddr *)&remote_addr,len);
	    			if(n < 0)
						cout << "Failed Send!" << endl;
	    			n = recvfrom(sockfd, (void*)&resend, sizeof(Message), 0,(struct sockaddr *)&remote_addr, &len);
	        		if(n < 0)
	        			cout << "Failed recieving" << endl;
	        		recvMessages.push_back(resend);
	        		n = recvfrom(sockfd, (void*)&resend, sizeof(Message), 0,(struct sockaddr *)&remote_addr, &len);
	        		if(n < 0)
	        			cout << "Failed recieving" << endl;
	        		foundLast = true;
	            }
	            
	            //cout << "recieved! sequence: " << ntohl(message.sequence) << endl;
	      
	            if(ntohl(message.flag) == RESEND)
	            {
	            	for(unsigned int numMessage : message.values)
	    			{
	    				unsigned int num = ntohl(numMessage);
	            		//cout << "Sending back : " << numMessage << endl;
	            		message = sentMessages[num];
	            		int n = sendto(sockfd, (void*)&message, sizeof(Message), 0, (struct sockaddr *)&remote_addr,len);
	    				if(n < 0)
	    					cout << "Failed Send!" << endl;	
	    			}
	            	message.sequence = htonl(0);
	            	message.flag = htonl(LAST);
	            	message.num_values = htonl(0);
	            	n = sendto(sockfd, (void*)&message, sizeof(Message), 0, (struct sockaddr *)&remote_addr,len);
	    			if(n < 0)
	    				cout << "Failed Send!" << endl;

	            }
	  			else
	  			{
	  				recvMessages.push_back(message);
	      		}

	            if(ntohl(recvMessages[recvMessages.size() - 1].flag) == LAST)
	            {
	            	foundLast = true;
	            } 
    		}
    	}

    	if(ntohl(recvMessages[0].sequence) != 0)
    	{
    		Message resend = makeMessage(htonl(1), htonl(0), htonl(RESEND));
			resend.values[0] = htonl(0);
			n = sendto(sockfd, (void*)&resend, sizeof(Message), 0, (struct sockaddr *)&remote_addr,len);
			if(n < 0)
				cout << "Failed Send!" << endl;
			n = recvfrom(sockfd, (void*)&resend, sizeof(Message), 0,(struct sockaddr *)&remote_addr, &len);
    		if(n < 0)
    			cout << "Failed recieving" << endl;
    		recvMessages.insert(recvMessages.begin() + 0, resend);
			n = recvfrom(sockfd, (void*)&resend, sizeof(Message), 0,(struct sockaddr *)&remote_addr, &len);
    		if(n < 0)
    			cout << "Failed recieving" << endl;
            		
    	}

    	while(ntohl(recvMessages[recvMessages.size() - 1].sequence) > recvMessages.size() - 1)
    	{
    		for(unsigned int i = 0; i < recvMessages.size(); i++)
    		{
    			if(i != ntohl(recvMessages[i].sequence))
    			{
    				Message resend = makeMessage(htonl(1), htonl(0), htonl(RESEND));
    				resend.values[0] = htonl(i);
    				n = sendto(sockfd, (void*)&resend, sizeof(Message), 0, (struct sockaddr *)&remote_addr,len);
	    			if(n < 0)
	    				cout << "Failed Send!" << endl;
	    			n = recvfrom(sockfd, (void*)&resend, sizeof(Message), 0,(struct sockaddr *)&remote_addr, &len);
            		if(n < 0)
            			cout << "Failed recieving" << endl;
            		recvMessages.insert(recvMessages.begin() + i, resend);
            		n = recvfrom(sockfd, (void*)&resend, sizeof(Message), 0,(struct sockaddr *)&remote_addr, &len);
            		if(n < 0)
            			cout << "Failed recieving" << endl;
            		
    			}
    		}
    	}



    	for(Message message : recvMessages)
    	{
    		for(unsigned int i = 0; i < ntohl(message.num_values); i++)
	        {
	            unsigned int onwire = message.values[i];
	            unsigned int local = ntohl(onwire);
	            //cout << "recieved: " << local << endl;
	            list.push_back(local);
	        }
    	}
    	recvMessages.clear();
    	sentMessages.clear();
	}
	close(sockfd);
}
