main: main.o Game.o Car.o Background.o Sprite.o State.o
	g++ -std=c++11 main.o State.o Game.o Car.o Background.o Sprite.o  -o main -lncurses
State.o: State.cpp State.h
	g++ -std=c++11 -c State.cpp -lncurses
Game.o: Game.cpp Game.h
	g++ -std=c++11 -c Game.cpp -lncurses
Sprite.o: Sprite.cpp Sprite.h
	g++ -std=c++11 -c Sprite.cpp -lncurses
main.o: main.cpp Game.h Sprite.h State.h
	g++ -std=c++11 -c main.cpp -lncurses
clean:
	rm -f main *.o
.PHONY: clean