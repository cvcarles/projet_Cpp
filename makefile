CC = g++
CFLAGS = -Wall
LDFLAGS = -lncurses
SRC = main.cpp
PROG = main
OBJS = $(SRC:.cpp=.o)
.SUFFIXES : .cpp .o

all: $(PROG)

$(PROG): $(OBJS)
	$(CC)	-o $@ $^ $(LDFLAGS)

main.o: File.hpp FileChainee.hpp Client.hpp Poste.hpp Guichet.hpp
%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *.o *~ core $(PROG)