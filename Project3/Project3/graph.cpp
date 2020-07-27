#include "Global.h"
#include "Graph.h"
#include <iostream>
#include <string>

//Description: default constructor that initializes all the elements in list array to null and all the elements in visited to ""
//Pre-condition: an object of Graph class has been created with no parameters
//Post-condition: all the elements in the list array are now null and all the elements in the visited array are now ""
Graph::Graph() {
	for (int i = 0; i < 100; i++) {
		list[i] = nullptr;
		visited[i] = "";
	}
}

//Description: will reset all of the elements in visited to ""
//Pre-condition: function is called with no parameters
//Post-condition: all of the elements in visited are now ""
void Graph::clearVisited() {
	for (int i = 0; i < 100; i++) {		// resetting visited array
		if (visited[i] == "") {
			break;
		}
		visited[i] = "";
	}
}

//Description: will insert a new vertex to the list array
//Pre-condition: function is called with a string cariable passed
//Post-condition: a new vertex has been added to the list array
void Graph::insertVertex(std::string v) {
	Node* n = new Node;
	n->vertex = v;
	n->next = nullptr;

	for (int i = 0; i < 100; i++) {		// finding an empty spot in the list array to insert new vertex
		if (list[i] == nullptr) {
			list[i] = n;
			std::cout << "Vertex " << v << " has been inserted successfully" << std::endl;
			output << "Vertex " << v << " has been inserted successfully" << std::endl;
			break;
		}
		else if (list[i]->vertex == v) {	// checking if the vertex already exists
			std::cout << "Error: the vertex " << v << " already exists!" << std::endl;
			output << "Error: the vertex " << v << " already exists!" << std::endl;
			break;
		}
	}
}

//Description: will insert an edge between two vertices
//Pre-condition: function is called with two string variables and an int passed in
//Post-condition: a new edge is created between two vertices
void Graph::insertEdge(std::string v1, std::string v2, int w) {
	int found = 0;
	Node* temp = nullptr;

	for (int i = 0; i < 100; i++) {		// ensuring that both vertices exist in the adjacency list
		if (list[i] == nullptr) {		// checking if there are anymore vertices is the adjacency list
			break;
		}
		if (list[i]->vertex == v1) {	// checking if the edge already exists
			found++;
			temp = list[i]->next;
			while (temp != nullptr) {
				if (temp->vertex == v2) {
					std::cout << "Error: the edge between " << v1 << " and " << v2 << " already exists!" << std::endl;
					output << "Error: the edge between " << v1 << " and " << v2 << " already exists!" << std::endl;
					return;
				}
				temp = temp->next;
			}
		}
		if (list[i]->vertex == v2) {	// checking if the edge already exists
			found++;
			temp = list[i]->next;
			while (temp != nullptr) {
				if (temp->vertex == v1) {
					std::cout << "Error: the edge between " << v1 << " and " << v2 << " already exists!" << std::endl;
					output << "Error: the edge between " << v1 << " and " << v2 << " already exists!" << std::endl;
					return;
				}
				temp = temp->next;
			}
		}
		if (found == 2) {	// both vertices exist
			break;
		}
	}
	if (found != 2) {
		std::cout << "Error: one (or both) of the vertices entered is not valid!" << std::endl;
		output << "Error: one (or both) of the vertices entered is not valid!" << std::endl;
		return;
	}

	for (int i = 0; i < 100; i++) {		// adding the edge to both vertices in the adjacency list
		if (list[i] != nullptr) {
			if (list[i]->vertex == v1) {
				Node* n = new Node;		// creating a new node to add to the end of the edge list of v1
				n->vertex = v2;
				n->weight = w;
				n->next = nullptr;
				temp = list[i];
				while (temp->next != nullptr) {	// moving to the end of the edge list
					temp = temp->next;
				}
				temp->next = n;
				found++;
			}
			else if (list[i]->vertex == v2) {
				Node* n = new Node;		// creating a new node to add to the end of the edge list of v1
				n->vertex = v1;
				n->weight = w;
				n->next = nullptr;
				temp = list[i];
				while (temp->next != nullptr) {
					temp = temp->next;
				}
				temp->next = n;
				found++;
			}
			if (found == 4) {	// both vertices were processed
				std::cout << "The edge between " << v1 << " and " << v2 << " has been added successfully" << std::endl;
				output << "The edge has been added successfully" << std::endl;
				break;
			}
		}
	}
}

//Description: will print the adjacency list
//Pre-condition: function is called with no parameters
//Post-condition: the adjacency list has been printed
void Graph::printGraph() {
	Node* temp = nullptr;
	//bool exist;

	std::cout << "Graph (vertex->[connected vertex|edge weight]->...): " << std::endl;
	output << "Graph (vertex->[connected vertex|edge weight]->...): " << std::endl;
	for (int i = 0; i < 100; i++) {
		if (list[i] == nullptr) {
			break;
		}
		std::cout << list[i]->vertex;
		output << list[i]->vertex;
		temp = list[i]->next;
		while (temp != nullptr) {
			std::cout << "->[" << temp->vertex << "|" << temp->weight << "]";
			output << "->[" << temp->vertex << "|" << temp->weight << "]";
			temp = temp->next;
		}
		std::cout << std::endl;
		output << std::endl;
	}
}

