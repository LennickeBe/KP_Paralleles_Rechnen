#!/bin/bash

#SBATCH --ntasks=16
#SBATCH --time=04:30:00
#SBATCH --account=p_tei_ra_hpc_courses
#SBATCH --job-name=kp_pr_aufgabe_b
#SBATCH --output=kp_pr_aufgabe_a_%j.out
#SBATCH --error=kp_pr_aufgabe_a_%j.err
#SBATCH --mem=5G
#SBATCH --cpus-per-task=32

# make sure run.sh is executable
chmod u+x run.sh

module load GCCcore/10.3.0
make clean
# Thread-Measurements
srun --exclusive -n 1 -c 1 --cpu-freq=2000000 ./run.sh 1 gcc
srun --exclusive -n 1 -c 2 --cpu-freq=2000000 ./run.sh 2 gcc
srun --exclusive -n 1 -c 4 --cpu-freq=2000000 ./run.sh 4 gcc
srun --exclusive -n 1 -c 8 --cpu-freq=2000000 ./run.sh 8 gcc
srun --exclusive -n 1 -c 16 --cpu-freq=2000000 ./run.sh 16 gcc
srun --exclusive -n 1 -c 32 --cpu-freq=2000000 ./run.sh 32 gcc

module load intel-compilers
make clean
srun --exclusive -n 1 -c 1 --cpu-freq=2000000 ./run.sh 1 icc
srun --exclusive -n 1 -c 2 --cpu-freq=2000000 ./run.sh 2 icc
srun --exclusive -n 1 -c 4 --cpu-freq=2000000 ./run.sh 4 icc
srun --exclusive -n 1 -c 8 --cpu-freq=2000000 ./run.sh 8 icc
srun --exclusive -n 1 -c 16 --cpu-freq=2000000 ./run.sh 16 icc
srun --exclusive -n 1 -c 32 --cpu-freq=2000000 ./run.sh 32 icc

# OMP_SCHEDULE measurements

srun --exclusive -n 1 -c 32 --cpu-freq=2000000 ./run.sh 32 icc static
srun --exclusive -n 1 -c 32 --cpu-freq=2000000 ./run.sh 32 icc guided
srun --exclusive -n 1 -c 32 --cpu-freq=2000000 ./run.sh 32 icc dynamic
srun --exclusive -n 1 -c 32 --cpu-freq=2000000 ./run.sh 32 icc auto
