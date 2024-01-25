#!/bin/bash

#SBATCH --ntasks=12
#SBATCH --time=04:30:00
#SBATCH --account=p_lv_kp_wise2324
#SBATCH --job-name=kp_pr_aufgabe_b
#SBATCH --output=kp_pr_aufgabe_a_%j.out
#SBATCH --error=kp_pr_aufgabe_a_%j.err

# make sure run.sh is executable
chmod u+x run.sh

module load GCCcore/10.3.0
make clean
# Thread-Measurements
srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 ./run.sh 1 gcc
srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 ./run.sh 2 gcc
srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 ./run.sh 4 gcc
srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 ./run.sh 8 gcc
srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 ./run.sh 16 gcc
srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 ./run.sh 32 gcc

module load intel-compilers
make clean
srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 ./run.sh 1 icc
srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 ./run.sh 2 icc
srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 ./run.sh 4 icc
srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 ./run.sh 8 icc
srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 ./run.sh 16 icc
srun -n 1 --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 ./run.sh 32 icc
