#include <cstdio>
#include <map>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

#define NUM_NOTE 12
#define MAJOR_SCALE 8
#define END_INPUT "END"
#define MAX_LENGTH_LINE 1000

const char * NOTE_LIST[NUM_NOTE] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#",
                                    "B"};
const int NUM_JUMP[MAJOR_SCALE - 1] = {2, 2, 1, 2, 2, 2, 1};

void generateMapNoteToId(map<string, int> & mapNoteToInd);
void generateNodePresentByKeys(vector<vector<bool> > & noteGeneratedByKeys);
void findAllMusicKey(char sequenceNote[], vector<int> & keyNoteIndVect, const map<string, int> & mapNoteToInd,
                     const vector<vector<bool> > & noteGenerateByKeys);
bool isSubset(const vector<bool> & smallSet, const vector<bool> & bigSet);

int main(void)
{
    char sequenceNote[MAX_LENGTH_LINE + 1];
    vector<int> noteKeyIndVect;
    map<string, int> mapNoteToInd;
    vector<vector<bool> > noteGeneratedByKeys;

    generateMapNoteToId(mapNoteToInd);
    generateNodePresentByKeys(noteGeneratedByKeys);

    while(1)
    {
        gets(sequenceNote);
        if(strcmp(sequenceNote, END_INPUT) == 0)
            break;

        findAllMusicKey(sequenceNote, noteKeyIndVect, mapNoteToInd, noteGeneratedByKeys);

        if(noteKeyIndVect.size() != 0)
        {
            printf("%s", NOTE_LIST[noteKeyIndVect[0]]);

            for(int i = 1; i < (int) noteKeyIndVect.size(); i++)
                printf(" %s", NOTE_LIST[noteKeyIndVect[i]]);
        }
        printf("\n");
    }

    return 0;
}

void generateMapNoteToId(map<string, int> & mapNoteToInd)
{
    for(int i = 0; i < NUM_NOTE; i++)
    {
        mapNoteToInd[NOTE_LIST[i]] = i;
    }
}

void generateNodePresentByKeys(vector<vector<bool> > & noteGeneratedByKeys)
{
    for(int ind = 0; ind < NUM_NOTE; ind++)
    {
        vector<bool> notePresent(NUM_NOTE, false);

        int noteInd = ind;

        for(int jumpId = 0; jumpId < MAJOR_SCALE - 1; jumpId++)
        {
            notePresent[noteInd] = true;

            noteInd += NUM_JUMP[jumpId];
            if(noteInd >= NUM_NOTE)
                noteInd -= NUM_NOTE;
        }

        noteGeneratedByKeys.push_back(notePresent);
    }
}

void findAllMusicKey(char sequenceNote[], vector<int> & keyNoteIndVect, const map<string, int> & mapNoteToInd,
                     const vector<vector<bool> > & noteGenerateByKeys)
{
    keyNoteIndVect.clear();

    vector<bool> notePresentSieve(NUM_NOTE, false);
    char delim[] = " ", *token;

    token = strtok(sequenceNote, delim);
    do
    {
        if(token == NULL)
            break;

        map<string, int>::const_iterator it = mapNoteToInd.find(token);
        if(it != mapNoteToInd.end())
            notePresentSieve[it->second] = true;

        token = strtok(NULL, delim);
    } while(token != NULL);

    for(int ind = 0; ind < NUM_NOTE; ind++)
        if(isSubset(notePresentSieve, noteGenerateByKeys[ind]))
            keyNoteIndVect.push_back(ind);
}

bool isSubset(const vector<bool> & smallSet, const vector<bool> & bigSet)
{
    for(int i = 0; i < (int) smallSet.size(); i++)
        if(bigSet[i] == false && smallSet[i] == true)
            return false;
    return true;
}
