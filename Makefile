hw4: main.o tablecheck.o encrypt.o
	gcc -g -pg main.o tablecheck.o  encrypt.o -o hw4  -lm

main.o: main.c functions.h
	gcc -c -g -Wall main.c  

tablecheck.o: tablecheck.c functions.h
	gcc -c -g -Wall tablecheck.c  

encrypt.o: encrypt.c functions.h
	gcc -c -g -Wall encrypt.c 

clean:
	rm *.o
	rm hw4
