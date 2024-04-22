#!/bin/bash

#SBATCH --ntasks=1                 
#SBATCH --time=00:10:00
#SBATCH --account=p_tei_ra_hpc_courses
#SBATCH --job-name=kp_pr_aufgabe_a
#SBATCH --output=kp_pr_aufgabe_a_%j.out
#SBATCH --error=kp_pr_aufgabe_a_%j.err
 
module load GCCcore/10.3.0

mkdir -p ../evaluation/data

srun --cpu-freq=2000000 -n 1 make clean; make all; ./string_manipulation
