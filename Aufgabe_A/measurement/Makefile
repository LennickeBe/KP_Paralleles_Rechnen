all: string_manipulation 
ycm: compile_commands.json

INCLUDE_DIR=./include

compile_commands.json:
	bear -- make

string_manipulation_par.o: string_manipulation_par.c
	gcc -I ${INCLUDE_DIR} -mavx2 -c string_manipulation_par.c

string_manipulation_seq.o: string_manipulation_seq.c
	gcc -I ${INCLUDE_DIR} -c string_manipulation_seq.c

string_manipulation.o: string_manipulation.c
	gcc -I ${INCLUDE_DIR} -mavx2 -c string_manipulation.c

string_manipulation: string_manipulation.o string_manipulation_par.o string_manipulation_seq.o
	gcc -I ${INCLUDE_DIR} -mavx2 -o string_manipulation string_manipulation.o string_manipulation_seq.o string_manipulation_par.o

clean:
	rm string_manipulation_par.o string_manipulation.o string_manipulation_seq.o string_manipulation
