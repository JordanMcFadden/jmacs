#include <iostream>
using namespace std;

class CRM {
protected:
    int n; //The number of rows of the original matrix
    int m; //The number of columns of the original matrix
    int nonZeros; //The number of non-zero elements in the original matrix
    int valueIdx; //Index number for values array
    int rowIdx; //Index number for rowPos array
    int colIdx; //Index number for colPos array
    int tally; // Accumulator of how many times the user inputs the same row (addRow method)
    int* values; //Array that contains all non-zero values of the matrix, assuming they are all integers
    int* rowPos; //Array that for each row of the original matrix contains the position in the values matrix in which the first non-zero element of this row is stored.
    int* colPos; //Array that contains the column number for each one of the non-zero values in the original matrix.

public:
    CRM ( ); //default or empty constructor
    CRM (int rows, int cols, int numNonZeros);
    int getNumRows ( ); //returns the size of the rowPos array
    void addValue (int value); //add a new value in the values array
    void addRow (int row); //add a row number in the rowPos array
    void addColumn (int col);//add a column number in the colPos array
    void display (); //print the contents of the three arrays. Each array must be on a different line (separated by a
    //new line character) and you have exactly a single space between each value printed.
    int mostInfluentialUser(); //find the most influential user
    int mostActiveUser(); //find the most active user
    int* influentialUsers (); //compute vector of users ranked by how influential they are
    int* activeUsers (); //compute vector of users ranked by how active they are
    ~CRM(); //destructor
    void sortByIndex(int *outputVector, int *tempVector) const;
};


//write the entire CRM class here with all the methods

//some of the methods – Katia Papakonstantinopoulou

//Constructs a CRM Method w/ all private fields set to 0 or NULL
CRM::CRM ( ) {
    n = 0;
    m = 0;
    nonZeros = 0;
    valueIdx = 0;
    rowIdx = 0;
    colIdx = 0;
    tally = 0;
    values = NULL;
    rowPos = NULL;
    colPos = NULL;
}

//Constructs a CRM objects with fields set w/ fields set to parameters and fixed values
CRM::CRM (int rows, int cols, int numNonZeros) {
    n = rows;
    m = cols;
    nonZeros = numNonZeros;
    valueIdx = 0;
    rowIdx = 0;
    colIdx = 0;
    tally = 0;
    values = new int [nonZeros];
    rowPos = new int [n];
    colPos = new int [nonZeros];
}

/*
 * Returns the number of rows in a CRM object
 * @return n: number of rows in CRM object
 */
int CRM::getNumRows() {
    return n;
}

/*
 * Adds the next value into the values array
 * @param value: value being added to array
 */
void CRM::addValue(int value) {
    values[valueIdx] = value;
    ++valueIdx;
}

/*
 * Adds the position of the first non-zero element in the values array to it's corresponding spot in the rowPos array
 * @param row: row to be added to rowPos array
 */
void CRM::addRow(int row) {
    // Sets the position of the non-zero element to -1 if there are no non-zero elements in the row
    if (row > rowIdx + 1)
    {
        ++rowIdx;
        rowPos[rowIdx] = -1;
    }
    /**
     * if the user inputs a row already in the array no value is assigned but accumulator increments, if a new row is
     * entered the index of the rowPos array is incremented and is set to the position in the values array where that
     * corresponds with it's first non-zero element
     */
    if (row == rowIdx)
    {
        ++tally;
    }
    else
    {
        ++rowIdx;
        rowPos[rowIdx] = tally;
        ++tally;
    }
}

/*
 * Adds the number of the column of the non-zero element in the values array that corresponds with the colPos arrays
 * index
 * @param col: number of column that corresponds with colPos arrays index
 */
void CRM::addColumn(int col)
{
    colPos[colIdx] = col;
    ++colIdx;
}
/*
 * Displays the values of each of the arrays in the CRM object on seperate lines
 */
void CRM::display()
{
    cout << "values: ";
    for(int i = 0; i < nonZeros; ++i) cout << values[i] << " ";
    cout << endl;

    cout << "rowPos: ";
    for(int i = 0; i < getNumRows(); ++i) cout << rowPos[i] << " ";
    cout << endl;

    cout << "colPos: ";
    for(int i = 0; i < nonZeros; ++i) cout << colPos[i] << " ";
    cout << endl << endl;
}

/*
 * Returns the user whose tweets were retweeted the most
 * @return topUsers[0]: the first element in array of users ranked most to least influential
 */
int CRM::mostInfluentialUser()
{
    int* topUsers = influentialUsers();
    return topUsers[0];
}

