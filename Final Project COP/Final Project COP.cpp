// Final Project COP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <random>
#include <vector>

using namespace std;


class WeightUndirectedGraph { 
    vector<pair<int, int>> *adjListGraph; //the first value will be the vertex name, and THE second will be the weight
    int vertices;
    int numOfRoads = 0; 
public:
    WeightUndirectedGraph(int numOfVertices) { //constructor for graph
        vertices = numOfVertices;
        adjListGraph = new vector<pair<int, int>>[vertices];
        
    }

    int getNumOfEdges() {
        return numOfRoads;
    }

    void addEdge(int vertexA, int vertexB, int dWeight) { //have to add edges to both placces, as the graph is undirected
        if (vertexA == vertexB) //incase we generate the same numbers
            return;
        adjListGraph[vertexA].push_back(make_pair(vertexB, dWeight));
        adjListGraph[vertexB].push_back(make_pair(vertexA, dWeight));
        numOfRoads++;
    }

    bool checkEdge(int vertexA, int vertexB) { // we will be checking if an edge already exists
        bool tick = false;

        for (int i = 0; adjListGraph[vertexA].size() > i; i++) {
            if (adjListGraph[vertexA][i].first != NULL && adjListGraph[vertexA][i].first == vertexB) {
                tick = true;
                break;
           }
        }
        return tick;
    }

    void generateGraph() {  //this is our function to create random number of graphs
         //will COUNT the number of roads we have currentl
        for (int i = 0; i < vertices; i++) {
            while (adjListGraph[i].size() < 4) { // we are filling up the graph with 4 edges per vertex
                if (adjListGraph[i].size() > 2 && i > (.7 * vertices)) { //once it fills up twice we are not going to fill it anymore, after 70%
                    break;
                }
                int randomNumberHelper = vertices - i;
                int randomVertex = rand() % randomNumberHelper + i;
                //we are going to look for edges with higher vertex number to make it quicker to find random
                if (i > (.7 * vertices)) {
                    randomNumberHelper = vertices - .7 * vertices;
                    //WE want the the last 30 precent of the problem to be the stuff randomly generated
                    randomVertex = rand() % randomNumberHelper + (.7 * vertices - 1);
                }
               
                int randomWeight = rand() % 100 + 1; // km between roads 
                if (checkEdge(i, randomVertex) && checkEdge(randomVertex, i)) {
                    continue;
                }
                else {
                    if (adjListGraph[randomVertex].size() >= 4) { // we check if the other vertex has 4 edges already or not
                        continue;
                    } //if it doesn't then we add it
                    addEdge(i, randomVertex, randomWeight);
                }
            }
        }
        
    }

    void printGraph() {
        for (int i = 0; vertices > i; i++) {
            cout << "Vertex " << i << " : ";
            for (auto itr : adjListGraph[i]) {
                cout << itr.first << " - " << itr.second << ", " ; 
            }
            cout << endl;
        }
    }
};

int main()
{
    int sizeOfCountry = 0;
    cout << "*********Welcome to Triple A’s Delivery service*********" << endl;
    cout << "Enter the Size of your Country(Area in km^2): " << endl;
    cin >> sizeOfCountry;

    WeightUndirectedGraph g(100000);
    
    g.generateGraph();
    cout << g.getNumOfEdges() << endl;
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging men
