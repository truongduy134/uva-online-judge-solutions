/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *  + Note that there are always 2 * N input segments
 *  + For any two segments L1 and L2, compute L = L1 + L2. Let S be the list of all such strings L
 *  + The answer to the problem is a string L in S that has frequency equal to N. We can maintain
 *      a map that maps string L to an integer (representing frequency) to find the answer efficiently
 */

#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <map>
#include <vector>

using namespace std;

void reconstructFile(const vector<string> & segmentList, string & fileContent) {
    int numSegment = segmentList.size();
    map<string, int> frequencyMap;

    for (int i = 0; i < numSegment; i++) {
        for (int j = 0; j < numSegment; j++) {
            if (i == j) {
                continue;
            }

            string combinedSegment = segmentList[i] + segmentList[j];
            if (frequencyMap.find(combinedSegment) == frequencyMap.end()) {
                frequencyMap[combinedSegment] = 1;
            } else {
                frequencyMap[combinedSegment]++;
            }

            if (frequencyMap[combinedSegment] == (numSegment >> 1)) {
                fileContent = combinedSegment;
                return;
            }
        }
    }
}

int main(void) {
    int numTest;
    string trash, segment, fileContent;
    vector<string> segmentList;

    scanf("%d", &numTest);
    getline(cin, trash);
    getline(cin, trash);

    while(numTest) {
        segmentList.clear();

        while(getline(cin, segment)) {
            if (segment.length() == 0) {
                break;
            }
            segmentList.push_back(segment);
        }

        reconstructFile(segmentList, fileContent);
        printf("%s\n", fileContent.c_str());
        if (numTest > 1) {
            printf("\n");
        }

        numTest--;
    }

    return 0;
}
