#include <iostream>
using namespace std;

#define V 7

string airport_names[] = {
    "Jinnah International (KHI)",
    "Gwadar International (GWD)",
    "Quetta International (UET)",
    "Allama Iqbal International (LHE)",
    "Islamabad International (ISB)",
    "Bacha Khan International (PSW)",
    "Skardu International (SKD)"};
int resultants[V][V];
void dijkstra(vector<vector<int>> adjacencyMatrix,int startVertex, int endVertex)
{
    int currentPathDist = 0;
    int distances[V];
    bool visited[V];
    
    for(int i = 0; i<V; i++)
        distances[i] = INT_MAX;
    for(int i = 0; i<V; i++)
        visited[i] = false;

    int curr = endVertex;
    for (int j = 0; j < V; j++)
    {
        cout << airport_names[curr] << " -> ";
        visited[curr] = true;
        resultant [curr] = currentPathDist;

        //get the distances from all points
        for(int i = 0; i<V; i++)
        {
            if(adjacencyMatrix[curr][i] != 0)
            {
                distances[i] = currentPathDist + adjacencyMatrix[curr][i];
            }
            else
                distances[i] = INT_MAX;
        }
        //find the shortest one
        int shortestOneNext = NULL;
        for (int i = 1; i < V; i++)
        {
            if (shortestOneNext != NULL)
            {
                if(distances[i] < distances[shortestOneNext]+currentPathDist && !visited[i])
                    shortestOneNext = i;
            }
            else
            {
                if(!visited[i] && adjacencyMatrix[curr][i] != 0)
                    shortestOneNext = i;
            }
        }
        currentPathDist += adjacencyMatrix[curr][shortestOneNext];
        curr = shortestOneNext;
    }
    /*
    for (int i = 0; i<V; i++)
    {
        cout << resultant[i] << ", ";
    }*/
}