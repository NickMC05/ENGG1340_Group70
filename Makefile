main: main.o Game.o Car.o Background.o Sprite.o State.o Menu.o Map.o Road.o
	g++ -std=c++11 main.o State.o Game.o Car.o Background.o Sprite.o Menu.o Map.o Road.o -o main -lncurses
Background.o: src/Background.cpp src/Background.h src/Sprite.h
	g++ -std=c++11 -c src/Background.cpp 
Road.o: src/Road.cpp src/Road.h src/State.h src/Car.h
	g++ -std=c++11 -c src/Road.cpp 
Car.o: src/Car.cpp src/Car.h src/State.h src/Sprite.h src/Road.h
	g++ -std=c++11 -c src/Car.cpp 
Map.o: src/Map.cpp src/Map.h src/State.h src/Road.h
	g++ -std=c++11 -c src/Map.cpp 
Menu.o: src/Menu.cpp src/Menu.h
	g++ -std=c++11 -c src/Menu.cpp 
State.o: src/State.cpp src/State.h src/Road.h
	g++ -std=c++11 -c src/State.cpp 
Game.o: src/Game.cpp src/Game.h src/Menu.h src/State.h src/Road.h src/Car.h
	g++ -std=c++11 -c src/Game.cpp 
Sprite.o: src/Sprite.cpp src/Sprite.h src/State.h
	g++ -std=c++11 -c src/Sprite.cpp 
main.o: src/main.cpp
	g++ -std=c++11 -c src/main.cpp 
clean:
	rm -f main *.o
.PHONY: cleans