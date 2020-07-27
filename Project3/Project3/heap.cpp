#include "Global.h"
#include "Heap.h"
#include "Graph.h"
#include <iostream>
#include <string>

//Description: default constructor that initializes all the weight members of each element in the heap array to -1
//Pre-condition: an object of Heap class is created with no parameters
//Post-condition: all the weight members of each element is now -1
Heap::Heap() {
	for (int i = 0; i < 100; i++) {
		heap[i].weight = -1;
	}
}

//Description: resets all the weight members of each element in the heap array to -1
//Pre-condition: function is called with no parameters
//Post-condition: all the weight members of each element is now -1
void Heap::clearHeap() {
	for (int i = 0; i < 100; i++) {
		heap[i].weight = -1;
	}
}

//Description: will add a new node to the heap
//Pre-condition: function is called with two string variables and an int passed in
//Post-condition: a new node has been added to the heap
void Heap::insert(std::string v1, std::string v2, int w) {
	int index;

	for (int i = 0; i < 100; i++) {		// inserting the new node to the next open spot
		if (heap[i].weight == -1) {
			heap[i].vertx1 = v1;
			heap[i].vertx2 = v2;
			heap[i].weight = w;
			index = i;
			break;
		}
	}

	while (index != 0) {
		if (heap[index].weight < heap[index / 2].weight) {	// the current node's weight is smaller than its parent's, so swapping them 
			heap[index].vertx1 = heap[index / 2].vertx1;
			heap[index].vertx2 = heap[index / 2].vertx2;
			heap[index].weight = heap[index / 2].weight;
			heap[index / 2].vertx1 = v1;
			heap[index / 2].vertx2 = v2;
			heap[index / 2].weight = w;
			index = index / 2;
		}
		else {
			break;
		}
	}
}

//Description: will remove a node from the heap
//Pre-condition: function is called with two string variables and an in passed in
//Post-condition: a node(s) is removed from the heap
std::string Heap::remove(std::string& v1, std::string& v2, int w) {
	std::string min = "";
	bool v1Exist, v2Exist;

	while (min == "") {
		if (heap[0].weight == -1) {
			break;
		}
		v1Exist = false;
		v2Exist = false;
		for (int i = 0; i < 100; i++) {	// checking if either endpoint vertex exists in the visited array
			if (visited[i] == heap[0].vertx1) {
				v1Exist = true;
			}
			else if (visited[i] == heap[0].vertx2) {
				v2Exist = true;
			}
			else if (visited[i] == "") {
				break;
			}
		}
		if ((!v1Exist) || (!v2Exist)) {	// one of the endpoint vertices of the edge doesn't exist in the visited array
			for (int i = 0; i < 100; i++) {
				if (visited[i] == "") {
					if (!v1Exist) {
						visited[i] = heap[0].vertx1;
						min = heap[0].vertx1;
					}
					else {
						visited[i] = heap[0].vertx2;
						min = heap[0].vertx2;
					}
					v1 = heap[0].vertx1;
					v2 = heap[0].vertx2;
					w = heap[0].weight;
					break;
				}
			}
		}
		else {	// delete the root and adjust the heap
			if (heap[1].weight == -1) {	// checking if the root is the only node left
				heap[0].weight = -1;
				break;
			}
			else {
				for (int i = 0; i < 100; i++) {
					if (heap[i].weight == -1) {	// i-1 represents the index of the last node in the heap
						heap[0].vertx1 = heap[i - 1].vertx1;	// copying the last node to the root
						heap[0].vertx2 = heap[i - 1].vertx2;
						heap[0].weight = heap[i - 1].weight;
						heap[i - 1].weight = -1;	// "deleting" the last node
						i = 0;
						while (i < 100) {
							if ((2 * i + 1 > 99) || (heap[2 * i + 1].weight == -1) || (2 * i + 2 > 99) || (heap[2 * i + 2].weight == -1)) {	// making sure that the child nodes of ith element exist																								
								break;
							}
							if ((heap[2 * i + 1].weight > heap[i].weight) && (heap[2 * i + 2].weight > heap[i].weight)) {	// ith node is smaller than both its children														
								break;
							}
							if (heap[2 * i + 1].weight < heap[i].weight) {
								if (heap[2 * i + 1].weight < heap[2 * i + 2].weight) {	// left child of ith node is smaller than its parent and sibling	
									v1 = heap[i].vertx1;	// saving data of ith element
									v2 = heap[i].vertx2;
									w = heap[i].weight;
									heap[i].vertx1 = heap[2 * i + 1].vertx1;	// swapping data from left child and parent
									heap[i].vertx2 = heap[2 * i + 1].vertx2;
									heap[i].weight = heap[2 * i + 1].weight;
									heap[2 * i + 1].vertx1 = v1;
									heap[2 * i + 1].vertx2 = v2;
									heap[2 * i + 1].weight = w;
									i = 2 * i + 1;
									continue;
								}
							}
							if (heap[2 * i + 2].weight < heap[i].weight) {		// right child of ith node is smaller than its parent and sibling	
								if (heap[2 * i + 2].weight < heap[2 * i + 1].weight) {
									v1 = heap[i].vertx1;	// saving data of ith element
									v2 = heap[i].vertx2;
									w = heap[i].weight;
									heap[i].vertx1 = heap[2 * i + 2].vertx1;	// swapping data from right child and parent
									heap[i].vertx2 = heap[2 * i + 2].vertx2;
									heap[i].weight = heap[2 * i + 2].weight;
									heap[2 * i + 2].vertx1 = v1;
									heap[2 * i + 2].vertx2 = v2;
									heap[2 * i + 2].weight = w;
									i = 2 * i + 2;
									continue;
								}
							}
							break;
						}
						break;
					}
				}
			}
		}
	}
	return min;
}