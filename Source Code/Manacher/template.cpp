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
void printOut(INT x)
{
	char buffer[20];
	INT length = 0;
	bool minus = x < 0;
	if (minus) x = -x;
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while (x);
	if (minus) buffer[length++] = '-';
	do
	{
		putchar(buffer[--length]);
	} while (length);
	putchar('\n');
}

const INT maxn = 11000005;

char str[maxn];
struct Manacher
{
	INT length;
	std::vector<char> a;
	std::vector<INT> f;
	INT maxLength;
	Manacher(const char* str)
	{
		length = strlen(str);
		a.resize(length * 2 + 1);
		f.resize(length * 2 + 1);
		INT pos = 0;
		a[pos++] = '#';
		for (int i = 0; i < length; i++)
		{
			a[pos++] = str[i];
			a[pos++] = '#';
		}
		manacher();
	}
	void manacher()
	{
		INT center; //undefined
		INT maxRight = -1; //±ÕÇø¼ä
		for (int i = 0; i < a.size(); i++)
		{
			if (i <= maxRight)
			{
				//i + j == 2 * center
				f[i] = std::min(f[2 * center - i], maxRight - i + 1);
			}
			else
				f[i] = 1;

			while (i - f[i] >= 0 && i + f[i] < a.size() && a[i - f[i]] == a[i + f[i]])
				f[i]++;

			if (i + f[i] - 1 > maxRight)
			{
				maxRight = i + f[i] - 1;
				center = i;
			}
			maxLength = std::max(maxLength, f[i]);
		}
		maxLength--;
	}
};

void run()
{
	scanf("%s", str);
	printOut(Manacher(str).maxLength);
}

int main()
{
	run();
	return 0;
}