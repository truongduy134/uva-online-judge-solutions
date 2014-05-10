/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

#include <stdio.h>
#include <string.h>

#define MAX_STRING_LENGTH 80

int main(void) {
    int i, j;
    int numRequirement, numProposal, numSatisfy, maxSatisfy;
    int testCase;
    double price, minPrice;
    char proposalName[MAX_STRING_LENGTH + 1], bestProposalName[MAX_STRING_LENGTH + 1], trash[MAX_STRING_LENGTH + 1];
    int isFirst;

    testCase = 1;
    isFirst = 1;
    while(1) {
        minPrice = -1;
        maxSatisfy = 0;

        scanf("%d %d", &numRequirement, &numProposal);
        if (!(numRequirement && numProposal)) {
            break;
        }
        gets(trash); /* Get rid of trailing end-of-line */

        if (isFirst) {
            isFirst = 0;
        } else {
            printf("\n");
        }

        for (i = 0; i < numRequirement; i++) {
            gets(trash);
        }
        
        for (i = 0; i < numProposal; i++) {
            gets(proposalName);
            scanf("%lf %d", &price, &numSatisfy);
            gets(trash);    /* Get rid of trailing end-of-line */
            for (j = 0; j < numSatisfy; j++) {
                gets(trash);
            }

            if (numSatisfy > maxSatisfy ||
                (numSatisfy == maxSatisfy && (minPrice < 0 || price < minPrice))) {
                minPrice = price;
                maxSatisfy = numSatisfy;
                strcpy(bestProposalName, proposalName);
            }
        }

        printf("RFP #%d\n%s\n", testCase, bestProposalName);

        testCase++;
    }

    return 0;
}
