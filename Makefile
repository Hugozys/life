.PHONY: clean
CXXFLAGS = -std=gnu++11 -Wall -Werror -pedantic
DFLAGS = -MMD
CC = g++
DEBUG = -ggdb3
SRCS = $(wildcard *.cc)
OBJS = $(patsubst %.cc, %.o, $(SRCS))

life: $(OBJS)
	$(CC) $^ -o $@

%.o: %.cc
	$(CC) $(CXXFLAGS)  -c $< $(DFLAGS) -o $@



-include *.d

clean:
	rm -f *~ life *.o *.d
