#!/bin/bash
#
#SBATCH --cpus-per-task=4
#SBATCH --time=02:00
#SBATCH --mem=8G
#SBATCH --partition=slow

srun ./SSSP_parallel --nThreads 2 --sourceVertex 1 --inputFile input_graphs/testG1 --displayOutput no
srun ./SSSP_parallel --nThreads 4 --sourceVertex 1 --inputFile input_graphs/testG1 --displayOutput no
srun ./SSSP_parallel --nThreads 8 --sourceVertex 1 --inputFile input_graphs/testG1 --displayOutput no
srun ./SSSP_parallel --nThreads 2 --sourceVertex 1 --inputFile input_graphs/Wiki --displayOutput no
srun ./SSSP_parallel --nThreads 4 --sourceVertex 1 --inputFile input_graphs/Wiki --displayOutput no
srun ./SSSP_parallel --nThreads 8 --sourceVertex 1 --inputFile input_graphs/Wiki --displayOutput no
srun ./SSSP_parallel --nThreads 2 --sourceVertex 1 --inputFile input_graphs/slash --displayOutput no
srun ./SSSP_parallel --nThreads 4 --sourceVertex 1 --inputFile input_graphs/slash --displayOutput no
srun ./SSSP_parallel --nThreads 8 --sourceVertex 1 --inputFile input_graphs/slash --displayOutput no
srun ./SSSP_parallel --nThreads 2 --sourceVertex 1 --inputFile input_graphs/roadNet-CA --displayOutput no
srun ./SSSP_parallel --nThreads 4 --sourceVertex 1 --inputFile input_graphs/roadNet-CA --displayOutput no
srun ./SSSP_parallel --nThreads 8 --sourceVertex 1 --inputFile input_graphs/roadNet-CA --displayOutput no
