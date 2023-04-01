Game.o: Game.cpp Game.h
	g++ -c Game.cpp -lncurses

main.o: main.cpp Game.h
	g++ -c main.cpp -lncurses

main: main.o Game.o
	g++ main.o Game.o -o main -lncurses

clean:
	rm -f *.o main

.PHONY: clean