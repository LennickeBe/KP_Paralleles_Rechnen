#!/bin/bash

#SBATCH --ntasks=12
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
srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 ./run.sh 1 gcc
srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 ./run.sh 2 gcc
srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 ./run.sh 4 gcc
srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 ./run.sh 8 gcc
srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 ./run.sh 16 gcc
srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 ./run.sh 32 gcc

module load intel-compilers

srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 ./run.sh 1 icc
srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 ./run.sh 2 icc
srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 ./run.sh 4 icc
srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 ./run.sh 8 icc
srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 ./run.sh 16 icc
srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 ./run.sh 32 icc
