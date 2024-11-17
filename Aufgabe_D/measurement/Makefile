gcc: gcc_gol_main
icc: icc_gol_main
ycm: compile_commands.json

INCLUDE_DIR=./include

compile_commands.json:
	bear -- make gcc

gcc_gol_board.o: gol_board.c
	gcc -I ${INCLUDE_DIR} -c gol_board.c

gcc_visualize.o: visualize.c
	gcc -I ${INCLUDE_DIR} -c visualize.c

gcc_gol_main.o: gol_main.c
	gcc -I ${INCLUDE_DIR} -c gol_main.c

gcc_gol_main: gcc_gol_main.o gcc_gol_board.o gcc_visualize.o
	gcc -I ${INCLUDE_DIR} -o gol_main gol_main.o gol_board.o visualize.o



icc_gol_board.o: gol_board.c
	icc -I ${INCLUDE_DIR} -c gol_board.c

icc_visualize.o: visualize.c
	icc -I ${INCLUDE_DIR} -c visualize.c

icc_gol_main.o: gol_main.c
	icc -I ${INCLUDE_DIR} -c gol_main.c

icc_gol_main: gcc_gol_main.o gcc_gol_board.o gcc_visualize.o
	icc -I ${INCLUDE_DIR} -o gol_main gol_main.o gol_board.o visualize.o


clean:
	rm gol_board.o visualize.o gol_main.o gol_main pbms/test* pbms/*.gif pbms/foo* pbms/*.mkv
