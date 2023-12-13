#!/bin/bash

#SBATCH --ntasks=1                 
#SBATCH --time=00:10:00
#SBATCH --account=p_lv_kp_wise2324
#SBATCH --job-name=kp_pr_aufgabe_a
#SBATCH --output=kp_pr_aufgabe_a_%j.out
#SBATCH --error=kp_pr_aufgabe_a_%j.err

module load GCCcore/10.3.0

# make sure the target directory for the data is there
mkdir -p ../evaluation/data

# make sure the executable is there
make clean
make all

srun './string_manipulation'
