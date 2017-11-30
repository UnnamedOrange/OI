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
INT n, m = 128; //m����ǰrank�����ֵ��һ��ʼû����ɢ��������char���͵����ֵ
char str[maxn]; //�±�ȫ����0��ʼ

INT SA[maxn];
INT x[maxn];
INT y[maxn];
INT buf[maxn]; //Ͱ
void getSA()
{
	INT *rank = x, *tSA = y;
	//��һ������ʼ��rank[i]Ϊstr[i]��������ֱ�Ӷ�����Ͱ���򣬲���rank����������ɢ��
	for(int i = 0; i < n; i++) rank[i] = str[i];

	//�ڶ�������rank�������Ͱ���򣬰�������ɢ���ء�����SA��
	memset(buf, 0, sizeof(INT) * m);
	for(int i = 0; i < n; i++) buf[rank[i]]++;
	for(int i = 1; i < m; i++) buf[i] += buf[i - 1]; //��ǰ׺�͡���ʱ=buf[i]����rankΪi���������������
	for(int i = n - 1; ~i; i--) SA[--buf[rank[i]]] = i; //��ʱ��֤SA[0] ~ SA[n - 1]��ֵ���Ҷ�����ͬ���ַ�Խ��ǰSAԽС��

	//������������
	for(int k = 1; k <= n; k <<= 1)
	{
		//��1������tSA�����ڶ��ؼ��ֵ�rank��Ӧ��SA
		INT p = 0; //��������
		for(int i = n - k; i < n; i++) tSA[p++] = i; //���k����rankΪ��Сֵ����������������ǰ��
		for(int i = 0; i < n; i++) if(SA[i] - k >= 0) tSA[p++] = SA[i] - k; //��SA[i]��ǰ��k���ַ�
		//��ʱtSA��ֵΪ[0, n - 1]

		//��2���û�����������rank
		memset(buf, 0, sizeof(INT) * m);
		for(int i = 0; i < n; i++) buf[rank[tSA[i]]]++; //дrank[i]������⣬��Ϊ���ǵ�rank����Ҫ����Ķ��󣬶�tSA��ֵ���Ǵ�0��n - 1��
		for(int i = 1; i < m; i++) buf[i] += buf[i - 1];
		for(int i = n - 1; ~i; i--) SA[--buf[rank[tSA[i]]]] = tSA[i]; //��������ľ��衣

		//��SA�����rank
		std::swap(rank, tSA); //��ʡ���������ʱ��
		INT* oldRank = tSA;
		p = 1;
		rank[SA[0]] = 0;
		for(int i = 1; i < n; i++)
		{
			rank[SA[i]] = (oldRank[SA[i]] == oldRank[SA[i - 1]] && oldRank[SA[i] + k] == oldRank[SA[i - 1] + k]) ? (p - 1) : (p++); //��Ԫ����ͬ���ҽ�����Ӧԭrank��ͬ
		}
		m = p;
		if(m >= n) break; //����Ѿ���n����ֵͬ���ͽ���
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
