#include <stdio.h>

int fastModularExpo(int base, int exponent, int modulo);

int main(void)
{
	int T, base, exponent, modulo;

	scanf("%d", &T);
	while(T)
	{
		scanf("%d %d %d", &base, &exponent, &modulo);

		printf("%d\n", fastModularExpo(base, exponent, modulo));
		T--;
	}
	return 0;
}

int fastModularExpo(int base, int exponent, int modulo)
{
	int halfResult, result;

	if(exponent == 0)
		return 1;
	if(exponent == 1)
		return base % modulo;

	halfResult = fastModularExpo(base, exponent >> 1, modulo);

	result = (halfResult * halfResult) % modulo;

	if(exponent & 1)
		result = ((base % modulo) * result) % modulo;

	return result;
}
