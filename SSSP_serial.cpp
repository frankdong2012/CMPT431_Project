#include "core/graph.h"
#include "core/utils.h"
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <queue>

/*---------------------------------------------------------------------
 * Function:  dijkstra_serial
 * Purpose:   Read in a graph, an distance array, an predecessor array
 *            a source vertex, and the time_taken to find the minimum
 *            distance and path from the source vertex to very other
 *            vertex in the graph
 * In args:   graph:  pointer to the graph to be processed
 *            dist_array:  pointer to the distance array which store
 *                         the minimum distance from the source to
 *                         each vertex
 *            prev_vertex_array:   pointer to the array which store
 *                                 the predecessor on the shortest
 *                                 path to each vertex
 *            source_vertex:   the id of the source vertex
 *            time_taken: pointer to the running time
 * Ret val:   Not applicable
 */
void dijkstra_serial(Graph *graph, uint *dist_array, uintV *prev_vertex_array, uintV source_vertex, double *time_taken){
    std::queue<uintV> Queue;        // The FIFO queue to store and query vertices
    uintV current_vertex;           // The vertex that is currently processed
    uint number_vertex = graph->n_; // Number of vertices in the graph
    timer t1;                       // Timer to record the run time

    t1.start();
    // Initialize the queue by pushing the source vertex and set its value in the dist_array and prev_vertex_array
    Queue.push(source_vertex);
    dist_array[source_vertex] = 0;
    prev_vertex_array[source_vertex] = source_vertex;

    while (!Queue.empty())      // The all the reachable would be visited already when the queue become empty
    {
        // Get the vertex layer by layer by dequeue from the queue
        current_vertex = Queue.front();
        Queue.pop();

        uintE out_degree = graph->vertices_[current_vertex].getOutDegree();     // Get the number of out edges from the current processed vertex
        for (uintE i = 0; i < out_degree; i++)
        {
            uintV adjacent_vertex = graph->vertices_[current_vertex].getOutNeighbor(i);     // Get the adjacent vertex to the current processed vertex
            if (dist_array[adjacent_vertex] == INT_MAX)         // Update if the vertex has not been visited
            {
                dist_array[adjacent_vertex] = dist_array[current_vertex] + 1;
                prev_vertex_array[adjacent_vertex] = current_vertex;
                Queue.push(adjacent_vertex);            // Enqueue the adjacent vertex to the queue to be processed later
            }
            
        }
        
    }
    *time_taken = t1.stop();
    
}

/*---------------------------------------------------------------------
 * Function:  display_result
 * Purpose:   display the result of the distance of the shortest patch
 *            from the source to each vertex and the predecessor for
 *            each vertex
 * In args:   dist_array:  pointer to the distance array which store
 *                         the minimum distance from the source to
 *                         each vertex
 *            prev_vertex_array:   pointer to the array which store
 *                                 the predecessor on the shortest
 *                                 path to each vertex
 *            number_vertex:   number of vertices in the graph 
 *            time_taken: pointer to the running time
 *            source_vertex:   the id of the source vertex
 * Ret val:   Not applicable
 */
void display_result(uint *dist_array, uintV *prev_vertex_array, uintV number_vertex, double time_taken, uintV source_vertex){
    std::cout << "Source vertex : " << source_vertex << std::endl;
    std::cout << "Vertex_id,  min_distance,  Predecessor" << std::endl;
    for (uintV i = 0; i < number_vertex; i++)
    {
        if (dist_array[i] == INT_MAX)           // If the vertex is not reachable from the source
        {
            std::cout << i << "  No path to source vertex"<< std::endl;
        }
        else
        {
            std::cout << i << ",      " << dist_array[i] << ",      " << prev_vertex_array[i] << std::endl;
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
          {"sourceVertex", "Source vertex",
           cxxopts::value<uintV>()->default_value(DEFAULT_MAX_ITER)},
          {"inputFile", "Input graph file path",
           cxxopts::value<std::string>()->default_value(
               "/scratch/input_graphs/roadNet-CA")},
            {"y_or_n", "displayOutput",
            cxxopts::value<std::string>()->default_value("no")}
      });

  auto cl_options = options.parse(argc, argv);
  uintV source_vertex = cl_options["sourceVertex"].as<uintV>();
  std::string input_file_path = cl_options["inputFile"].as<std::string>();
  std::string y_or_n = cl_options["y_or_n"].as<std::string>();


  Graph g;
  g.readGraphFromBinary<int>(input_file_path);          // Read in the graph to be processed
  uintV number_vertex = g.n_;
  double time_taken;

    // Initialize the dist_array and prev_array
  uint *dist_array = new uint[number_vertex];
  uintV *prev_vertex_array = new uintV[number_vertex];
  for (uintV i = 0; i < number_vertex; i++)
  {
      dist_array[i] = INT_MAX;
  }

  std::cout << "Using serial" << std::endl;
  dijkstra_serial(&g, dist_array, prev_vertex_array, source_vertex, &time_taken);
  if (y_or_n == "yes"){
    display_result(dist_array, prev_vertex_array, number_vertex, time_taken, source_vertex);
  }
  std::cout << "running time: " << time_taken << std::endl;
}