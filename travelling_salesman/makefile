CC = clang
CFLAGS = -g -Wall
LFLAGS = -L../lib
LIBS = -lm
SRCS = travsal.c
OBJS = $(SRCS:.c=.o)
MAIN = travsal

.PHONY: depend clean

all : $(MAIN)

$(MAIN) : $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS) $(LIBS)

.c.o :
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm $(OBJS) $(MAIN)
