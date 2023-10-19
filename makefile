todo: main.o sistema.o arbolg.o lista.o
	g++ -o main main.o sistema.o arbolg.o lista.o 

main.o: main.cpp
	g++ -c main.cpp

sistema.o: sistema.h sistema.cpp arbolg.h lista.h
	g++ -c sistema.cpp

arbolg.o: arbolg.h arbolg.cpp
	g++ -c arbolg.cpp

lista.o: lista.h lista.cpp
	g++ -c lista.cpp
	
limpiar:
	rm *.o
	rm main