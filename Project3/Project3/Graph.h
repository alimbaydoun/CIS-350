#ifndef GRAPH_H
#define GRAPH_H
#include <string>

class Graph {
public:
	struct Node {
		std::string vertex;
		int weight;
		Node* next;
	};
	std::string visited[100];
	Node* list[100];

	Graph();
	void clearVisited();
	void insertVertex(std::string);
	void insertEdge(std::string, std::string, int);
	void printGraph();
	void decreaseWeight(std::string, std::string, int);
	void deleteVertex(std::string);
	void deleteEdge(std::string, std::string);
	void increaseWeight(std::string, std::string, int);
};

#endif 