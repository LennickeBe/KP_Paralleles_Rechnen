#!/bin/bash

#SBATCH --ntasks=1
#SBATCH --account=p_lv_kp_wise2324

srun --cpu_bind=cores --distribution=block:block --cpu-freq=2000000 export OMP_PLACES=cores; export OMP_PROC_BIND=close; ./gol_main
