#include <cstdio>
#include <map>
#include <utility>

using namespace std;

#define MAX_NUM 200

int main(void)
{
	map<int, int> mapCubeToBase;
	map<int, int>::iterator it;

	for(int i = 2; i <= MAX_NUM; i++)
		mapCubeToBase[i * i * i] = i;	

	/* Find a, b, c, d such that
 	 *	a^3 = b^3 + c^3 + d^3 and 2 <= b <= c <= d
         */
	int cubeB, cubeC, cubeD, cubeA;
	for(int a = 2; a <= MAX_NUM; a++)
	{
		cubeA = a * a * a;
		for(int b = 2; 3 * (cubeB = b * b * b) <= cubeA; b++)
		{
			for(int c = b; 2 * (cubeC = c * c * c) + cubeB <= cubeA; c++)
			{
				cubeD = cubeA - cubeB - cubeC;
				it = mapCubeToBase.find(cubeD);
				if(it != mapCubeToBase.end())
				{
					printf("Cube = %d, Triple = (%d,%d,%d)\n", a, b, c, it->second);
				}
			}
		}
	} 

	return 0;
}
