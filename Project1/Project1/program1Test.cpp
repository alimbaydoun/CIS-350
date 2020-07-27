/** program1Test.cpp
 *
 * Desecription: A Test Program for Program 1
 */

#include <iostream>
#include <string>
#include "SortedArray.h"

using namespace std;


const int N = 1787;
const int M = 2357;

int main()
{
	SortedArray<int> q;
	SortedArray<string> animals;

	string str1[] = { "zebra", "tiger", "lion", "dog", "monkey", "snake", "turkey",
		"cat", "duck", "alligator" };

	int minVal1, maxVal1;
	int i, j;

	int index;

	for (i = N; i != 0; i = (i + N) % M)
		q.insert(i);

	cout << "Completed first round of insertions" << endl;

	for (j = 1; !q.empty(); j++)
	{
		minVal1 = q.findMin();
		q.deleteMin();
		if (minVal1 != j)
			cout << "OOPS!!!!!" << minVal1 << " " << j << endl;

		maxVal1 = q.findMax();
		q.deleteMax();
		if (maxVal1 != M - j)
			cout << "OOPS!!!!!" << maxVal1 << " " << (M - j) << endl;
	}

	cout << "Completed first round of deletions" << endl;

	for (i = N; i != 0; i = (i + N) % M)
		q.insert(i);

	cout << "Completed second round of insertions" << endl;

	for (i = 0; i < M - 5; i += 2)
	{
		q.deleteMin(); q.deleteMax();
	}

	while (!q.empty()) {
		cout << q.findMin() << endl;
		cout << q.findMax() << endl;
		q.deleteMin();
		q.deleteMax();
	}

	cout << "Completed the Integer Array test" << endl << endl;

	for (i = 0; i < 10; i++) {
		animals.insert(str1[i]);
	}

	cout << "Animal list: " << endl;
	animals.print(cout, '\n');
	cout << endl << endl;

	index = animals.binarySearch("lion");
	if (index >= 0) {
		cout << animals[index] << " is found in the list." << endl;
	}
	else {
		cout << "OOPS!!!!!" << "Lion should be in the list." << endl;
	}

	index = animals.binarySearch("bear");
	if (index >= 0) {
		cout << "OOPS!!!!!" << "Bear should not be in the list." << endl;
	}
	else {
		cout << "Bear is not found in the list." << endl;
	}

	SortedArray<string> animalsCopy(animals);

	if (animalsCopy.equals(animals)) {
		cout << "Correct! " << "The two animal lists are the same." << endl;
	}
	else {
		cout << "OOPS!!!!!" << "They should be equal" << endl;
	}

	animalsCopy.deleteMin();
	animalsCopy.deleteMax();

	cout << endl << "Animal list after the deletion: " << endl;
	animalsCopy.print(cout, '\n');
	cout << endl << endl;

	cout << "Completed the String Array test" << endl;

	return 0;
}
