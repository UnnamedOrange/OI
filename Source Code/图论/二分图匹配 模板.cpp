#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
#include <bitset>
typedef int INT;
using std::cin;
using std::cout;
using std::endl;
inline INT readIn()
{
    INT a = 0;
    bool minus = false;
    char ch = getchar();
    while (!(ch == '-' || (ch >= '0' && ch <= '9'))) ch = getchar();
    if (ch == '-')
    {
        minus = true;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        a = a * 10 + (ch - '0');
        ch = getchar();
    }
    if (minus) a = -a;
    return a;
}
inline void printOut(INT x)
{
    char buffer[20];
    INT length = 0;
    bool minus = x < 0;
    if (minus) x = -x;
    do
    {
        buffer[length++] = x % 10 + '0';
        x /= 10;
    }
    while (x);
    if (minus) buffer[length++] = '-';
    do
    {
        putchar(buffer[--length]);
    }
    while (length);
}

const INT maxn = 1005;
INT n, m, e;
INT linkX[maxn];
std::vector<std::vector<INT> > edges;

bool vis[maxn]; 

bool augment(INT x)
{
    for(int i = 0; i < edges[x].size(); i++)
    {
        INT to = edges[x][i];
        if(vis[to]) continue;
        vis[to] = true;
        if(!linkX[to] || augment(linkX[to]))
        {
            linkX[to] = x;
            return true;
        }
    }
    return false;
}

void run()
{
    n = readIn();
    m = readIn();
    e = readIn();
    edges.resize(n + 1);
    for(int i = 1; i <= e; i++)
    {
        INT u = readIn();
        INT v = readIn();
        if(u > n || v > m) continue;
        edges[u].push_back(v);
    }
    INT ans = 0;
    for(int i = 1; i <= n; i++)
    {
        memset(vis, 0, sizeof(vis));
        ans += augment(i);
    }
    printOut(ans);
}

int main()
{
    run();
    return 0;
}
