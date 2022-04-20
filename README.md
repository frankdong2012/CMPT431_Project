# CMPT431-Project
## Compile

1. To compile all the code, use the following command.

   ```shell
   make
   ```

2. To compile the serial implementation, use the following command.

   ```shell
   make SSSP_serial
   ```

3. To compile the parallel implementation, use the following command.

   ```shell
   make SSSP_parallel
   ```

4. To compile the distributed implementation, use the following command.

   ```shell
   make SSSP_MPI
   ```

## To run the serial implementation

1. To run the executable of the serial implementation, use the following command.

   ```shell
   ./SSSP_serial --sourceVertex 1 --inputFile absolute_path_of_input_graph --y_or_n yes
   ```

   --sourceVertex: the ID of the source vertex

   --inputeFile: absolute path of the input graph

   --y_or_n: whether or not to print out the shortest path

2. Run the executable file SSSP_serial on slurm:
   create a a bash script  in the following format:

   ```shell
   #!/bin/bash
   #
   #SBATCH --cpus-per-task=1
   #SBATCH --time=05:00
   #SBATCH --mem=10G
   #SBATCH --partition=fast
   
   srun ./SSSP_serial --sourceVertex 1 --inputFile absolute_path_of_input_graph --y_or_n yes
   ```

   run it on slurm by command:

   ```shell
   sbatch filename.sh
   ```

## To run the parallel implementation

1. To run the executable of the parallel implementation, use the following command.

   ```shell
   ./SSSP_parallel --nThreads 4 --sourceVertex 1 --inputFile [absolute_path_of_input_graph] --displayOutput [yes/no]
   ```

   --nThreads: number of threads

   --sourceVertex: the ID of the source vertex

   --inputFile: the absolute path of the input graph

   --displayOutput: whether to print out the result of the shortest path

2. Run the executable file SSSP_parallel on slurm:
   create a a bash script  in the following format:

   ```bash
   #!/bin/bash
   #
   #SBATCH --cpus-per-task=4
   #SBATCH --time=05:00
   #SBATCH --mem=10G
   #SBATCH --partition=fast
   
   srun ./SSSP_parallel --nThreads 4 --sourceVertex 1 --inputFile [absolute_path_of_input_graph] --displayOutput [yes/no]
   ```

   run it on slurm by command:

   ```bash
   sbatch filename.sh
   ```

## To run the distributed implementation

1. Run the executable file SSSP_MPI locally:

​		type the following command in terminal:

```shell
mpirun -n num_processes ./SSSP_MPI --sourceVertex vertex_num --inputFile path_of_graph --y_or_n str 
```

​	Arguments:

​	--num_precesses: indicates the number of processes used   

​	--vertex_num: indicates the vertex number of the source vertex

​	--path_of_graph: indicates the path of the input graph 

​	--str: can only be "yes" or "no". "yes" indicates printing out the detailed result, "no" indicates otherwise.

​	sample command:

```shell
mpirun -n 4 ./SSSP_MPI --sourceVertex 0 --inputFile input_graphs/testG1 --y_or_n yes
```

2. Run the executable file SSSP_MPI on slurm:
   create a a bash script  in the following format:

```shell
#!/bin/bash
#
#SBATCH --cpus-per-task=1
#SBATCH --nodes=1
#SBATCH --ntasks=4
#SBATCH --partition=fast
#SBATCH --mem=10G

srun ./SSSP_MPI --sourceVertex 0 --inputFile input_graphs/testG1 --y_or_n yes
```

​	options:
​	--ntasks: indicates the number of processes used

​	run it on slurm by command:

```shell
sbatch filename.sh
```

