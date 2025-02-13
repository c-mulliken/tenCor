CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
OBJ = tensor.o
TARGET = tensor

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)
	chmod +x $(TARGET)

tensor.o: tensor.c tensor.h
	$(CC) $(CFLAGS) -c tensor.c -o tensor.o
	chmod +x tensor.o

clean:
	rm -f $(TARGET) $(OBJ)
