#!/bin/bash

#SBATCH --ntasks=16
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
srun --exclusive -n 1 --cpu-freq=2000000 ./run.sh gcc

module load intel-compilers
make clean
srun --exclusive -n 1 --cpu-freq=2000000 ./run.sh icc

