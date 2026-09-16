CXX = g++
CXXFLAGS = -Wall -g

SRC_DIR = src
LIB_DIR = lib
INC_DIR = include
BIN_DIR = bin
LIBS_WIN = -lglfw3dll -lncursesw -DNCURSES_STATIC
LIBS_LINUX = -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lncursesw -DNCURSES_STATIC

NAME = fractal_explorer
OUT = $(BIN_DIR)/$(NAME)


win:
	-mkdir $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -I $(INC_DIR) -L $(LIB_DIR) $(SRC_DIR)/*.cpp $(SRC_DIR)/glad.c $(LIBS_WIN) -o $(OUT).exe
	cp $(SRC_DIR)/vertex.vs $(BIN_DIR)
	cp $(SRC_DIR)/fragment.fs $(BIN_DIR)
	cp $(SRC_DIR)/glfw3.dll $(BIN_DIR)




linux:
	-mkdir $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -I $(INC_DIR) -L $(LIB_DIR) $(SRC_DIR)/*.cpp $(SRC_DIR)/glad.c $(LIBS_LINUX) -o $(OUT).o
	cp $(SRC_DIR)/vertex.vs $(BIN_DIR)
	cp $(SRC_DIR)/fragment.fs $(BIN_DIR)


clean:
	rm -f $(BIN_DIR)/*
	
.PHONY: clean linux

