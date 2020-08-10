
#ifndef HEAP_H
#define HEAP_H
#include "Graph.h"
#include <string>

class Heap : public Graph {
protected:
	struct Data {
		std::string vertx1;
		std::string vertx2;
		int weight;
	};
	Data heap[100];

public:
	Heap();
	void clearHeap();
	void insert(std::string, std::string, int);
	std::string remove(std::string&, std::string&, int);
};

#endif