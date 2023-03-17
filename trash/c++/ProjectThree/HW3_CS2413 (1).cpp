/*
 *    Data Structures Featuring C++  (c) 2022 Katia Papakonstantinopoulou, based on Sridhar Radhakrishnan's files
 */
#include <iostream>
using namespace std;

// ----------------------------------------------------------------



/*
 *    Data Structures Featuring C++  (c) 2022 Katia Papakonstantinopoulou, based on source of Prof Sridhar Radhakrishnan
 */
int max(int a, int b)
{
	if (a < b) return b;
	else return a;
}

class Exception {};

class BinaryTreeException : Exception {};
class BinaryTreeMemory : BinaryTreeException {};
class BinaryTreeEmptyTree : BinaryTreeException {};

class BinarySearchTreeException : BinaryTreeException {};
class BinarySearchTreeNotFound : BinarySearchTreeException {};


// template for the Binary Search Tree class
template <class DataType>
class BinarySearchTree;

// overloading << operator, it returns an output stream object (to be used for printing the tree)
template <class DataType>
ostream& operator << (ostream& s, BinarySearchTree<DataType>& X);

// /////////////////////////////////////////////////////////////
template <class DataType>
class BinarySearchTree
	// /////////////////////////////////////////////////////////////
{
	friend ostream& operator<< <DataType> (ostream& s, BinarySearchTree<DataType>& X);

protected:
	DataType* _root;
	int ID;
	BinarySearchTree<DataType>* _left;
	BinarySearchTree<DataType>* _right;
	BinarySearchTree<DataType>* _yTree;
	bool _subtree;

	virtual BinarySearchTree<DataType>* makeSubtree();
	virtual void copyTree(BinarySearchTree<DataType>* bst);
	virtual void _makeNull();
public:

	BinarySearchTree();
	BinarySearchTree(const DataType& data);
	BinarySearchTree(const DataType& data1, const DataType& data2, int i); // constructor with y coordinate and ID given
	BinarySearchTree(const DataType& data2, int i); // constructor with ID given
	virtual ~BinarySearchTree();

	virtual void inOrder_xTreeDisplay();
	virtual void inOrder_yTreeDisplay();
	virtual void preOrder_xTreeDisplay();
	virtual void preOrder_yTreeDisplay();

	virtual bool isEmpty();
	// returns true if tree is empty,
	// but otherwise returns false

	virtual int height();
	// returns the height (or depth) of the tree

	virtual int size();
	// returns the number of nodes in the tree

	virtual DataType& root();
	// returns data from the root

	virtual BinarySearchTree<DataType>* left();
	// returns the left subtree

	virtual BinarySearchTree<DataType>* right();
	// returns the right subtree

	virtual void left(BinarySearchTree<DataType>* i);
	// sets the left subtree

	virtual void right(BinarySearchTree<DataType>* i);
	// sets the right subtree

	virtual void yT(BinarySearchTree<DataType>* setY);
	// sets the yTree

	virtual BinarySearchTree<DataType>* yT();
	// returns the yTree

	virtual bool subtree();
	virtual void makeEmpty();
	virtual int find(const DataType& q, const DataType& p);
	virtual BinarySearchTree<DataType>* _remove(const DataType& data);
	virtual int getInorderTraversal(BinarySearchTree<DataType>* node, BinarySearchTree<DataType>** inOrderArray, int index);
	virtual void remove(const DataType& data1, const DataType& data2);
	virtual void _rangeSearch(const DataType& low, const DataType& high);
	virtual void rangeSearch(const DataType& X_low, const DataType& X_high, const DataType& y_low, const DataType& y_high);
	virtual BinarySearchTree<DataType>* _insert(const DataType& data);
	virtual void insert(const DataType& data1, const DataType& data2, int i);
	BinarySearchTree<DataType>* _find(const DataType& data);

	//will return ID 
	virtual int getID();

};


