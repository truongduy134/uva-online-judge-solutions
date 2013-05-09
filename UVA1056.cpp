#include <cstdio>
#include <map>
#include <string>
#include <cstring>

using namespace std;

#define MAX_PEOPLE 50
#define LEN_NAME 1000

int findMaxDegreeSeperation(int adjMat[][MAX_PEOPLE], int numV)
{
	int i, j, k, newVal;

	for(k = 0; k < numV; k++)
		for(i = 0; i < numV; i++)
			for(j = 0; j < numV; j++)
			{
				if(adjMat[i][k] && adjMat[k][j])
				{
					newVal = adjMat[i][k] + adjMat[k][j];
					if(newVal < adjMat[i][j] || adjMat[i][j] == 0)
						adjMat[i][j] = newVal;
				}	
			}

	int maxDegree = 0;

	for(i = 0; i < numV; i++)
		for(j = 0; j < numV; j++)
			if(i != j)
			{
				if(adjMat[i][j] == 0)
					return -1;
				if(adjMat[i][j] > maxDegree)
					maxDegree = adjMat[i][j];
			}	

	return maxDegree;

}

int main(void)
{
	int numV, numE, personId, adjMat[MAX_PEOPLE][MAX_PEOPLE], v[2], maxDegree, caseId;
	char name[LEN_NAME + 1];
	map<string, int> mapNameToId;
	map<string, int>::iterator it;

	caseId = 1;
	while(1)
	{
		scanf("%d %d", &numV, &numE);
		if(!(numV || numE))
			break;

		personId = 0;
		mapNameToId.clear();
		memset((int * )adjMat, 0, MAX_PEOPLE * MAX_PEOPLE * sizeof(int));		
		
		for(int i = 0; i < numE; i++)
		{
			for(int j = 0; j < 2; j++)
			{
				scanf("%s", name);
				it = mapNameToId.find(name);
				if(it != mapNameToId.end())
					v[j] = it->second;
				else
				{
					v[j] = personId;
					mapNameToId[name] = personId;
					personId++;
				}
				
			}
			
			adjMat[v[0]][v[1]] = 1;
			adjMat[v[1]][v[0]] = 1;			
		}

		maxDegree = findMaxDegreeSeperation(adjMat, numV);
		
		printf("Network %d: ", caseId);
		if(maxDegree < 0)
			printf("DISCONNECTED\n\n");
		else
			printf("%d\n\n", maxDegree);

		caseId++;		
	}	
	return 0;	
}
