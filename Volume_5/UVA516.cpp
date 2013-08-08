/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *	+ Use Sieve of Erathosthenes to generate a list of primes less than 32767
 *	+ Find an integer N from the given prime base representation.
 *	+ Factorize N - 1 under the format of prime base representation.
 */

#include <cstdio>
#include <vector>
#include <utility>
#include <cstring>
#include <cstdlib>

using namespace std;

const int UPPERBOUND = 32767;
const int MAX_LEN_LINE = 10000;

void getPrimeBasePresentation(int n, vector<pair<int, int> > & primeRepresentation, const vector<int> & primeList);
void generatePrimeList(vector<int> & primeList, int upperBound);
int parseLineToGetNum(char line[]);

int main(void)
{
	vector<int> primeList;

	generatePrimeList(primeList, UPPERBOUND);
	
	char line[MAX_LEN_LINE + 1];
	vector<pair<int, int> > primeRepresentation;
	int n;

	while(1)
	{
		gets(line);
		
		n = parseLineToGetNum(line);
		if(n == 0)
			break;

		getPrimeBasePresentation(n - 1, primeRepresentation, primeList);

		bool isFirst = true;
		for(int i = (int) primeRepresentation.size() - 1; i >= 0; i--)
		{
			if(isFirst)
				isFirst = false;
			else
				printf(" ");
			printf("%d %d", primeRepresentation[i].first,
				primeRepresentation[i].second);
		} 
		printf("\n");
	}
	return 0;
}

void generatePrimeList(vector<int> & primeList, int upperBound)
{
	primeList.clear();

	vector<bool> primeSieve(upperBound + 1, true);

	for(int n = 2; n <= upperBound; n++)
		if(primeSieve[n])
		{
			primeList.push_back(n);

			for(int multipleN = n + n; multipleN <= upperBound; multipleN += n)
				primeSieve[multipleN] = false;
		}
}

int parseLineToGetNum(char line[])
{
	const char delim[] = " ";
	char * token;

	int prime, result = 1, power, temp;

	token = strtok(line, delim);
	while(token != NULL)
	{
		prime = atoi(token);
		if(prime == 0)
			return 0;

		token = strtok(NULL, delim);
		power = atoi(token);

		for(int i = 1; i <= power; i++)
			result *= prime;

		token = strtok(NULL, delim);
	}

	return result;
}

void getPrimeBasePresentation(int n, vector<pair<int, int> > & primeRepresentation, const vector<int> & primeList)
{
	primeRepresentation.clear();

	int prime, power, cpyN = n;

	for(int i = 0; i < (int) primeList.size(); i++)
	{
		prime = primeList[i];
		if(prime * prime > cpyN)
			break;

		power = 0;
		while(n % prime == 0)
		{
			power++;
			n /= prime;
		}

		if(power > 0)
			primeRepresentation.push_back(pair<int, int>(prime, power));
	}

	if(n > 1)
		primeRepresentation.push_back(pair<int, int> (n, 1));
}
