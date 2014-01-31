#include <iostream>
#include <list>
using namespace std;

#define N 7

bool canJump(int frog[N], int i, int len)
{
    return i+len*frog[i]<=N && i+len*frog[i]>0
             && frog[i+frog[i]*len]==0;
}


bool isOK(int frog[N])
{
    for (int i=1; i<=N/2; i++)
        if (frog[i] != -1)
            return false;
    for (int i=N/2+2; i<=N; i++)
        if (frog[i] != 1)
            return false;
    return true;
}

void jump(int frog[N], int i, int len, int flg)
{
    frog[i+flg*frog[i]*len] = frog[i];
    frog[i] = 0;
}

void show(list<int> lst)
{
    list<int>::iterator i = lst.begin();
    for( ; i!=lst.end(); ++i)
        cout << *i;
    cout << endl; 
}
void show (int arr[N])
{
    for (int i=1; i<=N; i++)\
        cout << arr[i] << " ";
    cout << endl;
}
void search(int frog[N], list<int> solution)
{
    for (int i=1; i<=N; i++)
    {
        if (frog[i]==0)
            continue;
        else
        {
            int tmp;
            for (int len=1; len<=2; len++)
                if (canJump(frog, i, len))
                {
                    tmp = frog[i];
                    jump(frog, i, len, 1);
                    solution.push_back(i);
                    if (isOK(frog))
                        show(solution) ;

                    search(frog, solution);
                    jump(frog, i+len*tmp, len, -1);
                    solution.pop_back();
                }
        }
    }

}           

int main()
{
    int frog[N+1] = {0, 1, 1, 1, 0, -1, -1, -1};
    list<int> solution;

    search(frog, solution);
    return 0;

}
