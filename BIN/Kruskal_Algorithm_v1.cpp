// Kruskal_Algorithm_v1.cpp : Defines the entry point for the console application.

// http://en.cppreference.com/w/cpp/algorithm/iota


#include "stdafx.h"
#include "Graph_Functions.h" // Includes the header from graph functions

#include <algorithm> // For std::sort
#include <numeric> // For std::iota
//#include <limits>
#include <Windows.h>

#define WHITE 15
#define YELLOW 14


// ------------------ FUNCTION PROTOTYPES ------------------

void Kruskal(std::vector<Edge> graph, int numVertices, std::vector<Edge> &minTree, int &treeCost); // Calculates the Minimum Spanning Tree of a given graph
bool OrderCost(const Edge &left, const Edge &right); // Function that orders edges by their cost, min to max
void TreeOutput(const std::vector<Edge> tree); // Prints out the Minimum Spanning Tree


int _tmain(int argc, _TCHAR* argv[])
{
	std::vector<Edge> graph;
	std::vector<Edge> tree;

	std::string fname("graph.txt");
	int costT = 0; // Cost of the edges in Minimum Spanning Tree
	int numV = 0; // Number of vertices in the graph
	int	numE = 0; // Number of edges in the graph

	ReadGraph(fname, graph, numV, numE);
	EdgeOutput(graph, numV, numE);

	//std::cout << "\nNumber of vertices " << numV << ", number of edges " << numE << std::endl; // Test output

	Kruskal(graph, numV, tree, costT);
	TreeOutput(tree);

	std::cout << "\n\tTree cost: " << costT << std::endl; // Test output

	//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignores everything until it encounters newline or fills the stream
	std::cin.get(); // Usually newline remains on the stream after cin

	return 0;
}

// ------------------ Mini function for comparison of costs ------------------

bool OrderCost(const Edge &left, const Edge &right)
{
	return left.cost < right.cost;
}

// ------------------ MINIMUM SPANNING TREE OUTPUT ------------------

void TreeOutput(const std::vector<Edge> tree)
{
	std::cout << "\n\n------------------ Minimum spanning tree / Forest ------------------" << std::endl << std::endl;

	for (size_t i = 0; i < tree.size(); i++)
	{
		std::cout << "(" << tree[i].u << ", " << tree[i].v << ") - cost: " << tree[i].cost << std::endl;
	}

}

// ------------------ KRUSKAL'S ALGORITHM ------------------

void Kruskal(std::vector<Edge> graph, int numVertices, std::vector<Edge> &minTree, int &costTree)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
	std::cout << "\n\n\t================== KRUSKAL'S ALGORITHM ==================" << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);



	std::vector<int> cluster(numVertices + 1); // Creates a cluster with vertices + 1 because vertices start at 0
	int temp = 0; // Temporary variable for the cluster
	int tmp = 0; // Second temporary variable for the cluster

	costTree = 0; // Cost of all edges in the tree is initially 0

	std::sort(graph.begin(), graph.end(), OrderCost); // Sorts the graph by price, ASC order
	std::iota(cluster.begin(), cluster.end(), 0); // C++11 standard, fills the vector with ascending integers starting with 0

	EdgeOutput(graph, 5, 5);

	for (size_t i = 0; i < graph.size(); i++) // Travels through every Edge in the graph
	{
		std::cout << "\n\n\tCurrent cluster: "; // Helpful output
		for (size_t k = 0; k < cluster.size(); k++)
		{
			std::cout << cluster[k] << " ";
		}

		std::cout << std::endl;

		if (cluster[graph[i].u] == cluster[graph[i].v]) // Checks if they're in the same set
		{
			std::cout << "\nEdge (" << graph[i].u << ", " << graph[i].v << ") " << "was not accepted." << std::endl;
		}

		else // (u,v) doesn't creat a cycle, it adds it to the tree and update the cluster
		{
			minTree.emplace_back(graph[i].u, graph[i].v, graph[i].cost); // Adds edge (u, v) to the tree
			std::cout << "\nEdge (" << graph[i].u << ", " << graph[i].v << ") " << "was added." << std::endl;

			costTree += graph[i].cost; // Adds the cost of a new edge

			temp = cluster[graph[i].u]; // Remembers the "names" of sets, that need to be combined
			tmp = cluster[graph[i].v];

			for (size_t j = 0; j < cluster.size(); j++) // Updates sets in the cluster
			{
				if (cluster[j] == temp || cluster[j] == tmp)
					cluster[j] = graph[i].v; // Combines sets, second component dictates the new name

				// We could count how many times we adjust the cluster, if it's the same as the number of vertices, we already have an MST
				// Should prove useful for big graphs as it would eliminate the need to test every edge since we already know there's an MST
			}
		}
	}
}

