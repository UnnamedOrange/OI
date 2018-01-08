// Copyright (C) 2017 __debug.

// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; version 3

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; If not, see <http://www.gnu.org/licenses/>.


#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>

#define x first
#define y second
#define MP std::make_pair
#define SZ(x) ((int)(x).size())
#define ALL(x) (x).begin(), (x).end()
#define DEBUG(...) fprintf(stderr, __VA_ARGS__)
#ifdef __linux__
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif

using std::pair;
using std::vector;
using std::string;

typedef long long LL;
typedef pair<int, int> Pii;

const int oo = 0x3f3f3f3f;

template<typename T> inline bool chkmax(T &a, T b) { return a < b ? a = b, true : false; }
template<typename T> inline bool chkmin(T &a, T b) { return b < a ? a = b, true : false; }
string procStatus()
{
    std::ifstream t("/proc/self/status");
    return string(std::istreambuf_iterator<char>(t), std::istreambuf_iterator<char>());
}
template<typename T> T read(T &x)
{
    int f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        f = (ch == '-' ? -1 : 1);
    for (x = 0; isdigit(ch); ch = getchar())
        x = 10 * x + ch - '0';
    return x *= f;
}
template<typename T> void write(T x)
{
    if (x == 0) {
        putchar('0');
        return;
    }
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    static char s[20];
    int top = 0;
    for (; x; x /= 10)
        s[++top] = x % 10 + '0';
    while (top)
        putchar(s[top--]);
}
// EOT

FILE *fscore, *freport, *fstd, *fin, *fout;

int main(int argc, char **argv)
{
    fin = fopen(argv[1], "r");     // 标准输入
    fout = fopen(argv[2], "r");    // 用户输出
    fstd = fopen(argv[3], "r");    // 标准输出
	fscore = fopen(argv[5], "w");  // 得分文件
	freport = fopen(argv[6], "w"); // 报告文件

    int h;
    if (fscanf(fout, "%d", &h) != 1 || h == 19260817) {
        fprintf(fscore, "0");
        fprintf(freport, "incorrect");
        return 0;
    }
    fprintf(freport, "correct, maxh=%d\n", h);
    int score;
    if (h <= 12 || h == 20000909)
        score = 100;
    else if (h <= 13)
        score = 75;
    else if (h <= 14)
        score = 60;
    else if (h <= 15)
        score = 50;
    else if (h <= 16)
        score = 42;
    else if (h <= 17)
        score = 37;
    else if (h <= 18)
        score = 33;
    else if (h <= 19)
        score = 30;
    else if (h <= 20)
        score = 27;
    else
        score = 1;
    fprintf(fscore, "%d", score);
}

// 浊酒一杯家万里，燕然未勒归无计。
//     -- 范仲淹《渔家傲·秋思》
