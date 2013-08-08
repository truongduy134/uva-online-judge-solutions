/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

#include <cstdio>
#include <string>
#include <map>
#include <utility>
#include <vector>

using namespace std;

class ArrayRef
{
private:
	int _dimension;
	vector<long long> _constant;

public:
	ArrayRef() : _dimension(0), _constant(vector<long long>()) {}

	ArrayRef(long long baseAddr, int dimension, const vector<int> & lowerBound,
		 const vector<int> & upperBound, int eleSize);

	ArrayRef(const ArrayRef & other) : _dimension(other._dimension),
		                           _constant(other._constant) {}
	~ArrayRef() {}

	long long getAddr(const vector<int> & indArr) const;
	int getDimension() const { return _dimension; }
};

ArrayRef::ArrayRef(long long baseAddr, int dimension, const vector<int> & lowerBound,
		   const vector<int> & upperBound, int eleSize)
{
	_dimension = dimension;

	// Calculate the constants
	_constant.assign(dimension + 1, 0);

	_constant[dimension] = (long long) eleSize;
	for(int d = dimension - 1; d >= 1; d--)
	{
		_constant[d] = _constant[d + 1] * (upperBound[d] - lowerBound[d] + 1);
	}
	_constant[0] = baseAddr;
	for(int d = 1; d <= dimension; d++)
		_constant[0] -= _constant[d] * lowerBound[d - 1];
}

long long ArrayRef::getAddr(const vector<int> & indArr) const
{
	if((int) indArr.size() != _dimension)
		return -1;

	long long addr = _constant[0];
	for(int d = 1; d <= _dimension; d++)
		addr += indArr[d - 1] * _constant[d];

	return addr;
}

const int MAX_LEN_NAME = 10;

int main(void)
{
	map<string, ArrayRef> mapNameToArr;
	vector<int> upperBound, lowerBound, indArr;
	long long baseAddr;
	char name[MAX_LEN_NAME + 1];
	int eleSize, numArr, numQuery, dimension;

	scanf("%d %d", &numArr, &numQuery);
	
	// Read arr
	for(int i = 0; i < numArr; i++)
	{
		scanf("%s %lld %d %d", name, &baseAddr, &eleSize, &dimension);
		
		upperBound.assign(dimension, 0);
		lowerBound.assign(dimension, 0);

		for(int d = 0; d < dimension; d++)
			scanf("%d %d", &lowerBound[d], &upperBound[d]);

		ArrayRef arrRef(baseAddr, dimension, lowerBound, upperBound, eleSize);
		mapNameToArr.insert(pair<string, ArrayRef> (name, arrRef));
	}

	for(int i = 0; i < numQuery; i++)
	{
		scanf("%s", name);

		const ArrayRef arrRef = mapNameToArr[name];
		dimension = arrRef.getDimension();

		indArr.assign(dimension, 0);
		for(int d = 0; d < dimension; d++)
			scanf("%d", &indArr[d]);

		printf("%s[", name);
		printf("%d", indArr[0]);
		for(int d = 1; d < dimension; d++)
			printf(", %d", indArr[d]);
		printf("] = %lld\n", arrRef.getAddr(indArr));
	}

	return 0;
}
