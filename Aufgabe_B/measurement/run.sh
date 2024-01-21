#!/bin/bash

#SBATCH --ntasks=1
#SBATCH --time=00:25:00
#SBATCH --account=p_lv_kp_wise2324
#SBATCH --job-name=kp_pr_aufgabe_b
#SBATCH --output=kp_pr_aufgabe_a_%j.out
#SBATCH --error=kp_pr_aufgabe_a_%j.err


module load GCCcore/10.3.0

export OMP_PLACES=cores
export OMP_PROC_BIND=close

make clean

# Thread-Measurements
export THREADS=1
make gcc
srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 export OMP_PLACES=cores; export OMP_PROC_BIND=close; ./gol_main
export THREADS=2
make gcc
srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 export OMP_PLACES=cores; export OMP_PROC_BIND=close; ./gol_main
export THREADS=4
make gcc
srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 export OMP_PLACES=cores; export OMP_PROC_BIND=close; ./gol_main
export THREADS=8
make gcc
srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 export OMP_PLACES=cores; export OMP_PROC_BIND=close; ./gol_main
export THREADS=16
make gcc
srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 export OMP_PLACES=cores; export OMP_PROC_BIND=close; ./gol_main
export THREADS=32
make gcc
srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 export OMP_PLACES=cores; export OMP_PROC_BIND=close; ./gol_main

module load intel-compilers

export THREADS=1
make icc
srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 export OMP_PLACES=cores; export OMP_PROC_BIND=close; ./gol_main
export THREADS=2
make icc
srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 export OMP_PLACES=cores; export OMP_PROC_BIND=close; ./gol_main
export THREADS=4
make icc
srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 export OMP_PLACES=cores; export OMP_PROC_BIND=close; ./gol_main
export THREADS=8
make icc
srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 export OMP_PLACES=cores; export OMP_PROC_BIND=close; ./gol_main
export THREADS=16
make icc
srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 export OMP_PLACES=cores; export OMP_PROC_BIND=close; ./gol_main
export THREADS=32
make icc
srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 export OMP_PLACES=cores; export OMP_PROC_BIND=close; ./gol_main
