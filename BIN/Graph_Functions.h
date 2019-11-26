// Graph_Functions.h
// Declaration of methods and data structures needed for working with graphs
// http://www.umich.edu/~eecs381/handouts/CppHeaderFileGuidelines.pdf
// http://stackoverflow.com/questions/6500313/c-why-should-new-be-used-as-little-as-possible

// #pragma once - Not standard
#ifndef GRAPH_FUNCTIONS_H
#define GRAPH_FUNCTIONS_H
#endif

#include <vector>
//#include <set>
//#include <string>
//#include <iosfwd>
#include <iostream>

// ------------------ DATA STRUCTURES ------------------

struct Edge // Structure for the presentation of an edge
{
	Edge(); // Default constructor for Edge
	Edge(int p, int q, int cost); //  Parameterized constructor for Edge
	int u; // Vertex u
	int v; // Vertex v
	int cost; // Edge cost
};


// ------------------ FUNCTIONS ------------------

void EdgeOutput(std::vector<Edge> graph, int numEdges, int numVertices); // Prints all edges in a graph
void ReadGraph(std::string fname, std::vector<Edge> &graph, int &numV, int &numE); // Reads the graph from a file
void ReadMatrix(std::string fname, std::vector<std::vector<int>> &adjMatrix); // Reads the graph from a file in matrix form
void MatrixOutput(const std::vector<std::vector<int>> matrix); // Prints the matrix