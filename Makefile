.PHONY: clean
CXXFLAGS = -std=gnu++11 -Wall -Werror -pedantic
DFLAGS = -MMD
CC = g++
DEBUG = -ggdb3
#TUI = -DTUI
LIBS = -lncurses -lmenu -lglog
SRCS = $(wildcard *.cc)
OBJS = $(patsubst %.cc, %.o, $(SRCS))

life: $(OBJS)
	$(CC) $(DEBUG) $^ -o $@ $(LIBS)

%.o: %.cc
	$(CC) $(CXXFLAGS) $(DEBUG) $(TUI)  -c $< $(DFLAGS) -o $@



-include *.d

clean:
	rm -f *~ life *.o *.d log* UNKNOWN.INFO
