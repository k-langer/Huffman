# Makefile: EMERGE

CC = gcc

CFLAGS = -g -O0 -lm

INC = -Iinc

OBJS = huffman.o

TARGET = Huffman

all: $(TARGET)

$(TARGET):$(OBJS)
	$(CC) $(INC) $(CFLAGS) -o $@ $^

.c.o:
	$(CC) $(INC) $(CFLAGS) -c -o $@ $<

clean: 
	rm -rf $(TARGET) $(OBJS)

test: 
	./$(TARGET)
