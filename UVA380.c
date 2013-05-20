/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + Since the input size is small, we can do a straight forward brute force simulation
 */

#include <cstdio>
#include <vector>

using namespace std;

struct ForwardRequest
{
    int source, dest, startTime, endTime;

    ForwardRequest() : source(0), dest(0), startTime(0), endTime(0) {}
    ForwardRequest(int iSource, int iDest, int iStartTime, int iEndTime) :
        source(iSource), dest(iDest), startTime(iStartTime), endTime(iEndTime) {}
    ForwardRequest(const ForwardRequest & another):
        source(another.source), dest(another.dest), startTime(another.startTime), endTime(another.endTime) {}
};

struct CallRequest
{
    int startTime, dest;

    CallRequest() : startTime(0), dest(0) {}
    CallRequest(int iStartTime, int iDest) : startTime(iStartTime), dest(iDest) {}
    CallRequest(const CallRequest & another) :
        startTime(another.startTime), dest(another.dest) {}
};

const int END_FORWARD_REQUEST = 0;
const int END_CALL_REQUEST = 9000;
const int MAX_NUM_PEOPLE = 10000;
const int WHO_HANDLE_WHEN_LOOP = 9999;

int findWhoHandleCall(const vector<vector<ForwardRequest> > & forwardSystem, CallRequest & call);

int main(void)
{
    int T, caseId, from, to, startTime, duration, whoHandle;
    vector<vector<ForwardRequest>  > forwardSystem;
    vector<ForwardRequest> emptyList;
    CallRequest call;

    scanf("%d", &T);
    caseId = 1;

    printf("CALL FORWARDING OUTPUT\n");
    while(caseId <= T)
    {
        forwardSystem.assign(MAX_NUM_PEOPLE, emptyList);

        while(1)
        {
            scanf("%d", &from);
            if(from == END_FORWARD_REQUEST)
                break;

            scanf("%d %d %d", &startTime, &duration, &to);
            forwardSystem[from].push_back(ForwardRequest(from, to, startTime, startTime + duration));
        }

        printf("SYSTEM %d\n", caseId);
        while(1)
        {
            scanf("%d", &startTime);
            if(startTime == END_CALL_REQUEST)
                break;
            scanf("%d", &to);

            call.dest = to;
            call.startTime = startTime;

            whoHandle = findWhoHandleCall(forwardSystem, call);

            printf("AT %04d CALL TO %04d RINGS %04d\n", call.startTime, call.dest, whoHandle);
        }

        caseId++;
    }
    printf("END OF OUTPUT\n");
    return 0;
}

int findWhoHandleCall(const vector<vector<ForwardRequest> > & forwardSystem, CallRequest & call)
{
    int whoHandle = call.dest;
    bool needForward = false;
    int originalForward = 0;

    ForwardRequest forwardRequest;

    do
    {
        needForward = false;
        for(int i = 0; i < (int) forwardSystem[whoHandle].size(); i++)
        {
            forwardRequest = forwardSystem[whoHandle][i];
            if(call.startTime >= forwardRequest.startTime && call.startTime <= forwardRequest.endTime)
            {
                // Forward
                if(originalForward == 0)
                    originalForward = call.dest;

                whoHandle = forwardRequest.dest;
                needForward = true;

                break;
            }
        }
    } while(needForward && whoHandle != originalForward);

    if(!needForward)
        return whoHandle;

    // Otherwise, there is a loop
    return WHO_HANDLE_WHEN_LOOP;
}

