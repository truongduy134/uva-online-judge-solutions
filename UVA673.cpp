
#include <iostream>
#include <string>
#include <stack>
using namespace std;

#define MAX 150
bool isParenthesesBalance(string);

int main()
{
    char buffer[MAX];

    int numTest;
    cin >> numTest;
    cin.getline(buffer, MAX);

    while(numTest)
    {
        cin.getline(buffer, MAX);
        string expr(buffer);

        if(isParenthesesBalance(expr))
            cout << "Yes" << endl;
        else
            cout << "No" << endl;

        numTest--;
    }

    return 0;
}

// Return true if expr is parentheses balanced. Return false otherwise.
// There are only 2 kinds of parentheses: () and []
bool isParenthesesBalance(string expr)
{
    stack<char> openParenStack;

    int lenExpr = expr.length();

    for(int index = 0; index < lenExpr; index++)
    {
        if(expr[index] == '(' || expr[index] == '[')
           openParenStack.push(expr[index]);
        else
        {
            // There is a right parenthesis
            if(openParenStack.empty())
                return false;

            char topStack = openParenStack.top();
            openParenStack.pop();

            if((expr[index] == ')' && topStack != '(') ||
               (expr[index] == ']' && topStack != '['))
                return false;
        }
    }

    if(!openParenStack.empty())
        return false;

    return true;
}
