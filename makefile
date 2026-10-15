CC = gcc
CFLAGS = -Wall -pedantic -std=c11

BINARIES = nevvvbtc

SRCS = $(addsuffix .c, $(BINARIES))
OBJS = $(addsuffix .o, $(BINARIES))

.PHONY: all clean

all: $(BINARIES)


%.out: %.o
	$(CC) $(CFLAGS) $^ -o $@
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJS) $(BINARIES)

