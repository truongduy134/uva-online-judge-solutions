/*
 * UVA Problem ID: 10394 (Twin Primes)
 *
 * Twin primes are pairs of primes of the form (p, p + 2)
 *
 * Input:
 *  + The input will contain less than 10001 lines of input.
 *  + Each line contains an integer S (1 <= S <= 100000), which is the serial number of
 *          a twin prime pair.
 *  + Input file is terminated by end of file.
 *
 * Output:
 *  + For each line of input, print a line of output which contains the S-th twin prime pair.
 *  + The pair is printed in the form "(p1, p2)"
 *
 * Hint: Safely assume that the primes in the 100000-th twin prime pair are less than 20000000.
 */
#include <iostream>
#include <vector>

using namespace std;

#define MAX 20000000
#define MAX_GENERATE 100000

vector<int> generateTwinPrime(int, int);

int main()
{
    vector<int> twinPrimeList = generateTwinPrime(MAX_GENERATE, MAX);

    int serial;
    while(cin >> serial)
    {
        // Beware of 0-indexing in twinPrimeList and 1-indexing in the input number.
        cout << "(" << twinPrimeList[serial - 1] << ", " << twinPrimeList[serial - 1] + 2 << ")" << endl;
    }

    return 0;
}

// Generate the list of twin primes (p, p + 2) less than limit. Only p is stored in the result list.
vector<int> generateTwinPrime(int maxGenerate, int limit)
{
    // After execution, primeSieve[i] = true if i is a prime. Otherwise, primeSieve[i] = false
    vector<bool> primeSieve(limit, true);
    vector<int> twinPrimeList;
    int numGenerate = 0;

    primeSieve[0] = primeSieve[1] = false;

    for(int num = 0; num < limit; num++)
        if(primeSieve[num])
        {
            // num is a prime!
            if(primeSieve[num - 2])
            {
                // (num - 2, num) is a pair of twin prime
                numGenerate++;
                twinPrimeList.push_back(num - 2);

                if(numGenerate == maxGenerate)
                    return twinPrimeList;
            }

            for(int multiple = num + num; multiple < limit; multiple += num)
                primeSieve[multiple] = false;
        }

    return twinPrimeList;
}
