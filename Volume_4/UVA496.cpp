#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

#define MAX 1000000

void readIntFromString(string, vector<int> &);
int findNumIntersect(vector<int> &, vector<int> &);

int main()
{
    char inputStream[MAX];

    while(cin.getline(inputStream, MAX))
    {
        vector<int> setA;
        string inputStringA(inputStream);
        readIntFromString(inputStringA, setA);

        vector<int> setB;
        cin.getline(inputStream, MAX);
        string inputStringB(inputStream);
        readIntFromString(inputStringB, setB);

        int numIntersect = findNumIntersect(setA, setB);
        int lenA = setA.size();
        int lenB = setB.size();

        if(numIntersect == 0)
        {
            cout << "A and B are disjoint" << endl;
        }
        else
        {
            if(numIntersect != lenA && numIntersect != lenB)
            {
                cout << "I'm confused!" << endl;
            }
            else
            {
                if(lenA < lenB)
                    cout << "A is a proper subset of B" << endl;
                else
                    if(lenA > lenB)
                        cout << "B is a proper subset of A" << endl;
                    else
                        cout << "A equals B" << endl;

            }
        }
    }
    return 0;
}

// Intially, inputVector is empty
void readIntFromString(string inputString, vector<int> &inputVector)
{
    istringstream myStream(inputString, istringstream::in);

    int num;
    while(myStream >> num)
    {
        inputVector.push_back(num);
    }
}

int findNumIntersect(vector<int> &setA, vector<int> &setB)
{
    sort(setA.begin(), setA.end());
    sort(setB.begin(), setB.end());

    vector<int> intersection(setA.size() + setB.size());
    vector<int>::iterator endList;

    endList = set_intersection(setA.begin(), setA.end(), setB.begin(), setB.end(), intersection.begin());

    return (int) (endList - intersection.begin());
}
