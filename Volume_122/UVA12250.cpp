#include <cstdio>
#include <string>
#include <map>

using namespace std;

#define MAX_LEN 100
#define END_CHAR '#'
#define UNKNOWN_LANG "UNKNOWN"

void prepareMap(map<string, string> & mapHelloToLanguage);

int main(void)
{
    map<string, string> mapHelloToLanguage;
    map<string, string>::iterator it;
    char str[MAX_LEN + 1];
    int caseId;

   // freopen("in.txt", "r", stdin);

    prepareMap(mapHelloToLanguage);

    caseId = 1;
    while(1)
    {
        scanf("%s", str);
        if(str[0] == END_CHAR)
            break;

        it = mapHelloToLanguage.find(str);

        if(it != mapHelloToLanguage.end())
            printf("Case %d: %s\n", caseId, it->second.c_str());
        else
            printf("Case %d: %s\n", caseId, UNKNOWN_LANG);

        caseId++;
    }
    return 0;
}

void prepareMap(map<string, string> & mapHelloToLanguage)
{
    mapHelloToLanguage["HELLO"] = "ENGLISH";
    mapHelloToLanguage["HOLA"] = "SPANISH";
    mapHelloToLanguage["HALLO"] = "GERMAN";
    mapHelloToLanguage["BONJOUR"] = "FRENCH";
    mapHelloToLanguage["CIAO"] = "ITALIAN";
    mapHelloToLanguage["ZDRAVSTVUJTE"] = "RUSSIAN";
}
