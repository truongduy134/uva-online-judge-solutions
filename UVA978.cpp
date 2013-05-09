#include <iostream>
#include <vector>
using namespace std;

#define MAX_SIZE 102

void printPosNum(int arr[]);
bool noMoreSold(int arr[]);
void doBattle(int greenSold[], int blueSold[], int numBattle);
void addSoldier(int soldArr[], vector<int> &listNew);

int main()
{
    int numTest, input;

    cin >> numTest;

    while(numTest)
    {
        int numBattle, numGreen, numBlue;
        int greenSold[MAX_SIZE] = {0}, blueSold[MAX_SIZE] = {0};

        /* Reading input for each test case */
        cin >> numBattle >> numGreen >> numBlue;
        for(int index = 0; index < numGreen; index++)
        {
            cin >> input;
            greenSold[input]++;
        }
        for(int index = 0; index < numBlue; index++)
        {
            cin >> input;
            blueSold[input]++;
        }

        bool greenAllDead, blueAllDead;
        do
        {
            /* 1 round */
            doBattle(greenSold, blueSold, numBattle);
            greenAllDead = noMoreSold(greenSold);
            blueAllDead = noMoreSold(blueSold);
        } while(!(greenAllDead || blueAllDead));

        if(greenAllDead && blueAllDead)
            cout << "green and blue died" << endl;
        else
        {
            if(greenAllDead)
            {
                cout << "blue wins" << endl;
                printPosNum(blueSold);
            }
            else
            {
                cout << "green wins" << endl;
                printPosNum(greenSold);
            }
        }

        numTest--;
        if(numTest)
            cout << endl;
    }

    return 0;
}

void printPosNum(int arr[])
{
    for(int index = MAX_SIZE - 1; index >= 0; index--)
        while(arr[index])
        {
            cout << index << endl;
            arr[index]--;
        }
}

bool noMoreSold(int arr[])
{
    for(int index = 0; index < MAX_SIZE; index++)
        if(arr[index])
            return false;

    return true;
}

void doBattle(int greenSold[], int blueSold[], int numBattle)
{
    vector<int> surviveGreen, surviveBlue;
    int greenId = MAX_SIZE - 1, blueId = MAX_SIZE - 1;
    while(numBattle)
    {
        /* Choose opponents */
        while(greenSold[greenId] == 0 && greenId >= 0)
            greenId--;
        if(greenId < 0)
            break;
        while(blueSold[blueId] == 0 && blueId >= 0)
            blueId--;
        if(blueId < 0)
            break;

        /* Fight */
        if(greenId > blueId)
            surviveGreen.push_back(greenId - blueId);
        else
        {
            if(greenId < blueId)
                surviveBlue.push_back(blueId - greenId);
        }
        blueSold[blueId]--;
        greenSold[greenId]--;

        numBattle--;
    }
    addSoldier(greenSold, surviveGreen);
    addSoldier(blueSold, surviveBlue);
}

void addSoldier(int soldArr[], vector<int> &listNew)
{
    for(int index = 0; index < listNew.size(); index++)
        soldArr[listNew[index]]++;
}
