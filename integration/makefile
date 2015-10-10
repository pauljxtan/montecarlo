CC = clang
#CC = gcc
CFLAGS = -g -Wall
LIBS = -lm
SRCS = mcintegral.c
OBJS = $(SRCS:.c=.o)
MAIN = mcintegral

.PHONY: depend clean

all : $(MAIN)

$(MAIN) : $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS) $(LIBS)

.c.o :
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm $(OBJS) $(MAIN)
