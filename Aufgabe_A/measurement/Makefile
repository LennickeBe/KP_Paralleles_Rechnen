all: string_manipulation 
ycm: compile_commands.json

compile_commands.json:
	bear -- make

string_manipulation_par.o: string_manipulation_par.c
	gcc -mavx2 -c string_manipulation_par.c

string_manipulation_seq.o: string_manipulation_seq.c
	gcc -c string_manipulation_seq.c

string_manipulation.o: string_manipulation.c
	gcc -mavx2 -c string_manipulation.c

string_manipulation: string_manipulation.o string_manipulation_par.o string_manipulation_seq.o
	gcc -mavx2 -o string_manipulation string_manipulation.o string_manipulation_seq.o string_manipulation_par.o

clean:
	rm string_manipulation_par.o string_manipulation.o string_manipulation_seq.o string_manipulation
