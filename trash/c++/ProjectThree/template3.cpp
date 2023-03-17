/*
 *    Data Structures Featuring C++  (c) 2022 Katia Papakonstantinopoulou, based on Sridhar Radhakrishnan's files
 */
#include <iostream>
#include "BinarySearchTree.h"

using namespace std;

// --------------------------------------------------------------


// bubble sort algorithm with D number of comparisons allowed
int* bubbleSort(int* arr, int numElements, int D)
{
	int numComp = 0; // used to count the number of comparisons and to check with D

	int* arrCopy = new int[numElements]; // making a copy of arr as this is an inplace sorting algorithm
										// we want to retain the ordering of arr for shell sort 
	for (int i = 0; i < numElements; i++)
		arrCopy[i] = arr[i];

	// bubble sort starts
	for (int i = 0; i < numElements; i++)
	{
		for (int j = 0; j < numElements - 1; j++)
		{
			numComp++; // incrementing the number of comparisons done right before 
						// the if condition where the comparison happens each time
			if (numComp >= D) // checking for number of comparisons
				return arrCopy; // return the not necessarily sorted array = approximately sorted array

			if (arrCopy[j] > arrCopy[j + 1])
			{
				// swap
				int temp = arrCopy[j];
				arrCopy[j] = arrCopy[j + 1];
				arrCopy[j + 1] = temp;
			}
		}
	}
	// return the completely sorted array
	return arrCopy;
}

// shell sort algorithm with D number of comparisons allowed
int* shellSort(int* arr, int numElements, int D)
{
	int j;
	int numComp = 0;

	// need not make a copy of the arr array since shell sort is performed later/last

	// Start with a largest increment, then reduce by factors of 3 
	for (int inc = numElements / 3; inc > 1; inc /= 3)
	{
		// Insertion sort for the increment length
		for (int i = inc; i < numElements; ++i)
		{
			int temp = arr[i];
			j = i - inc;

			numComp++; // incrementing the number of comparisons done right before 
						// the if condition where the comparison happens each time
			if (numComp >= D) // checking for number of comparisons
				return arr; // return the not necessarily sorted array = approximately sorted array

			while ((j >= 0) && (arr[j] > temp))
			{
				arr[j + inc] = arr[j];
				j = j - inc;
			}
			arr[j + inc] = temp;
		}
	}
	// Insertion sort for the increment length = 1; force length 1 in case of inc/3 == 0
	for (int i = 1; i < numElements; ++i)
	{
		int temp = arr[i];
		j = i - 1;

		numComp++; // incrementing the number of comparisons done right before 
					// the if condition where the comparison happens each time
		if (numComp >= D) // checking for number of comparisons
			return arr; // return the not necessarily sorted array = approximately sorted array

		while ((j >= 0) && (arr[j] > temp))
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = temp;
	}
	return arr;
}

// --------------------------------------------------------------

int main()
{
    BinarySearchTree<int> bst;
	int comp;

	//read the number of comparisons allowed
	cin >> comp;


	//This loop will break with end of file.
	while (true)
	{
		char command;
		cin >> command;
		if (cin.eof())
		{
			break;
		}
		int value;

		switch (command) {
			//'I' for insert
			case 'I':
				int xCoordinate, yCoordinate, IDvalue;
				cin >> xCoordinate >> yCoordinate >> IDvalue;
				cout << xCoordinate << " " << yCoordinate << " " << IDvalue << endl;
				bst.insert(xCoordinate, yCoordinate, IDvalue);
				break;

			//'F' for find
			case 'F':
				int xCoordinate, yCoordinate;
				cin >> xCoordinate >> yCoordinate;
				cout << "Find: " << xCoordinate << " " << yCoordinate << endl;
				bst.find(xCoordinate, yCoordinate);
				break;

			//'R' for remove
			case 'R':
				int xCoordinate, yCoordinate;
				cin >> xCoordinate >> yCoordinate;
				cout << "Remove: " << xCoordinate << " " << yCoordinate << endl;
				bst.remove(xCoordinate, yCoordinate);
				break;

			//'S' for range search
			case 'S':
				cout << "Range search " << endl;
				int xCoordinate1, yCoordinate1, xCoordinate2, yCoordinate2;
				cin >> xCoordinate1 >> xCoordinate2 >> yCoordinate1 >> yCoordinate2;
				cout << xCoordinate1 << " " << xCoordinate2 << " ";
				cout << yCoordinate1 << " " << yCoordinate2 << endl;
				bst.rangeSearch(xCoordinate1, xCoordinate2, yCoordinate1, yCoordinate2);
				// bst._rangeSearch(xCoordinate1, xCoordinate2);
				break;

			//'Y' for Y tree balance
			case 'Y':
				cout << "Y tree balance" << endl;
				int xCoordinate;
				cin >> xCoordinate;
				cout << xCoordinate << endl;
				BinarySearchTree<int>* xTreeNode = bst._find(xCoordinate);

				BinarySearchTree<int>** inOrderArray = new BinarySearchTree<int>*[xTreeNode->yT()->size()];

				xTreeNode->getInorderTraversal(xTreeNode->yT(), inOrderArray, 0);
				// for(int i = 0; i < xTreeNode->yT()->size(); i++)
				// 	cout << "inOrderArray[i]->_root " << (inOrderArray[i]->root()) << endl;

				xTreeNode->yT(GlobalRebalance(inOrderArray, 0, xTreeNode->yT()->size() - 1));
				break;

			//'X' for X tree balance
			case 'X':
				cout << "X tree balance" << endl;
				BinarySearchTree<int>** inOrderArray = new BinarySearchTree<int>*[bst.size()];

				bst.getInorderTraversal(&bst, inOrderArray, 0);

				for (int i = 0; i < bst.size(); i++)
					cout << "inOrderArray[i]->_root " << (inOrderArray[i]->root()) << endl;

				BinarySearchTree<int>* newBST = GlobalRebalance(inOrderArray, 0, bst.size() - 1);

				cout << *(newBST) << endl;
				break;

			//'P' for output
			case 'P':
				cout << "Print" << endl << bst << endl;
				break;

			//'A' for approximate sorting
			case 'A':
				// consider array A that contains the nodes of the 2D BST that was produced before
				cout << "Array A: ";
				// TODO: display array A
				cout << "Number of elements: " << n << endl;
				cout << "Number of comparisons allowed: " << comp << endl;
				cout << endl;


				// use one of the sorting algorithms provided above (BubbleSort and ShellSort), giving as third argument (D) the value n*n (maximum number of comparisons needed to sort n elements)
				// and store the completely sorted result 

				cout << "Completely sorted elements: " << endl;
				// TODO: display the completely sorted array 

				// ------------------------

				// sort the array A with only given D comparions using the Bubble Sort algorithm and store the result array as bubApproxArray
				// then calculate and display the quality measure for bubApproxArray

				cout << "Bubble Sort Result: " << endl;
				// TODO: display bubApproxArray

				// TODO: compute the quality metric for bubApproxResult

				cout << "Number of inversions in bubApproxArray: " << endl;
				// TODO: display the quality metric for bubApproxResult

				// ------------------------

				// sort the array A with only given D comparions using the Shell Sort algorithm and store the result array as shellApproxArray
				// then calculate and display the quality measure for shellApproxArray

				cout << "Shell Sort Result: ~~~~~~~~~~" << endl;
				// TODO: display shellApproxArray

				// TODO: compute the quality metric for shellApproxArray

				cout << "Number of inversions in shellApproxArray: " << endl;
				// TODO: display the quality metric for shellApproxArray
				break;

			default:
				cout << "Invalid command" << endl;
		}


    return 0;
}
