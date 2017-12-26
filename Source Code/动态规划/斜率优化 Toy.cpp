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
using std::cin;
using std::cout;
using std::endl;
typedef long long INT;
inline INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || ch >= '0' && ch <= '9')) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a *= 10;
		a += ch;
		a -= '0';
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}

const INT INF = ~(INT(1) << (sizeof(INT) * 8 - 1));
const INT maxn = 50005;
INT n;
INT L;
INT s[maxn];

struct deque
{
	std::vector<INT> container;

	INT head;
	INT tail;

	deque() : container(maxn), head(), tail() {}

	INT size()
	{
		return tail - head;
	}
	void push_back(INT x)
	{
		container[tail++] = x;
	}
	void pop_back()
	{
		tail--;
	}
	void pop_front()
	{
		head++;
	}
	INT front()
	{
		return container[head];
	}
	INT back()
	{
		return container[tail - 1];
	}
	INT front2()
	{
		return container[head + 1];
	}
	INT back2()
	{
		return container[tail - 2];
	}
};

#define RunInstance(x) delete new x
struct SlopeOptimization
{
	INT f[maxn];

	inline INT y(INT sp)
	{
		INT temp = s[sp] + sp;
		return f[sp] + temp * temp;
	}
	inline INT x(INT sp)
	{
		return s[sp] + sp;
	}
	inline INT up(INT s1, INT s2)
	{
		return y(s1) - y(s2);
	}
	inline INT down(INT s1, INT s2)
	{
		return x(s1) - x(s2);
	}
	inline INT K(INT stage)
	{
		return 2 * (s[stage] + stage - L - 1);
	}
	inline INT dp(INT stage, INT strategy)
	{
		INT temp = s[stage] - s[strategy] + stage - strategy - 1 - L;
		return f[strategy] + temp * temp;
	}
	inline double slope(INT s1, INT s2)
	{
		return double(y(s1) - y(s2)) / double(x(s1) - x(s2));
	}

	SlopeOptimization() : f()
	{
		//原始状态转移方程:
		//f[i] = min{ f[j] + (s[i] - s[j] + i - j - 1 - L) ^ 2 } (0 <= j < i)

		f[1] = dp(1, 0);
		deque strategy;
		strategy.push_back(0);
		strategy.push_back(1);

		for(int i = 2; i <= n; i++)
		{
			while(strategy.size() > 1 &&
			        slope(strategy.front2(), strategy.front()) < K(i))
			{
				strategy.pop_front();
			}
			f[i] = dp(i, strategy.front());

			while(strategy.size() > 1 &&
			        slope(i, strategy.back()) < slope(strategy.back(), strategy.back2()))
			{
				strategy.pop_back();
			}
			strategy.push_back(i);
		}
		cout << f[n] << endl;
	}
};

void run()
{
	n = readIn();
	L = readIn();
	for(int i = 1; i <= n; i++)
	{
		s[i] = readIn() + s[i - 1];
	}

	RunInstance(SlopeOptimization);
}

int main()
{
	run();
	return 0;
}
