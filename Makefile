CC = gcc

maker: code.h
	$(CC) maker.c -o maker

clean:
	rm maker
