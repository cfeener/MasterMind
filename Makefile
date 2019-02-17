CC = gcc

maker: code.h
	$(CC) maker.c -o maker

breaker: code.h
	$(CC) breaker.c -o breaker

clean:
	rm maker breaker
