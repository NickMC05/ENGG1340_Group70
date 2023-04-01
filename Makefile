main: main.o Game.o Car.o Background.o Sprite.o
	g++ -std=c++11 main.o Game.o Car.o Background.o Sprite.o -o main -lncurses
Game.o: Game.cpp Game.h
	g++ -std=c++11 -c Game.cpp -lncurses
Sprite.o: Sprite.cpp Sprite.h
	g++ -std=c++11 -c Sprite.cpp -lncurses

main.o: main.cpp Game.h Sprite.h
	g++ -std=c++11 -c main.cpp -lncurses

clean:
	rm -f main *.o
.PHONY: clean