template <class DataType>
ostream& operator<< (ostream& s, BinarySearchTree<DataType>& X) {
	cout << "INORDER TRAVERSAL: " << endl;
	X.inOrder_xTreeDisplay();
	cout << "PREORDER TRAVERSAL: " << endl;
	X.preOrder_xTreeDisplay();
	return s;
}

template <class DataType>
void BinarySearchTree<DataType>::inOrder_xTreeDisplay()
// inorder display of the xTree
{
	if (!this->isEmpty()) {
		this->left()->inOrder_xTreeDisplay();

		cout << this->root() << ": " << endl;
		if (!(this->yT() == NULL)) {
			(this->yT())->inOrder_yTreeDisplay();
			cout << endl;
		}

		this->right()->inOrder_xTreeDisplay();
	}

}

template <class DataType>
void BinarySearchTree<DataType>::inOrder_yTreeDisplay()
// inorder display of the yTree
{
	if (this->left()->_root != NULL)
		(this->left())->inOrder_yTreeDisplay();

	cout << " " << this->root() << "(" << this->ID << ") ";

	if (this->right()->_root != NULL)
		(this->right())->inOrder_yTreeDisplay();
}



template <class DataType>
void BinarySearchTree<DataType>::preOrder_xTreeDisplay()
// preorder display of the xTree
{
	if (!this->isEmpty()) {
		cout << this->root() << ": " << endl;

		if (!(this->yT() == NULL)) {
			(this->yT())->preOrder_yTreeDisplay();
			cout << endl;
		}

		this->left()->preOrder_xTreeDisplay();

		this->right()->preOrder_xTreeDisplay();
	}

}

template <class DataType>
void BinarySearchTree<DataType>::preOrder_yTreeDisplay()
// preorder display of the yTree
{
	cout << " " << this->root() << "(" << this->ID << ") ";

	if (this->left()->_root != NULL)
		(this->left())->preOrder_yTreeDisplay();

	if (this->right()->_root != NULL)
		(this->right())->preOrder_yTreeDisplay();
}

// ==============================================================

template <class DataType>
int BinarySearchTree<DataType>::getID()
// returns ID
{
	return this->ID;
}
// --------------------------------------------------------------
template <class DataType>
BinarySearchTree<DataType>::BinarySearchTree()
{
	// default constructor
	ID = -1;
	_root = NULL;
	_left = NULL;
	_right = NULL;
	_yTree = NULL;
	_subtree = false;
}
// --------------------------------------------------------------
template <class DataType>
BinarySearchTree<DataType>::BinarySearchTree(const DataType& data)
{
	// non default constructor, version 1
	_subtree = false;
	_root = new DataType(data);
	ID = -1;

	_left = makeSubtree();
	_right = makeSubtree();
	_yTree = NULL;
}
// --------------------------------------------------------------
template <class DataType>
BinarySearchTree<DataType>::BinarySearchTree(const DataType& data2, int i)
{
	// non default constructor, version 2
	_subtree = false;
	_root = new DataType(data2);
	ID = i;

	_left = makeSubtree();
	_right = makeSubtree();
	_yTree = NULL;
}
// --------------------------------------------------------------
template <class DataType>
BinarySearchTree<DataType>::BinarySearchTree(const DataType& data1, const DataType& data2, int i)
{
	// non default constructor, version 3
	_subtree = false;
	_root = new DataType(data1);
	ID = -1;

	_left = makeSubtree();
	_right = makeSubtree();
	_yTree = new BinarySearchTree<DataType>(data2, i);
}
// --------------------------------------------------------------
template <class DataType>
BinarySearchTree<DataType>* BinarySearchTree<DataType>::makeSubtree()
{
	BinarySearchTree<DataType>* bst = new BinarySearchTree<DataType>();
	bst->_subtree = true;
	return bst;
}
// --------------------------------------------------------------
template <class DataType>
BinarySearchTree<DataType>::~BinarySearchTree()
{
	if (_root != NULL)
		delete _root;
	_root = NULL;
	if (_left != NULL)
		delete _left;
	_left = NULL;
	if (_right != NULL)
		delete _right;
	_right = NULL;
	if (_yTree != NULL)
		delete _yTree;
	_yTree = NULL;

	ID = -1;
}
// --------------------------------------------------------------
template <class DataType>
bool BinarySearchTree<DataType>::isEmpty()
{
	return (_root == NULL);
}
// --------------------------------------------------------------
template <class DataType>
int BinarySearchTree<DataType>::height()
{
	if (isEmpty()) return 0;
	return (1 + max(_left->height(), _right->height()));
	// max() is defined in the beginning of this file
}
// --------------------------------------------------------------
template <class DataType>
int BinarySearchTree<DataType>::size()
{
	if (isEmpty())
		return 0;
	return (1 + _left->size() + _right->size());
}
// --------------------------------------------------------------
template <class DataType>
DataType& BinarySearchTree<DataType>::root()
// returns the root of the tree
{
	if (isEmpty()) throw BinaryTreeEmptyTree();
	return *_root;
}
// --------------------------------------------------------------
template <class DataType>
BinarySearchTree<DataType>* BinarySearchTree<DataType>::left()
// returns the left subtree
{
	return _left;
}

