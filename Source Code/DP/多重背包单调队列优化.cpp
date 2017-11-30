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

const INT maxn = 7005;
INT n, m;
INT f[maxn];

struct MonotonicQueue
{
	std::deque<INT> origin; //�����е������д��� 
	std::deque<INT> deq; //���е������д��� 

	void push(const INT x)
	{
		origin.push_back(x);
		while (!deq.empty() && deq.back() < x) deq.pop_back(); //����д<= 
		deq.push_back(x);
	}
	void pop()
	{
		if (origin.front() == deq.front()) deq.pop_front();
		origin.pop_front();
	}
	INT size()
	{
		return origin.size();
	}
	INT max()
	{
		return deq.front();
	}
};

void run()
{
	n = readIn();
	m = readIn();
	while (n--)
	{
		INT cost = readIn();
		INT value = readIn();
		INT num = readIn();
		for (int i = 0; i < cost; i++)
		{
			MonotonicQueue mono;
			INT sumCost = i;
			INT delta = 0;
			while (sumCost <= m)
			{
				mono.push(f[sumCost] - delta); //�Ȳ��룬�����Ͳ������״̬���ң���ʱ��û��ѡ��Ʒ 

				if (mono.size() > num + 1) //+1����Ϊ���ǵ�ѡ���Ǵ�0��num 
					mono.pop();
				f[sumCost] = mono.max() + delta;
				sumCost += cost;
				delta += value;
			}
		}
	}
	cout << f[m] << endl;
}

int main()
{
	run();
	return 0;
}
