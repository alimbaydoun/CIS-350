#ifndef TREE_H
#define TREE_H
#include "Heap.h"
#include <string>
#include <vector>

class Tree : public Heap {
public:
	struct Vertex {
		std::string vertex;
		int weight;
		Vertex* left;
		Vertex* right;
	};
	Vertex* roots[100];
	std::string pathArr[100];

	Tree();
	void clear(Vertex*);
	void checkBuild();
	void callPrint();
	void build(Node*);
	bool findPath(Vertex*, std::string, int&);
	Vertex* findStart(Vertex*, std::string, std::string);
	bool search(Vertex*, std::string, std::string);
	void path(std::string, std::string);
	void printMST(Vertex*, int);
};
#endif
