CC = gcc
CFLAGS = -Wall -g
TARGET = test
OUTPUT = answer.txt

$(TARGET): test.c
	$(CC) $(CFLAGS) -o $(TARGET) test.c

run: $(TARGET)
	./$(TARGET) > $(OUTPUT)

clean:
	rm -f $(TARGET) $(OUTPUT)
