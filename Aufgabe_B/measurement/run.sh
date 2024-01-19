#!/bin/bash

#SBATCH --ntasks=1
#SBATCH --time=00:10:00
#SBATCH --account=p_lv_kp_wise2324
#SBATCH --job-name=kp_pr_aufgabe_b
#SBATCH --output=kp_pr_aufgabe_a_%j.out
#SBATCH --error=kp_pr_aufgabe_a_%j.err

srun --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 export OMP_PLACES=cores; export OMP_PROC_BIND=close; ./gol_main
