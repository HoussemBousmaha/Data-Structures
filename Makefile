CC = clang
CXX = clang++
CFLAGS = -Wall -Wextra -Werror -std=c99
CXXFLAGS = -Wall -Wextra -Werror -std=c++11

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

%: %.cc
	$(CXX) $(CXXFLAGS) -o $@ $<

all: $(patsubst %.c,%,$(wildcard *.c)) $(patsubst %.cc,%,$(wildcard *.cc))

clean:
	rm -f $(patsubst %.c,%,$(wildcard *.c)) $(patsubst %.cc,%,$(wildcard *.cc))

.PHONY: all clean
