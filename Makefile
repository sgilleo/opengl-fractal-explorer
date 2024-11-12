all:
	g++ -g -I .\include\ -L .\lib\ .\src\main.cpp .\src\glad.c -lglfw3dll -lncurses -DNCURSES_STATIC -o .\src\main.exe
clean:
	rm .\src\main.exe