// --------------------------------------------------------------
template <class DataType>
BinarySearchTree<DataType>* BinarySearchTree<DataType>::right()
// returns the right subtree
{
	return _right;
}


// --------------------------------------------------------------
template <class DataType>
void BinarySearchTree<DataType>::left(BinarySearchTree<DataType>* i)
// sets the left subtree
{
	_left = i;
}
// --------------------------------------------------------------
template <class DataType>
void BinarySearchTree<DataType>::right(BinarySearchTree<DataType>* i)
// sets the right subtree
{
	_right = i;
}
// --------------------------------------------------------------
template <class DataType>
void BinarySearchTree<DataType>::yT(BinarySearchTree<DataType>* i)
// sets the yTree
{
	_yTree = i;
}
// --------------------------------------------------------------
template <class DataType>
BinarySearchTree<DataType>* BinarySearchTree<DataType>::yT()
// returns the yTree
{
	return _yTree;
}
// --------------------------------------------------------------
template <class DataType>
bool BinarySearchTree<DataType>::subtree()
// returns whether there is a subtree
{
	return _subtree;
}
// --------------------------------------------------------------
template <class DataType>
void BinarySearchTree<DataType>::makeEmpty()
// empties a tree
{
	if (_root != NULL)
		delete _root;
	_root = NULL;
	if (_left != NULL)
		delete _left;
	_left = NULL;
	if (_right != NULL)
		delete _right;
	_right = NULL;
}
// --------------------------------------------------------------
template <class DataType>
void BinarySearchTree<DataType>::copyTree(BinarySearchTree<DataType>* bst)
// initializes a tree, given another tree (bst)
{
	_root = bst->_root;
	ID = bst->ID;
	_left = bst->_left;
	_right = bst->_right;
	_yTree = bst->_yTree;
}
// --------------------------------------------------------------
template <class DataType>
void BinarySearchTree<DataType>::_makeNull()
// prepares a tree for deletion
{
	_root = NULL;
	_left = NULL;
	_right = NULL;
	_yTree = NULL;
}
// --------------------------------------------------------------
template <class DataType>
BinarySearchTree<DataType>* BinarySearchTree<DataType>::_find(const DataType& data)
// returns the node that contains the 'data' we look for
{
	BinarySearchTree<DataType>* bst = this;
	while (true)
	{
		if (bst->isEmpty())
			return bst;
		if (*(bst->_root) < data)
		{
			bst = bst->_right;
		}
		else if (*(bst->_root) > data)
		{
			bst = bst->_left;
		}
		else
		{
			return bst;
		}
	}
}
// --------------------------------------------------------------
template <class DataType>
int BinarySearchTree<DataType>::find(const DataType& data1, const DataType& data2)
// returns the ID in the given coordinates of the 2D tree
{
	BinarySearchTree<DataType>* bst = _find(data1);
	try {
		if (bst->isEmpty()) throw BinarySearchTreeNotFound();
		BinarySearchTree<DataType>* bst2 = (bst->yT())->_find(data2);
		try {
			if (bst2->isEmpty()) throw BinarySearchTreeNotFound();
			cout << "\nThe coordinates " << bst->root() << ", " << bst2->root() << " is found in the tree with ID value " << bst2->ID << endl;
			return bst2->ID;
		}
		catch (BinarySearchTreeNotFound e)
		{
			cout << "\nSorry!!! Coordinate is not found in the Y tree" << endl;
			return bst2->ID;
		}
		return bst->ID;
	}
	catch (BinarySearchTreeNotFound e)
	{
		cout << "\nSorry!!! Coordinate is not found in the X tree" << endl;
		return bst->ID;
	}
}
// --------------------------------------------------------------
template <class DataType>
BinarySearchTree<DataType>* BinarySearchTree<DataType>::_insert(const DataType& data)
// inserts 'data' in the correct position of the Binary Search Tree
{
	BinarySearchTree<DataType>* bst = _find(data);
	if (bst->isEmpty())
	{
		bst->_root = new DataType(data);
		bst->_left = makeSubtree();
		bst->_right = makeSubtree();
		// need to do for yTree as well
	}
	else
	{
		delete bst->_root;
		bst->_root = new DataType(data);
	}
	return bst;
}
// --------------------------------------------------------------
template <class DataType>
void BinarySearchTree<DataType>::insert(const DataType& data1, const DataType& data2, int i)
// inserts 'i' in the correct position of the 2D Binary Search Tree
{
	BinarySearchTree<DataType>* search = _find(data1);
	if (search->isEmpty()) {
		BinarySearchTree<DataType>* bst = this->_insert(data1);
		if (bst->_yTree == NULL)
		{
			bst->_yTree = new BinarySearchTree<DataType>(data2, i);
		}
		else
		{
			BinarySearchTree<DataType>* bst2 = bst->yT()->_insert(data2);
			bst2->ID = i;
		}
	}
	else {
		if (search->_yTree == NULL)
		{
			search->_yTree = new BinarySearchTree<DataType>(data2, i);
		}
		else
		{
			BinarySearchTree<DataType>* bst2 = search->_yTree->_insert(data2);
			bst2->ID = i;
		}
	}
}

