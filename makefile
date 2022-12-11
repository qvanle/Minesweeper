INCLUDE_PATH :=/home/qvanle/College/CS161/Minesweeper/include

INIT:
	find lib || mkdir lib
	find log || mkdir log

Building: INIT
	clear
	g++ -c src/Data.cpp -I $(INCLUDE_PATH) -o lib/Data.o
	g++ -c src/Visual.cpp -I $(INCLUDE_PATH) -olib/Visual.o
	g++ -c src/main.cpp -I $(INCLUDE_PATH) -o lib/main.o

Linking:
	g++ -o MyGame.out lib/*.o -lsfml-system -lsfml-window -lsfml-graphics

Compiling: Building Linking

GetLog: Compiling
	./MyGame.out > log/BoardData.log
Clear:
	find MyGame.out && rm MyGame.out || echo Mygame.out is not exist
	Find lib && rm -rf lib || echo lib folder is not exist
	find log && rm -rf log || echo log folder is not exist