/*
 * Returns the user who retweeted the most
 * @return topUsers[0]: the first element in array of users ranked most to least active
 */
int CRM::mostActiveUser()
{
    int* topUsers = activeUsers();
    return topUsers[0];
}

//Sorts two arrays, one by values and the other by index
void CRM::sortByIndex(int *outputVector, int *tempVector) const {
    for(int i = 0; i < n; ++i)
    {
        for (int idx = i + 1; idx < n; ++idx)
        {
            if (tempVector[idx] > tempVector[i])
            {
                int tempVectorTemp = tempVector[i];
                int outVectorTemp = outputVector[i];
                tempVector[i] = tempVector[idx];
                outputVector[i] = outputVector[idx];
                tempVector[idx] = tempVectorTemp;
                outputVector[idx] = outVectorTemp;
            }
        }
    }
}

/*
 * Creates a vector of the user who got the most retweets ranked from most to least
 * @return outputVector: Vector with users ranked most to least based on amount of retweets
 */
int* CRM::influentialUsers ()
{
    int* outputVector = new int [n];
    //Assigning the number of the users to their index
    for(int i = 0; i < n; ++i)
    {
        outputVector[i] = i;
    }

    int* tempVector = new int[n];
    //Assigning how many times each user was retweeted to their corresponding index, if user did not get any
    // retweets indexes were assigned to -1
    for(int i = 0; i < n; ++i)
    {   int sum = 0;
        for(int idx = 0; idx < nonZeros; ++idx)
        {
            if(i == colPos[idx])
            {
                sum += values[idx];
            }
        }
        tempVector[i] = sum;
    }
    //Sorting vector
    sortByIndex(outputVector, tempVector);
    return outputVector;
}

/*
 * Creates a vector with the users who retweeted the most ranked from most to least
 * @return outputVector: Vector with users ranked most ot least based on how much they retweeted
 */
int* CRM::activeUsers()
{
    int* outputVector = new int[n];
    //Assigning the number of the users to their index
    for(int i = 0; i < n; ++i) outputVector[i] = i;

    int* tempVector = new int[n];
    int index = 0;
    int row = 1;

    //Assigning how many times each user retweeted to their corresponding index, if user did not retweet indexes were
    // assigned to -1
    for(int i = 0; i < nonZeros; ++i)
    {
        if(i == rowPos[row])
        {
            if(row > index + 1)
            {
                ++index;
                tempVector [index] = 0;
            }
            ++row;
            ++index;
        }
        else if (rowPos[row] == -1)
        {
            ++row;
        }
        tempVector [index] += values[i];
    }

    //Sorting vectors
    sortByIndex(outputVector, tempVector);
    return outputVector;
}

//Deconstructs a CRM object
CRM::~CRM ( ) {
    if (values != NULL) delete [ ] values;
    if (rowPos != NULL) delete [ ] rowPos;
    if (colPos != NULL) delete [ ] colPos;
    cout << "CRM Object Destroyed!!" << endl;
    n = 0;
    m = 0;
    nonZeros = 0;
}


int main ( ) {

    CRM* A;
    int numRows, numColumns, numNonZeros;
    int row, col, value;

    //read in the first matrix
    cin >> numRows >> numColumns;
    cin >> numNonZeros;

    A = new CRM (numRows, numColumns, numNonZeros);
    for (int i = 0; i < numNonZeros; i++) {
        cin >> row >> col >> value;
        (*A).addValue (value);
        (*A).addRow (row);
        (*A).addColumn (col);
    }
    (*A).display ( );

//Find most influential user
    int mostInf = (*A).mostInfluentialUser ();
    cout << "Most influential user: " << mostInf << endl;
    cout << endl;

//Find most active user
    int mostAct = (*A).mostActiveUser();
    cout << "Most active user: " << mostAct << endl;
    cout << endl;

//Rank users based on how influential they are
    int* influentialityVector = (*A).influentialUsers ();
    cout << "Users ranked by Influentiality: ";
    for (int i = 0; i < (*A).getNumRows( ); i++) cout << influentialityVector[i] << " ";
    cout << endl << endl;

//Rank users based on how active they are
    int* activityVector = (*A).activeUsers();
    cout << "Users ranked by Activity: ";
    for (int i = 0; i < (*A).getNumRows ( ); i++) cout << activityVector[i] << " ";
    cout << endl;

// Call the destructors
    delete A;
    delete [ ] influentialityVector;
    delete [ ] activityVector;

    return 0;
}
