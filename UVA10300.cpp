#include <iostream>

using namespace std;

int main()
{
    int numTestCase;
    int numFarmer;
    long long result = 0;
    long long area, numAnimal, mulValue;

    cin >> numTestCase;

    while(numTestCase)
    {
        result = 0;

        cin >> numFarmer;

        while(numFarmer)
        {
            cin >> area >> numAnimal >> mulValue;
            result += area * mulValue;
            numFarmer--;
        }

        cout << result << endl;
        numTestCase--;
    }
    return 0;
}
