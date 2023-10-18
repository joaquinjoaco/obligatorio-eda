todo: main.o sistema.o arbolg.o
	g++ -o main main.o sistema.o arbolg.o 

main.o: main.cpp
	g++ -c main.cpp

sistema.o: sistema.h sistema.cpp arbolg.h
	g++ -c sistema.cpp

arbolg.o: arbolg.h arbolg.cpp
	g++ -c arbolg.cpp

limpiar:
	rm *.o
	rm main