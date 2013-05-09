#include <stdio.h>

#define MAX_LEN 100
#define NUM_PAGE 10

typedef struct {
        char _url[MAX_LEN + 1];
        int _relevance;
} WebPage;

int main(void)
{
    WebPage listPage[NUM_PAGE];
    int caseId, T, i, maxRelevance;

    scanf("%d", &T);
    caseId = 1;
    while(caseId <= T)
    {
        for(i = 0; i < NUM_PAGE; i++)
            scanf("%s %d", listPage[i]._url, &listPage[i]._relevance);

        maxRelevance = listPage[0]._relevance;
        for(i = 1; i < NUM_PAGE; i++)
            if(maxRelevance < listPage[i]._relevance)
                maxRelevance = listPage[i]._relevance;

        printf("Case #%d:\n", caseId);
        for(i = 0; i < NUM_PAGE; i++)
            if(listPage[i]._relevance == maxRelevance)
                printf("%s\n", listPage[i]._url);

        caseId++;
    }
    return 0;
}
