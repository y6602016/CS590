#include <iostream>
#include <set>
#include <queue>

#include "graph.h"

using namespace std;

Graph::Graph(int nodes)
{
    this->nodes = nodes;
    this->matrix = new int*[nodes];

    for (int i = 0; i < nodes; ++i) {
        (this->matrix)[i] = new int[nodes];

        for (int j = 0; j < nodes; ++j) {
            (this->matrix)[i][j] = NO_EDGE;
        }
    }
}

Graph::Graph(int **matrix, int nodes) {
    this->nodes = nodes;
    this->matrix = new int*[nodes];

    for (int i = 0; i < nodes; ++i) {
        (this->matrix)[i] = new int[nodes];

        for (int j = 0; j < nodes; ++j) {
            (this->matrix)[i][j] = matrix[i][j];
        }
    }
}

Graph::~Graph()
{
    for (int i = 0; i < this->nodes; ++i) {
        delete[] (this->matrix)[i];
    }
    delete[] this->matrix;
}

bool Graph::set_edge(int i, int j, int edge)
{
    if (i < this->nodes && j < this->nodes && i >= 0 && j >= 0) {
        (this->matrix)[i][j] = edge;
        return true;
    }

    return false;
}

void Graph::dfs()
{

}
void Graph::dfs(int start, set<int> *visited)
{
    
}
void Graph::bfs(int start)
{
    
}
void Graph::bfs(int start, set<int> *visited)
{

}

