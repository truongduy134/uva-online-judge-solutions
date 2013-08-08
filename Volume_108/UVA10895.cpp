#include <iostream>
#include <vector>
#include <utility>
using namespace std;

void readSparse(vector<vector<pair<int, int> > > &, int, int);
void printSparse(const vector<vector<pair<int, int> > > &, int, int);
void transposeSparse(const vector<vector<pair<int, int> > > &, int, int,
                     vector<vector<pair<int, int> > > &);
int main()
{
    int numRow, numCol;
    while(cin >> numRow >> numCol)
    {
        vector<vector<pair<int, int> > > matrix(numRow);
        vector<vector<pair<int, int> > > transpose(numCol);

        readSparse(matrix, numRow, numCol);
        transposeSparse(matrix, numRow, numCol, transpose);
        printSparse(transpose, numCol, numRow);
    }
    return 0;
}


void transposeSparse(const vector<vector<pair<int, int> > > &matrix,
                     int numRow, int numCol, vector<vector<pair<int, int> > > &transpose)
{
    for(int index = 0; index < numCol; index++)
    {
        vector<pair<int, int> > rowContent;
        transpose[index] = rowContent;
    }

    for(int row = 0; row < numRow; row++)
    {
        int numEle = matrix[row].size();

        for(int inner = 0; inner < numEle; inner++)
        {
            pair<int, int> element = matrix[row][inner];

            transpose[element.first].push_back(make_pair(row, element.second));
        }
    }
}

void readSparse(vector<vector<pair<int, int> > > &matrix, int numRow, int numCol)
{
    for(int index = 0; index < numRow; index++)
    {
        int numEleRow;
        cin >> numEleRow;

        vector<pair<int, int> > rowEle(numEleRow);

        for(int ele = 0; ele < numEleRow; ele++)
        {
            int colNo;
            cin >> colNo;
            rowEle[ele] = make_pair(colNo - 1, 0);
        }

        for(int ele = 0; ele < numEleRow; ele++)
        {
            int val;
            cin >> val;
            rowEle[ele].second = val;
        }

        matrix[index] = rowEle;
    }
}

void printSparse(const vector<vector<pair<int, int> > > &matrix, int numRow, int numCol)
{
    cout << numRow << " " << numCol << endl;
    for(int index = 0; index < numRow; index++)
    {
        // Note: all rows and columns are stored in 0-indexing while in the printed format,
        // they should be in 1-indexing!
        int numEle = matrix[index].size();

        cout << numEle;
        // Print the columns of nonzero elements
        for(int inner = 0; inner < numEle; inner++)
            cout << " " << matrix[index][inner].first + 1;
        cout << endl;

        // Print the elements themselves
        if(numEle > 0)
            cout << matrix[index][0].second;
        for(int inner = 1; inner < numEle; inner++)
            cout << " " << matrix[index][inner].second;
        cout << endl;
    }
}
