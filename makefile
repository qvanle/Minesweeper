INIT: # remove this one and add some command to Building and GetLog
	mkdir lib
	mkdir log
Building:
	clear
	g++ -c src/Data.cpp -I/home/qvanle/College/CS161/Minesweeper/include -o lib/Data.o
	g++ -c src/main.cpp -I/home/qvanle/College/CS161/Minesweeper/include -o lib/main.o

Linking:
	g++ -o MyGame.exe lib/*.o

Compiling: Building Linking

GetLog: Compiling
	./MyGame.exe > log/BoardData.log

