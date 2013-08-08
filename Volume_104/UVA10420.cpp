#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int numLine, indexSpace;
    string trash, line;
    vector<string> countryList;

    cin >> numLine;
    getline(cin, trash);    // Get rid of the new line character

    while(numLine)
    {
        getline(cin, line);
        indexSpace = line.find_first_of(" ", 0);
        if(indexSpace != string::npos)
        {
            countryList.push_back(line.substr(0, indexSpace));
        }
        else
            countryList.push_back(line);
        numLine--;
    }

    /* Sort the list of country names */
    sort(countryList.begin(), countryList.end());

    /* Print result */
    string country = countryList[0];
    int mCount = 1;

    for(int index = 1; index < countryList.size(); index++)
        if(country.compare(countryList[index]) == 0)
            mCount++;
        else
        {
            cout << country << " " << mCount << endl;
            mCount = 1;
            country = countryList[index];
        }

    cout << country << " " << mCount << endl;

    return 0;
}
