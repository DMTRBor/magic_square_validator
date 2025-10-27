magic: magic.o input_utils.o square_utils.o magic.h
	gcc -g -ansi -Wall -pedantic magic.o input_utils.o square_utils.o -o magic -lm

input_utils.o: input_utils.c magic.h
	gcc -c -g -ansi -Wall -pedantic input_utils.c -o input_utils.o
square_utils.o: square_utils.c magic.h
	gcc -c -g -ansi -Wall -pedantic square_utils.c -o square_utils.o
