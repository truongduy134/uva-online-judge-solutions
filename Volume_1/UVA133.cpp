/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + Just do a brute-force simulation.
 *  + The code is cleaner and shorter with the use of C++ STL <list>
 */

#include <cstdio>
#include <list>
#include <iterator>

using namespace std;

int main(void)
{
    int numPeople, countStart, countEnd;
    bool single;
    list<int> mList;
    list<int>::iterator itStart, itTemp;
    list<int>::reverse_iterator itEnd;

    while(1)
    {
        scanf("%d %d %d", &numPeople, &countStart, &countEnd);
        if(numPeople == 0 && countStart == 0 && countEnd == 0)
            break;

        mList.clear();
        for(int i = 1; i <= numPeople; i++)
            mList.push_back(i);

        // Do simulation
        itStart = mList.begin();
        itEnd = mList.rbegin();

        bool isFirst = true;
        while(mList.size() > 0)
        {
            // Count clockwise
            for(int step = 1; step < countStart; step++)
            {
                itStart++;
                if(itStart == mList.end())
                    itStart = mList.begin();
            }

            // Count anticlockwise
            for(int step = 1; step < countEnd; step++)
            {
                itEnd++;
                if(itEnd == mList.rend())
                    itEnd = mList.rbegin();
            }

            single = false;
            itTemp = itEnd.base();
            itTemp--;
            if(itStart == itTemp)
                single = true;

            // Print result
            if(isFirst)
                isFirst = false;
            else
                printf(",");
            printf("%3d", *itStart);
            if(!single)
                printf("%3d", *itEnd);

            // Remove elements
            itStart = mList.erase(itStart);
            if(!single)
            {
                itTemp = itEnd.base();
                itTemp--;
                if(itStart == itTemp)
                    itStart++;
                itTemp = mList.erase(itTemp);
            }
            else
                itTemp = itStart;

            itEnd = reverse_iterator<list<int>::iterator>(itTemp);

            if(itStart == mList.end())
                itStart = mList.begin();
            if(itEnd == mList.rend())
                itEnd = mList.rbegin();
        }

        printf("\n");
    }

    return 0;
}
