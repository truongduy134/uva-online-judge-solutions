/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 * - Key observation: the real time and the mirror time sum up to 12:00 or 24:00
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10

int main(void) {
  char hhmm[MAX_SIZE + 1];
  char *token;
  int numCases, hour, minute, mirrorHour, mirrorMinute;

  scanf("%d", &numCases);
  while (numCases--) {
    scanf("%s", hhmm);

    token = strtok(hhmm, ":");
    mirrorHour = atoi(token);
    token = strtok(NULL, ":");
    mirrorMinute = atoi(token);

    minute = 60 - mirrorMinute;
    hour = 23 - mirrorHour;
    if (minute == 60) {
      hour++;
      minute = 0;
    }
    if (hour > 12) {
      hour -= 12;
    }

    printf("%02d:%02d\n", hour, minute);
  }

  return 0;
}

