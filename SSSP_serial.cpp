#include "core/graph.h"
#include "core/utils.h"
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <queue>

void dijkstra_serial(Graph *graph, uint *dist_array, uintV *prev_vertex_array, uintV source_vertex, double *time_taken){
    std::queue<uintV> Queue;
    uintV current_vertex;
    uint number_vertex = graph->n_;
    timer t1;

    t1.start();
    Queue.push(source_vertex);
    dist_array[source_vertex] = 0;
    prev_vertex_array[source_vertex] = source_vertex;

    while (!Queue.empty())
    {
        current_vertex = Queue.front();
        Queue.pop();

        uintE out_degree = graph->vertices_[current_vertex].getOutDegree();
        for (uintE i = 0; i < out_degree; i++)
        
        {
            uintV adjacent_vertex = graph->vertices_[current_vertex].getOutNeighbor(i);
            if (dist_array[adjacent_vertex] == INT_MAX)
            {
                dist_array[adjacent_vertex] = dist_array[current_vertex] + 1;
                prev_vertex_array[adjacent_vertex] = current_vertex;
                Queue.push(adjacent_vertex);
            }
            
        }
        
    }
    *time_taken = t1.stop();
    
}

void display_result(uint *dist_array, uintV *prev_vertex_array, uintV number_vertex, double time_taken){
    std::cout << "Time taken:" << time_taken << std::endl;
    std::cout << "Vertex id, Shortest distance to source, Previous vertex on the path" << std::endl;
    for (uintV i = 0; i < number_vertex; i++)
    {
        if (dist_array[i] == INT_MAX)
        {
            std::cout << i << "No path, No previous vertex"<< std::endl;
        }
        else
        {
            std::cout << i << ", " << dist_array[i] << ", " << prev_vertex_array[i] << std::endl;
        }
        
        
        
    }
    
}

int main(int argc, char *argv[]) {
  cxxopts::Options options(
      "SSSP_serial",
      "Calculate SSSP using serial execution");
  options.add_options(
      "",
      {
          {"nIterations", "Maximum number of iterations",
           cxxopts::value<uintV>()->default_value(DEFAULT_MAX_ITER)},
          {"inputFile", "Input graph file path",
           cxxopts::value<std::string>()->default_value(
               "/scratch/input_graphs/roadNet-CA")},
      });

  auto cl_options = options.parse(argc, argv);
  uintV source_vertex = cl_options["nIterations"].as<uintV>();
  std::string input_file_path = cl_options["inputFile"].as<std::string>();


  Graph g;
  std::cout << "Reading graph\n";
  g.readGraphFromBinary<int>(input_file_path);
  std::cout << "Created graph\n";
  uintV number_vertex = g.n_;
  double time_taken;

  uint *dist_array = new uint[number_vertex];
  uintV *prev_vertex_array = new uintV[number_vertex];
  for (uintV i = 0; i < number_vertex; i++)
  {
      dist_array[i] = INT_MAX;
  }

  
  dijkstra_serial(&g, dist_array, prev_vertex_array, source_vertex, &time_taken);
  //display_result(dist_array, prev_vertex_array, number_vertex, time_taken);
  std::cout << time_taken << std::endl;
}