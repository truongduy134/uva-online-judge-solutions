#include <iostream>
#include <ctype.h>
#include <algorithm>
#include <string>

using namespace std;

bool cmpLetter(char a, char b)
{
    if(!isalpha(a) || !isalpha(b))
        return a < b;

    char upperA = toupper(a), upperB = toupper(b);

    if(upperA < upperB)
        return true;
    if(upperA == upperB)
    {
        if(isupper(a) && islower(b))
            return true;
    }

    return false;

}

int main()
{
    int numTest;
    string inputStr;

    cin >> numTest;

    while(numTest)
    {
        cin >> inputStr;

        sort(inputStr.begin(), inputStr.end(), cmpLetter);

        do
        {
            cout << inputStr << endl;

        } while(next_permutation(inputStr.begin(), inputStr.end(), cmpLetter));

        numTest--;
    }

    return 0;
}
