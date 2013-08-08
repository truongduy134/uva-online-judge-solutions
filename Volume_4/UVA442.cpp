/*******************************************************************************
 * Author: Nguyen Truong Duy
 *******************************************************************************/

/* Methodology:
 *	+ Let (m, n) represent the matrix of size m x n
 *	+ Let T be the total number of elementary operations performed.
 *	  Initially T = 0
 *
 * 	+ We assume the input expression is correct.
 *	+ We maintain a stack S
 *	+ Going from left to right,
 *		- If we encounter '(', ignore
 *		- If we encounter an alphabet, push the size of the matrix into the stack
 *		- If we encounter ')', if S has only 1 element, do nothing.
 *		  Otherwise, pop the top 2 elements (m2, n2) (top) and (m1, n1) (second top) from the stack.
 *		 	* If m2 != n1, error
 *			* If m2 = n1, then T += m1 * n1 * n2 (The number of elementary operation perform to multiple an m x n and n x r matrix is m x n x r).
 *			  Push (m1, n2) to the stack.
 *
 *	+ Time complexity: O(N) where N is the number of matrices in the expression.
 */

#include <cstdio>
#include <stack>
#include <cctype>

using namespace std;

struct MatrixSize
{
	int numRow, numCol;

	MatrixSize() : numRow(0), numCol(0) {}
	MatrixSize(int iNumRow, int iNumCol) : numRow(iNumRow), numCol(iNumCol) {}
	MatrixSize(const MatrixSize & another) :
		numRow(another.numRow), numCol(another.numCol) {}
};

const int MAX_NUM_MAT = 26;
const int MAX_LEN_EXPR = 100000;
const int MAX_LEN_ID = 1;

int computeNumElementaryOp(MatrixSize matArr[], char expr[]);

int main(void)
{
	MatrixSize matArr[MAX_NUM_MAT];
	char matId[MAX_LEN_ID + 1], expr[MAX_LEN_EXPR + 1], trash[MAX_LEN_ID + 1];
	int numRow, numCol, numMat, numOp;

	for(int i = 0; i < MAX_NUM_MAT; i++)
		matArr[i].numRow = matArr[i].numCol = 0;

	scanf("%d", &numMat);
	for(int i = 0; i < numMat; i++)
	{
		scanf("%s %d %d", matId, &numRow, &numCol);
		matArr[(int) matId[0] - 'A'].numRow = numRow;
		matArr[(int) matId[0] - 'A'].numCol = numCol;
	}
	gets(trash);

	while(gets(expr) != NULL)
	{
		numOp = computeNumElementaryOp(matArr, expr);

		if(numOp < 0)
			printf("error\n");
		else
			printf("%d\n", numOp);
	}

	return 0;
}

int computeNumElementaryOp(MatrixSize matArr[], char expr[])
{
	stack<MatrixSize> matStack;
	int numOp = 0;

	for(int i = 0; expr[i] != '\0'; i++)
	{
		if(isalpha(expr[i]))
			matStack.push(matArr[(int) expr[i] - 'A']);
		
		if(expr[i] == ')')
		{
			if(matStack.size() < 2)
				continue;

			MatrixSize two = matStack.top();
			matStack.pop();
			MatrixSize one = matStack.top();
			matStack.pop();

			if(one.numCol != two.numRow)
				return -1;
			numOp += one.numRow * one.numCol * two.numCol;

			matStack.push(MatrixSize(one.numRow, two.numCol));
		}
	}

	return numOp;
}
