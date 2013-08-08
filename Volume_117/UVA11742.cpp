/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + Since the input size is small (n <= 8), we can generate 8! permutations and count
 *      the number of permutations satisfying the constraints
 */

#include <cstdio>
#include <algorithm>

using namespace std;

struct SeatConstraint {
    int pOne, pTwo, relativeDist;

    SeatConstraint() : pOne(0), pTwo(0), relativeDist(0) {}
    SeatConstraint(int iPOne, int iPTwo, int iRelativeDist) :
        pOne(iPOne), pTwo(iPTwo), relativeDist(iRelativeDist) {}
    SeatConstraint(const SeatConstraint & another) :
        pOne(another.pOne), pTwo(another.pTwo), relativeDist(another.relativeDist) {}
};

const int MAX_NUM_CONSTRAINT = 20;

int abs(int x);
int countNumPermutation(int numPeople, SeatConstraint constraintArr[], int numConstraint);
bool satisfyConstraintArr(int arrangement[], int numPeople, SeatConstraint constraintArr[], int numConstraint);
int findIndex(int arrangement[], int numPeople, int id);

int main(void)
{
    int numPeople, numConstraint;
    SeatConstraint constraintArr[MAX_NUM_CONSTRAINT];

    while(1)
    {
        scanf("%d %d", &numPeople, &numConstraint);
        if(numPeople == 0 && numConstraint == 0)
            break;

        for(int i = 0; i < numConstraint; i++)
            scanf("%d %d %d", &constraintArr[i].pOne,
                  &constraintArr[i].pTwo, &constraintArr[i].relativeDist);

        printf("%d\n", countNumPermutation(numPeople, constraintArr, numConstraint));
    }
    return 0;
}

int countNumPermutation(int numPeople, SeatConstraint constraintArr[], int numConstraint)
{
    int arrangement[numPeople];

    for(int i = 0; i < numPeople; i++)
        arrangement[i] = i;

    int countArrangement = 0;
    do
    {
        if(satisfyConstraintArr(arrangement, numPeople, constraintArr, numConstraint))
            countArrangement++;
    } while(next_permutation(arrangement, arrangement + numPeople));

    return countArrangement;
}

bool satisfyConstraintArr(int arrangement[], int numPeople, SeatConstraint constraintArr[], int numConstraint)
{
    int indOne, indTwo, dist, requireDist;
    for(int i = 0; i < numConstraint; i++)
    {
        indOne = findIndex(arrangement, numPeople, constraintArr[i].pOne);
        indTwo = findIndex(arrangement, numPeople, constraintArr[i].pTwo);
        if(indOne < 0 || indTwo < 0)
            return false;

        dist = abs(indTwo - indOne);
        requireDist = abs(constraintArr[i].relativeDist);

        if(constraintArr[i].relativeDist < 0)
        {
            // Two people must sit at least requireDist seat apart
            if(dist < requireDist)
                return false;
        }
        else
        {
            // Two people must sit at most requireDist seat apart
            if(dist > requireDist)
                return false;
        }
    }

    return true;
}

int findIndex(int arrangement[], int numPeople, int id)
{
    for(int i = 0; i < numPeople; i++)
        if(arrangement[i] == id)
            return i;

    return -1;
}

int abs(int x)
{
    return (x < 0) ? -x : x;
}