//Description: will decrease the weight of an edge
//Pre-condition: function is called with two string variables and an int passed in
//Post-condition: the weight of an edge hass been decreased
void Graph::decreaseWeight(std::string v1, std::string v2, int w) {
	int found = 0;
	bool negative = false;
	Node* temp = nullptr;

	for (int i = 0; i < 100; i++) {
		if (list[i] == nullptr) {
			break;
		}
		if (list[i]->vertex == v1) {
			temp = list[i]->next;
			while (temp != nullptr) {
				if (temp->vertex == v2) {
					found++;
					if (temp->weight - w < 1) {
						negative = true;
					}
					else {
						temp->weight -= w;
					}
					break;
				}
				temp = temp->next;
			}
		}
		if (list[i]->vertex == v2) {
			temp = list[i]->next;
			while (temp != nullptr) {
				if (temp->vertex == v1) {
					found++;
					if (temp->weight - w < 1) {
						negative = true;
					}
					else {
						temp->weight -= w;
					}
					break;
				}
				temp = temp->next;
			}
		}
		if (found == 2) {
			std::cout << "The edge between " << v1 << " and " << v2 << " is now " << temp->weight << std::endl;
			output << "The edge between " << v1 << " and " << v2 << " is now " << temp->weight << std::endl;
			return;
		}
		if (negative) {
			std::cout << "Error: the weight of an edge cannot be negative!" << std::endl;
			output << "Error: the weight of an edge cannot be negative!" << std::endl;
			return;
		}
	}

	if (found != 2) {
		std::cout << "Error: the edge between " << v1 << " and " << v2 << " does not exist!" << std::endl;
		output << "Error: the edge between " << v1 << " and " << v2 << " does not exist!" << std::endl;
	}
}

//Description: will delete a vertex from the adjacency list and all of its incident edges
//Pre-condition: function is called with a string parameter passed in
//Post-condition: the vertex and all of its incident edges have been deleted
void Graph::deleteVertex(std::string v) {
	for (int i = 0; i < 100; i++) {
		if (list[i] == nullptr) {
			std::cout << "Error: the vertex " << v << " does not exist!" << std::endl;
			output << "Error: the vertex " << v << " does not exist!" << std::endl;
			return;
		}
		if (list[i]->vertex == v) {
			while (list[i]->next != nullptr) {
				deleteEdge(v, list[i]->next->vertex);
			}
			delete list[i];
			list[i] = nullptr;
			for (int j = i; j < 100; j++) {
				list[j] = list[j + 1];
			}
			std::cout << "The vertex " << v << " has beed deleted" << std::endl;
			output << "The vertex " << v << " has beed deleted" << std::endl;
			break;
		}
	}
}

//Description: will delete an edge from the adjacency list
//Pre-condition: function is called with two string parameters passed in
//Post-condition: the edge is deleted from the ajacency list
void Graph::deleteEdge(std::string v1, std::string v2) {
	Node* temp = nullptr;
	Node* prev = nullptr;
	int deleted = 0;

	for (int i = 0; i < 100; i++) {
		if (list[i] == nullptr) {
			std::cout << "Error: the edge between " << v1 << " and " << v2 << " does not exist!" << std::endl;
			output << "Error: the edge between " << v1 << " and " << v2 << " does not exist!" << std::endl;
			return;
		}
		if (list[i]->vertex == v1) {
			temp = list[i]->next;
			prev = list[i];
			while (temp != nullptr) {
				if (temp->vertex == v2) {
					prev->next = temp->next;
					delete temp;
					temp = nullptr;
					deleted++;
					break;
				}
				prev = temp;
				temp = temp->next;
			}
		}
		if (list[i]->vertex == v2) {
			temp = list[i]->next;
			prev = list[i];
			while (temp != nullptr) {
				if (temp->vertex == v1) {
					prev->next = temp->next;
					delete temp;
					temp = nullptr;
					deleted++;
					break;
				}
				prev = temp;
				temp = temp->next;
			}
		}
		if (deleted == 2) {
			std::cout << "The edge between " << v1 << " and " << v2 << " has been deleted" << std::endl;
			output << "The edge between " << v1 << " and " << v2 << " has been deleted" << std::endl;
			return;
		}
	}
	std::cout << "Error: the edge between " << v1 << " and " << v2 << " does not exist!" << std::endl;
	output << "Error: the edge between " << v1 << " and " << v2 << " does not exist!" << std::endl;
}

//Description: will increase the weight of an edge
//Pre-condition: function is called with two string variables and an int passed in
//Post-condition: the weight of the edge has been increased
void Graph::increaseWeight(std::string v1, std::string v2, int w) {
	int found = 0;
	Node* temp = nullptr;

	for (int i = 0; i < 100; i++) {
		if (list[i] == nullptr) {
			break;
		}
		if (list[i]->vertex == v1) {
			temp = list[i]->next;
			while (temp != nullptr) {
				if (temp->vertex == v2) {
					found++;
					temp->weight += w;
					break;
				}
				temp = temp->next;
			}
		}
		if (list[i]->vertex == v2) {
			temp = list[i]->next;
			while (temp != nullptr) {
				if (temp->vertex == v1) {
					found++;
					temp->weight += w;
					break;
				}
				temp = temp->next;
			}
		}
		if (found == 2) {
			std::cout << "The edge between " << v1 << " and " << v2 << " is now " << temp->weight << std::endl;
			output << "The edge between " << v1 << " and " << v2 << " is now " << temp->weight << std::endl;
			return;
		}
	}

	if (found != 2) {
		std::cout << "Error: the edge between " << v1 << " and " << v2 << " does not exist!" << std::endl;
		output << "Error: the edge between " << v1 << " and " << v2 << " does not exist!" << std::endl;
	}
}