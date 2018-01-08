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

const int LIM = 12;

int type, N;
vector<int> code;

void init()
{
	for (int s = 0; s < (1 << LIM) && SZ(code) < N; ++s) {
		if (__builtin_popcount(s) == LIM / 2)
			code.push_back(s);
	}
	assert(SZ(code) == N);
}

int encode(int x, int y)
{
	return 32 - __builtin_clz((code[x - 1] ^ code[y - 1]) & code[x - 1]);
}

bool decode(int q, int h)
{
	return code[q - 1] >> (h - 1) & 1;
}

int main()
{
	int T;
	read(type); read(N); read(T);
	init();
	while (T--) {
		int x, y;
		read(x); read(y);
		if (type == 1)
			printf("%d\n", encode(x, y));
		else
			puts(decode(x, y) ? "yes" : "no");
	}
}

// 咬定青山不放松，立根原在破岩中。
//     -- 郑燮《竹石》
