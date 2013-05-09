#include <iostream>
//#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
  //  freopen("in.txt", "r", stdin);
  //  freopen("out.txt", "w", stdout);

    string input;

    while(1)
    {
        cin >> input;

        if(input[0] == '#')
            break;

        bool hasSuccessor = next_permutation(input.begin(), input.end());
   //     bool hasSuccessor = false;
        if(hasSuccessor)
            cout << input << endl;
        else
            cout << "No Successor" << endl;
    }
    return 0;
}
