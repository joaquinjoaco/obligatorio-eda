todo: main.o sistema.o 
	g++ -o main main.o sistema.o 
main.o: main.cpp
	g++ -c main.cpp
sistema.o: sistema.h sistema.cpp
	g++ -c sistema.cpp
limpiar:
	rm *.o
	rm main

