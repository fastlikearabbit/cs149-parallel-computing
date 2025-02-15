#include "bfs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstddef>
#include <omp.h>

#include <vector>

#include "../common/CycleTimer.h"
#include "../common/graph.h"

#define ROOT_NODE_ID 0
#define NOT_VISITED_MARKER -1

// #define VERBOSE

void vertex_set_clear(vertex_set* list) {
    list->count = 0;
}

void vertex_set_init(vertex_set* list, int count) {
    list->max_vertices = count;
    list->vertices = (int*)malloc(sizeof(int) * list->max_vertices);
    vertex_set_clear(list);
}

// Take one step of "top-down" BFS.  For each vertex on the frontier,
// follow all outgoing edges, and add all neighboring vertices to the
// new_frontier.
void parallel_top_down_step(
    Graph g,
    vertex_set* frontier,
    vertex_set* new_frontier,
    int* distances)
{

#pragma omp parallel
{
    int local_count = 0;
    int* local_next_frontier = (int*)malloc(sizeof(int) * frontier->max_vertices);
    if (local_next_frontier == NULL) printf("malloc failed\n");

    #pragma omp for
    for (int i=0; i<frontier->count; i++) {

        int node = frontier->vertices[i];

        int start_edge = g->outgoing_starts[node];
        int end_edge = (node == g->num_nodes - 1)
                           ? g->num_edges
                           : g->outgoing_starts[node + 1];

        // attempt to add all neighbors to the new frontier
        for (int neighbor=start_edge; neighbor<end_edge; neighbor++) {
            int outgoing = g->outgoing_edges[neighbor];

            if (distances[outgoing] != NOT_VISITED_MARKER) continue;

            if (__sync_bool_compare_and_swap(&distances[outgoing], NOT_VISITED_MARKER, distances[node] + 1)) {
                local_next_frontier[local_count++] = outgoing;
            }
        }
    }
    int base;
    #pragma omp atomic capture
    {
        base = new_frontier->count;
        new_frontier->count += local_count;
    }
    
    memcpy(&new_frontier->vertices[base], local_next_frontier, sizeof(int) * local_count);
    free(local_next_frontier);
}
}

// Implements top-down BFS.
//
// Result of execution is that, for each node in the graph, the
// distance to the root is stored in sol.distances.
void bfs_top_down(Graph graph, solution* sol) {

    vertex_set list1;
    vertex_set list2;
    vertex_set_init(&list1, graph->num_nodes);
    vertex_set_init(&list2, graph->num_nodes);

    vertex_set* frontier = &list1;
    vertex_set* new_frontier = &list2;

    for (int i=0; i<graph->num_nodes; i++)
        sol->distances[i] = NOT_VISITED_MARKER;

    frontier->vertices[frontier->count++] = ROOT_NODE_ID;
    sol->distances[ROOT_NODE_ID] = 0;

    while (frontier->count != 0) {

#ifdef VERBOSE
        double start_time = CycleTimer::currentSeconds();
#endif

        vertex_set_clear(new_frontier);

        parallel_top_down_step(graph, frontier, new_frontier, sol->distances);
#ifdef VERBOSE
    double end_time = CycleTimer::currentSeconds();
    printf("frontier=%-10d %.4f sec\n", frontier->count, end_time - start_time);
#endif

        // swap pointers
        vertex_set* tmp = frontier;
        frontier = new_frontier;
        new_frontier = tmp;
    }
}

void bottom_up_step(
    Graph g,
    const std::vector<bool>& frontier_mask,
    vertex_set* new_frontier,
    vertex_set* unvisited,
    vertex_set* new_unvisited,
    int* distances)
{
#pragma omp parallel
{
    std::vector<int> local_frontier;
    std::vector<int> local_unvisited;

    const int num_threads = omp_get_num_threads();
    const int approx_chunk_size = (unvisited->count + num_threads - 1) / num_threads;
    local_frontier.reserve(approx_chunk_size);
    local_unvisited.reserve(approx_chunk_size);

    #pragma omp for
    for (int i = 0; i < unvisited->count; i++) {
        int node = unvisited->vertices[i];
        int start_edge = g->incoming_starts[node];
        int end_edge = (node == g->num_nodes - 1) ? g->num_edges : g->incoming_starts[node + 1];

        bool found = false;
        for (int neighbor = start_edge; neighbor < end_edge; neighbor++) {
            int incoming = g->incoming_edges[neighbor];
            if (frontier_mask[incoming]) {
                distances[node] = distances[incoming] + 1;
                local_frontier.push_back(node);
                found = true;
                break;
            }
        }
        if (!found) {
            local_unvisited.push_back(node);
        }
    }

    if (!local_frontier.empty()) {
        int local_size = static_cast<int>(local_frontier.size());
        int base;
        #pragma omp atomic capture
        { base = new_frontier->count; new_frontier->count += local_size; }

        for (int j = 0; j < local_size; j++) {
            new_frontier->vertices[base + j] = local_frontier[j];
        }
    }

    if (!local_unvisited.empty()) {
        int local_size = static_cast<int>(local_unvisited.size());
        int base;
        #pragma omp atomic capture
        { base = new_unvisited->count; new_unvisited->count += local_size; }

        for (int j = 0; j < local_size; j++) {
            new_unvisited->vertices[base + j] = local_unvisited[j];
        }
    }
}
}

void bfs_bottom_up(Graph graph, solution* sol) {
    std::vector<bool> frontier_mask(graph->num_nodes, false);

    vertex_set list1;
    vertex_set list2;
    vertex_set list3;
    vertex_set_init(&list1, graph->num_nodes);
    vertex_set_init(&list2, graph->num_nodes);
    vertex_set_init(&list3, graph->num_nodes);

    vertex_set* unvisited = &list1;
    vertex_set* new_unvisited = &list2;
    vertex_set* new_frontier = &list3;

    for (int i = 0; i < graph->num_nodes; i++) {
        sol->distances[i] = NOT_VISITED_MARKER;
        if (i != ROOT_NODE_ID)
            unvisited->vertices[unvisited->count++] = i;
    }

    new_frontier->vertices[new_frontier->count++] = ROOT_NODE_ID;
    frontier_mask[ROOT_NODE_ID] = true;
    sol->distances[ROOT_NODE_ID] = 0;

    while (new_frontier->count) {
        vertex_set_clear(new_frontier);
        vertex_set_clear(new_unvisited);

#ifdef VERBOSE
        double start_time = CycleTimer::currentSeconds();
#endif
        bottom_up_step(graph, frontier_mask, new_frontier, unvisited, new_unvisited, sol->distances);
#ifdef VERBOSE
        double end_time = CycleTimer::currentSeconds();
        printf("frontier=%-10d %.4f sec\n", (int)frontier.size(), end_time - start_time);
#endif

        vertex_set* tmp = unvisited;
        unvisited = new_unvisited;
        new_unvisited = tmp;

        std::fill(frontier_mask.begin(), frontier_mask.end(), false);
        for (int i = 0; i < new_frontier->count; i++) {
            int node = new_frontier->vertices[i];
            frontier_mask[node] = true;
        }
    }
}


void bfs_hybrid(Graph graph, solution* sol)
{
    bfs_bottom_up(graph, sol);
}
