test: main.o card.o player.o tile.o
	g++ main.o card.o player.o tile.o -o test

main.o: main.cpp card.h player.h tile.h
	g++ -c main.cpp -std=c++11

tile.o: tile.cpp tile.h
	g++ -c tile.cpp -std=c++11

player.o: player.cpp player.h
	g++ -c player.cpp -std=c++11

card.o: card.cpp card.h
	g++ -c card.cpp -std=c++11

clean:
	rm *.o test