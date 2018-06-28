#ifdef LOCAL
#include "diff.h"
#endif

#include <algorithm>
#include <map>

using LL = long long;
using ULL = unsigned long long;

std::map<std::pair<int, int>, LL> map;
LL query(int x, int y)
{
	if (map.count(std::make_pair(x, y)))
		return map[std::make_pair(x, y)];
	return map[std::make_pair(x, y)] = getDistance(x, y);
}

long long getMiniumDistance(int n, int m)
{
	double ratio = (3 - std::sqrt(5.0)) / 2;
	int x, y;
	double l, r;

	l = 1;
	r = n;
	int t = std::round(1 + (m - 1) * ratio);
	while (r - l > 4)
	{
		double divide3 = (r - l) * ratio;
		double midl = l + divide3;
		double midr = r - divide3;
		LL val1 = query(std::round(midl), t);
		LL val2 = query(std::round(midr), t);
		if (val1 == val2)
		{
			l = midl;
			r = midr;
		}
		else if (val1 > val2)
		{
			l = midl;
		}
		else if (val1 < val2)
		{
			r = midr;
		}
	}
	x = std::round(l);
	for (int i = x + 1; i <= std::round(r); i++)
		if (query(i, t) < query(x, t))
			x = i;

	l = 1;
	r = m;
	while (r - l > 4)
	{
		double divide3 = (r - l) * ratio;
		double midl = l + divide3;
		double midr = r - divide3;
		LL val1 = query(x, std::round(midl));
		LL val2 = query(x, std::round(midr));
		if (val1 == val2)
		{
			l = midl;
			r = midr;
		}
		else if (val1 > val2)
		{
			l = midl;
		}
		else if (val1 < val2)
		{
			r = midr;
		}
	}
	y = std::round(l);
	for (int i = y + 1; i <= std::round(r); i++)
		if (query(x, i) < query(x, y))
			y = i;
	return query(x, y);
}

long long getMiniumDistance3(int n, int m)
{
	int lx = 1, rx = n + 1;
	int ly = 1, ry = m + 1;
	while (rx - lx > 1 && ry - ly > 1)
	{
		int midx = (lx + rx) >> 1;
		int midy = (ly + ry) >> 1;
		LL val = query(midx, midy);
		LL val1 = query(midx - 1, midy);
		LL val2 = query(midx, midy - 1);
		if (val1 == val)
		{
			lx = midx - 1;
			rx = midx;
		}
		else if (val1 > val)
			lx = midx;
		else if (val1 < val)
			rx = midx;

		if (val2 == val)
		{
			ly = midy - 1;
			ry = midy;
		}
		else if (val2 > val)
			ly = midy;
		else if (val2 < val)
			ry = midy;
	}
	while (rx - lx > 1)
	{
		int midx = (lx + rx) >> 1;
		LL val = query(midx, ly);
		LL val1 = query(midx - 1, ly);
		if (val1 == val)
		{
			lx = midx - 1;
			rx = midx;
		}
		else if (val1 > val)
			lx = midx;
		else if (val1 < val)
			rx = midx;
	}
	while (ry - ly > 1)
	{
		int midy = (ly + ry) >> 1;
		LL val = query(lx, midy);
		LL val1 = query(lx, midy - 1);
		if (val1 == val)
		{
			ly = midy - 1;
			ry = midy;
		}
		else if (val1 > val)
			ly = midy;
		else if (val1 < val)
			ry = midy;
	}
	return query(lx, ly);
}

long long getMiniumDistance2(int n, int m)
{
	int x, y;

	int l, r;
	LL vall, valr;
	LL minVal;

	l = 1;
	r = n + 1;
	while (r - l > 1)
	{
		int mid = (l + r) >> 1;
		LL val1 = query(mid - 1, 1);
		LL val2 = query(mid, 1);
		if (val1 == val2)
		{
			l = mid - 1;
			r = mid;
			break;
		}
		else if (val1 > val2)
			l = mid;
		else if (val1 < val2)
			r = mid;
	}
	x = l;

	l = 1;
	r = m + 1;
	while (r - l > 1)
	{
		int mid = (l + r) >> 1;
		LL val1 = query(x, mid - 1);
		LL val2 = query(x, mid);
		if (val1 == val2)
		{
			l = mid - 1;
			r = mid;
			break;
		}
		else if (val1 > val2)
			l = mid;
		else if (val1 < val2)
			r = mid;
	}
	y = l;
	return query(x, y);
}

long long getMiniumDistance1(int n, int m)
{
	int x, y;

	int l, r;
	LL vall, valr;
	LL minVal;

	l = 1;
	r = n;
	vall = query(l, 1);
	valr = query(r, 1);
	while (r - l > 2)
	{
		int divide3 = (r - l + 1) / 3;
		int midl = l + divide3;
		int midr = midl + divide3;
		LL val1 = query(midl, 1);
		LL val2 = query(midr, 1);
		if (val1 == val2)
		{
			vall = val1;
			valr = val2;
			l = midl;
			r = midr;
		}
		else if (val1 > val2)
		{
			vall = val1;
			l = midl;
		}
		else if (val1 < val2)
		{
			valr = val2;
			r = midr;
		}
	}
	x = l;
	minVal = vall;
	if (valr < vall)
	{
		minVal = valr;
		x = r;
	}
	if (l + 1 < r)
	{
		LL t = query(l + 1, 1);
		if (t < minVal)
		{
			minVal = t;
			x = l + 1;
		}
	}

	l = 1;
	r = m;
	vall = query(x, l);
	valr = query(x, r);
	while (r - l > 2)
	{
		int divide3 = (r - l + 1) / 3;
		int midl = l + divide3;
		int midr = midl + divide3;
		LL val1 = query(x, midl);
		LL val2 = query(x, midr);
		if (val1 == val2)
		{
			vall = val1;
			valr = val2;
			l = midl;
			r = midr;
		}
		else if (val1 > val2)
		{
			vall = val1;
			l = midl;
		}
		else if (val1 < val2)
		{
			valr = val2;
			r = midr;
		}
	}
	y = l;
	minVal = vall;
	if (valr < vall)
	{
		minVal = valr;
		y = r;
	}
	if (l + 1 < r)
	{
		LL t = query(x, l + 1);
		if (t < minVal)
		{
			minVal = t;
			y = l + 1;
		}
	}
	return minVal;
}