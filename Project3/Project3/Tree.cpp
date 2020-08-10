
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



/*

// create a structure to represent a node in adjacency list
struct AdjListNode
{
	int dest;
	int weight;
	struct AdjListNode* next;
};

// create a structure to represent an adjacency liat
struct AdjList
{
	struct AdjListNode* head;  // pointer to head node of list
};

// create a structure to represent a graph, which is an array of adjacency lists.
// Size of array will be number of vertices in graph
struct Graph
{
	int V;
	struct AdjList* array;
};

// the following function is to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest, int weight)
{
	struct AdjListNode* newNode =
		(struct AdjListNode*)malloc(sizeof(struct AdjListNode));
	newNode->dest = dest;
	newNode->weight = weight;
	newNode->next = NULL;
	return newNode;
}

// A utility function that creates a graph of V vertices
struct Graph* createGraph(int V)
{
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
	graph->V = V;

	// Create an array of adjacency lists.  Size of array will be V
	graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));

	// Initialize each adjacency list as empty by making head as NULL
	for (int i = 0; i < V; ++i)
		graph->array[i].head = NULL;

	return graph;
}

// Adds an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest, int weight)
{
	// Add an edge from src to dest.  A new node is added to the adjacency
	// list of src.  The node is added at the begining
	struct AdjListNode* newNode = newAdjListNode(dest, weight);
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;

	// Since graph is undirected, add an edge from dest to src also
	newNode = newAdjListNode(src, weight);
	newNode->next = graph->array[dest].head;
	graph->array[dest].head = newNode;
}

// Structure to represent a min heap node
struct MinHeapNode
{
	int  v;
	int key;
};

// Structure to represent a min heap
struct MinHeap
{
	int size;      // Number of heap nodes present currently
	int capacity;  // Capacity of min heap
	int* pos;     // This is needed for decreaseKey()
	struct MinHeapNode** array;
};

// A utility function to create a new Min Heap Node
struct MinHeapNode* newMinHeapNode(int v, int key)
{
	struct MinHeapNode* minHeapNode =
		(struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
	minHeapNode->v = v;
	minHeapNode->key = key;
	return minHeapNode;
}

// A utilit function to create a Min Heap
struct MinHeap* createMinHeap(int capacity)
{
	struct MinHeap* minHeap =
		(struct MinHeap*)malloc(sizeof(struct MinHeap));
	minHeap->pos = (int*)malloc(capacity * sizeof(int));
	minHeap->size = 0;
	minHeap->capacity = capacity;
	minHeap->array =
		(struct MinHeapNode**)malloc(capacity * sizeof(struct MinHeapNode*));
	return minHeap;
}

// A utility function to swap two nodes of min heap. Needed for min heapify
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
	struct MinHeapNode* t = *a;
	*a = *b;
	*b = t;
}

// A standard function to heapify at given idx
// This function also updates position of nodes when they are swapped.
// Position is needed for decreaseKey()
void minHeapify(struct MinHeap* minHeap, int idx)
{
	int smallest, left, right;
	smallest = idx;
	left = 2 * idx + 1;
	right = 2 * idx + 2;

	if (left < minHeap->size &&
		minHeap->array[left]->key < minHeap->array[smallest]->key)
		smallest = left;

	if (right < minHeap->size &&
		minHeap->array[right]->key < minHeap->array[smallest]->key)
		smallest = right;

	if (smallest != idx)
	{
		// The nodes to be swapped in min heap
		MinHeapNode* smallestNode = minHeap->array[smallest];
		MinHeapNode* idxNode = minHeap->array[idx];

		// Swap positions
		minHeap->pos[smallestNode->v] = idx;
		minHeap->pos[idxNode->v] = smallest;

		// Swap nodes
		swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

		minHeapify(minHeap, smallest);
	}
}

// A utility function to check if the given minHeap is ampty or not
int isEmpty(struct MinHeap* minHeap)
{
	return minHeap->size == 0;
}

// Standard function to extract minimum node from heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
	if (isEmpty(minHeap))
		return NULL;

	// Store the root node
	struct MinHeapNode* root = minHeap->array[0];

	// Replace root node with last node
	struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
	minHeap->array[0] = lastNode;

	// Update position of last node
	minHeap->pos[root->v] = minHeap->size - 1;
	minHeap->pos[lastNode->v] = 0;

	// Reduce heap size and heapify root
	--minHeap->size;
	minHeapify(minHeap, 0);

	return root;
}

// Function to decreasy key value of a given vertex v. This function
// uses pos[] of min heap to get the current index of node in min heap
void decreaseKey(struct MinHeap* minHeap, int v, int key)
{
	// Get the index of v in  heap array
	int i = minHeap->pos[v];

	// Get the node and update its key value
	minHeap->array[i]->key = key;

	// Travel up while the complete tree is not hepified.
	// This is a O(Logn) loop
	while (i && minHeap->array[i]->key < minHeap->array[(i - 1) / 2]->key)
	{
		// Swap this node with its parent
		minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
		minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
		swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

		// move to parent index
		i = (i - 1) / 2;
	}
}

// A utility function to check if a given vertex
// 'v' is in min heap or not
bool isInMinHeap(struct MinHeap* minHeap, int v)
{
	if (minHeap->pos[v] < minHeap->size)
		return true;
	return false;
}

// A utility function used to print the constructed MST
void printArr(int arr[], int n, int key[])
{
	int totalCost = 0;
	for (int i = 1; i < n; i++)
		totalCost = totalCost + key[i];

	int A[n - 1], B[n - 1];
	for (int i = 1; i < n; i++) {
		if (arr[i] < i) {
			A[i - 1] = arr[i];
			B[i - 1] = i;
		}
		else {
			A[i - 1] = i;
			B[i - 1] = arr[i];
		}
	}
	// sort the resultant MST nodes
	for (int k = 0; k < n - 2; k++) {
		for (int j = 0; j < n - k - 2; j++) {
			if ((A[j + 1] < A[j]) || ((A[j + 1] == A[j]) && (B[j + 1] < B[j]))) {
				auto tempA = A[j];
				auto tempB = B[j];
				A[j] = A[j + 1];
				B[j] = B[j + 1];
				A[j + 1] = tempA;
				B[j + 1] = tempB;
			}
		}
	}

	cout << totalCost << '\n';
	for (int j = 0; j < n - 1; j++) {
		cout << A[j] + 1 << ' ' << B[j] + 1 << '\n';
	}
}

// The main function that constructs Minimum Spanning Tree (MST)
// using Prim's algorithm
void PrimMST(struct Graph* graph)
{
	int V = graph->V;// Get the number of vertices in graph
	int parent[V];   // Array to store constructed MST
	int key[V];      // Key values used to pick minimum weight edge in cut

	// minHeap represents set E
	struct MinHeap* minHeap = createMinHeap(V);

	// Initialize min heap with all vertices. Key value of
	// all vertices (except 0th vertex) is initially infinite
	for (int v = 1; v < V; ++v)
	{
		parent[v] = -1;
		key[v] = INT_MAX;
		minHeap->array[v] = newMinHeapNode(v, key[v]);
		minHeap->pos[v] = v;
	}

	// Make key value of 0th vertex as 0 so that it
	// is extracted first
	key[0] = 0;
	minHeap->array[0] = newMinHeapNode(0, key[0]);
	minHeap->pos[0] = 0;

	// Initially size of min heap is equal to V
	minHeap->size = V;

	// In the followin loop, min heap contains all nodes
	// not yet added to MST.
	while (!isEmpty(minHeap))
	{
		// Extract the vertex with minimum key value
		struct MinHeapNode* minHeapNode = extractMin(minHeap);
		int u = minHeapNode->v; // Store the extracted vertex number

		// Traverse through all adjacent vertices of u (the extracted
		// vertex) and update their key values
		struct AdjListNode* pCrawl = graph->array[u].head;
		while (pCrawl != NULL)
		{
			int v = pCrawl->dest;

			// If v is not yet included in MST and weight of u-v is
			// less than key value of v, then update key value and
			// parent of v
			if (isInMinHeap(minHeap, v) && pCrawl->weight < key[v])
			{
				key[v] = pCrawl->weight;
				parent[v] = u;
				decreaseKey(minHeap, v, key[v]);
			}
			pCrawl = pCrawl->next;
		}
	}

	// print edges of MST
	printArr(parent, V, key);
}

// Driver program to test above functions
/*
int main()
{
	// Let us create the graph given in above fugure
	int V = 9;
	struct Graph* graph = createGraph(V);
	addEdge(graph, 0, 1, 4);
	addEdge(graph, 0, 7, 8);
	addEdge(graph, 1, 2, 8);
	addEdge(graph, 1, 7, 11);
	addEdge(graph, 2, 3, 7);
	addEdge(graph, 2, 8, 2);
	addEdge(graph, 2, 5, 4);
	addEdge(graph, 3, 4, 9);
	addEdge(graph, 3, 5, 14);
	addEdge(graph, 4, 5, 10);
	addEdge(graph, 5, 6, 2);
	addEdge(graph, 6, 7, 1);
	addEdge(graph, 6, 8, 6);
	addEdge(graph, 7, 8, 7);
	PrimMST(graph);
	return 0;
}


int main()
{

	char filename[256];
	cout << "Please type in the name of the input file, hit ENTER to complete: ";
	int V;
	int E = 0;
	fstream myfile;
	fstream myfile1;
	char input[256];
	cin >> filename;
	myfile.open(filename);
	myfile.getline(input, 256, '\n');
	V = atoi(input);

	while (!myfile.eof()) {
		myfile.getline(input, 256, '\n');
		E++;
	}
	E--;
	myfile.close();

	struct Graph* graph = createGraph(V);
	myfile1.open(filename);
	myfile1.getline(input, 256, '\n');

	string str;
	for (int i = 0; i < E; i++) {
		str.clear();
		getline(myfile1, str, '\n');
		string::size_type sy;
		int a = stoi(str, &sy) - 1;
		string subs = str.substr(sy);
		string::size_type sz;
		int b = stoi(subs, &sz) - 1;
		string subs1 = subs.substr(sz);
		int c = stoi(subs1, nullptr);
		addEdge(graph, a, b, c);
	}

	PrimMST(graph);
	return 0;
}

*/