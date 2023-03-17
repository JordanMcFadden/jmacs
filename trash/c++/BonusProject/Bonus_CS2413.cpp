#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // used for remove
#include <math.h>

using namespace std;

template <class DT>
class HashTableVector
{
protected:
    vector< vector < DT > >* htable; // vector of vector hash table

public:
    HashTableVector<DT>();	//TODO: default constructor
    ~HashTableVector(); 	//TODO: destructor
    void insert(string str); //TODO: insert a string into the right spot in the hash table
    int hashing(char a); //TODO: hash function - returns the key
    void displayTable(); //TODO: display the contents of hash table
    void remove(string str); //TODO: removes a name from hash table
    //Add more helper functions if necessary
};

template<class DT>
HashTableVector<DT>::HashTableVector() {
    //Creates hashtable using 2d vector
    htable = new vector <vector <DT>>;
}

template<class DT>
HashTableVector<DT>::~HashTableVector() {
    //Deallocate the memory
    delete htable;
}

template<class DT>
void HashTableVector<DT>::insert( string str) {
    //Gets hash value
    int hashNum = hashing(str[0]);

    //resizing if hash value is greater than the size of the vector
    if (hashNum >= (htable->size())) {
        htable->resize(hashNum + 1);
    }

    //Inserts string into vector at hashValue Index
    (*htable)[hashNum].push_back(str);
}

template<class DT>
int HashTableVector<DT>::hashing(char a) {
    // Returns & Calculates Hash value
    return a - 'A';
}

template<class DT>
void HashTableVector<DT>::displayTable() {

    for (int i = 0; i < (*htable).size(); i++) {
        cout << i << ": ";

        //Prints inner vector
        for (int j = 0; j < (*htable)[i].size(); j++) {
            cout << (*htable)[i][j];
            if (j < (*htable)[i].size() - 1) cout << " => ";
        }
        cout << endl;
    }
}

template<class DT>
void HashTableVector<DT>::remove(string str) {
    int index = -1 ;

    //Gets hash value
    int hashNum = hashing(str[0]);

    //Searches the vector for repeated string
    for (int i = 0; i < (*htable)[hashNum].size(); i++) {
        if ((*htable)[hashNum][i] == str) {
            index = i;
            break;
        }
    }

    // If string was found, removes it from vector at that index.
    if (index != -1) (*htable)[hashNum].erase((*htable)[hashNum].begin()+index);
}

int main()
{
    //string tempName; 						// to store the name using cin

    HashTableVector<string>* h1 = new HashTableVector<string>(); // hash table object for vector

    char option; 							// to store the option from redirected input
    string tempName;
    while (cin >> option)
    {
        switch (option) {
            case 'D':
            {
                //TODO: call display method
                h1->displayTable();
                break;
            }
            case 'I':
            {
                cin >> tempName;
                cout << "adding " << tempName << endl;
                //TODO: call insert method
                h1->insert(tempName);
                break;
            }
            case 'R':
            {
                cin >> tempName;
                cout << "removing " << tempName << endl;
                //TODO: call remove method
                h1->remove(tempName);
                break;
            }

        } // switch case

        if (option == 'Q')
            break;
    } // while

    delete h1;

    return 0;

}

