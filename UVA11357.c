#include <stdio.h>
#include <string.h>

/* Methodology:
 *  + In this expression, we consider the expression S of the form
 *         S = (AND_CLAUSE) OR (AND_CLAUSE) OR ... (AND_CLAUSE)
 *      where AND_CLAUSE = literal AND literal AND literal ...
 *  + Therefore, S is false if and only if every AND_CLAUSE C such that
 *          C = a AND ~a AND AND_CLAUSE
 *    for some variable a.
 *
 *  + Otherwise, S is true
 */

#define MAX_LEN 1000
#define MAX_ALPHA 26
#define NOT_EXIST_YET 0
#define POSITIVE 1
#define NEGATIVE 2

int hasConflict(char andClause[]);
int isSatisfiable(char expr[]);

int main(void)
{
    char expr[MAX_LEN + 2], trash[MAX_LEN + 2];
    int T;

    /*freopen("in.txt", "r", stdin);*/

    scanf("%d", &T);
    fgets(trash, MAX_LEN + 2, stdin);

    while(T)
    {
        fgets(expr, MAX_LEN + 2, stdin);

        if(isSatisfiable(expr))
            printf("YES\n");
        else
            printf("NO\n");
        T--;
    }

    return 0;
}

int isSatisfiable(char expr[])
{
    char * andClause[MAX_LEN], *token, delimExpr[] = "|\n";
    int numAndClause = 0, i;

    token = strtok(expr, delimExpr);
    while(token != NULL)
    {
        andClause[numAndClause] = token;
        numAndClause++;

        token = strtok(NULL, delimExpr);
    }

    for(i = 0; i < numAndClause; i++)
        if(!hasConflict(andClause[i]))
            return 1;
    return 0;
}

int hasConflict(char andClause[])
{
    int variable[MAX_ALPHA] = {NOT_EXIST_YET}, varState, varAlpha;
    char *literal, delimAndClause[] = ")(&\n";

    literal = strtok(andClause, delimAndClause);
    while(literal != NULL)
    {
        varState = POSITIVE;
        if(literal[0] == '~')
        {
           varState = NEGATIVE;
           varAlpha = literal[1];
        }
        else
        {
            varAlpha = literal[0];
        }
        varAlpha -= 'a';

        if(variable[varAlpha] == NOT_EXIST_YET)
            variable[varAlpha] = varState;
        else
            if(variable[varAlpha] != varState)
                /* Both x and ~x exists in this AND clause */
                return 1;

        literal = strtok(NULL, delimAndClause);
    }

    return 0;
}
