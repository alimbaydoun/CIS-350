#include "Global.h"
#include "Tree.h"
#include "Heap.h"
#include <iostream>
#include <string>
#include <vector>

//Description: default constructor, that initialized all elements in roots array to null and all elements in pathArr to ""
//Pre-condition: an object of Tree class is created with no parameters
//Post-condition: all the elements in roots array are null and all elements in pathArr are ""
Tree::Tree() {
	for (int i = 0; i < 100; i++) {
		roots[i] = nullptr;
		pathArr[i] = "";
	}
}

//Description: will recursively delete the multiway tree
//Pre-condition: function is called with a Vertex pointer passed in
//Post-condition: the mutiway tree is deleted
void Tree::clear(Vertex* v) {
	if (v->left != nullptr) {	// checking if current node has a child
		clear(v->left);
	}
	if (v->right != nullptr) {	// checking if current node has a sibling
		clear(v->right);
	}
	delete v;
	v = nullptr;
}

//Description: ensures that all of the vertices in the adjacency list are a part of the MST
//Pre-condition: function is called with no parameters
//Post-condition: all of the vertices in the adjacency list are now a part of the MST
void Tree::checkBuild() {
	bool exist;
	clearHeap();	// clearing the heap

	for (int i = 0; i < 100; i++) {
		if (list[i] == nullptr) {	// if there are no more vertices, end the search
			break;
		}

		exist = false;
		for (int j = 0; j < 100; j++) {		// searching for the current vertex in the visited array
			if (list[i]->vertex == visited[j]) {	// vertex is found in the visited array
				exist = true;
				break;
			}
			else if (visited[j] == "") {	// there are no more vertices in the visited array
				break;
			}
		}
		if (!exist) {
			build(list[i]);
			checkBuild();
			return;
		}
	}
}

//Description: ensures that all of the separate MST are printed, and then are deleted
//Pre-condition: function is called with no parameters
//Post-condition: all of the separate MST are printed, and are deleted
void Tree::callPrint() {
	for (int i = 0; roots[i] != nullptr; i++) {
		printMST(roots[i], 0);
		std::cout << std::endl;
		output << std::endl;
	}
	for (int i = 0; roots[i] != nullptr; i++) {	// clearing the tree
		clear(roots[i]);
		roots[i] = nullptr;
	}
}

//Description: will build the MST
//Pre-condition: function is called with a Node pointer passed in
//Post-condition: the MST is built
void Tree::build(Node* vertx) {
	bool done = false, exist;
	std::string v1 = "", v2 = "", node = vertx->vertex;
	Vertex* temp = nullptr;
	Node* curr = nullptr;
	int index;

	Vertex* n = new Vertex;		// creating a new Vertex node
	n->vertex = vertx->vertex;
	n->left = nullptr;
	n->right = nullptr;

	for (int i = 0; i < 100; i++) {	// finding the first nullptr in roots and making that point to the new Vertex node
		if (roots[i] == nullptr) {
			roots[i] = n;
			temp = n;	// making temp point to the newly created Vertex node
			index = i;
			break;
		}
	}

	for (int i = 0; i < 100; i++) {	// adding the vertex member of vertx to the visited array
		if (visited[i] == "") {
			visited[i] = vertx->vertex;
			break;
		}
	}

	while (!done) {
		for (int i = 0; i < 100; i++) {
			if (list[i]->vertex == node) {
				curr = list[i];
				break;
			}
		}
		v1 = curr->vertex;
		while (curr->next != nullptr) {	// inserting each node in the adjacency list of a vertex to the heap
			curr = curr->next;
			exist = false;
			for (int i = 0; i < 100; i++) {		// checking if the vertex of the current node exists in the visited array
				if (visited[i] == curr->vertex) {
					exist = true;
					break;
				}
				if (visited[i] == "") {
					break;
				}
			}
			if (!exist) {
				insert(v1, curr->vertex, curr->weight);
			}
		}

		node = remove(v1, v2, 0);
		if (node == "") {
			done = true;
		}
		else {
			search(roots[index], v1, v2);	// finding the appropritate spot to add a new Vertex node
		}
	}
}

//Description: will search for the appropriate spot to add a new node to the multiway tree
//Pre-condition: function is called with a Vertex pointer and two string variables passed in
//Post-condition: a new node has been added to the multiway tree
bool Tree::search(Vertex* temp, std::string v1, std::string v2) {
	bool exit;

	if (temp->vertex == v1) {
		Vertex* m = new Vertex;	// creating a new Vertex node and setting its vertex member to node variable
		m->vertex = v2;
		m->left = nullptr;
		m->right = nullptr;

		if (temp->left == nullptr) {
			temp->left = m;
		}
		else {
			temp = temp->left;
			while (temp->right != nullptr) {
				temp = temp->right;
			}
			temp->right = m;
		}
		return true;
	}
	if (temp->left != nullptr) {
		exit = search(temp->left, v1, v2);
		if (exit) {
			return true;
		}
	}
	if (temp->right != nullptr) {
		exit = search(temp->right, v1, v2);
		if (exit) {
			return true;
		}
	}
	return false;
}

