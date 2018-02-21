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
#include <functional>
#include <ctime>
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
}

FILE *fscore, *freport, *fstd, *fin, *fout;
int fullmark;
int mark;

void judge()
{
	int n;
	fscanf(fin, "%d", &n);

	int ans1 = -1, std1 = -1;
	fscanf(fout, "%d", &ans1);
	fscanf(fstd, "%d", &std1);
	if (ans1 == std1)
		mark += fullmark * 2 / 5;

	for (int i = 1; i <= n; i++)
	{
		int ans2 = -1, std2 = -1;
		fscanf(fout, "%d", &ans2);
		fscanf(fstd, "%d", &std2);
		if (ans2 != std2)
			return;
	}
	mark += fullmark * 3 / 5;
}

int main(int argc, char **argv)
{
	fin = fopen(argv[1], "r"); //input
	fout = fopen(argv[2], "r"); //output
	fstd = fopen(argv[3], "r"); //stdout
	fscore = fopen(argv[5], "w"); //score
	freport = fopen(argv[6], "w"); //report
	sscanf(argv[4], "%d", &fullmark);

	judge();

	fprintf(fscore, "%d", mark);

	if (mark == fullmark)
		fprintf(freport, "大吉大利，晚上吃鸡");
	else
		fprintf(freport, "祝你下次好运");
	return 0;
}