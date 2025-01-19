CC_C = clang
CC_CPP = clang++
CFLAGS = -Wall -Wextra -Werror -std=c11
CPPFLAGS = -Wall -Wextra -Werror -std=c++17

%: %.c
	$(CC_C) $(CFLAGS) -o $@ $<

%: %.cpp
	$(CC_CPP) $(CPPFLAGS) -o $@ $<

all: $(patsubst %.c,%,$(wildcard *.c)) $(patsubst %.cpp,%,$(wildcard *.cpp))

clean:
	rm -f $(patsubst %.c,%,$(wildcard *.c)) $(patsubst %.cpp,%,$(wildcard *.cpp))

.PHONY: all clean