// --------------------------------------------------------------
template <class DataType>
BinarySearchTree<DataType>* BinarySearchTree<DataType>::_remove(const DataType& data)
// removes 'data' from the Binary Search Tree
{
	BinarySearchTree<DataType>* bst;
	BinarySearchTree<DataType>* bst2;
	BinarySearchTree<DataType>* bst3;

	bst = _find(data);
	try {
		if (bst->isEmpty()) throw BinarySearchTreeNotFound();
	}
	catch (BinarySearchTreeNotFound e) {
		cout << "The element you are trying to remove is not in the tree " << endl;
		return bst;
	}

	// dispose of the existing data; the pointer will be overwritten
	delete bst->_root;

	// .............................................................
	if (bst->_left->isEmpty())
	{

		delete bst->_left;
		bst2 = bst->_right;		// save the pointer to the right subtree
		bst->copyTree(bst2);	// copy the right subtree;
		// this empties tree if right empty
		bst2->_makeNull();		// prepare right subtree for deletion
		delete bst2;				// delete right subtree to avoid garbage
	}

	else if (bst->_right->isEmpty())
	{

		delete bst->_right;
		bst2 = bst->_left;		// save the pointer to the left subtree
		bst->copyTree(bst2);	// copy the left subtree
		bst2->_makeNull();		// prepare left subtree for deletion
		delete bst2;				// delete left subtree to avoid garbage
	}

	else		// both subtrees non-empty
	{
		// move to the right
		bst2 = bst->_right;
		// then move down to the left as far as possible
		while (!bst2->_left->isEmpty()) bst2 = bst2->_left;
		// overwrite the data pointer
		bst->_root = bst2->_root;

		// bst2's left child is known to be empty and pointer will be overwritten
		delete bst2->_left;
		// now bst2's right child is copied into it
		if (bst2->_right->isEmpty())
		{
			delete bst2->_right;
			bst2->_makeNull();
		}
		else
		{
			bst3 = bst2->_right;
			bst2->copyTree(bst2->_right);
			bst3->_makeNull();
			delete bst3;
		}
	}

	return bst;
}
// --------------------------------------------------------------
template <class DataType>
void BinarySearchTree<DataType>::remove(const DataType& data1, const DataType& data2)
// removes the data from the given coordinates of the 2D BST
{

	BinarySearchTree<DataType>* bst = _find(data1);

	try {
		if (bst->isEmpty()) throw BinarySearchTreeNotFound();
	}
	catch (BinarySearchTreeNotFound e) {
		cout << "The element you are trying to remove is not in the tree " << endl;
		return;
	}

	if (!bst->isEmpty()) {
		BinarySearchTree<DataType>* bst2 = (bst->_yTree)->_remove(data2);
		bst2->ID = -1;

		try {
			if (bst->_yTree->_root == NULL) throw BinarySearchTreeNotFound();

		}
		catch (BinarySearchTreeNotFound e) {
			_remove(data1);
		}
	}
}

