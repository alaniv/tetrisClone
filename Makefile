CFLAGS=-std=c++11 -Wfatal-errors -Wall -Werror -Wextra -pedantic -g
LDIR=-L./lib/SDL2
IDIR=-I./include -I./src
LIBS=-lmingw32 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2
OBJS=./obj/Game.o ./obj/Main.o ./obj/Board.o ./obj/Tetromino.o ./obj/TextureManager.o ./obj/Background.o

.PHONY: build clean run
build: $(OBJS)
	g++ $(CFLAGS) $^ -o ./bin/Main.exe $(IDIR) $(LDIR) $(LIBS)

clean:
	rm -f ./bin/Main.exe && rm -f ./obj/*.o
  
./obj/Game.o: ./src/Game.cpp ./src/Game.h
	g++ -c $(CFLAGS) ./src/Game.cpp -o ./obj/Game.o $(IDIR) $(LDIR) $(LIBS)

./obj/%.o: ./src/%.cpp ./src/%.h
	g++ -c $(CFLAGS) $< -o $@ $(IDIR) $(LDIR) $(LIBS)

./obj/Main.o: ./src/Main.cpp
	g++ -c $(CFLAGS) $< -o $@ $(IDIR) $(LDIR) $(LIBS)

run:
	cd bin && ./Main.exe