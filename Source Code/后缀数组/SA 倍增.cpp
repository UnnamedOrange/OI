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
#include <cassert>
using std::cin;
using std::cout;
using std::endl;
typedef int INT;
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

const INT maxn = INT(1e5) + 5;
INT n, m = 128; //m代表当前rank的最大值，一开始没有离散化，代表char类型的最大值
char str[maxn]; //下标全部从0开始

INT SA[maxn];
INT x[maxn];
INT y[maxn];
INT buf[maxn]; //桶
void getSA()
{
	INT *rank = x, *tSA = y;
	//第一步：初始化rank[i]为str[i]，接下来直接对它用桶排序，不对rank单独进行离散化
	for(int i = 0; i < n; i++) rank[i] = str[i];

	//第二步：对rank数组进行桶排序，把它“离散化地”放入SA中
	memset(buf, 0, sizeof(INT) * m);
	for(int i = 0; i < n; i++) buf[rank[i]]++;
	for(int i = 1; i < m; i++) buf[i] += buf[i - 1]; //求前缀和。此时=buf[i]代表rank为i的数的最大排名。
	for(int i = n - 1; ~i; i--) SA[--buf[rank[i]]] = i; //此时保证SA[0] ~ SA[n - 1]有值，且对于相同的字符越靠前SA越小。

	//第三步：倍增
	for(int k = 1; k <= n; k <<= 1)
	{
		//（1）构造tSA，即第二关键字的rank对应的SA
		INT p = 0; //计数变量
		for(int i = n - k; i < n; i++) tSA[p++] = i; //最后k个的rank为最小值，所以排名排在最前面
		for(int i = 0; i < n; i++) if(SA[i] - k >= 0) tSA[p++] = SA[i] - k; //把SA[i]向前移k个字符
		//此时tSA的值为[0, n - 1]

		//（2）用基数排序排序rank
		memset(buf, 0, sizeof(INT) * m);
		for(int i = 0; i < n; i++) buf[rank[tSA[i]]]++; //写rank[i]更易理解，因为我们的rank才是要排序的对象，而tSA的值就是从0到n - 1。
		for(int i = 1; i < m; i++) buf[i] += buf[i - 1];
		for(int i = n - 1; ~i; i--) SA[--buf[rank[tSA[i]]]] = tSA[i]; //基数排序的精髓。

		//用SA获得新rank
		std::swap(rank, tSA); //节省拷贝数组的时间
		INT* oldRank = tSA;
		p = 1;
		rank[SA[0]] = 0;
		for(int i = 1; i < n; i++)
		{
			rank[SA[i]] = (oldRank[SA[i]] == oldRank[SA[i - 1]] && oldRank[SA[i] + k] == oldRank[SA[i - 1] + k]) ? (p - 1) : (p++); //二元组相同当且仅当对应原rank相同
		}
		m = p;
		if(m >= n) break; //如果已经有n个不同值，就结束
	}
}

INT rank[maxn];
INT height[maxn];
void getHeight()
{
	INT same = 0;
	for(int i = 0; i < n; i++) rank[SA[i]] = i;
	for(int i = 0; i < n; i++)
	{
		if(!rank[i]) same = 0; //Attention!
		else
		{
			if(same) same--;
			INT pre = SA[rank[i] - 1];
			while(i + same < n && pre + same < n && str[i + same] == str[pre + same]) same++; //Attention!
		}
		height[rank[i]] = same;
	}
}

void run()
{
	scanf("%s", str);
	n = strlen(str);
	getSA();
	getHeight();
	
	INT ans = height[1];
	for(int i = 2; i < n; i++)
	{
		ans += std::max(0, height[i] - height[i - 1]);
	}
	cout << ans << endl;
}

int main()
{
	run();
	return 0;
}
