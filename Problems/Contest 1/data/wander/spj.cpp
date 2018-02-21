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

int main(int argc, char **argv)
{
	fin = fopen(argv[1], "r");     // 鏍囧噯杈撳叆
	fout = fopen(argv[2], "r");    // 鐢ㄦ埛杈撳嚭
	fstd = fopen(argv[3], "r");    // 鏍囧噯杈撳嚭
	fscore = fopen(argv[5], "w");  // 寰楀垎鏂囦欢
	freport = fopen(argv[6], "w"); // 鎶ュ憡鏂囦欢

	long long ans1 = -1, ans2 = -1;
	fscanf(fout, "%lld%lld", &ans1, &ans2);
	long long std1, std2;
	fscanf(fstd, "%lld%lld", &std1, &std2);
	if (ans1 == std1 && ans2 == std2)
	{
		fprintf(freport, "恭喜你得到了 5 分");
		fprintf(fscore, "5");
	}
	else if (ans1 == std1 && ans2 != std2)
	{
		fprintf(freport, "恭喜你只得到了 2 分(读取到 %lld, 但期望得到 %lld)", ans2, std2);
		fprintf(fscore, "2");
	}
	else if (ans1 != std1 && ans2 == std2)
	{
		fprintf(freport, "恭喜你只得到了 3 分(读取到 %lld, 但期望得到 %lld)", ans1, std1);
		fprintf(fscore, "3");
	}
	else if (ans1 != std1 && ans2 != std2)
	{
		fprintf(freport, "恭喜你被 WA 飞了(读取到 %lld %lld, 但期望得到 %lld %lld)", ans1, ans2, std1, std2);
		fprintf(fscore, "0");
	}
	return 0;
}
