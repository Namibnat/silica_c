CC = gcc
CFLAGS = -Wall -g

TARGET = silica_c
SRCS = silica_c.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)


assembly: $(SRCS)
	$(CC) $(CFLAGS) -S $(SRCS)


clean:
	rm -f $(TARGET) *.o *.s


.PHONY: all clean assembly


