/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + This problem can be solved using C++ STL set (which is implemented as a balanced search tree)
 *
 *  + We encode the opinion of person i as a string S of length T (where T is the number of trees)
 *          S[k] = 'T' if person i heard tree k fall.
 *          S[k] = 'F' if person i did not hear tree k fall.
 *  + So now we have P strings (representing the opinions of P people).
 *  + The original problem now becomes counting the number of distinct strings among those P strings.
 *    This can be done using C++ STL set.
 *
 *  + Time complexity: O(P * T * logP) where P, T < 100
 */

#include <cstdio>
#include <string>
#include <set>

using namespace std;

const int MAX_SIZE = 100;
const int MAX_LEN_LINE = 100;

int countNumDistinctHearing(char heardMat[][MAX_SIZE + 1], int numPeople, int numTree);

int main(void)
{
    // heardMat[i][j] = 'T' if person i hears tree j fall.
    // heardMat[i][j] = 'F' otherwise
    char heardMat[MAX_SIZE][MAX_SIZE + 1];
    int numPeople, numTree, T;
    char line[MAX_LEN_LINE + 1], trash[MAX_LEN_LINE + 1];

    scanf("%d", &T);
    gets(trash);
    gets(trash);

    while(T)
    {
        scanf("%d %d", &numPeople, &numTree);
        gets(trash);

        for(int p = 0; p < numPeople; p++)
            for(int t = 0; t < numTree; t++)
                heardMat[p][t] = 'F';

        while(gets(line) != NULL)
        {
            if(line[0] == '\0')
                break;

            int person, tree;
            sscanf(line, "%d %d", &person, &tree);
            person--;
            tree--;
            heardMat[person][tree] = 'T';
        }

        printf("%d\n", countNumDistinctHearing(heardMat, numPeople, numTree));
        if(T > 1)
            printf("\n");
        T--;
    }
    return 0;
}

int countNumDistinctHearing(char heardMat[][MAX_SIZE + 1], int numPeople, int numTree)
{
    set<string> heardSet;

    for(int p = 0; p < numPeople; p++)
        heardMat[p][numTree] = '\0';
    for(int p = 0; p < numPeople; p++)
        heardSet.insert(heardMat[p]);

    return (int) heardSet.size();
}
