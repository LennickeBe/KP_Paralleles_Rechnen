gcc: gcc_gol_main
icc: icc_gol_main
ngcc: ngcc_gol_main
nicc: nicc_gol_main
ycm: compile_commands.json

compile_commands.json:
	bear -- make gcc


gcc_gol_board.o: gol_board.c
	gcc -g -mavx2 -fopenmp -c gol_board.c

gcc_visualize.o: visualize.c
	gcc -g -c visualize.c

gcc_gol_main.o: gol_main.c
	gcc -g -D COMPILER=gcc -D SIMD=1 -c gol_main.c

gcc_gol_main: gcc_gol_main.o gcc_visualize.o gcc_gol_board.o
	gcc -g -mavx2 -fopenmp -o gol_main gol_main.o visualize.o gol_board.o


icc_gol_board.o: gol_board.c
	icc -mavx2 -fopenmp -c gol_board.c

icc_visualize.o: visualize.c
	icc -c visualize.c

icc_gol_main.o: gol_main.c
	icc -D COMPILER=icc -D SIMD=1 -c gol_main.c

icc_gol_main: icc_gol_main.o icc_visualize.o icc_gol_board.o
	icc -maxv2 -fopenmp -o gol_main gol_main.o visualize.o gol_board.o


ngcc_gol_board.o: gol_board.c
	gcc -mno-avx -mno-sse2 -mno-avx2 -fno-tree-vectorize -c gol_board.c

ngcc_visualize.o: visualize.c
	gcc -c visualize.c

ngcc_gol_main.o: gol_main.c
	gcc -D COMPILER=gcc -D SIMD=0 -c gol_main.c

ngcc_gol_main: ngcc_gol_main.o ngcc_visualize.o ngcc_gol_board.o
	gcc -mno-avx -mno-sse2 -mno-avx2 -fno-tree-vectorize -o gol_main gol_main.o visualize.o gol_board.o


nicc_gol_board.o: gol_board.c
	icc -mno-avx -mno-sse2 -mno-avx2 -fno-tree-vectorize -c gol_board.c

nicc_visualize.o: visualize.c
	icc -c visualize.c

nicc_gol_main.o: gol_main.c
	icc -D COMPILER=icc -D SIMD=0 -c gol_main.c

nicc_gol_main: nicc_gol_main.o nicc_visualize.o nicc_gol_board.o
	icc -mno-avx -mno-sse2 -mno-avx2 -fno-tree-vectorize -o gol_main gol_main.o visualize.o gol_board.o


clean:
	rm gol_board.o visualize.o gol_main.o gol_main pbms/test* pbms/*.gif pbms/foo* pbms/*.mkv
