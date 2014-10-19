#CC = g++
CC = clang++
CFLAGS = -g -Wall
INCLUDES = -I../include
LFLAGS = -L../lib
LIBS = -lm
SRCS = dla.cpp simulate.cpp
OBJS = $(SRCS:.cpp=.o)
MAIN = simulate

.PHONY: depend clean

all : $(MAIN)

$(MAIN) : $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LIBS)

.cpp.o :
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean :
	rm *.o $(MAIN)
