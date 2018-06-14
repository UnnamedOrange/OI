# 专题：数学

## 数论

### 质数筛法

#### 埃氏筛

##### 时间复杂度

###### ①用所有数去筛

$O(n \log n)$

###### ②用质数筛

$O(n \log \log n)$

##### 扩展

###### ①区间筛

###### ②分段打表

#### 线性筛

##### e.g.

###### 题目大意

​	求 $\sum_{i = 1}^n i \sigma_1(i^2)$ 取模。

​	模数不固定，$n \le 10^7$；模数固定，$n \le 10^9$。

###### 解决方法

1. 线性筛

$$
f(x) = x \sigma_1(x^2)
$$

$$
f(p) = p(1 + p + p^2)
$$

$$
f(p_k) = p^k(1 + p + \cdots + p^{2k})
$$

2. 分段打表

   每隔 $10^3$ 个数求和，然后用区间筛求积性函数。

### 欧几里得算法与扩展欧几里得算法

##### e.g.

###### 题目大意

​	已知 $c_1$，$c_2$，$e_1$，$e_2$，$N$。满足 $\gcd(e_1, e_2) = \gcd(m, N) = 1$，$c_1 \equiv m^{e_1} \pmod N$，$c_2 \equiv m^{e_2} \pmod N$，求 $m$。

​	数据规模：$N \le 10^{18}$。

###### 解决方法

$$
c_1 c_2^{-1} \equiv m^{e_1 - e_2} \pmod N
$$

（由于 $m$ 与 $N$ 互质，因此 $c_2 \equiv m^{e_2}$ 与 $N$ 互质）

​	得到：
$$
c_3 \equiv m^{e_3} \pmod N
$$
​	一直递归，直到 $e = 1$。

### 费马小定理和欧拉定理

##### 同余式的除法

$$
ak \equiv bk \pmod c
$$

​	若 $\gcd(k, c) = 1$，则：
$$
a \equiv b \pmod c
$$
​	若 $k \mid c$，则：
$$
a \equiv b \pmod {\frac {c} {k}}
$$


##### 扩展欧拉定理

（类似于混循环）

##### e.g.

###### 题目大意

​	给定 $p$，求 $2^{2^{2^{\dots}}} \bmod p$。

###### 解决方法

$$
2^{2^{2 \cdots} \bmod \varphi (b) + \varphi(b)} \bmod b
$$

$$
f(b) = 2^{f(\varphi(b)) + \varphi(b)} \bmod b
$$

### 原根

​	设 $b$ 是正整数，$a$ 是整数**且与 $b$ 互质**，若 $a_0, a_1, \cdots, a^{\varphi(b) - 1}$ 互不相同，则称 $a$ 为模 $b$ 的一个原根。

#### 求原根

​	若广义黎曼猜想成立，则 $p$ 的最小正原根是 $O(\log^6 n)$ 级别的。通过枚举法可以快速找到（最小的）原根。

判断 $a$ 是否为 $b$ 的原根。

​	由于欧拉定理成立，方程 $a^x \equiv 1$ 的一个解是 $\varphi(b)$。因为它的最小正整数解 $x \mid \varphi(b)$，**逐个尝试 $\varphi(b)$ 的约数即可**。时间复杂度 $O(\sqrt b \log b)$。

​	更好的方法：尝试 $\varphi(b)$ 除以 $\varphi(b)$ 的所有质因数。（$\frac {\varphi(b)} {p_i}$）

### *线性同余方程

​	考虑将每两个方程合并，而不是中国剩余定理的整体考虑。
$$
\begin{cases}
x \equiv a_1 \pmod {b_1}
\\
x\equiv a_2 \pmod {b_2}
\end{cases}
$$
​	考虑特殊情况：$a_1 = 0$，$\gcd(b_1, b_2) = 1$。
$$
\begin{cases}
x \equiv 0 \pmod{b_1}
\\
x \equiv a \pmod{b_2}
\end{cases}
$$

### 第一类指数同余方程

$$
a^x \equiv b \pmod p
$$

​	BSGS。

​	BSGSEx：除以 $\gcd$。
$$
\frac {a} {d} a^{x - 1} \equiv \frac {b} {d} \pmod {\frac {p} {d}}
$$

$$
\frac {a} {d_1} \frac {a} {d_2} \cdots \frac {a} {d_k} a^{x - k} \equiv {b} {d_1 d_2 \cdots d_k} \pmod {\frac {p} {d_1 d_2 \cdots d_k}}
$$

### *第二类指数同余方程

$$
x^a \equiv b \pmod {p}
$$

用原根，BSGS，费马小定理。

（……有 $d$ 组解）

### 二次剩余

$$
x^2 \equiv n \pmod p
$$

​	有解则必有两解。
$$
(x - x_1)(x + x_1) \equiv n \pmod p
$$

#### 勒让德符号

$$
\left( \frac {n} {p} \right)
=
\begin{cases}
0 & n = 0
\\
1 & \text{有二次剩余}
\\
-1 & \text{没有二次剩余}
\end{cases}
$$

$$
n^{\frac {p - 1} {2}} \equiv
\begin {cases}
1 & \text{有二次剩余}
\\
-1 & \text{没有二次剩余}
\end {cases}
$$

## 线性代数

### 向量与向量空间

### 行列式

#### *积和式

​	行列式不要那个 $(-1)^{N}$，叫做积和式。

​	积和式很难算，但是**奇偶性与行列式相同**。

#### *伴随矩阵

​	第 $i$ 行第 $j$ 列为 $A_{j, i}$ 的矩阵为矩阵 $A$ 的伴随矩阵，记作 $A^*$。

​	伴随矩阵的重要性质：若矩阵 $A$ 可逆，有：
$$
A^* = \det(A) A^{-1}
$$
