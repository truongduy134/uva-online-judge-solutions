/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + Use the straight-forward recursive algorithm.
 *  + It is better to use STL C++ list (or self-implementing linked list data structure)
 *      because list supports O(1) insertion and deletion given a pointer to the position.
 *
 *  + Time complexity: O(n * n!) to generate all n! permutations (since all characters are distinct)
 *      and print them.
 */

#include <list>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAX_LEN = 10;

void printKnuthPermutation(char str[], int ind, list<char> & permutation);
void printList(const list<char> & permutation);

int main(void)
{
    char str[MAX_LEN + 1];
    bool isFirst = true;
    list<char> permutation;

    while(scanf("%s", str) > 0)
    {
        if(isFirst)
            isFirst = false;
        else
            printf("\n");

        printKnuthPermutation(str, 0, permutation);
    }
    return 0;
}

void printKnuthPermutation(char str[], int ind, list<char> & permutation)
{
    if(str[ind] == '\0')
    {
        printList(permutation);
        return;
    }

    if(ind == 0)
        permutation.clear();

    // IMPORTANT: This loop does not handle the case we insert the new character at the end of the list
    for(list<char>::iterator it = permutation.begin(); it != permutation.end(); ++it)
    {
        list<char>::iterator newIt = permutation.insert(it, str[ind]);
        // Recurse
        printKnuthPermutation(str, ind + 1, permutation);

        // Backtrack
        it = permutation.erase(newIt);
    }

    // Append at the end of the list
    permutation.push_back(str[ind]);
    printKnuthPermutation(str, ind + 1, permutation);
    permutation.pop_back();
}

void printList(const list<char> & permutation)
{
    char str[MAX_LEN + 1];
    int len = 0;

    for(list<char>::const_iterator it = permutation.begin(); it != permutation.end(); ++it)
    {
        str[len] = *it;
        len++;
    }
    str[len] = '\0';
    printf("%s\n", str);
}
