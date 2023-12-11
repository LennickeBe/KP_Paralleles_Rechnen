all: gol_main

gol_board.o: gol_board.c
	gcc -fopenmp -c gol_board.c

visualize.o: visualize.c
	gcc -c visualize.c

gol_main.o: gol_main.c
	gcc -c gol_main.c

gol_main: gol_main.o visualize.o gol_board.o
	gcc -fopenmp -o gol_main gol_main.o visualize.o gol_board.o

clean:
	rm gol_board.o visualize.o gol_main.o gol_main pbms/test* pbms/*.gif pbms/foo*
