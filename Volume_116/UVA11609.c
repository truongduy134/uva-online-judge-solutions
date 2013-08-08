#include <stdio.h>

/* Methodology:
 *	+ The number of ways to select a team is
 *		A = sum (k * (N choose k) ) for k = 1 to N
 *	+ By considering the binomial expansionn of (x + 1) ^ N and differentiating both sides, we have:
		A = N * 2^(N - 1)
 *
 */

const unsigned long long int MOD = 1000000007;

unsigned long long int findNumWayToChooseTeam(unsigned long long int numPlayer);
unsigned long long int fastPowerMod(unsigned long long int base, unsigned long long int power, unsigned long long int mod);

int main(void)
{
	int T, caseId;
	unsigned long long int numPlayer;

	scanf("%d", &T);
	caseId = 1;

	while(caseId <= T)
	{
		scanf("%llu", &numPlayer);

		printf("Case #%d: %llu\n", caseId, findNumWayToChooseTeam(numPlayer));

		caseId++;
	}
	return 0;
}

unsigned long long int findNumWayToChooseTeam(unsigned long long int numPlayer)
{
	unsigned long long int result;

	result = fastPowerMod(2, numPlayer - 1, MOD);
	result = (numPlayer % MOD * result) % MOD;

	return result;
}

unsigned long long int fastPowerMod(unsigned long long int base, unsigned long long int power, unsigned long long int mod)
{
	if(base == 0)
		return 0;
	if(base == 1 || power == 0)
		return 1;
	if(power == 1)
		return base;

	unsigned long long int half = fastPowerMod(base, power >> 1, mod);
	unsigned long long int result = (half * half) % mod;

	if(power & 1)
		result = (result * (base % mod)) % mod;

	return result;
}
