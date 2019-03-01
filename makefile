
snake: main.o Game.o Graphics.o Board.o Snake.o FrameTimer.o Goal.o
	g++ main.o Game.o Graphics.o Board.o Snake.o FrameTimer.o Goal.o `pkg-config --libs sfml-graphics` -o snake

main.o: main.cpp
	g++ -c main.cpp

Game.o:	Game.cpp Game.hpp
	g++ -c Game.cpp

Graphics.o: Graphics.cpp Graphics.hpp
	g++ -c Graphics.cpp

Board.o: Board.cpp Board.hpp
	g++ -c Board.cpp

Location.hpp.gch: Location.hpp
	g++ -c Location.hpp

Snake.o: Snake.cpp Snake.hpp
	g++ -c Snake.cpp

FrameTimer.o: FrameTimer.cpp FrameTimer.hpp
	g++ -c FrameTimer.cpp

Goal.o: Goal.cpp Goal.hpp
	g++ -c Goal.cpp

clean:
	rm *.o snake
