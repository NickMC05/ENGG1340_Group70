Game.o: Game.cpp Game.h
	g++ -c Game.cpp -lncurses

<<<<<<< HEAD
Car.o: Car.cpp Car.h
	g++ -c Car.cpp -lncurses

Background.o: Background.cpp Background.h
	g++ -c Background.cpp -lncurses

main.o: main.cpp Game.h
	g++ -c main.cpp -lncurses

main: main.o Game.o Car.o Background.o
	g++ main.o Game.o Car.o Background.o -o main -lncurses
=======
Sprite.o: Sprite.cpp Sprite.h
	g++ -c Sprite.cpp -lncurses

main.o: main.cpp Game.h Sprite.h
	g++ -c main.cpp -lncurses

main: main.o Game.o Sprite.o
	g++ main.o Game.o Sprite.o -o main -lncurses

clean:
	rm -f main *.o

.PHONY: clean
>>>>>>> 9913b4f46c1ec27a7e328471ec538e1fae0f1357
