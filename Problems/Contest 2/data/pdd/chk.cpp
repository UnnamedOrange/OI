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
#include "testlib.h"

int fullmark = 5;
int mark;

void judge()
{
	int n = inf.readInt();

	int ans1 = ouf.readInt();
	int std1 = ans.readInt();
	if (ans1 == std1)
		mark += fullmark * 2 / 5;

	for (int i = 1; i <= n; i++)
	{
		int ans2 = ouf.readInt();
		int std2 = ans.readInt();
		if (ans2 != std2)
			return;
	}
	mark += fullmark * 3 / 5;
}

int main(int argc, char* argv[])
{
	registerTestlibCmd(argc, argv);
	judge();

	if (mark == fullmark)
		quitf(_ok, "Winner winner, chicken dinner.");
	else
		quitp(std::ceil(100.0 * mark / fullmark) / 100, "Better luck next time.");
}