

CC = gcc          # Compiler to use
CFLAGS = -Wall -Werror  # Compiler flags (to show all warnings and treat warnings as errors)
TARGET = test     # Name of the final executable

all: $(TARGET)

$(TARGET): test.o
	$(CC) $(CFLAGS) -o $(TARGET) test.o

test.o: test.c
	$(CC) $(CFLAGS) -c test.c

clean:
	rm -f *.o $(TARGET)
1;95;0c
