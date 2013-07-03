/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + Use greedy approach.
 *  + Try to pack boxes of size 6, 5, 4, 3, 2, 1 in that order.
 *    For 1 packet, try to put as many boxes as possible.
 *
 *  + A packet can fully contain
 *      - 1 box of size 6 x 6.
 *      - 1 box of size 5 x 5 and 11 boxes of size 1 x 1
 *      - 1 box of size 4 x 4 and 5 boxes of size 2 x 2
 *      - 4 boxes of size 3 x 3
 *      - 3 boxes of size 3 x 3, 1 boxes of size 2 x 2, and 5 boxes of size 1 x 1
 *      - 2 boxes of size 3 x 3, 3 boxes of size 2 x 2, and 6 boxes of size 1 x 1
 *      - 1 box of size 3 x 3, 5 boxes of size 2 x 2, and 7 boxes of size 1 x 1
 *      - etc.
 */

#include <stdio.h>

const int NUM_KIND_SIZE = 6;
const int NUM_SQUARE_IN_SIZE[] = {0, 1, 4, 9, 16, 25, 36};
const int MAX_NUM_BOX_FITTED[] = {0, 36, 9, 4, 1, 1, 1};

int findMinPacket(int numBox[NUM_KIND_SIZE + 1]);
int findMin(int a, int b);

int main(void)
{
    int numBox[NUM_KIND_SIZE + 1], i, allZero;

    while(1)
    {
        allZero = 1;

        for(i = 1; i <= NUM_KIND_SIZE; i++)
        {
            scanf("%d", &numBox[i]);
            if(numBox[i] > 0)
                allZero = 0;
        }

        if(allZero)
            break;

        printf("%d\n", findMinPacket(numBox));
    }
    return 0;
}

int findMinPacket(int numBox[NUM_KIND_SIZE + 1])
{
    int numPacket = 0, numBoxTwoUse, numBoxOneUse, maxNumBoxTwo;

    /* Handle 6 x 6 boxes first */
    numPacket += numBox[6];

    /* Handle 5 x 5 boxes */
    numPacket += numBox[5];
    /* After putting a 5 x 5 box into a 6 x 6 packet, we can put 11 more 1 x 1 boxes */
    numBox[1] -= findMin(numBox[1], (NUM_SQUARE_IN_SIZE[6] - NUM_SQUARE_IN_SIZE[5]) * numBox[5]);

    /* Handle 4 x 4 boxes */
    numPacket += numBox[4];
    /* After putting a 4 x 4 box into a 6 x 6 packet, we can put 5 more 2 x 2 boxes */
    numBoxTwoUse = findMin(numBox[2], (NUM_SQUARE_IN_SIZE[6] - NUM_SQUARE_IN_SIZE[4]) *
                              numBox[4] / NUM_SQUARE_IN_SIZE[2]);
    numBox[2] -= numBoxTwoUse;
    numBoxOneUse = findMin(numBox[1], (NUM_SQUARE_IN_SIZE[6] - NUM_SQUARE_IN_SIZE[4]) * numBox[4] -
                           numBoxTwoUse * NUM_SQUARE_IN_SIZE[2]);
    numBox[1] -= numBoxOneUse;

    /* Handle 3 x 3 boxes */
    numPacket += numBox[3] / MAX_NUM_BOX_FITTED[3];
    int numBoxThreeLeft = numBox[3] % MAX_NUM_BOX_FITTED[3];
    if(numBoxThreeLeft)
    {
        numPacket++;
        switch(numBoxThreeLeft)
        {
            case 3:
                /* Can put at most 1 box of size 2, and 5 boxes of size 1 */
                maxNumBoxTwo = 1;
                break;
            case 2:
                /* Can put at most 3 boxes of size 2, and 6 boxes of size 1 */
                maxNumBoxTwo = 3;
                break;
            case 1:
                /* Can put at most 5 box of size 2, and 7 boxes of size 1 */
                maxNumBoxTwo = 5;
                break;
            default:
                maxNumBoxTwo = 0;
        }
        numBoxTwoUse = findMin(numBox[2], maxNumBoxTwo);
        numBox[2] -= numBoxTwoUse;
        numBoxOneUse = findMin(numBox[1], NUM_SQUARE_IN_SIZE[6] - numBoxThreeLeft *
                               NUM_SQUARE_IN_SIZE[3] - numBoxTwoUse * NUM_SQUARE_IN_SIZE[2]);
        numBox[1] -= numBoxOneUse;
    }

    /* Handle 2 x 2 boxes */
    numPacket += numBox[2] / MAX_NUM_BOX_FITTED[2];
    if(numBox[2] % MAX_NUM_BOX_FITTED[2])
    {
        numPacket++;
        numBoxOneUse = findMin(numBox[1], NUM_SQUARE_IN_SIZE[6] - (numBox[2] % MAX_NUM_BOX_FITTED[2]) *
                               NUM_SQUARE_IN_SIZE[2]);
        numBox[1] -= numBoxOneUse;
    }

    /* Handle 1 x 1 boxes */
    numPacket += numBox[1] / MAX_NUM_BOX_FITTED[1];
    if(numBox[1] % MAX_NUM_BOX_FITTED[1])
        numPacket++;

    return numPacket;
}

int findMin(int a, int b)
{
    if(a < b)
        return a;
    return b;
}
