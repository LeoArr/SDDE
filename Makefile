SRC=$(wildcard src/*.cpp)
SRC_DIR=src/
INC_DIR=include/
OBJ_DIR=obj/

CC = c++17
CXXFLAGS = -g -Wall
packages = sdl2 SDL2_image SDL2_ttf
CPPFLAGS := $(shell pkg-config --cflags $(packages))
LIBS := $(shell pkg-config --static --libs $(packages))

BIN=bin/a.out

all: objs
	g++ -std=$(CC) $(CXXFLAGS) $(CPPFLAGS) $(SRC) -I$(INC_DIR) $(LIBS) -o $(BIN) \

objs: clean
	mkdir $(OBJ_DIR)
	g++ -std=$(CC) $(FLAGS) -c $(SRC) -I$(INC_DIR); \
	mv *.o ./$(OBJ_DIR); \

clean:
	rm -rf $(OBJ_DIR) $(BIN)

run: all
	./$(BIN)
