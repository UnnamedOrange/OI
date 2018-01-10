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
#include <list>
typedef int INT;
using std::cin;
using std::cout;
using std::endl;
INT readIn()
{
    INT a = 0;
    bool minus = false;
    char ch = getchar();
    while (!(ch == '-' || (ch >= '0' && ch <= '9')))
        ch = getchar();
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
    if (minus)
        a = -a;
    return a;
}
void printOut(INT x)
{
    char buffer[20];
    INT length = 0;
    if (x < 0)
    {
        putchar('-');
        x = -x;
    }
    do
    {
        buffer[length++] = x % 10 + '0';
        x /= 10;
    } while (x);
    do
    {
        putchar(buffer[--length]);
    } while (length);
    putchar('\n');
}

const INT maxn = 100005;
const INT maxk = 320;
INT n, w, q, type;
INT lastans;
INT a[maxn];

INT sqrtN, N;
inline INT block(INT x)
{
    return (x - 1) % sqrtN;
}

void init()
{
    sqrtN = std::sqrt(n);
    N = (n + sqrtN - 1) / n;

    for (int i = 1; i <= N; i++)
    {
        INT inBlock = block(i);
    }
}
INT work()
{
}

void run()
{
    n = readIn();
    w = readIn();
    q = readIn();
    type = readIn();
    for (int i = 1; i <= n; i++)
        a[i] = readIn();

    init();
    while (q--)
    {
        INT l = readIn() ^ (type * lastans);
        INT r = readIn() ^ (type * lastans);
        INT k = readIn() ^ (type * lastans);
        printOut(lastans = work());
    }
}

int main()
{
#ifndef LOCAL
    freopen("kth.in", "r", stdin);
    freopen("kth.out", "w", stdout);
#endif
    run();
    return 0;
}