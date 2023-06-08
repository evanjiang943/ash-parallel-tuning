# CS205 Final Project

## Contributors
Roy Han, Evan Jiang

## Overview
Our project aims to adapt and implement Asynchronous Successive Halving (ASH) to accelerate the search for the best hyperparameter configurations in artificial neural networks (ANNs). Hyperparameters are crucial in determining model performance (e.g. maintaining highest predictive accuracy), and they are foundational to training and/or architecture. Since the process of finding the set of hyperparameters for an ANN is lengthy, time-drawn out, and expensive, our group devised an approach that leverages parallelization techniques using openMP. Through a comparison between our parallelized implementation (ASH) to the sequential baseline of Successive Halving (SH), we show that our project yields results that indicate hyperparameter search speedup while maintaining scalability and productionizability.

## Execution Instructions
### Command Line
1. Import modules:
    ```
    module load gcc/12.1.0-fasrc01
    module load git/2.17.0-fasrc01
    module load openmpi/4.1.3-fasrc01
    module load python/3.9.12-fasrc01
    ```
2. Build the executables:
    ```
    make all
    ```
3. Run the programs:
    - For SH: 
        ```
        ./m5_SH {number of models to be trained}
        ```
    - For ASH:
        ```
        ./m5_ASH {number of models to be trained}
        ```

4. Clean with:
    ```
    make clean
    ```

### Job Script
1. For SH:
    - Open `sh_check.sh` and edit `{nModels}` in `./m5_SH {nModels}` to the number of models to be trained.
    - Submit the job with: `sbatch sh_check.sh`
    - View the output file: `sh_check_%j.out`
2. For ASH:
    - Open `ash_check.sh` and:
        1. Edit `{cores}` in `#SBATCH --cpus-per-task={cores}` to the number of preferred ASH workers.
        2. Edit `{nModels}` in `./m5_ASH {nModels}` to the number of models to be trained.
    - Submit the job with: `sbatch ash_check.sh`
    - View the output file: `ash_check_%j.out`

## File Descriptions
ASH.cpp: This code file implements ASH using openMP. After defining and discretizng the solution space into the vector `candidates`, it defines a `ladder`, which is a vector of max-heaps and serves as the basis of candidate rung climbing. It then spawns a parallel region, in which each thread identifies the highest (on the ladder) model available, trains it, then pushes it to the next rung. Any operations on `candidates` or `ladder` are protected from race conditions.

SH.cpp: This code file implements SH. It defines and discretizes the solution space into the first rung of `ladder`, which is a vector of vectors and represents candidate rungs. It then iterates through each rung while using a max-heap to train each candidate and promote the top half candidates to the next rung.
    
Makefile: This automates the build for our programs, and compiles and links everything together into executables.

sh_check.sh & ash_check.sh: These are scripts that handle program compilation and jobs with the cluster.

m5_neural_network.cpp: This code file is an open source neural network.

## Contact Information
If you have any questions, please contact our team:
- Roy Han: royhan@college.harvard.edu
- Evan Jiang: evanjiang@college.harvard.edu
