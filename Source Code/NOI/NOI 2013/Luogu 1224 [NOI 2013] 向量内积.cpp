#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cassert>
#include <cctype>
#include <climits>
#include <ctime>
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
#include <functional>
#define loop register int
typedef long long LL;
typedef unsigned long long ULL;
using std::cin;
using std::cout;
using std::endl;
typedef int INT_PUT;
INT_PUT readIn()
{
	INT_PUT a = 0; bool positive = true;
	char ch = getchar();
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
	if (ch == '-') { positive = false; ch = getchar(); }
	while (std::isdigit(ch)) { a = a * 10 - (ch - '0'); ch = getchar(); }
	return positive ? -a : a;
}
void printOut(INT_PUT x)
{
	char buffer[20]; int length = 0;
	if (x < 0) putchar('-'); else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
}

const int maxn = int(1e5) + 5;
int n, d, K;
struct Rect
{
	int c[3000105];
	int* operator[](int x)
	{
		return c + x * d;
	}
	const int* operator[](int x) const
	{
		return c + x * d;
	}
} vec;

#define RunInstance(x) delete new x
struct brute
{
	brute()
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < d; j++)
				vec[i][j] %= K;

		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++)
			{
				int sum = 0;
				for (int k = 0; k < d; k++)
					sum += vec[i][k] * vec[j][k];
				if (!(sum % K))
				{
					printOut(i + 1);
					putchar(' ');
					printOut(j + 1);
					return;
				}
			}
		printf("-1 -1");
	}
};
struct work2
{
	int random[maxn];
	int diagonal[maxn];
	int temp[105];

	work2()
	{
		for (loop i = 0; i < n; i++)
		{
			loop t = 0;
			for (loop j = 0; j < d; j++)
				t += vec[i][j] * vec[i][j];
			t &= 1;
			diagonal[i] = t;
		}
		int T = 1e8 / (n * d);
		while (T--)
		{
			int count1 = 0;
			for (loop i = 0; i < n; i++)
				count1 += random[i] = rand() & 1;

			for (loop j = 0; j < d; j++)
			{
				loop t = 0;
				for (loop i = 0; i < n; i++)
					t += vec[i][j] & random[i];
				temp[j] = t;
			}

			for (loop i = 0; i < n; i++)
			{
				loop t = 0;
				for (loop j = 0; j < d; j++)
					t += vec[i][j] * temp[j];
				if ((t & 1) != ((count1 - (!diagonal[i] && random[i])) & 1))
				{
					for (loop j = 0; j < n; j++) if (i != j)
					{
						loop sum = 0;
						for (loop k = 0; k < d; k++)
							sum += vec[i][k] * vec[j][k];
						if (!(sum % K))
						{
							if (i > j)
								std::swap(i, j);
							printOut(i + 1);
							putchar(' ');
							printOut(j + 1);
							return;
						}
					}
				}
			}
		}
		puts("-1 -1");
	}
};
struct work3
{
	int random[maxn];
	int diagonal[maxn];
	int temp[105 * 105]; // note: 数组要开足够大

	work3()
	{
		for (loop i = 0; i < n; i++)
		{
			loop t = 0;
			loop v;
			for (loop j = 0; j < d; j++)
				for (loop k = 0; k < d; k++)
					t += (v = vec[i][j] * vec[i][k]) * v;
			t %= 3; // note: 注意在模 3 意义下进行
			diagonal[i] = t;
		}
		int T = 1e8 / (n * d * d);
		while (T--)
		{
			int count1 = 0;
			for (loop i = 0; i < n; i++)
				count1 += random[i] = rand() & 1; // note: 生成的仍是 01 向量

			for (loop j = 0, v = 0; j < d; j++)
				for (loop k = 0; k < d; k++, v++)
				{
					loop t = 0;
					for (loop i = 0; i < n; i++)
						t += vec[i][j] * vec[i][k] * random[i];
					temp[v] = t % 3;
				}

			for (loop i = 0; i < n; i++)
			{
				loop t = 0;
				for (loop j = 0, v = 0; j < d; j++)
					for (loop k = 0; k < d; k++, v++)
						t += vec[i][j] * vec[i][k] * temp[v] % 3;
				if ((t % 3) != ((count1 - (!diagonal[i] && random[i])) % 3)) // note: 注意在模 3 意义下进行
				{
					for (loop j = 0; j < n; j++) if (i != j)
					{
						loop sum = 0;
						for (loop k = 0; k < d; k++)
							sum += vec[i][k] * vec[j][k];
						if (!(sum % K))
						{
							if (i > j)
								std::swap(i, j);
							printOut(i + 1);
							putchar(' ');
							printOut(j + 1);
							return;
						}
					}
				}
			}
		}
		puts("-1 -1");
	}
};

void run()
{
	n = readIn();
	d = readIn();
	K = readIn();
	for (int i = 0; i < n; i++)
		for (int j = 0; j < d; j++)
			vec[i][j] = readIn();

	if ((LL)n * n * d <= LL(3e8))
		RunInstance(brute);
	else if (K == 2)
		RunInstance(work2);
	else
		RunInstance(work3);
}

int main()
{
	run();
	return 0;
}