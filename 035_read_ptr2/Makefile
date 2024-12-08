
CC = gcc
CFLAGS = -Wall -Werror
TARGET = test

all: $(TARGET)

$(TARGET): test.o
	$(CC) $(CFLAGS) -o $(TARGET) test.o

test.o: test.c
	$(CC) $(CFLAGS) -c test.c

clean:
	rm -f *.o $(TARGET)
