#!/bin/bash

#SBATCH --ntasks=1
#SBATCH --time=00:10:00
#SBATCH --account=p_lv_kp_wise2324
#SBATCH --job-name=kp_pr_aufgabe_b
#SBATCH --output=kp_pr_aufgabe_a_%j.out
#SBATCH --error=kp_pr_aufgabe_a_%j.err


module load GCCcre/10.3.0

export OMP_PLACES=cores
export OMP_PROC_BIND=close

make clean

# Thread-Measurements
export THREADS=1
make all
srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 --export=ALL ./gol_main
export THREADS=2
make all
srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 --export=ALL ./gol_main
export THREADS=4
make all
srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 --export=ALL ./gol_main
export THREADS=8
make all
srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 --export=ALL ./gol_main
export THREADS=16
make all
srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 --export=ALL ./gol_main
export THREADS=32
make all
srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 --export=ALL ./gol_main
