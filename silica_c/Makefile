CC = gcc
CFLAGS = -Wall -g

TARGET = silica
SRCS = silica.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)


assembly: $(SRCS)
	$(CC) $(CFLAGS) -S $(SRCS)


clean:
	rm -f $(TARGET) *.o *.s


.PHONY: all clean assembly


