/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 * + We need a data structure that support fast on-line finding max and min elements
 * + STL multiset is suitable for this problem. We can find max and min in
 *      constant time. Insertion takes logarithmic time.
 */

#include <cstdio>
#include <set>
#include <iterator>

using namespace std;

int main(void) {
    int numDay, numBill, billValue;
    multiset<int> billList;
    long long promotionCost = 0;
    int maxBill, minBill;

    while (1) {
        scanf("%d", &numDay);
        if (numDay < 1) {
            break;
        }

        billList.clear();
        promotionCost = 0;

        for (int i = 0; i < numDay; i++) {
            scanf("%d", &numBill);

            for (int k = 0; k < numBill; k++) {
                scanf("%d", &billValue);
                billList.insert(billValue);
            }

            maxBill = *(billList.rbegin());
            minBill = *(billList.begin());
            promotionCost += (maxBill - minBill);

            // Remove these bills from the list
            billList.erase(billList.begin());
            billList.erase(billList.find(maxBill));
        }

        printf("%lld\n", promotionCost);
    }

    return 0;
}
