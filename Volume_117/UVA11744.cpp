/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/**
 * Methodology:
 * - Straightforward problem.
 * - The use of C++ bitset library and long long type makes the coding simpler
 */

#include <cstdio>
#include <bitset>

using namespace std;

#define MAX_LENGTH 31
const long long MAX_VALUE = ((long long) 1) << MAX_LENGTH;

int main(void) {
  char strA[MAX_LENGTH + 1], strB[MAX_LENGTH + 1];
  int numTests;
  long long a, b, c, d;

  scanf("%d", &numTests);
  while (numTests) {
    scanf("%s %s", strA, strB);

    a = bitset<MAX_LENGTH>(string(strA)).to_ulong();
    b = bitset<MAX_LENGTH>(string(strB)).to_ulong();

    do {
      printf(
        "%s %s\n",
        bitset<MAX_LENGTH>(a).to_string().c_str(),
        bitset<MAX_LENGTH>(b).to_string().c_str()
      );

      c = a ^ b;
      d = a & b;
      a = c;
      b = d << 1;
    } while (b && b < MAX_VALUE);

    printf(
      "%s %s\n",
      bitset<MAX_LENGTH>(a).to_string().c_str(),
      (!b) ? bitset<MAX_LENGTH>(b).to_string().c_str() : "overflow"
    );

    if (numTests > 1) {
      printf("\n");
    }

    numTests--;
  }

  return 0;
}
