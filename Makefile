CC=g++
CFLAGS=-I
CFLAGS+=-Wall
SERVERFILE=server.cpp
CLIENTFILE=client.cpp


server:$(SERVERFILE)
	$(CC) $(CFLAGS) $^ -o $@


client:$(CLIENTFILE)
	$(CC) $(CFLAGS) $^ -o $@

all :server client


clean :
	rm -f *.o server client

