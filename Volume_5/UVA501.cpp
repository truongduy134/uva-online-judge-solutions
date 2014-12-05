/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 * - Maintain two heaps maxH (max heap) and minH (min heap) with the property:
 * the size of maxH is always i (i is the counter variable of the black box
 * structure) (**)
 * - When inserting a new element E, first insert E into maxH. If the size of
 * maxH violates the property (**), pop the maximum element in maxH and insert
 * it into minH
 * - When querying the i-th minimum number, use the minimum element in minH
 * as the return value. Increment i. Then pop the minimum element in minH, and
 * insert it into maxH.
 *
 * Time complexity: O(log n) per insertion and i-th minimum querying
 * Space complexity: O(n)
 */

#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

class BlackBox {

private:
  priority_queue<int> _maxHeap;
  priority_queue<int, vector<int>, greater<int> > _minHeap;
  int _counter;

public:
  BlackBox() {
    _counter = 0;
  }

  void add(int newElement) {
    _maxHeap.push(newElement);
    if (_maxHeap.size() >= _counter) {
      int maxHeapTop = _maxHeap.top();
      _maxHeap.pop();
      _minHeap.push(maxHeapTop);
    }
  }

  int queryKMin() {
    int minHeapTop = _minHeap.top();
    _minHeap.pop();
    _maxHeap.push(minHeapTop);
    _counter++;
    return minHeapTop;
  }
};

int main(void) {
  int numTest, numAdd, numGet;
  vector<int> addList, getInstrPosList, result;

  scanf("%d", &numTest);
  while (numTest) {
    scanf("%d %d", &numAdd, &numGet);
    addList.assign(numAdd, 0);
    getInstrPosList.assign(numGet, 0);
    result.assign(numGet, 0);
    for (int i = 0; i < numAdd; ++i) {
      scanf("%d", &addList[i]);
    }
    for (int i = 0; i < numGet; ++i) {
      scanf("%d", &getInstrPosList[i]);
    }

    BlackBox blackBox;
    int addInd = 0;
    int getQueryInd = 0;
    while (getQueryInd < numGet) {
      int numAddBeforeGet = getInstrPosList[getQueryInd];
      while (addInd < numAddBeforeGet && addInd < numAdd) {
        blackBox.add(addList[addInd]);
        addInd++;
      }

      result[getQueryInd] = blackBox.queryKMin();
      getQueryInd++;
    }

    for (int i = 0; i < numGet; ++i) {
      printf("%d\n", result[i]);
    }
    if (numTest > 1) {
      printf("\n");
    }
    numTest--;
  }

  return 0;
}

