all : main
main : MatrixDG.o main.o
	g++ MatrixDG.o main.o -o main
MatrixDG.o : MatrixDG.cpp MatrixDG.h Complex.h Vexs.h Edge.h
	g++ -c MatrixDG.cpp -o MatrixDG.o
main.o : main.cpp MatrixDG.h Complex.h Vexs.h Edge.h
	g++ -c main.cpp -o main.o
clear:
	del *.o main.exe