#define _CRT_SECURE_NO_WARINGS
/* 
   A simple server in the internet domain using TCP
   Usage:./server port (E.g. ./server 10000 )
*/
#include <stdio.h>
#include <sys/types.h>   // definitions of a number of data types used in socket.h and netinet/in.h
#include <sys/socket.h>  // definitions of structures needed for sockets, e.g. sockaddr
#include <sys/stat.h>
#include <netinet/in.h>  // constants and structures needed for internet domain addresses, e.g. sockaddr_in
#include <fcntl.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>

/* process sending file */
int sendfile(int sockfd, char *file, char *type)
{
	int fd;
	char buffer[1024];
	int readn;
	char page[1024];
	char header[1024];
	int contentlen;
	struct stat fstat;
	strncpy(page, file+1, strlen(file));

	bzero(header, 1024);
	if (page != NULL)
	{
		stat(page, &fstat);
		contentlen = (int)fstat.st_size;
		sprintf(header, "HTTP/1.1 200 OK\r\nContent-length: %d\r\nContent-Type: %s; charset=UTF8\r\n\r\n", contentlen, type);
	}

	char target[1024];
	strcat(target, header);
	if (page != NULL)
	{
		fd = open(page, O_RDONLY);
		bzero(buffer, 1024);
		while ((readn = read(fd, buffer, 1024)) > 0)
		{
			strcat(target, buffer);
		}
		write(sockfd, target, (int)strlen(target));
		close(fd);
	}
	else
	{
		write(sockfd, "404 NOT FOUND", strlen("404 NOT FOUND"));
	}

	return 1;

}


/* parsing the content-type */
int typeparse(char *page, char *type)
{
     char *tmp;
     char *filetypes[] = { ".html", ".gif", ".jpeg", ".mp3", ".pdf" };
     char *changetype[] = { "text/html", "image/gif", "image/jpeg", "audio/mpeg", "application/pdf" };
     int typelen = 5;

     tmp = strrchr(page, '.');
     for (int i=0; i<typelen; ++i)
    {
	if (strcmp(filetypes[i],tmp) == 0) strcpy(type, changetype[i]);
    }


     return 1;
}

/* parsing the page */
int reqparse(char *req, char *page)
{
     char *lines;
     char seperate[] = " \r\n";
     lines = strtok(req, seperate);
     int i=0;

     while(lines != NULL)
     {
          if (i==1)
	  {
	  	strcpy(page, lines);
		break;
	  }
	  lines = strtok(NULL, seperate);
	  i+=1;
     }
     return 1;

}


void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd; //descriptors rturn from socket and accept system calls
     int portno; // port number
     socklen_t clilen;
     
     char buffer[1024];
     char page[255];
     char type[255];

     /*sockaddr_in: Structure Containing an Internet Address*/
     struct sockaddr_in serv_addr, cli_addr;
     
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     
     /*Create a new socket
       AF_INET: Address Domain is Internet 
       SOCK_STREAM: Socket Type is STREAM Socket */
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]); //atoi converts from String to Integer
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY; //for the server the IP address is always the address that the server is running on
     serv_addr.sin_port = htons(portno); //convert from host to network byte order
     
     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) //Bind the socket to the server address
              error("ERROR on binding");
     
     listen(sockfd,5); // Listen for socket connections. Backlog queue (connections to wait) is 5

     while(1) { 
       clilen = sizeof(cli_addr);
       /*accept function: 
         1) Block until a new connection is established
         2) the new socket descriptor will be used for subsequent communication with the newly connected client.
       */
       newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
       if (newsockfd < 0) 
            error("ERROR on accept");
       bzero(buffer,1024);
       n = read(newsockfd,buffer,1024); //Read is a block function. It will read at most 255 bytes
       if (n < 0) 
	    error("ERROR reading from socket");
       printf("Here is the message: %s\n",buffer);

       /* requested page parsing */
       reqparse(buffer, page);

       /* process page sending */
       typeparse(page, type);
       sendfile(newsockfd, page, type);
       close(newsockfd);
     }
     return 0; 
}
