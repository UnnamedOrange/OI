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

const INT INF = (~(INT(1) << (sizeof(INT) * 8 - 1)));
const INT maxn = 1005;
INT n;
INT a[maxn];

std::vector<std::vector<INT> > edges;

INT vis[maxn];
bool dfs(INT node, INT color)
{
	vis[node] = color;
	for(int i = 0; i < edges[node].size(); i++)
	{
		INT to = edges[node][i];
		if(vis[to] == color) return false;
		else if(vis[to] == !color) continue;
		else if(!dfs(to, !color)) return false;
	}
	return true;
}

void run()
{
	n = readIn();
	for(int i = 1; i <= n; i++)
	{
		a[i] = readIn();
	}
	edges.resize(n + 1);

	INT minVal = INF;
	for(int i = n; i >= 1; i--)
	{
		for(int j = 1; j < i; j++)
		{
			if(a[j] < a[i] && minVal < a[j])
			{
				edges[j].push_back(i);
				edges[i].push_back(j);
			}
		}
		minVal = std::min(minVal, a[i]);
	}

	bool bOk = true;
	memset(vis, -1, sizeof(vis));
	for(int i = 1; i <= n; i++)
	{
		if(!~vis[i])
		{
			bOk = dfs(i, 0);
			if(!bOk) break;
		}
	}
	if(!bOk)
	{
		cout << 0 << endl;
		return;
	}

	INT input = 1;
	INT output = 1;
	std::stack<INT> s1, s2;
	s1.push(a[1]);
	input++;
	cout << "a";

	while(output <= n)
	{
		if(!s1.empty() && s1.top() == output)
		{
			s1.pop();
			output++;
			cout << " b";
		}
		else if(!vis[input] && (s1.empty() || s1.top() > a[input]))
		{
			s1.push(a[input]);
			input++;
			cout << " a";
		}
		else if(!s2.empty() && s2.top() == output)
		{
			s2.pop();
			output++;
			cout << " d";
		}
		else if(vis[input] && (s2.empty() || s2.top() > a[input]))
		{
			s2.push(a[input]);
			input++;
			cout << " c";
		}
	}
}

int main()
{
	run();
	return 0;
}
