gcc: gcc_gol_main
icc: icc_gol_main

threads:
	if [ -z "${THREADS}" ]; then \
		echo "THREADS is not defined."; \
		exit 1; \
	fi

gcc_gol_board.o: threads gol_board.c
	gcc -mavx2 -fopenmp -D THREADS=${THREADS} -c gol_board.c

gcc_visualize.o: visualize.c
	gcc -c visualize.c

gcc_gol_main.o: gol_main.c
	gcc -D THREADS=${THREADS} -D COMPILER=gcc -c gol_main.c

gcc_gol_main: gcc_gol_main.o gcc_visualize.o gcc_gol_board.o
	gcc -mavx2 -fopenmp -o gol_main gol_main.o visualize.o gol_board.o


icc_gol_board.o: threads gol_board.c
	icc -mavx2 -fopenmp -D THREADS=$(THREADS) -c gol_board.c

icc_visualize.o: visualize.c
	icc -c visualize.c

icc_gol_main.o: gol_main.c
	icc -D THREADS=${THREADS} -D COMPILER=icc -c gol_main.c

icc_gol_main: icc_gol_main.o icc_visualize.o icc_gol_board.o
	icc -maxv2 -fopenmp -o gol_main gol_main.o visualize.o gol_board.o

clean:
	rm gol_board.o visualize.o gol_main.o gol_main pbms/test* pbms/*.gif pbms/foo* pbms/*.mkv
