all:	cipher

cipher:	cipher.o Playfair.o RowTransposition.o Railfence.o Vigenere.o Caesar.o
	g++ cipher.o Playfair.o RowTransposition.o Railfence.o Vigenere.o Caesar.o -o cipher

cipher.o:	cipher.cpp
	g++ -g -c cipher.cpp 

Playfair.o:	Playfair.cpp Playfair.h CipherInterface.h
	g++ -g -c Playfair.cpp

RowTransposition.o:	RowTransposition.cpp RowTransposition.h
	g++ -g -c RowTransposition.cpp

Railfence.o: Railfence.cpp Railfence.h
	g++ -g -c Railfence.cpp

Vigenere.o: Vigenere.cpp Vigenere.h
	g++ -g -c Vigenere.cpp

Caesar.o: Caesar.cpp Caesar.h
	g++ -g -c Caesar.cpp

clean:
	rm -rf *.o cipher
