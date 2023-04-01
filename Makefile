main: main.o Game.o Sprite.o
	g++ main.o Game.o Sprite.o -o main -lncurses
Game.o: Game.cpp Game.h
	g++ -c Game.cpp -lncurses
Sprite.o: Sprite.cpp Sprite.h
	g++ -c Sprite.cpp -lncurses
main.o: main.cpp Game.h Sprite.h
	g++ -c main.cpp -lncurses
clean:
	rm -f main *.o
.PHONY: clean