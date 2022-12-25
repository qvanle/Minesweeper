INCLUDE_PATH :=/home/qvanle/College/CS161/Minesweeper/include

INIT:
	rm -rf lib
	mkdir lib

Building: INIT
	clear
	g++ -c src/Button.cpp -I $(INCLUDE_PATH) -o lib/Button.o
	g++ -c src/Graphics.cpp -I $(INCLUDE_PATH) -o lib/Graphics.o
	g++ -c src/InitData.cpp -I $(INCLUDE_PATH) -o lib/InitData.o
	g++ -c src/Screen.cpp -I $(INCLUDE_PATH) -o lib/Screen.o
	g++ -c src/main.cpp -I $(INCLUDE_PATH) -o lib/main.o


Linking:
	g++ -o MyGame.out lib/*.o -lsfml-system -lsfml-window -lsfml-graphics


Compiling: Building Linking

GetGame: Compiling
	./MyGame.out

GetLog: Compiling
	./MyGame.out > .log

DEBUG:
	gdb ./MyGame.out

Cleaning: INIT
	find MyGame.out && rm MyGame.out || echo MyGame.out is not exist
	rm -rf lib
