/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology
 *
 *  + Generate all primes less than 1299710 using Sieve of Eratosthenes algorithm. Let the list be L
 *  + For each input value v > 1, if v is a prime, the prime gap is 0.
 *  + Otherwise, let i be the index of the smallest prime larger than v. We can find i using binary search.
 *    The prime gap is L[i] - L[i - 1]
 */

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_SIZE = 1299710;

void generatePrimeSieve(vector<bool> & primeSieve) {
    fill(primeSieve.begin(), primeSieve.end(), true);
    primeSieve[0] = false;
    primeSieve[1] = false;

    for (int p = 2; p < primeSieve.size(); p++) {
        if (primeSieve[p]) {
            // Multiple of p is not a prime
            for (int multipleP = p + p; multipleP < primeSieve.size(); multipleP += p) {
                primeSieve[multipleP] = false;
            }
        }
    }
}

void generatePrimeListFromSieve(vector<int> & primeList, const vector<bool> & primeSieve) {
    primeList.clear();
    for (int p = 2; p < primeSieve.size(); p++) {
        if (primeSieve[p]) {
            primeList.push_back(p);
        }
    }
}

int main(void) {
    vector<bool> primeSieve(MAX_SIZE);
    vector<int> primeList;

    // Preprocessing
    generatePrimeSieve(primeSieve);
    generatePrimeListFromSieve(primeList, primeSieve);

    int val;
    int primeGap;
    int upperboundPrime;
    int lowerboundPrime;
    vector<int>::iterator upperboundIterator;

    while (1) {
        scanf("%d", &val);
        if (!val) {
            break;
        }

        if (primeSieve[val]) {
            primeGap = 0;
        } else {
            upperboundIterator = upper_bound(primeList.begin(), primeList.end(), val);
            upperboundPrime = *upperboundIterator;
            upperboundIterator--;
            lowerboundPrime = *upperboundIterator;
            primeGap = upperboundPrime - lowerboundPrime;
        }

        printf("%d\n", primeGap);
    }

    return 0;
}
