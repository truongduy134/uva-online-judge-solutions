/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *	+ Observation:
 *		- If x, y are enemies of z, then x and y are friends
 *		- An enemy of a friend is also an enemy.
 *	+ Hence, we maintain a data structure for disjoint friend sets.
 *	  (This can be implemented using UnionFind)
 *	+ We also maintain an additional information:
 *		- For each person i, we keep track of E[i] which is a representative
 *			of a friend set whose people are enemies of person i.
 *		- Initally, E[i] = -1 (person i has no enemy yet)
 *	+ Before doing an operation setFriend, setEnemy, we check the consistencies.
 *
 *	+ Time complexity: O((V + E) * inverseAckermann(V)) (V: number of people, 
 *		E: number of relation)
 */

#include <cstdio>
#include <vector>

using namespace std;

const int YES = 1;
const int NO = 0;
const int CONTRADICTORY = -1;
const int SET_FRIEND_OP = 1;
const int SET_ENEMY_OP = 2;
const int ARE_FRIEND_OP = 3;
const int ARE_ENEMY_OP = 4;

class RelationManager {
private:
	vector<int> _parentFriend, _rank, _enemy;

	int getFriendLeader(int ele);
	int getEnemyLeader(int ele);
	void unionFriendSet(int eleOne, int eleTwo);

public:
	RelationManager() { reset(0); }
	RelationManager(int mSize) { reset(mSize); }
	~RelationManager() {}

	void reset(int newSize);
	bool areFriends(int eleOne, int eleTwo);
	bool areEnemies(int eleOne, int eleTwo);
	bool makeFriend(int eleOne, int eleTwo);
	bool makeEnemy(int eleOne, int eleTwo);
};

void RelationManager::reset(int newSize)
{
	_parentFriend.assign(newSize, 0);
	_rank.assign(newSize, 0);
	_enemy.assign(newSize, -1);

	for(int i = 0; i < newSize; i++)
		_parentFriend[i] = i;
}

int RelationManager::getFriendLeader(int ele)
{
	if(_parentFriend[ele] == ele)
		return ele;
	_parentFriend[ele] = getFriendLeader(_parentFriend[ele]);
	return _parentFriend[ele];
}

int RelationManager::getEnemyLeader(int ele)
{
	int friendLeader = getFriendLeader(ele);
	if(_enemy[friendLeader] < 0)
		return _enemy[friendLeader];
	return getFriendLeader(_enemy[friendLeader]);
}

bool RelationManager::areFriends(int eleOne, int eleTwo)
{
	if(getFriendLeader(eleOne) == getFriendLeader(eleTwo))
		return true;

	return false;
}

bool RelationManager::areEnemies(int eleOne, int eleTwo)
{
	int enemyLeaderOne = getEnemyLeader(eleOne);
	if(enemyLeaderOne < 0)
		return false;
	return enemyLeaderOne == getFriendLeader(eleTwo);
}

bool RelationManager::makeFriend(int eleOne, int eleTwo)
{
	if(areFriends(eleOne, eleTwo))
		return true;
	if(areEnemies(eleOne, eleTwo))
		return false;

	int enemyLeaderOne = getEnemyLeader(eleOne);
	int enemyLeaderTwo = getEnemyLeader(eleTwo);
	
	unionFriendSet(eleOne, eleTwo);
	unionFriendSet(enemyLeaderOne, enemyLeaderTwo);
	return true;
}

bool RelationManager::makeEnemy(int eleOne, int eleTwo)
{
	if(areFriends(eleOne, eleTwo))
		return false;
	if(areEnemies(eleOne, eleTwo))
		return true;

	int enemyLeaderOne = getEnemyLeader(eleOne);
	int enemyLeaderTwo = getEnemyLeader(eleTwo);
	unionFriendSet(eleTwo, enemyLeaderOne);	
	unionFriendSet(eleOne, enemyLeaderTwo);

	int friendLeaderOne = getFriendLeader(eleOne);
	int friendLeaderTwo = getFriendLeader(eleTwo);
	_enemy[friendLeaderOne] = friendLeaderTwo;
	_enemy[friendLeaderTwo] = friendLeaderOne;

	return true;
}

void RelationManager::unionFriendSet(int eleOne, int eleTwo)
{
	if(eleOne < 0 || eleTwo < 0)
		return;

	int friendLeaderOne = getFriendLeader(eleOne);
	int friendLeaderTwo = getFriendLeader(eleTwo);

	if(friendLeaderOne == friendLeaderTwo)
		return;

	if(_rank[friendLeaderOne] < _rank[friendLeaderTwo])
	{
		if(_enemy[friendLeaderTwo] < 0)
			_enemy[friendLeaderTwo] = getEnemyLeader(friendLeaderOne);
		_parentFriend[friendLeaderOne] = friendLeaderTwo;
	}
	else
	{
		if(_enemy[friendLeaderOne] < 0)
			_enemy[friendLeaderOne] = getEnemyLeader(friendLeaderTwo);
		_parentFriend[friendLeaderTwo] = friendLeaderOne;
		
		if(_rank[friendLeaderOne] == _rank[friendLeaderTwo])
			_rank[friendLeaderOne]++;
	}
}

int main(void)
{
	int numPeople;

	scanf("%d", &numPeople);

	RelationManager relationManager(numPeople);

	int one, two, op;

	while(1)
	{
		scanf("%d %d %d", &op, &one, &two);
		if(!(op || one || two))
			break;

		switch(op)
		{
			case ARE_FRIEND_OP:
				printf("%d\n", relationManager.areFriends(one, two) ? YES : NO);
				break;
			case ARE_ENEMY_OP:
				printf("%d\n", relationManager.areEnemies(one, two) ? YES : NO);
				break;
			case SET_FRIEND_OP:
				if(!relationManager.makeFriend(one, two))
					printf("%d\n", CONTRADICTORY);
				break;
			case SET_ENEMY_OP:
				if(!relationManager.makeEnemy(one, two))
					printf("%d\n", CONTRADICTORY);
		}
	}
	return 0;
}
