CC=gcc
CFLAGS=-g -O1 -Wall
LDLIBS=-lpthread

all: hostinfo echoclient echoserver 

echoclient: echoclient.c csapp.h csapp.c
echoserver: echoserver.c echo.c csapp.h csapp.c
hostinfo: hostinfo.c csapp.h csapp.c

clean:
	rm -f *.o *~ *.exe hostinfo echoclient echoserver csapp.o

