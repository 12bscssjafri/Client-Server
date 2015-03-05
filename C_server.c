#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

int main(void)
{
	
    int listenfd = 0, connfd = 0;
    char buffer_send[1025];
    struct sockaddr_in serv_addr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);	//creating a socket to use for transmission

    printf("created Socket.\n");

	
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(buffer_send, '0', sizeof(buffer_send));
	
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(10000); //use port 10000 of pc

    bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));	//bind to specified port

    if(listen(listenfd, 10) == -1)
    {
        printf("Listening failed. Exiting program...\n");
        return -1;
    }

    while(1)
    {
	
        connfd = accept(listenfd, (struct sockaddr*)NULL ,NULL);

        /* Open the file that we wish to transfer */
        FILE *fp = fopen("file.txt","rb"); //this is the file to be transferred to the server	
        if(fp==NULL)
        {
            printf("file cannot be open");
            return 1;   
        }   

       
        while(1)	
        {	
            /* First read file in chunks of 256 bytes */
            unsigned char buff[256]={0};
            int filesize = fread(buff,1,256,fp);            

            /* If read was success, send data. */
            if(filesize> 0)
            {
                printf("Sending \n");
                write(connfd, buff, filesize);
            }

            /* If there is a problem reading the file .. 
             * Error or EOF
             */
            if (filesize < 256)
            {
                if (feof(fp))
                    printf("End of file\n");
                if (ferror(fp))
                    printf("Error reading\n");
                break;
            }
        }

        close(connfd);	//close the connection
        sleep(1);
    }

    return 0;
}
