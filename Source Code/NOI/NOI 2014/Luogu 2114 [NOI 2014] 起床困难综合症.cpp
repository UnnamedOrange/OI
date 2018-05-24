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
int n, m;
int ans;
struct Instruction
{
	enum
	{
		AND, OR, XOR
	};
	int type;
	int val;
	void read()
	{
		char str[10];
		scanf("%s", str);
		if (str[0] == 'A')
			type = AND;
		else if (str[0] == 'O')
			type = OR;
		else if (str[0] == 'X')
			type = XOR;
		val = readIn();
	}
	int calc(int input)
	{
		if (type == AND)
			return input & val;
		else if (type == OR)
			return input | val;
		else
			return input ^ val;
	}
} ins[maxn];

int calc(int input)
{
	for (int i = 1; i <= n; i++)
		input = ins[i].calc(input);
	return input;
}

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
		ins[i].read();
	int through = calc(0);
	for (int i = 30; ~i; i--)
	{
		if ((ans | (1 << i)) > m)
			continue;
		int v = calc(1 << i);
		if ((v & (1 << i)) > (through & (1 << i)))
			ans |= 1 << i;
	}
	printOut(calc(ans));
}

int main()
{
	run();
	return 0;
}