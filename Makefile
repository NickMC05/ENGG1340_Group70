Game.o: Game.cpp Game.h
	g++ -c Game.cpp -lncurses

Car.o: Car.cpp Car.h
	g++ -c Car.cpp -lncurses

Background.o: Background.cpp Background.h
	g++ -c Background.cpp -lncurses

main.o: main.cpp Game.h
	g++ -c main.cpp -lncurses

main: main.o Game.o Car.o Background.o
	g++ main.o Game.o Car.o Background.o -o main -lncurses