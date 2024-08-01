CC = gcc
CFLAGS = -Wall -Wextra

run: pideShop.c hungryVeryMuch.c log.c
	$(CC) $(CFLAGS) -o PideShop pideShop.c log.c p_inverse.c
	$(CC) $(CFLAGS) -o HungryVeryMuch hungryVeryMuch.c log.c

clean:
	rm -f *.o a.out PideShop HungryVeryMuch server_log.log client_log.log