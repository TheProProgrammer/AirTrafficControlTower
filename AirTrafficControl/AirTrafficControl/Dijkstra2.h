#include <iostream>
#include <vector>
using namespace std;
 
int NO_PARENT = -1;

string airport_names[] = {
    "Jinnah International (KHI)",
    "Gwadar International (GWD)",
    "Quetta International (UET)",
    "Allama Iqbal International (LHE)",
    "Islamabad International (ISB)",
    "Bacha Khan International (PSW)",
    "Skardu International (SKD)"};

void printPath(int currentVertex, vector<int> parents)
{
    if (currentVertex == NO_PARENT) {
        return;
    }
    printPath(parents[currentVertex], parents);
    cout << airport_names[currentVertex] << " -> ";
}
void printSolution(int startVertex, int endVertex, vector<int> distances,vector<int> parents)
{
    int nVertices = distances.size();
    for (int vertexIndex = 0; vertexIndex < nVertices;
         vertexIndex++) {
        if (vertexIndex != startVertex && vertexIndex == endVertex) {
            cout << "\n" << airport_names[startVertex] << " -> ";
            cout << airport_names[vertexIndex] << " \t\t ";
            cout << "\nDistance of trip: " << distances[vertexIndex] << "\t\t";
            cout << "\nIn accordance to weather conditions, route to follow:\n";
            printPath(vertexIndex, parents);
        }
    }
}
void dijkstra(vector<vector<int> > adjacencyMatrix,int startVertex, int endVertex)
{
    int nVertices = adjacencyMatrix[0].size();
    vector<int> shortestDistances(nVertices);
    vector<bool> added(nVertices);
    for (int vertexIndex = 0; vertexIndex < nVertices;vertexIndex++)
    {
        shortestDistances[vertexIndex] = INT_MAX;
        added[vertexIndex] = false;
    }
    shortestDistances[startVertex] = 0;
    vector<int> parents(nVertices);
    parents[startVertex] = NO_PARENT;
    for (int i = 1; i < nVertices; i++)
    {
        int nearestVertex = -1;
        int shortestDistance = INT_MAX;
        for (int vertexIndex = 0; vertexIndex < nVertices;vertexIndex++)
        {
            if (!added[vertexIndex]&& shortestDistances[vertexIndex]< shortestDistance)
            {
                nearestVertex = vertexIndex;
                shortestDistance= shortestDistances[vertexIndex];
            }
        }
        added[nearestVertex] = true;
        for (int vertexIndex = 0; vertexIndex < nVertices;vertexIndex++)
        {
            int edgeDistance= adjacencyMatrix[nearestVertex][vertexIndex];
            if (edgeDistance > 0 && ((shortestDistance + edgeDistance) < shortestDistances[vertexIndex]))
            {
                parents[vertexIndex] = nearestVertex;
                shortestDistances[vertexIndex] = shortestDistance + edgeDistance;
            }
        }
    }
 
    printSolution(startVertex,endVertex, shortestDistances, parents);
}