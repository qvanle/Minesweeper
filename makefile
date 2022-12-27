INCLUDE_PATH :=/home/qvanle/College/CS161/Minesweeper/include

QuickBuild:
	clear
	g++ -w -o MyGame.out src/*.cpp -I $(INCLUDE_PATH)  -lsfml-system -lsfml-window -lsfml-graphics && ./MyGame.out


INIT:
	find lib || mkdir lib

Building: INIT
	clear
	g++ -c src/BoardData.cpp -I $(INCLUDE_PATH) -o lib/BoardData.o
	g++ -c src/Graphics.cpp -I $(INCLUDE_PATH) -o lib/Graphics.o
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
