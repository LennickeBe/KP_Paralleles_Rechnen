#!/bin/bash

#SBATCH --ntasks=16
#SBATCH --time=04:30:00
#SBATCH --account=p_tei_ra_hpc_courses
#SBATCH --job-name=kp_pr_aufgabe_b
#SBATCH --output=kp_pr_aufgabe_a_%j.out
#SBATCH --error=kp_pr_aufgabe_a_%j.err
#SBATCH --mem=5G

# make sure run.sh is executable
chmod u+x run.sh

# make sure directories for data is there
mkdir -p ../evaluation/data/gcc/simd
mkdir -p ../evaluation/data/gcc/no_simd
mkdir -p ../evaluation/data/icc/simd
mkdir -p ../evaluation/data/icc/no_simd

# SIMD-Measurements
module load GCCcore/10.3.0
make clean
srun --exclusive -n 1 --cpu-freq=2000000 ./run.sh gcc

module load intel-compilers
make clean
srun --exclusive -n 1 --cpu-freq=2000000 ./run.sh icc

# no SMID-Measurements
module load GCCcore/10.3.0
make clean
srun --exclusive -n 1 --cpu-freq=2000000 ./run.sh ngcc

module load intel-compilers
make clean
srun --exclusive -n 1 --cpu-freq=2000000 ./run.sh nicc