//Description: determines the path from one vertex to another
//Pre-condition: function is called with two string parameters passed in
//Post-condition: the path has been printed
void Tree::path(std::string v1, std::string v2) {
	bool reverse = false, found;
	int pathWeight = 0, depth = 0, i = 0;
	Vertex* temp = roots[0];

	for (int i = 0; i < 100; i++) {	// resetting pathArr
		pathArr[i] = "";
	}

	while (temp != nullptr) {
		temp = findStart(temp, v1, v2);
		if (temp->vertex == v1) {
			pathWeight -= temp->weight;
			found = findPath(temp, v2, pathWeight);
			if (found) {
				for (int i = 0; i < 100; i++) {
					if (pathArr[i] != "") {
						break;
					}
					for (int j = 0; j < depth; j++) {
						std::cout << ".";
						output << ".";
					}
					depth++;
					std::cout << pathArr[i] << std::endl;
					output << pathArr[i] << std::endl;
				}
				std::cout << "Path Weight = " << pathWeight << std::endl;
				output << "Path Weight = " << pathWeight << std::endl;
				break;
			}
			else {
				std::cout << "Error: " << v1 << " and " << v2 << " are not on the same graph!" << std::endl;
				output << "Error: " << v1 << " and " << v2 << " are not on the same graph!" << std::endl;
				return;
			}
		}
		else if (temp->vertex == v2) {
			pathWeight -= temp->weight;
			found = findPath(temp, v1, pathWeight);
			if (found) {
				for (int i = 0; i < 100; i++) {
					if (pathArr[i] == "") {
						break;
					}
					for (int j = 0; j < depth; j++) {
						std::cout << ".";
						output << ".";
					}
					depth++;
					std::cout << pathArr[i] << std::endl;
					output << pathArr[i] << std::endl;
				}
				std::cout << "Path Weight = " << pathWeight << std::endl;
				output << "Path Weight = " << pathWeight << std::endl;
				break;
			}
			else {
				std::cout << "Error: " << v1 << " and " << v2 << " are not on the same graph!" << std::endl;
				output << "Error: " << v1 << " and " << v2 << " are not on the same graph!" << std::endl;
				return;
			}
		}
		i++;
		temp = roots[i];
	}
}

//Description: will look for the start of the path from one vertex to another
//Pre-condition: function is called with a Vertex pointer and two string variables passed in
//Post-condition: the start of the path has been found and returned
Tree::Vertex* Tree::findStart(Vertex* temp, std::string v1, std::string v2) {
	if ((temp->vertex == v1) || (temp->vertex == v2)) {
		return temp;
	}

	if (temp->left != nullptr) {
		temp = findStart(temp->left, v1, v2);
		if (temp != nullptr) {
			if ((temp->vertex == v1) || (temp->vertex == v2)) {
				return temp;
			}
		}
	}
	if (temp->right != nullptr) {
		temp = findStart(temp->right, v1, v2);
		if (temp != nullptr) {
			if ((temp->vertex == v1) || (temp->vertex == v2)) {
				return temp;
			}
		}
	}
	temp = nullptr;
	return temp;
}

//Description: determines the path from one vertex to another and its weight
//Pre-condition: function is called with a Vertex pointer, a string variable, and an int passed in
//Post-condition: the path has been stored in the pathArr and weight of the path has been stored in pathWeight
bool Tree::findPath(Vertex* temp, std::string v, int& pathWeight) {
	pathWeight += temp->weight;
	for (int i = 0; i < 100; i++) {
		if (pathArr[i] == "") {
			pathArr[i] = temp->vertex;
		}
	}

	if (temp->vertex == v) {
		return true;
	}
	if (temp->left != nullptr) {
		if (findPath(temp->left, v, pathWeight)) {
			return true;
		}
	}
	if (temp->right != nullptr) {
		if (findPath(temp->right, v, pathWeight)) {
			return true;
		}
	}

	pathWeight -= temp->weight;
	for (int i = 0; i < 100; i++) {
		if (pathArr[i] == temp->vertex) {
			pathArr[i] = "";
		}
	}
	return false;
}

//Description: will print the MST
//Pre-condition: function is called with a Vertex pointer and an int passed in
//Post-condition: the MST has been printed
void Tree::printMST(Vertex* node, int depth) {
	for (int i = 0; i < depth; i++) {	// printing the depth of the current node
		std::cout << ".";
		output << ".";
	}
	std::cout << node->vertex << std::endl;
	output << node->vertex << std::endl;

	if (node->left != nullptr) {	// will print left child of current node
		printMST(node->left, depth + 1);
	}
	if (node->right != nullptr) {	// will print right sibling of current node
		printMST(node->right, depth);
	}
}