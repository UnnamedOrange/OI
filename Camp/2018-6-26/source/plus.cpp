using LL = long long;

#ifdef LOCAL
#include <bits/stdc++.h>
using namespace std;
std::vector<int> assign(int, int, int, int, int, int);

namespace __unused
{
	std::default_random_engine e(std::time(NULL));
	using Rand = std::uniform_int_distribution<int>;
	int rand(int l, int r)
	{
		return Rand(l, r)(e);
	}
	int backup[4][11][11];
	int f[4][11][11];
	int seq1[11];
	int seq2[11];
	void init()
	{
		for (int i = 1; i <= 3; i++)
		{
			for (int j = 1; j <= 10; j++)
				for (int k = 1; k < j; k++)
				{
					f[i][j][k] = rand(100, 300);
					f[i][k][j] = 400 - f[i][j][k];
				}
			for (int j = 1; j <= 10; j++)
				f[i][j][j] = 200;
		}
		std::memcpy(backup, f, sizeof(backup));
	}
	void adjust()
	{
		std::memcpy(f, backup, sizeof(f));
		for (int i = 1; i <= 3; i++)
			for (int j = 1; j <= 10; j++)
				for (int k = 1; k <= 10; k++)
					f[i][j][k] += rand(-20, 20);
		std::random_shuffle(seq1 + 1, seq1 + 1 + 10);
		std::random_shuffle(seq2 + 1, seq2 + 1 + 10);
	}
	LL ans;
	LL yours;
	LL last;
	void statistic(const std::vector<int>& per)
	{
		auto t = per;
		std::sort(t.begin(), t.end());
		if (!(t[0] == 1 && t[1] == 2 && t[2] == 3))
			return throw;
		last = f[per[0]][seq1[1]][seq2[per[0]]] +
			f[per[1]][seq1[2]][seq2[per[1]]] +
			f[per[2]][seq1[3]][seq2[per[2]]];
		yours += last;

		LL Max = LLONG_MIN;
		do
		{
			LL sum = f[t[0]][seq1[1]][seq2[t[0]]] +
				f[t[1]][seq1[2]][seq2[t[1]]] +
				f[t[2]][seq1[3]][seq2[t[2]]];
			Max = std::max(Max, sum);
		} while (std::next_permutation(t.begin(), t.end()));
		ans += Max;
	}
}

int getinfo()
{
	using namespace __unused;
	return last;
}

int main()
{
	using namespace __unused;

	init();
	for (int i = 1; i <= 10; i++)
		seq1[i] = seq2[i] = i;
	for (int i = 1; i <= 100000; i++)
	{
		adjust();
		auto per = assign(seq1[1], seq1[2], seq1[3],
			seq2[1], seq2[2], seq2[3]);
		statistic(per);
	}

	printf("You got %d points.\n", (int)std::floor(100.0 *
		std::pow((double)yours / ans, 3) + 0.5));
	printf("Your score: %lld\n", yours);
	printf("Std have got: %lld\n", ans);
	return 0;
}
#endif

int Round;

std::default_random_engine e(std::time(NULL));
using Rand = std::uniform_int_distribution<int>;
int rand(int l, int r)
{
	return Rand(l, r)(e);
}

int f[4][11][11];
int seq1[4], seq2[4];
std::vector<int> lastans;
void init()
{
	for (int i = 1; i <= 3; i++)
	{
		for (int j = 1; j <= 10; j++)
			for (int k = 1; k < j; k++)
			{
				f[i][j][k] = rand(100, 300);
				f[i][k][j] = 400 - f[i][j][k];
			}
		for (int j = 1; j <= 10; j++)
			f[i][j][j] = 200;
	}
}
void adjust()
{
	if (getinfo() >= 600 + rand(-30, 90))
	{
		f[lastans[0]][seq1[1]][seq2[lastans[0]]] += rand(20, rand(20, 100));
		f[lastans[1]][seq1[2]][seq2[lastans[1]]] += rand(20, rand(20, 100));
		f[lastans[2]][seq1[3]][seq2[lastans[2]]] += rand(20, rand(20, 100));
	}
	else
	{
		f[lastans[0]][seq1[1]][seq2[lastans[0]]] -= rand(20, rand(20, 100));
		f[lastans[1]][seq1[2]][seq2[lastans[1]]] -= rand(20, rand(20, 100));
		f[lastans[2]][seq1[3]][seq2[lastans[2]]] -= rand(20, rand(20, 100));
	}
}
std::vector<int> statistic()
{
	std::vector<int> t(3);
	t[0] = 1;
	t[1] = 2;
	t[2] = 3;

	std::vector<int> ret;
	LL Max = LLONG_MIN;
	do
	{
		LL sum = f[t[0]][seq1[1]][seq2[t[0]]] +
			f[t[1]][seq1[2]][seq2[t[1]]] +
			f[t[2]][seq1[3]][seq2[t[2]]];
		if (sum > Max)
		{
			Max = sum;
			ret = t;
		}
	} while (std::next_permutation(t.begin(), t.end()));
	return ret;
}

std::vector<int> assign(int A, int B, int C,
	int D, int E, int F)
{
	std::vector<int> ret;
	if (!Round)
	{
		ret.resize(3);
		for (int i = 0; i < 3; i++)
			ret[i] = i + 1;
		std::random_shuffle(ret.begin(), ret.end());
	}
	else
	{
		adjust();
		seq1[1] = A;
		seq1[2] = B;
		seq1[3] = C;
		seq2[1] = D;
		seq2[2] = E;
		seq2[3] = F;
		ret = statistic();
	}
	Round++;
	return lastans = ret;
}