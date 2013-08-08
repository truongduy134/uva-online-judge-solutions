/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

#include <cstdio>
#include <set>
#include <map>
#include <cctype>

using namespace std;

const int NUM_ALPHA = 26;
const int MAX_LEN = 10000;

void generateMapAlphaToNum(int mapAlphaToNum[]);
int getSerialFromPhoneNo(char phoneNo[], int mapAlphaToNum[]);

int main(void)
{
	int mapAlphaToNum[NUM_ALPHA];

	generateMapAlphaToNum(mapAlphaToNum);

	int T, numPhoneNo;
	char phoneNo[MAX_LEN + 1];
	set<int> serialSet;
	map<int, int> mapSerialToFreq;
	bool noDup;

	scanf("%d", &T);
	while(T)
	{
		scanf("%d", &numPhoneNo);

		noDup = true;
		serialSet.clear();
		mapSerialToFreq.clear();

		for(int i = 0; i < numPhoneNo; i++)
		{
			scanf("%s", phoneNo);

			int serial = getSerialFromPhoneNo(phoneNo, mapAlphaToNum);
			
			if(serialSet.find(serial) != serialSet.end())
			{
				noDup = false;
				map<int, int>::iterator it = mapSerialToFreq.find(serial);
				if(it == mapSerialToFreq.end())
					mapSerialToFreq[serial] = 2;
				else
					(it->second)++;
			}
			else
				serialSet.insert(serial);
		}
	
		if(!noDup)
		{
			for(map<int, int>::const_iterator it = mapSerialToFreq.begin();
				it != mapSerialToFreq.end(); ++it)
			{
				printf("%03d-%04d %d\n", it->first / 10000, it->first % 10000, it->second);
			}
		}
		else
			printf("No duplicates.\n");

		if(T > 1)
			printf("\n");		
		T--;
	}
	return 0;
}

void generateMapAlphaToNum(int mapAlphaToNum[])
{
	char alpha;
	int curSerial = 2;
	int num = 0;

	for(alpha = 'A'; alpha <= 'Z'; alpha++)
	{
		if(alpha == 'Q' || alpha == 'Z')
			mapAlphaToNum[(int) alpha - 'A'] = -1;
		else
		{
			mapAlphaToNum[(int) alpha - 'A'] = curSerial;
			num++;
			if(num == 3)
			{
				num = 0;
				curSerial++;
			}
		}
	}
}

int getSerialFromPhoneNo(char phoneNo[], int mapAlphaToNum[])
{
	int serial = 0;

	for(int ind = 0; phoneNo[ind] != '\0'; ind++)
		if(isalnum(phoneNo[ind]))
		{
			int val = 0;
			if(isalpha(phoneNo[ind]))
				val = mapAlphaToNum[(int) phoneNo[ind] - 'A'];
			else
				val = phoneNo[ind] - '0';

			serial = serial * 10 + val;
		}

	return serial;
}
