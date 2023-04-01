Game.o: Game.cpp Game.h
	g++ -c Game.cpp -lncurses

Sprite.o: Sprite.cpp Sprite.h
	g++ -c Sprite.cpp -lncurses

Car.o: Car.cpp Car.h
	g++ -c Car.cpp -lncurses

Background.o: Background.cpp Background.h
	g++ -c Background.cpp -lncurses

main.o: main.cpp Game.h
	g++ -c main.cpp -lncurses

main: main.o Game.o Car.o Background.o Sprite.o
	g++ main.o Game.o Car.o Background.o Sprite.o -o main -lncurses

clean:
	rm -f main *.o

.PHONY: clean