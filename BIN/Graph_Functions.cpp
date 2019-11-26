// Graph_Functions.cpp
// Definicija metod za delo in predstavitev graphov

// http://en.cppreference.com/w/cpp/container/vector/emplace_back


#include "stdafx.h"
#include "Graph_Functions.h"

#include <fstream>
#include <iostream>


// ------------------ STRUCTURE INITIALIZATION ------------------

std::vector<Edge> graph(0); // Graph is empty

Edge::Edge() : u(0), v(0), cost(0) {} // Initializer list for the default constructor of Edge
Edge::Edge(int p, int q, int cost) : u(p), v(q), cost(cost) {} // Initializer list for the parameterized constructor of Edge

// ------------------ READ GRAPH ------------------

void ReadGraph(std::string fname, std::vector<Edge> &graph, int &numV, int &numE)
{

	std::ifstream dat(fname); // Stream for reading from file

	if (dat.is_open()) // Checks if the file could open
	{
		int i = 0; // Counter
		int u, v, cost;

		if (dat.good())
			dat >> numV >> numE; // Saves number of vertices and edges from the file
		else
			std::cout << "\nProblem with reading from file." << std::endl;

		while (!dat.eof() && i < numE)
		{
			if (dat.good())
			{
				dat >> u >> v >> cost; // Adds vertices u and v, and the cost of the edge uv to the file
				graph.emplace_back(u, v, cost); // C++11 standard
				i++;
			}

			else
				std::cout << "\nProblem with reading from file." << std::endl;
		}
	}

	else
		std::cout << "\nFile could not be opened." << std::endl;

	// Test output

	/*std::cout << "\n\tGraph output." << std::endl;

	std::cout << numV << " " << numE << std::endl;

	for (int j = 0; j < numE; j++)
	{
	std::cout << graph[j].u << " " << graph[j].v << " " << graph[j].cost << std::endl;
	}
	*/

	dat.close();

	//EdgeOutput(graph, stP, stV);
}

// ------------------ EDGE OUTPUT ------------------

void EdgeOutput(std::vector<Edge> graph, int numEdges, int numVertices)
{
	std::cout << "\nNumber of edges in the graph: " << numEdges << std::endl;
	std::cout << "\nNumber of vertices in the graph: " << numVertices << std::endl << std::endl;

	for (size_t i = 0; i < graph.size(); i++)
	{
		std::cout << "(" << graph[i].u << ", " << graph[i].v << ") - cost: " << graph[i].cost << std::endl;
	}
}

// ------------------ READ MATRIX ------------------

void ReadMatrix(std::string fname, std::vector<std::vector<int>> &adjMatrix)
{
	std::ifstream dat(fname); // Stream for reading from file

	if (dat.is_open()) // Checks if the file could open
	{
		int i = 0; // Counter
		int n; // Matrix dimension

		if (dat.good())
			dat >> n;
		else
			std::cout << "\nProblem with reading from file." << std::endl;

		adjMatrix.resize(n); // Resizes vector to length n

		for (int j = 0; j < n; j++) // Resizes every subsequent vector to length n
			adjMatrix[j].resize(n);

		while (!dat.eof() && i < n)
		{
			if (dat.good())
			{
				for (int j = 0; j < n; j++)
				{
					dat >> adjMatrix[i][j];
				}

				i++;
			}

			else
				std::cout << "\nProblem with reading from file." << std::endl;
		}
	}

	else
		std::cout << "\nFile could not be opened." << std::endl;

	dat.close();

}

// ------------------ MATRIX OUTPUT ------------------

void MatrixOutput(const std::vector<std::vector<int>> matrix)
{
	std::cout << "\n\tMatrix output." << std::endl;

	for (size_t i = 0; i < matrix.size(); i++)
	{
		std::cout << std::endl;

		for (size_t j = 0; j < matrix[i].size(); j++)
			std::cout << matrix[i][j] << " ";
	}
}