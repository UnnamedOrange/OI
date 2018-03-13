#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cctype>
#include <climits>
#include <cassert>
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
	INT_PUT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (std::isdigit(ch))
	{
		a = a * 10 + (ch - '0');
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
void printOut(INT_PUT x)
{
	char buffer[20];
	int length = 0;
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
	putchar(' ');
}

const int maxn = int(1e6) + 5;

int n;
char str[maxn];
int buf_size = 128;
int buf[maxn];
int SA[maxn]; // SA: �� i �����˭��rank: i �ǵڼ���rank �� rank �� SA
int x[maxn], y[maxn];
void GetSA()
{
	int *rank = x, *SA_second = y;

	for (int i = 0; i < n; i++)
		rank[i] = str[i];

	for (int i = 0; i < buf_size; i++) buf[i] = 0;
	for (int i = 0; i < n; i++) buf[rank[i]]++;
	for (int i = 1; i < buf_size; i++) buf[i] += buf[i - 1];
	for (int i = n - 1; ~i; i--)
		SA[--buf[rank[i]]] = i; // ��ɢ��(SA[--buf[rank[i]]] = rank[i])��rank[i]->i

	for (int k = 1; k <= n; k <<= 1)
	{
		int t = 0;
		for (int i = n - k; i < n; i++) // β����û�С��ڶ��ؼ��ֵ�Ԫ�أ����ǵ�������Ϊ��С
			SA_second[t++] = i;
		for (int i = 0; i < n; i++)
			if (SA[i] >= k) SA_second[t++] = SA[i] - k;
		// ��С����ö�ٵڶ��ؼ��ֶ�Ӧ���ַ������Ҷ˵� SA[i]

		// �� rank ���򣬰��յڶ��ؼ��ִ�С������� buf����֤����ʱ��һ�ؼ�����ͬ�ĵڶ��ؼ�������
		for (int i = 0; i < buf_size; i++) buf[i] = 0;
		for (int i = 0; i < n; i++) buf[rank[SA_second[i]]]++;
		for (int i = 1; i < buf_size; i++) buf[i] += buf[i - 1];
		for (int i = n - 1; ~i; i--)
			SA[--buf[rank[SA_second[i]]]] = SA_second[i];

		int* preRank = rank;
		std::swap(rank, SA_second);
		t = 1;
		rank[SA[0]] = 0;
		for (int i = 1; i < n; i++)
			rank[SA[i]] = (preRank[SA[i - 1]] == preRank[SA[i]] &&
				SA[i - 1] + k < n && SA[i] + k < n && // note
				preRank[SA[i - 1] + k] == preRank[SA[i] + k]) ? t - 1 : t++;
		if (t >= n) break;
		buf_size = t;
	}
}

void run()
{
	scanf("%s", str);
	n = strlen(str);

	GetSA();
	for (int i = 0; i < n; i++)
		printOut(SA[i] + 1);
}

int main()
{
	run();
	return 0;
}