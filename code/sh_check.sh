#!/usr/bin/env bash
# File       : submit_check.sh
# Description: Submit a test job to check your implementation
# Copyright 2023 Harvard University. All Rights Reserved.
#SBATCH --job-name=cs205_team21_sh_check
#SBATCH --output=sh_check_%j.out
#SBATCH --mem=2048
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1
#SBATCH --time=02:00:00

module purge
module load gcc/12.1.0-fasrc01
module load git/2.17.0-fasrc01
module load openmpi/4.1.3-fasrc01
module load python/3.9.12-fasrc01
# module load valgrind/3.13.0-fasrc01

# build
make all

# run

# Usage ./m5_SH {nModels}
time srun ./m5_SH 512
# time srun valgrind --leak-check=full ./m5_SH 32

# clean
make clean
