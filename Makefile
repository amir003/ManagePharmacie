all: gestion.o Pharmacie.o parser.o
	g++ gestion.o Pharmacie.o parser.o -o Programme

gestion.o: gestion.cpp Pharmacie.hpp
	g++ -c gestion.cpp -o gestion.o
	
Pharmacie.o: Pharmacie.cpp Pharmacie.hpp
	g++ -c Pharmacie.cpp -o Pharmacie.o
	
parser.o: parser.cpp Pharmacie.hpp
	g++ -c parser.cpp -o parser.o
	
clean:
	rm -rf *.o
	
mrproper: clean
	rm -rf 
	
	
	



