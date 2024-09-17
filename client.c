/*///////////////////////////////////////////////////////////
*
* FILE:		client.c
* AUTHOR:	Jamin Chung
* PROJECT:	CNT 4007 Project 1 - Professor Traynor
* DESCRIPTION:	Network Client Code
*
*////////////////////////////////////////////////////////////

/* Included libraries */

#include <stdio.h>		    /* for printf() and fprintf() */
#include <sys/socket.h>		    /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h>		    /* for sockaddr_in and inet_addr() */
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <openssl/evp.h>	    /* for OpenSSL EVP digest libraries/SHA256 */

/* Constants */
#define RCVBUFSIZE 512		    /* The receive buffer size */
#define SNDBUFSIZE 512		    /* The send buffer size */
#define MDLEN 32

/* The main function */
int main(int argc, char *argv[])
{

    int clientSock;		    /* socket descriptor */
    struct sockaddr_in serv_addr;   /* The server address */

    char *studentName;		    /* Your Name */

    char sndBuf[SNDBUFSIZE];	    /* Send Buffer */
    char rcvBuf[RCVBUFSIZE];	    /* Receive Buffer */
    
    int i;			    /* Counter Value */

    /* Get the Student Name from the command line */
    if (argc != 2) 
    {
	printf("Incorrect input format. The correct format is:\n\tnameChanger your_name\n");
	exit(1);
    }
    studentName = argv[1];
    memset(&sndBuf, 0, RCVBUFSIZE);
    memset(&rcvBuf, 0, RCVBUFSIZE);

    /* Create a new TCP socket*/
    clientSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    


    /* Construct the server address structure */
    memset(&serv_addr, 0, sizeof(serv_addr)); //clears mem structure
    serv_addr.sin_family = AF_INET; //addy family
    serv_addr.sin_addr.s_addr = inet_addr("10.20.0.233"); //assign it (INADDR_ANY MAKES IT SO THAT YOU ACCEPT CONN FROM ANY IP ADDY)
    serv_addr.sin_port = htons(80); //port


    /* Establish connecction to the server */
    connect(clientSock, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    
    /* Send the string to the server */
    send(clientSock, studentName, strlen(studentName), 0);

    /* Receive and print response from the server */
    read(clientSock, rcvBuf, sizeof(rcvBuf) - 1);

    printf("This is message: %s\n", rcvBuf);

    printf("%s\n", studentName);
    printf("Transformed input is: ");
    for(i = 0; i < MDLEN; i++) printf("%02x", rcvBuf[i]);
    printf("\n");

    return 0;
}
