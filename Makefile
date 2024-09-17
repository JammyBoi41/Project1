#################################################################
##
## FILE:	Makefile
## PROJECT:	CNT 4007 Project 1 - Professor Traynor
## DESCRIPTION: Compile Project 1
##
#################################################################

CC=gcc
CFLAGS += -I/opt/homebrew/opt/openssl@3/include
LDFLAGS += -L/opt/homebrew/opt/openssl@3/lib
OS := $(shell uname -s)

# Extra LDFLAGS if Solaris
ifeq ($(OS), SunOS)
	LDFLAGS=-lsocket -lnsl
    endif

all: client server 

client: client.c
	$(CC) $(CFLAGS) $(LDFLAGS) client.c -o nameChanger -lcrypto

server: server.c
	$(CC) $(CFLAGS) $(LDFLAGS) server.c -o changeServer -lcrypto

clean:
	    rm -f client server *.o

