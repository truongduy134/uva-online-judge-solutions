#include <stdio.h>

double convertCToFDegree(double cDegree);
double convertFToCDegree(double fDegree);

int main(void)
{
	int T, caseId;
	double oldCelcius, fChange;

	scanf("%d", &T);
	caseId = 1;

	while(caseId <= T)
	{
		scanf("%lf %lf", &oldCelcius, &fChange);

		printf("Case %d: %.2lf\n", caseId, convertFToCDegree(convertCToFDegree(oldCelcius) + fChange));

		caseId++;
	}
	return 0;
}

double convertCToFDegree(double cDegree)
{
	return 9.0 * cDegree / 5.0 + 32.0;
}

double convertFToCDegree(double fDegree)
{
	return 5.0 * (fDegree - 32.0) / 9.0;
}		
