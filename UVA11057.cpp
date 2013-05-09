/*
 * UVA Problem ID: 11057 (Exact Sum)
 *
 * Input:
 *  + The input consists of multiple test cases.
 *  + Each test case starts with 2 <= N <= 10000, the number of available books.
 *  + Next line will have N integers, representing the price of each book, a book costs less than
 *          1000001.
 *  + Then there is another line with an integer M, representing how much money Peter has.
 *  + There is a blank line after each test case.
 *  + The input is terminated by end of file (EOF).
 *
 * Output:
 *  + For each test case, print the message: "Peter should buy books whose prices are i and j.",
 *    where i and j are the prices of the books whose sum is equal do M and i <= j.
 *  + Assumption: there is always possible to find a solution.
 *         If there are multiple solutions print the solution that minimizes the difference
 *         between the prices i and j.
 *  + After each test case you must print a blank line.
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

pair<int, int> findExactSum(vector<int> & , int);

int main()
{
    int numBook, totalMoney;
    while(cin >> numBook)
    {
        vector<int> bookPrice(numBook);

        for(int index = 0; index < numBook; index++)
            cin >> bookPrice[index];

        cin >> totalMoney;

        pair<int, int> optimalPair = findExactSum(bookPrice, totalMoney);

        cout << "Peter should buy books whose prices are " << optimalPair.first << " and "
                << optimalPair.second << "." << endl << endl;
    }

    return 0;
}

// Find a pair (i, j) in arr such that i <= j and i + j = sum.
// If there are multiple such pairs, choose the pair that minimizes j - i.
pair<int, int> findExactSum(vector<int> & arr, int sum)
{
    // Sort the vector in non-decreasing order
    sort(arr.begin(), arr.end());

    pair<int, int> optimalPair;
    bool notInitialize = true;

    int left = 0;
    int right = arr.size() - 1;
    while(left < right)
    {
        if(arr[left] + arr[right] > sum)
            // Should reduce the sum
            right--;
        else
            if(arr[left] + arr[right] < sum)
                left++;
            else
            {
                // Equality happens
                if(notInitialize)
                {
                    notInitialize = false;
                    optimalPair = make_pair(arr[left], arr[right]);
                }
                else
                {
                    if(optimalPair.second - optimalPair.first > arr[right] - arr[left])
                        optimalPair = make_pair(arr[left], arr[right]);
                }
                left++;
                right--;
            }
    }

    return optimalPair;
}
