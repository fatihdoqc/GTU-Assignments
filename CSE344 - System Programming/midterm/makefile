CC = gcc
CFLAGS = -Wall -Wextra

run: server.c client.c
	$(CC) $(CFLAGS) -o server server.c
	$(CC) $(CFLAGS) -o client client.c

clean:
	rm -f *.o a.out server client