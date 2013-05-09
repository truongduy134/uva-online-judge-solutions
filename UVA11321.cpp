#include <algorithm>
#include <cstdio>

using namespace std;

#define MAX_SIZE 10000
class MyCompareFunctor {
private:
    int _modulo;
public:
    MyCompareFunctor() : _modulo(1) {}
    MyCompareFunctor(int modulo) : _modulo(modulo) {}
    MyCompareFunctor(const MyCompareFunctor & another) : _modulo(another._modulo) {}
    ~MyCompareFunctor() {}

    bool operator() (int numOne, int numTwo);
    void setParam(int modulo) {_modulo = modulo;}
};

bool MyCompareFunctor::operator() (int numOne, int numTwo)
{
    int modOne = numOne % _modulo, modTwo = numTwo % _modulo;

    if(numOne < 0 && modOne > 0)
        modOne -= _modulo;
    if(numTwo < 0 && modTwo > 0)
        modTwo -= _modulo;

    if(modOne < modTwo)
        return true;
    if(modOne > modTwo)
        return false;

    // There is a tie between two odd numbers
    if((numOne & 1) && (numTwo & 1))
    {
        if(numOne > numTwo)
            return true;
        else
            return false;
    }

     // There is a tie between two even numbers
     if((numOne & 1) == 0 && (numTwo & 1) == 0)
     {
         if(numOne < numTwo)
            return true;
         else
            return false;
     }

     // There is a tie between an odd and even number
     if(numOne & 1)
        return true;
     return false;
}

int main(void)
{
    int N, M, arr[MAX_SIZE];
    MyCompareFunctor cmpFunctor;

    while(1)
    {
        scanf("%d %d", &N, &M);
        if(N == 0 && M == 0)
            break;

        cmpFunctor.setParam(M);

        for(int i = 0; i < N; i++)
            scanf("%d", &arr[i]);

        sort(arr, arr + N, cmpFunctor);

        printf("%d %d\n", N, M);
        for(int i = 0; i < N; i++)
            printf("%d\n", arr[i]);
    }
    printf("0 0\n");
    return 0;
}
