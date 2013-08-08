#include <iostream>
#include <vector>
using namespace std;

bool isJolly(vector<int> & arr);

int main()
{
    int arrSize;

    while(true)
    {
        cin >> arrSize;
        if(cin.eof())
            break;

        vector<int> arr(arrSize);

        for(int index = 0; index < arrSize; index++)
            cin >> arr[index];

        if(isJolly(arr))
            cout << "Jolly" << endl;
        else
            cout << "Not jolly" << endl;
    }

    return 0;
}

bool isJolly(vector<int> & arr)
{
    int diff, sizeArr = arr.size();
    vector<bool> isPresent(sizeArr, false);


    for(int index = 1; index < sizeArr; index++)
    {
        diff = arr[index] - arr[index - 1];
        if(diff < 0)
            diff = -diff;

        if(diff >= sizeArr || diff == 0)
            return false;

        if(isPresent[diff] == true)
            return false;

        isPresent[diff] = true;
    }

    for(int index = 1; index < sizeArr; index++)
        if(!isPresent[index])
            return false;

    return true;
}
