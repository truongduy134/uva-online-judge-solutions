#include <cstdio>
#include <string>

using namespace std;

#define MAX_LEN 60

int findIndexOfChar(char str[], int s, int e, char key)
{
    for(int i = s; i <= e; i++)
        if(str[i] == key)
            return i;

    return -1;
}

void findPostOrder(char preOrder[], int startPre, int endPre,
                   char inOrder[], int startIn, int endIn, string & postOrder)
{
    // Base case
    if(startPre > endPre || startIn > endIn)
        return;

    int ind = findIndexOfChar(inOrder, startIn, endIn, preOrder[startPre]);

    // In inOrder, left subtree is from startIn to ind - 1
    // In preOrder, left subtree is from startPre + 1 to startPre + (ind - startIn)
    // Go left first
    findPostOrder(preOrder, startPre + 1, startPre + ind - startIn,
                  inOrder, startIn, ind - 1, postOrder);


    // In inOrder, right subtree is from ind + 1 to endIn
    // In preOrder, right subtree is from startPre + (ind - startIn) + 1 to endPre
    // Go right
    findPostOrder(preOrder, startPre + ind - startIn + 1, endPre,
                  inOrder, ind + 1, endIn, postOrder);

    // Visit root
    postOrder.push_back(preOrder[startPre]);
}
int main(void)
{
    int T, len;
    char preOrder[MAX_LEN + 1], inOrder[MAX_LEN + 1];
    string postOrder;

//    freopen("in.txt", "r", stdin);

    scanf("%d", &T);
    while(T)
    {
        postOrder.clear();
        scanf("%d %s %s", &len, preOrder, inOrder);

        findPostOrder(preOrder, 0, len - 1, inOrder, 0, len - 1, postOrder);

        printf("%s\n", postOrder.c_str());
        T--;
    }
    return 0;
}