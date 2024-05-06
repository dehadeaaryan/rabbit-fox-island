# Makefile for compiling rabbitfox.c

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c99 -fopenmp

# Source files
SRCS = rabbitfox.c events.c

# Object files
OBJS = $(SRCS:.c=.o)

# Header files directory
INCDIR = .

# Executable name
EXEC = rabbitfox

# Targets
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c $<

clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all clean
