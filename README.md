# CMPT431-Project
CMPT431 Group Project

1.Run the executable file SSSP_MPI locally:
  
type the following command in terminal:
mpirun -n num_processes ./SSSP_MPI --sourceVertex vertex_num --inputFile path_of_graph --y_or_n str   

arguments:
num_precesses indicates the number of processes used   
vertex_num indicates the vertex number of the source vertex
path_of_graph indicates the path of the input graph
str can only be "yes" or "no". "yes" indicates printing out the detailed result, "no" indicates otherwise.
  
sample command:
mpirun -n 4 ./SSSP_MPI --sourceVertex 0 --inputFile input_graphs/testG1 --y_or_n yes
  
2.Run the executable file SSSP_MPI on slurm:
create a a bash script  in the following format:


#!/bin/bash
#
#SBATCH --cpus-per-task=1
#SBATCH --nodes=1
#SBATCH --ntasks=4
#SBATCH --partition=fast
#SBATCH --mem=10G

srun ./SSSP_MPI --sourceVertex 0 --inputFile input_graphs/testG1 --y_or_n yes

options:
--ntasks indicates the number of processes used

run it on slurm by command: sbatch filename.sh
