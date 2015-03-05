
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>

int main(void)
{
    int sockfd = 0;
    int file = 0;
    char mybuffer[256];
	char ip[100];
    memset(mybuffer, '0', sizeof(mybuffer));
    struct sockaddr_in serv_addr;

    /* Create a socket first */
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0)	
    {
        printf("\n Socket couldnt be created sorry \n");
        return 1;
    }

    /* Initializing the connection attributes */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(10000); // To connect to Java Server,change this port number to 45678
	ip="localhost";
    serv_addr.sin_addr.s_addr = inet_addr(ip);	//the ip address of pc

    /* Attempt a connection */
    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
    {
        printf("\n Error : Failed to connect to server,try again!\n");
        return 1;
    }

    
    FILE *fp;   //open a new file,to write the recieved content into it
    fp = fopen("fromclient_c.txt", "wb"); 
    if(NULL == fp)
    {
        printf("Error opening file");
        return 1;
    }

    
    while((file = read(sockfd, mybuffer, 256)) > 0) //read from input stream 256 bytes at at time
    {
		//printf("in while");
        printf("file size %d\n",file);    
        fwrite(mybuffer, 1,file,fp);
        
    }

    if(file < 0)
    {
        printf("\n Read Error \n");
    }


    return 0;
}
