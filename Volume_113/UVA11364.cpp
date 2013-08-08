/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + Sort the locations of stores in the increasing order.
 *          L[1] < L[2] < ... < L[n]
 *  + Then we can park anywhere between L[1] and L[n] and obtain the optimal cost which is equal to
 *          2 * sum (L[i] - L[i - 1]) for i = 2, ... , n
 *
 *  + Time complexity:
 *      - O(n log n) if we use comparison sorts like merge sort, heap sort, etc.
 *      - O(n) if we use counting sort (note that L[i] is an integer less than 100)
 */

#include <algorithm>
#include <cstdio>

using namespace std;

const int MAX_NUM_STORE = 20;

int main(void)
{
    int T, numStore, location[MAX_NUM_STORE];

    scanf("%d", &T);
    while(T)
    {
        scanf("%d", &numStore);

        for(int i = 0; i < numStore; i++)
            scanf("%d", &location[i]);

        sort(location, location + numStore);

        int distWalk = 0;

        for(int i = 1; i < numStore; i++)
            distWalk += location[i] - location[i - 1];
        distWalk <<= 1;

        printf("%d\n", distWalk);

        T--;
    }
    return 0;
}


