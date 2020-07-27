#include "Global.h"
#include "Graph.h"
#include "Heap.h"
#include "Tree.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

std::ofstream output;

int main() {
	ifstream input;
	string vertex, vertex2, fileName;
	int num = -1, weight, selection = 1;
	Tree tree;

	output.open("output.txt");

	cout << "\t\tWelcome to my Dynamic MST Program" << endl << endl;
	output << "\t\tWelcome to my Dynamic MST Program" << endl << endl;

	do {
		if (selection != 1) {
			cout << "Error: invalid input!" << endl;
			cout << "Please try again" << endl << endl;
			output << "Error: invalid input!" << endl;
			output << "Please try again" << endl << endl;
		}

		cout << "1. Enter data through a file" << endl;
		cout << "2. Enter data through keyboard" << endl;
		cout << "Select One of the Above: ";
		cin >> selection;
		output << "1. Enter data through a file" << endl;
		output << "2. Enter data through keyboard" << endl;
		output << "Select One of the Above: ";
		output << selection << endl;
	} while ((selection != 1) && (selection != 2));

	if (selection == 1) {	// user wants to enter initial data through a file
		cout << "Enter the file name: ";
		cin >> fileName;
		output << "Enter the file name: " << fileName << endl;
		input.open(fileName.c_str());
		if (!input.is_open()) {	// checking if file exists
			cout << "Error: file does not exist!" << endl;
			output << "Error: file does not exist!" << endl;
		}
		else {
			input >> num;	// getting number of vertices
			if (num == -1) {	// checking if the file is empty
				cout << "Error: file is empty!" << endl;
				output << "Error: file is empty!" << endl;
			}
			else {
				for (int i = 0; i < num; i++) {	// inserting each vertex to the adjacency list
					input >> vertex;
					tree.insertVertex(vertex);
				}
				input >> num;	// getting number of edges
				for (int i = 0; i < num; i++) {		// adding each edge to the adjacency list
					input >> vertex;
					input >> vertex2;
					input >> weight;
					tree.insertEdge(vertex, vertex2, weight);
				}
			}
		}
		input.close();
	}
	else { // user will enter initial data through keyboard
		cout << "\nEnter the number of vertices: ";
		cin >> num;
		output << "\nEnter the number of vertices: " << num;
		for (int i = 0; i < num; i++) {	// inserting all of the vertices in the adjacency list
			cout << "Vertex: ";
			cin >> vertex;
			output << "Vertex: " << vertex;
			tree.insertVertex(vertex);
		}
		cout << "\nEnter the number of edges: ";
		cin >> num;
		output << "\nEnter the number of edges: " << num;
		for (int i = 0; i < num; i++) {		// adding all of the edges in the adjacency list
			cout << "First vertex: ";
			cin >> vertex;
			cout << "Second vertex: ";
			cin >> vertex2;
			cout << "Weight: ";
			cin >> weight;
			output << "First vertex: " << vertex;
			output << "Second vertex: " << vertex2;
			output << "Weight: " << weight;
			tree.insertEdge(vertex, vertex2, weight);
		}
	}

	do {
		cout << "---------------------------------------------------------------------" << endl;
		cout << "Directives List" << endl;
		cout << "1. Print Graph" << endl;
		cout << "2. Print MST" << endl;
		cout << "3. Path" << endl;
		cout << "4. Insert Vertex" << endl;
		cout << "5. Insert Edge" << endl;
		cout << "6. Delete Vertex" << endl;
		cout << "7. Delete Edge" << endl;
		cout << "8. Increase Weight" << endl;
		cout << "9. Decrease Weight" << endl;
		cout << "10. Quit" << endl;
		cout << "Select One of the Above: ";
		output << "---------------------------------------------------------------------" << endl;
		output << "Directives List" << endl;
		output << "1. Print Graph" << endl;
		output << "2. Print MST" << endl;
		output << "3. Path" << endl;
		output << "4. Insert Vertex" << endl;
		output << "5. Insert Edge" << endl;
		output << "6. Delete Vertex" << endl;
		output << "7. Delete Edge" << endl;
		output << "8. Increase Weight" << endl;
		output << "9. Decrease Weight" << endl;
		output << "10. Quit" << endl;
		output << "Select One of the Above: ";
		cin >> selection;
		output << selection << endl;

		switch (selection) {
		case 1:
			tree.Graph::printGraph();
			break;
		case 2:
			tree.clearVisited();
			tree.checkBuild();
			tree.callPrint();
			//tree.printMST(tree.roots[0], 0);
			break;
		case 3:
			cout << "Enter the starting vertex: ";
			output << "Enter the starting vertex: ";
			cin >> vertex;
			output << vertex << endl;
			cout << "Enter the end vertex: ";
			output << "Enter the end vertex: ";
			cin >> vertex2;
			output << vertex2 << endl;
			tree.clearVisited();
			tree.checkBuild();
			tree.path(vertex, vertex2);
			break;
		case 4:
			cout << "\nEnter vertex identifier: ";
			output << "\nEnter vertex identifier: ";
			cin >> vertex;
			output << vertex;
			tree.Graph::insertVertex(vertex);
			break;
		case 5:
			cout << "\nEnter the first endpoint vertex: ";
			output << "\nEnter the first endpoint vertex: ";
			cin >> vertex;
			output << vertex << endl;
			cout << "Enter the second endpoint vertex: ";
			output << "Enter the second endpoint vertex: ";
			cin >> vertex2;
			output << vertex2 << endl;
			cout << "Enter the weight: ";
			output << "Enter the weight: ";
			cin >> weight;
			output << weight << endl;
			tree.Graph::insertEdge(vertex, vertex2, weight);
			break;
		case 6:
			cout << "Enter the vertex: ";
			output << "Enter the vertex: ";
			cin >> vertex;
			output << vertex << endl;
			tree.Graph::deleteVertex(vertex);
			break;
		case 7:
			cout << "Enter the first endpoint vertex: ";
			output << "Enter the first endpoint vertex: ";
			cin >> vertex;
			output << vertex << endl;
			cout << "Enter the second endpoint vertex: ";
			output << "Enter the second endpoint vertex: ";
			cin >> vertex2;
			output << vertex2 << endl;
			tree.Graph::deleteEdge(vertex, vertex2);
			break;
		case 8:
			cout << "Enter the first endpoint vertex: ";
			output << "Enter the first endpoint vertex: ";
			cin >> vertex;
			output << vertex << endl;
			cout << "Enter the second endpoint vertex: ";
			output << "Enter the second endpoint vertex: ";
			cin >> vertex2;
			output << vertex2 << endl;
			cout << "Enter the amount to increase the edge by: ";
			output << "Enter the amount to increase the edge by: ";
			cin >> weight;
			output << weight << endl;
			tree.Graph::increaseWeight(vertex, vertex2, weight);
			break;
		case 9:
			cout << "Enter the first endpoint vertex: ";
			output << "Enter the first endpoint vertex: ";
			cin >> vertex;
			output << vertex << endl;
			cout << "Enter the second endpoint vertex: ";
			output << "Enter the second endpoint vertex: ";
			cin >> vertex2;
			output << vertex2 << endl;
			cout << "Enter the amount to decrease the edge by: ";
			output << "Enter the amount to decrease the edge by: ";
			cin >> weight;
			output << weight << endl;
			tree.Graph::decreaseWeight(vertex, vertex2, weight);
			break;
		case 10:
			cout << "\nThank You for Using this Program!" << endl;
			output << "\nThank You for Using this Program!" << endl;
			break;
		default:
			cout << "\nError: invalid input" << endl;
			cout << "Please try again" << endl;
			output << "\nError: invalid input" << endl;
			output << "Please try again" << endl;
		}
	} while (selection != 10);

	output.close();

	system("pause");
	return 0;
}