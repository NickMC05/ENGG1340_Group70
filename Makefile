main: main.o Game.o Car.o Background.o Sprite.o State.o Menu.o Map.o
	g++ -std=c++11 main.o State.o Game.o Car.o Background.o Sprite.o Menu.o Map.o -o main -lncurses
Background.o: src/Background.cpp src/Background.h
	g++ -std=c++11 -c src/Background.cpp -lncurses
Car.o: src/Car.cpp src/Car.h
	g++ -std=c++11 -c src/Car.cpp -lncurses
Map.o: src/Map.cpp src/Map.h
	g++ -std=c++11 -c src/Map.cpp -lncurses
Menu.o: src/Menu.cpp src/Menu.h
	g++ -std=c++11 -c src/Menu.cpp -lncurses
State.o: src/State.cpp src/State.h
	g++ -std=c++11 -c src/State.cpp -lncurses
Game.o: src/Game.cpp src/Game.h
	g++ -std=c++11 -c src/Game.cpp -lncurses
Sprite.o: src/Sprite.cpp src/Sprite.h
	g++ -std=c++11 -c src/Sprite.cpp -lncurses
main.o: src/main.cpp src/Game.h src/Sprite.h src/State.h src/Menu.h src/Car.h
	g++ -std=c++11 -c src/main.cpp -lncurses
clean:
	rm -f main *.o
.PHONY: cleans