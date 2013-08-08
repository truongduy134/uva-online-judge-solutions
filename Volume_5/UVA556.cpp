#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

enum DIRECTION {NORTH, SOUTH, EAST, WEST};

void doRightHandMazeTraversal(vector<vector<int> > & visitArr);
void countNumVisit(vector<int> &numVisitArr, vector<vector<int> > &visitArr);
bool canProceed(int &rowPos, int &colPos, enum DIRECTION direct, vector<vector<int> > &visitArr);
enum DIRECTION turnLeft(enum DIRECTION oldDirect);
enum DIRECTION turnRight(enum DIRECTION oldDirect);

int main()
{
    int numLine, numChar;
    string trash, lineMaze;

    while(true)
    {
        cin >> numLine >> numChar;
        getline(cin, trash);

        if(numLine == 0 && numChar == 0)
            break;

        vector<vector<int> > visitArr(numLine, vector<int> (numChar));

        /* Read maze and initialize visitArr*/
        for(int lineIndex = 0; lineIndex < numLine; lineIndex++)
        {
            getline(cin, lineMaze);
            for(int charIndex = 0; charIndex < numChar; charIndex++)
                if(lineMaze[charIndex] == '1')
                    /* This is a close square. Set visitArr[lineIndex][charIndex] = -1 */
                    visitArr[lineIndex][charIndex] = -1;
                else
                    visitArr[lineIndex][charIndex] = 0;
        }

        /* Simulate the traversing process */
        doRightHandMazeTraversal(visitArr);

        /* Count the number of targeted cells */
        vector<int> numVisitArr(5);
        countNumVisit(numVisitArr, visitArr);

        /* Print result */
        for(int index = 0; index < numVisitArr.size(); index++)
            cout << std::right << std::setw(3) << numVisitArr[index];
        cout << endl;
    }


    return 0;
}

void doRightHandMazeTraversal(vector<vector<int> > & visitArr)
{
    int numLine = visitArr.size();

    enum DIRECTION mDirect = EAST;
    int rowPos = numLine - 1, colPos = 0;   // Start at the south west corner

    do
    {
        // First, turn right and try to go 1 step in the new direction
        enum DIRECTION newRightDirect = turnRight(mDirect);
        if(canProceed(rowPos, colPos, newRightDirect, visitArr))
        {
            visitArr[rowPos][colPos]++;
            mDirect = newRightDirect;
        }
        else
        {
            // If we cannot turn right, we are sure the wall are on the right side of us.
            if(canProceed(rowPos, colPos, mDirect, visitArr))
            {
                // Every time we enter a cell, we can leave it. So it counts as 1 visit.
                // For the initial position, it is the opposite (we leave it first and reenter it)
                visitArr[rowPos][colPos]++;
            }
            else
            {
                mDirect = turnLeft(mDirect);
            }
        }
    } while(rowPos != (numLine - 1) || colPos != 0);   // Stop when returning to the initial position
}

void countNumVisit(vector<int> &numVisitArr, vector<vector<int> > &visitArr)
{
    int numRow = visitArr.size(), numCol = visitArr[0].size();

    for(int index = 0; index < numVisitArr.size(); index++)
        numVisitArr[index] = 0;

    for(int row = 0; row < numRow; row++)
        for(int col = 0; col < numCol; col++)
            if(visitArr[row][col] >= 0 && visitArr[row][col] < numVisitArr.size())
                numVisitArr[visitArr[row][col]]++;
}

bool canProceed(int &rowPos, int &colPos, enum DIRECTION direct, vector<vector<int> > &visitArr)
{
    int numRow = visitArr.size(), numCol = visitArr[0].size();
    int newRow, newCol;

    switch(direct)
    {
        case EAST:
            newRow = rowPos;
            newCol = colPos + 1;
            break;
        case WEST:
            newRow = rowPos;
            newCol = colPos - 1;
            break;
        case NORTH:
            newRow = rowPos - 1;
            newCol = colPos;
            break;
        default:
            newRow = rowPos + 1;
            newCol = colPos;
    }

    if(newRow < 0 || newCol < 0 || newRow >= numRow || newCol >= numCol || visitArr[newRow][newCol] < 0)
        return false;

    rowPos = newRow;
    colPos = newCol;

    return true;
}

enum DIRECTION turnLeft(enum DIRECTION oldDirect)
{
    switch(oldDirect)
    {
        case EAST:
            return NORTH;
        case WEST:
            return SOUTH;
        case NORTH:
            return WEST;
        default:
            return EAST;
    }
}

enum DIRECTION turnRight(enum DIRECTION oldDirect)
{
    switch(oldDirect)
    {
        case EAST:
            return SOUTH;
        case WEST:
            return NORTH;
        case NORTH:
            return EAST;
        default:
            return WEST;
    }
}

