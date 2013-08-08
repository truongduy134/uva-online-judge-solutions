/*******************************************************************************
 * Author: Nguyen Truong Duy
 *******************************************************************************/

/* Methodology:
 *	+ This is a straight-forward problem.
 *	+ We do not need to declare a 2D array after all.
 *	  Suppose the length of the input string is L^2
 *	  Then there are L columns and L rows
 *	  Elements in the first column are at index 0, L, 2L, 3L, ... L(L - 1) in the original string.
 *	  Similarly, elements in the i-th column are at index (from top to bottom):
 *		i, i + L, i + 2L, ..., i + L(L - 1)
 *	+ So we can decrypt the text without using an intermediate 2D array.
 *
 *	+ Time complexity: O(H) where H is the length of the original string
 */

#include <stdio.h>
#include <string.h>
#include <math.h>

const int MAX_LEN_LINE = 10000;
const int MAX_LEN_TRASH = 2;

int decryptText(char txt[], char result[]);

int main(void)
{
	int T;
	char txt[MAX_LEN_LINE + 1], decrypt[MAX_LEN_LINE + 1], trash[MAX_LEN_TRASH + 1];

	scanf("%d", &T);
	gets(trash);
	while(T)
	{
		gets(txt);
		if(decryptText(txt, decrypt))
			printf("%s\n", decrypt);
		else
			printf("INVALID\n");
		T--;
	}
	return 0;
}

int decryptText(char txt[], char result[])
{
	int len = (int) strlen(txt);
	int rootLen = (int) sqrt(len);

	if(rootLen * rootLen != len)
		return 0;
	
	int col, txtInd, curInd = 0;

	for(col = 0; col < rootLen; col++)
	{
		txtInd = col;
		while(txtInd < len)
		{
			result[curInd] = txt[txtInd];
			curInd++;
			txtInd += rootLen;
		}
	}
	result[len] = '\0';	
	return 1;
}