// --------------------------------------------------------------
template <class DataType>
void BinarySearchTree<DataType>::_rangeSearch(const DataType& low, const DataType& high)
// returns the nodes with values between 'low' and 'high'
{
	if (this->_root == NULL) return;
	if (*_root >= low)
	{
		_left->_rangeSearch(low, high);
	}
	if (*_root >= low && *_root <= high)
	{
		cout << *_root << "  ";
	}
	if (*_root <= high)
		_right->_rangeSearch(low, high);
}

// --------------------------------------------------------------
template <class DataType>
void BinarySearchTree<DataType>::rangeSearch(const DataType& x_low, const DataType& x_high, const DataType& y_low, const DataType& y_high)
// returns the nodes of the 2D BST with values between 'low' and 'high'
{

	if (isEmpty()) return;
	if (*_root >= x_low)
	{
		_left->rangeSearch(x_low, x_high, y_low, y_high);
		if (*_root <= x_high)
		{
			cout << *_root << " : ";
			(this->_yTree)->_rangeSearch(y_low, y_high);
			cout << endl;
		}
	}
	if (*_root <= x_high)
		_right->rangeSearch(x_low, x_high, y_low, y_high);
	// cout << endl;

}


template <class DataType>
int BinarySearchTree<DataType>::getInorderTraversal(BinarySearchTree<DataType>* node, BinarySearchTree<DataType>** inOrderArray, int index)
{
	try {
		if (node->isEmpty()) throw BinarySearchTreeNotFound();
	}
	catch (BinarySearchTreeNotFound e) {
		cout << "No tree for inorder traversal" << endl;
		return index;
	}

	//cout << "value: " << this->root() << endl;
	// cout << "left: " << *(this->left()->_root) << endl;
	// cout << "right: " << *(this->right()->_root) << endl;

	if (!this->isEmpty()) {
		if (node->left()->_root != NULL)
		{
			// cout << "\tcalling left" << endl;
			index = node->left()->getInorderTraversal(node->left(), inOrderArray, index);
		}

		inOrderArray[index++] = node;
		// cout << "index: " << index - 1 << " inOrderArray[i]: " << inOrderArray[index - 1]->root() << endl;

		if (node->right()->_root != NULL)
		{
			// cout << "\tcalling right" << endl;
			index = node->right()->getInorderTraversal(node->right(), inOrderArray, index);
		}
	}
	return index;
}


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



