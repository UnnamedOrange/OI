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
typedef LL INT_PUT;
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
	putchar('\n');
}

const int maxn = int(1e5) + 5;
int n, k;
LL a[maxn];

struct HeapNode
{
	LL w;
	int h;
	HeapNode(LL w, int h) : w(w), h(h) {}
	bool operator<(const HeapNode& b) const
	{
		if (w != b.w) return w > b.w;
		return h > b.h;
	}
};

void run()
{
	std::priority_queue<HeapNode> pq;
	n = readIn();
	k = readIn();
	for (int i = 1; i <= n; i++)
		pq.push(HeapNode(readIn(), 0));
	while ((pq.size() - 1) % (k - 1))
		pq.push(HeapNode(0, 0));

	LL ans = 0;
	while (pq.size() > 1)
	{
		LL sum = 0;
		int height = 0;
		for (int i = 1; i <= k; i++)
		{
			HeapNode t = pq.top();
			pq.pop();
			sum += t.w;
			height = std::max(height, t.h);
		}
		ans += sum;
		pq.push(HeapNode(sum, height + 1));
	}

	printOut(ans);
	printOut(pq.top().h);
}

int main()
{
	run();
	return 0;
}