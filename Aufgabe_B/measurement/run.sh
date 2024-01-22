#!/bin/sh

make clean
THREADS=$1 make $2
OMP_PLACES=cores OMP_PROC_BIND=close ./gol_main
