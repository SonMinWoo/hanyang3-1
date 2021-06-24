CC = gcc
CFLAGS = -W -Wall
TARGET = server
OBJECTS = server.o

All : $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

clean :
	rm *.o server
