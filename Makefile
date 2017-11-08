OBJS = main.o alphabet.o dfa.o state.o word.o symbol.o glr.o
BINARY = dfa.out
CFLAGS = -g

all: program

program: $(OBJS)
	g++ $(CFLAGS) $(OBJS) -o $(BINARY)

main.o: #main.cpp dfa.hpp
	g++ $(CFLAGS) -c main.cpp

dfa.o: #alphabet.hpp state.hpp dfa.cpp
	g++ $(CFLAGS) -c dfa.cpp

state.o: #state.cpp
	g++ $(CFLAGS) -c state.cpp

alphabet.o: #alphabet.cpp
	g++ $(CFLAGS) -c alphabet.cpp

word.o: #word.cpp alphabet.hpp
	g++ $(CFLAGS) -c word.cpp

symbol.o:
	g++ $(CFLAGS) -c symbol.cpp

glr.o:
	g++ $(CFLAGS) -c glr.cpp


clean:
	rm $(OBJS)

cleanall:
	rm $(OBJS) $(BINARY)