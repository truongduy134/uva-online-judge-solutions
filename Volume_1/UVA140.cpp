/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *	+ Because the graph has at most 8 vertices, we can use brute-force approach
 *		for this problem.
 *	+ Consider all V! vertex ordering (N <= 8). For each ordering, compute its
 *		bandwidth in O(V^2) (using double nested loops).
 *	+ Then choose an ordering with minimum bandwidth.
 *
 *	+ Time complexity: O(V! * V^2)
 */

#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_NUM_ALPHA = 26;
const int MAX_LEN_LINE = 10000;

int ComputeBandwidth(char order[], bool adjmat[MAX_NUM_ALPHA][MAX_NUM_ALPHA]);
void ConstructAdjMat(char graphstr[], bool adjmat[MAX_NUM_ALPHA][MAX_NUM_ALPHA], char vertexlist[]);

int main(void)
{
	char graphstr[MAX_LEN_LINE + 1];
	int minbandwidth = -1;
	char order[MAX_LEN_LINE + 1], resultorder[MAX_LEN_LINE + 1];
	bool adjmat[MAX_NUM_ALPHA][MAX_NUM_ALPHA];

	while(1)
	{
		scanf("%s", graphstr);
		if(graphstr[0] == '#')
			break;

		// It is guaranteed order is a string of vertex names in alphabetical order
		ConstructAdjMat(graphstr, adjmat, order);
		int numv = strlen(order);

		minbandwidth = -1;
		do
		{
			int bandwidth = ComputeBandwidth(order, adjmat);
			if(minbandwidth < 0 || bandwidth < minbandwidth)
			{
				minbandwidth = bandwidth;
				strcpy(resultorder, order);
			}
		} while(next_permutation(order, order + numv));

		for(int i = 0; resultorder[i] != '\0'; ++i)
			printf("%c ", resultorder[i]);
		printf("-> %d\n", minbandwidth);
	}
	return 0;
}

int ComputeBandwidth(char order[], bool adjmat[MAX_NUM_ALPHA][MAX_NUM_ALPHA])
{
	int bandwidth = 0;

	for(int uind = 0; order[uind] != '\0'; uind++)
		for(int vind = uind + 1; order[vind] != '\0'; vind++)
		{
			int u = order[uind] - 'A';
			int v = order[vind] - 'A';
			if(adjmat[u][v])
			{
				int val = vind - uind;
				if(val > bandwidth)
					bandwidth = val;
			}
		}

	return bandwidth;
}

void ConstructAdjMat(char graphstr[], bool adjmat[MAX_NUM_ALPHA][MAX_NUM_ALPHA], char vertexlist[])
{
	for(int u = 0; u < MAX_NUM_ALPHA; u++)
		for(int v = 0; v < MAX_NUM_ALPHA; v++)
			adjmat[u][v] = false;

	char *token;
	char delim[] = ";";
	
	int present[MAX_NUM_ALPHA] = {0};
	token = strtok(graphstr, delim);
	while(token != NULL)
	{
		int u = token[0] - 'A';
		present[u] = 1;
		for(int ind = 2; token[ind] != '\0'; ind++)
		{
			int v = token[ind] - 'A';
			present[v] = 1;
			adjmat[u][v] = true;
			adjmat[v][u] = true;
		}

		token = strtok(NULL, delim);
	}

	int lenvlist = 0;
	for(int i = 0; i < MAX_NUM_ALPHA; i++)
		if(present[i])
			vertexlist[lenvlist++] = (char) ('A' + i);
	vertexlist[lenvlist] = '\0';
}