BinarySearchTree<int>* GlobalRebalance(BinarySearchTree<int>** inOrderArray, int left, int right) {
	int mid = 0;
	BinarySearchTree<int>* temp = new BinarySearchTree<int>;
	if (left <= right) {
		mid = (left + right) / 2;
		temp = inOrderArray[mid];
		temp->left(GlobalRebalance(inOrderArray, left, mid - 1));
		temp->right(GlobalRebalance(inOrderArray, mid+1, right));
	}
	return temp;
}


int inversionsNeeded(int* arr, int size) {
	int inversions = 0;
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			if (arr[j] < arr[i]) {
				inversions++;
			}
		}
	}

	return inversions;
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
		case 'I': {
			int xCoordinate, yCoordinate, IDvalue;
			cin >> xCoordinate >> yCoordinate >> IDvalue;
			cout <<"Insert " << xCoordinate << " " << yCoordinate << " " << IDvalue << endl;
			bst.insert(xCoordinate, yCoordinate, IDvalue);
			break;
		}

			//'F' for find
		case 'F': {
			int xCoordinate, yCoordinate;
			cin >> xCoordinate >> yCoordinate;
			cout << "Find " << xCoordinate << " " << yCoordinate << endl;
			bst.find(xCoordinate, yCoordinate);
			break;
		}

			//'R' for remove
		case 'R': {
			int xCoordinate, yCoordinate;
			cin >> xCoordinate >> yCoordinate;
			cout << "Remove " << xCoordinate << " " << yCoordinate << endl;
			bst.remove(xCoordinate, yCoordinate);
			break;
		}

			//'S' for range search
		case 'S': {
			cout << "Range search " << endl;
			int xCoordinate1, yCoordinate1, xCoordinate2, yCoordinate2;
			cin >> xCoordinate1 >> xCoordinate2 >> yCoordinate1 >> yCoordinate2;
			cout << xCoordinate1 << " " << xCoordinate2 << " ";
			cout << yCoordinate1 << " " << yCoordinate2 << endl;
			bst.rangeSearch(xCoordinate1, xCoordinate2, yCoordinate1, yCoordinate2);
			// bst._rangeSearch(xCoordinate1, xCoordinate2);
			break;
		}

			//'Y' for Y tree balance
		case 'Y': {
			cout << "Y tree balance" << endl;
			int xCoordinate;
			cin >> xCoordinate;
			cout << xCoordinate << endl;
			BinarySearchTree<int>* xTreeNode = bst._find(xCoordinate);

			BinarySearchTree<int>** inOrderArray = new BinarySearchTree<int> * [xTreeNode->yT()->size()];

			xTreeNode->getInorderTraversal(xTreeNode->yT(), inOrderArray, 0);
			// for(int i = 0; i < xTreeNode->yT()->size(); i++)
			// 	cout << "inOrderArray[i]->_root " << (inOrderArray[i]->root()) << endl;

			xTreeNode->yT(GlobalRebalance(inOrderArray, 0, xTreeNode->yT()->size() - 1));
			break;
		}

			//'X' for X tree balance
		case 'X': {
			cout << "X tree balance" << endl;
			BinarySearchTree<int>** inOrderArray = new BinarySearchTree<int> * [bst.size()];

			bst.getInorderTraversal(&bst, inOrderArray, 0);

			for (int i = 0; i < bst.size(); i++)
				cout << "inOrderArray[i]->_root " << (inOrderArray[i]->root()) << endl;

			BinarySearchTree<int>* newBST = GlobalRebalance(inOrderArray, 0, bst.size() - 1);

			cout << *(newBST) << endl;
			break;
		}

			//'P' for output
		case 'P': {
			cout << "Print" << endl << bst << endl;
			break;
		}

			//'A' for approximate sorting
		case 'A': {
			// consider array A that contains the nodes of the 2D BST that was produced before
			cout << "Array A: ";
			// TODO: display array A

			//getting address of root node
			BinarySearchTree<int>* xTreeNode = bst._find(bst.root());

			//making xTree array using bst root
			BinarySearchTree<int>** inOrderArray = new BinarySearchTree<int> * [xTreeNode->size()];
			xTreeNode->getInorderTraversal(xTreeNode, inOrderArray, 0);
			
			//number of x roots
			int size = xTreeNode->size();
			
			//calculating total number of elements in the entire tree
			int n = 0;
			for (int i = 0; i < size; i++) {
				n += inOrderArray[i]->yT()->size();
			}

			int* elements = new int[n];

			//updating elements array
			int k = 0;
			for (int i = 0; i < size; i++) {

				//getting the size of the yTree of the current xTree node
				int mySize = inOrderArray[i]->yT()->size();

				//traversing all values of the yTree 
				BinarySearchTree<int>* temp = inOrderArray[i]->yT(); //yTree root
				BinarySearchTree<int>** tempArr = new BinarySearchTree<int> * [mySize]; //array to store yTree node addresses
				temp->getInorderTraversal(temp, tempArr, 0); //populating array

				//updating elements list using yTree nodes of current xTree
				for (int j = 0; j < mySize; j++) {
					elements[j + k] = tempArr[j]->getID();
				}
				k += mySize;
				
			}
			
			//printing nodes
			for (int i = 0; i < n-1; i++) {
				cout << elements[i] << " ";
			}
			cout << elements[n - 1] << endl;
			

			cout << "Number of elements: " << n << endl;
			cout << "Number of comparisons allowed: " << comp << endl;
			cout << endl;

			
		
			// use one of the sorting algorithms provided above (BubbleSort and ShellSort), giving as third argument (D) the value n*n (maximum number of comparisons needed to sort n elements)
			// and store the completely sorted result
			int* completelySorted = bubbleSort(elements, n, n * n);

			cout << "Completely sorted elements: ";
			// TODO: display the completely sorted array

			for (int i = 0; i < n-1; i++) {
				cout << completelySorted[i] << " ";
			}
			cout << completelySorted[n - 1] << endl<<endl;


			// ------------------------

			// sort the array A with only given D comparions using the Bubble Sort algorithm and store the result array as bubApproxArray
			// then calculate and display the quality measure for bubApproxArray
			int* bubApproxArray = bubbleSort(elements, n, comp);
			cout << "Sorted by Bubble Sort: ";
			// TODO: display bubApproxArray
			for (int i = 0; i < n - 1; i++) {
				cout << bubApproxArray[i] << " ";
			}
			cout << bubApproxArray[n - 1] << endl;

			// TODO: compute the quality metric for bubApproxResult
			int bubInversions = inversionsNeeded(bubApproxArray, n);

			cout << "Number of inversions: ";
			// TODO: display the quality metric for bubApproxResult
			cout << bubInversions << endl << endl;

			// ------------------------
			
			// sort the array A with only given D comparions using the Shell Sort algorithm and store the result array as shellApproxArray
			// then calculate and display the quality measure for shellApproxArray

			int* shellApproxArray = shellSort(elements, n, comp);

			cout << "Sorted by Shell Sort: ";
			// TODO: display shellApproxArray
			for (int i = 0; i < n - 1; i++) {
				cout << shellApproxArray[i] << " ";
			}
			cout << shellApproxArray[n - 1] << endl;



			// TODO: compute the quality metric for shellApproxArray
			int shellInversions = inversionsNeeded(shellApproxArray, n);
			cout << "Number of inversions: ";
			// TODO: display the quality metric for shellApproxArray
			cout << shellInversions << endl;

			break;
		}
		default: {
			cout << "Invalid command" << endl; }
		}
	}
	
	return 0;

}
