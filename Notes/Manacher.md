[TOC]

# Manacher

##### 1. 问题定义

&emsp;&emsp;最长回文子串问题：给定一个字符串，求出它的最长回文子串长度。回文串的定义是：如果一个字符串正着读和反着读是一样的，那么它就是回文串。

###### ① 暴力方法

&emsp;&emsp;找到所有子串，验证它是否为回文子串。时间复杂度 $O(n^3)$。

###### ② 改进的方法

&emsp;&emsp;枚举中心，向两边扩张，时间复杂度为 $O(n^2)$。

##### 2. Manacher 算法

###### ①问题 1

&emsp;&emsp;当回文串长度的奇偶性不同时，回文串的形式是不同的。

&emsp;&emsp;Manacher 首先要做一个预处理，在包括首尾的空隙位置插入一个同样的，但是不会在原串中出现的符号。**这使得所有的回文子串的长度变为了奇数**，但是不影响原串的回文性质：原来是回文的串，插完之后还是回文的，原来不是回文的，依然不会是回文。

###### ②问题 2

&emsp;&emsp;效率问题。如何将时间复杂度将为 $O(n)$？

##### 3. Manacher 算法的定义

###### 回文半径

&emsp;&emsp;设一个回文串中最左或最右位置的字符与其对称轴的距离称为回文半径。Manacher 定义了一个回文半径数组 RL，用 $RL_i$ 表示**以第 i 个字符为对称轴的回文串的回文半径。**由于我们一般对字符串从左往右处理，因此这里定义 $RL_i$ 表示以第 i 个字符为对称轴的回文串的**最右**一个字符与字符 i 的距离。

&emsp;&emsp;距离在这里指**包含开始和结尾的字符个数。**

```
str:     # a # b # a # a #
RL:      1 2 1 4 1 2 3 2 1 
RL - 1:  0 1 0 3 0 1 2 1 0
```

&emsp;&emsp;观察上例，发现 **$RL_i - 1$ 的值正是原字符串以 i 为对称轴的最长回文子串的长度。** 

&emsp;&emsp;定义：RL 的物理意义是以 i 为回文中心的回文串的回文半径。RL 的匹配意义是原串中以位置 i 为对称轴的最长回文串的长度 + 1。

##### 4. Manacher 算法的过程

###### ①基本思路

&emsp;&emsp;利用回文串的对称性，扩展回文串。

###### ②算法步骤

&emsp;&emsp;**我们的任务是求 RL 数组。**

&emsp;&emsp;![Manacher 1](pic\Manacher 1.png)

&emsp;&emsp;我们需要维护两个变量：maxRight 和 center。maxRight 代表从左到右处理时已经到达过的最右位置（它是一个回文子串的端点），center 代表 maxRight 对应的回文子串的回文中心。

&emsp;&emsp;**注意：上图中从未说到目前正在处理哪里！接下来将对此分情况讨论！**

&emsp;&emsp;我们设当前正在处理第 i 位，毫无疑问，第 i 位一定在 center 的右边。然后我们分成以下三种情况：

①若 i 在 maxRight 左边

![Manacher 2](pic\Manacher 2.png)

&emsp;&emsp;上图应该是最简单的情况了。**我们找到 i 关于 center 对称的点 j，发现 j 的回文半径居然还不足以触及到 center！**所以此时 $RL_i = RL_j$。（1）

&emsp;&emsp;![Manacher 3](pic\Manacher 3.png)

&emsp;&emsp;当 j 的回文半径更大，超过了 center 时，我们只能知道 **i 到 maxRight 是以 i 为回文中心的最小回文半径（粗虚线）。**能否到细虚线**或是更远**，只能扩张 i 并且**更新 maxRight 和 center** 来检查了。（2）

②当 i 在 maxRight 的右边

![Manacher 4](pic\Manacher 4.png)

&emsp;&emsp;**只有唯一一种情况：i 与 maxRight 相邻。**这时让回文半径从 1 开始（即从 i 开始）不断扩张，直到**不再回文或到达边界，同时更新 center 和 maxRight 即可。**（3）

&emsp;&emsp;总的来说分成三种情况，但其中（1）（2）一并处理，以代码实现为准。

##### 5. 时空复杂度

&emsp;&emsp;空间复杂度明显是线性的。由于扩张 maxRight 的操作对于每个位置只会进行一次，因此我们得到：Manacher 的时间复杂度是线性的。

##### 6. 参考代码

```c++
struct Manacher
{
	INT length;
	std::vector<char> a;
	std::vector<INT> f;
	INT maxLength;
	Manacher(const char* str)
	{
		length = strlen(str);
		a.resize(length * 2 + 1);
		f.resize(length * 2 + 1);
		INT pos = 0;
		a[pos++] = '#';
		for (int i = 0; i < length; i++)
		{
			a[pos++] = str[i];
			a[pos++] = '#';
		}
		manacher();
	}
	void manacher()
	{
		INT center; //undefined
		INT maxRight = -1; //闭区间
		for (int i = 0; i < a.size(); i++)
		{
			if (i <= maxRight)
			{
				//i + j == 2 * center
				f[i] = std::min(f[2 * center - i], maxRight - i + 1);
			}
			else
				f[i] = 1;

			while (i - f[i] >= 0 && i + f[i] < a.size() && a[i - f[i]] == a[i + f[i]])
				f[i]++;

			if (i + f[i] - 1 > maxRight)
			{
				maxRight = i + f[i] - 1;
				center = i;
			}
			maxLength = std::max(maxLength, f[i]);
		}
		maxLength--;
	}
};
```