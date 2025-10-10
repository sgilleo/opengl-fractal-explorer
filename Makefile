CXX = g++
CXXFLAGS = -Wall -g

SRC_DIR = src
LIB_DIR = lib
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin
LIBS = -lglfw3dll -lncursesw -DNCURSES_STATIC

NAME = fractal_explorer.exe
OUT = $(BIN_DIR)/$(NAME)

SRCS = $(wildcard $(SRC_DIR)/*.cpp) 
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)


$(OUT): $(OBJS)
	-mkdir $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -I $(INC_DIR) -L $(LIB_DIR) $(OBJS) $(SRC_DIR)/glad.c $(LIBS) -o $(OUT)
	cp $(SRC_DIR)/vertex.vs $(BIN_DIR)
	cp $(SRC_DIR)/fragment.fs $(BIN_DIR)
	cp $(SRC_DIR)/glfw3.dll $(BIN_DIR)

# Regla para compilar archivos .cpp a .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	-mkdir $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -f $(OBJS) $(BIN_DIR)/*

run:
	cd $(BIN_DIR)
	$(NAME)
	
.PHONY: all clean install

