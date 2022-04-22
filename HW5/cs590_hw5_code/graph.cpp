#include <iostream>
#include <set>
#include <queue>

#include "graph.h"

using namespace std;

Graph::Graph(int nodes)
{
    this->nodes = nodes;
    this->matrix = new int *[nodes];

    for (int i = 0; i < nodes; ++i)
    {
        (this->matrix)[i] = new int[nodes];

        for (int j = 0; j < nodes; ++j)
        {
            (this->matrix)[i][j] = 0;
        }
    }
}

Graph::Graph(int **matrix, int nodes)
{
    this->nodes = nodes;
    this->matrix = new int *[nodes];

    for (int i = 0; i < nodes; ++i)
    {
        (this->matrix)[i] = new int[nodes];

        for (int j = 0; j < nodes; ++j)
        {
            (this->matrix)[i][j] = matrix[i][j];
        }
    }
}

Graph::~Graph()
{
    for (int i = 0; i < this->nodes; ++i)
    {
        delete[](this->matrix)[i];
    }
    delete[] this->matrix;
}

bool Graph::set_edge(int i, int j, int edge)
{
    if (i < this->nodes && j < this->nodes && i >= 0 && j >= 0)
    {
        (this->matrix)[i][j] = edge;
        return true;
    }

    return false;
}

void Graph::dfs()
{
    set<int> visited;
    for (int i = 0; i < this->nodes; i++)
    {
        if (visited.find(i) == visited.end())
        {
            // if the node is not in visited, explore it by dfs
            this->dfs(i, &visited);
        }
    }
}
void Graph::dfs(int start, set<int> *visited)
{
    // add the node into visited set
    visited->insert(start);
    cout << start << " ";
    // explore matrix to find next node
    for (int j = 0; j < this->nodes; j++)
    {
        if (((this->matrix)[start][j] != 0) && (visited->find(j) == visited->end()))
        {
            this->dfs(j, visited);
        }
    }
}
void Graph::bfs(int start)
{
    if (start > nodes - 1 || start < 0)
    {
        cout << "Not valid" << endl;
        return;
    }

    set<int> visited;
    this->bfs(start, &visited);
}
void Graph::bfs(int start, set<int> *visited)
{
    queue<int> queue;
    queue.push(start);
    visited->insert(start);

    while (!queue.empty())
    {
        int curr_node = queue.front();
        queue.pop();

        cout << curr_node << " ";

        for (int j = 0; j < this->nodes; j++)
        {
            if (((this->matrix)[curr_node][j] != 0) && (visited->find(j) == visited->end()))
            {
                queue.push(j);
                visited->insert(j);
            }
        }
    }
}
