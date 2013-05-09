#include <iostream>
#include <string>
using namespace std;

#define NUM_FRAME 10

int getScoreFrame(string & bowlScoreStr, int index);
int getScoreRoll(string & bowlScoreStr, int index);
int calculateTotalScore(string & bowlScoreStr);

int main()
{
    string bowlScoreStr;

    while(true)
    {
        getline(cin, bowlScoreStr);

        if(bowlScoreStr[0] == 'G')
            break;

        cout << calculateTotalScore(bowlScoreStr) << endl;
    }

    return 0;
}

int calculateTotalScore(string & bowlScoreStr)
{
    int frame = 1, index = 0, totalScore = 0;

    while(frame <= NUM_FRAME)
    {
        totalScore += getScoreFrame(bowlScoreStr, index);

        if(bowlScoreStr[index] == 'X')
        {
            // Bonus for a strike
            totalScore += getScoreFrame(bowlScoreStr, index + 2);

            if(bowlScoreStr[index + 2] == 'X')
                /* In this case, two rolls spans 1 frame (with 'X') and 1 roll */
                totalScore += getScoreRoll(bowlScoreStr, index + 4);

            index += 2;
        }
        else
        {
            if(bowlScoreStr[index + 2] == '/')
            {
                // Bonus for a spare
                totalScore += getScoreRoll(bowlScoreStr, index + 4);
            }
            index += 4;
        }

        frame++;
    }

    return totalScore;
}

// The score information of the frame starts with index
int getScoreFrame(string & bowlScoreStr, int index)
{
    if(bowlScoreStr[index] == 'X')
        return 10;

    // Note the two rolls are separated by a white space
    char rollTwo = bowlScoreStr[index + 2];
    if(rollTwo == '/')
        return 10;

    return (bowlScoreStr[index] - '0') + (rollTwo - '0');
}

// The score information of the roll starts with index
int getScoreRoll(string & bowlScoreStr, int index)
{
    if(bowlScoreStr[index] == 'X')
        return 10;

    return bowlScoreStr[index] - '0';
}
