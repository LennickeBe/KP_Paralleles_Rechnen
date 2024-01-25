#!/bin/sh

make clean
THREADS=$1 make $2
if [ -z $3 ]; then
	OMP_PLACES=cores OMP_PROC_BIND=close ./gol_main
else
	OMP_SCHEDULE=$3 OMP_PLACES=cores OMP_PROC_BIND=close ./gol_main $3
fi

