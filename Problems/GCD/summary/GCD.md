##### GCD 1

&emsp;&emsp;因为都是 $n$，所以使用欧拉函数即可。单次查询时间复杂度为 $O(\frac {n} {\log n})$。

##### GCD 2

&emsp;&emsp;首先做到单次询问 $O(\frac {n^2} {\log n})$，然后再次枚举积，提出来，将时间复杂度优化至 $O(\sqrt n)$。

##### GCD 3

&emsp;&emsp;加上一个简单的容斥，本身相当于是不需要枚举质数的 GCD 2。

##### GCD 4

&emsp;&emsp;与前面的不同的是，这道题需要用到 $\varphi$ 而不是 $\mu$。

##### GCD 5

&emsp;&emsp;直接枚举 $\gcd$ 进行化简，接下来仍然是枚举积。

##### GCD 6

&emsp;&emsp;又有 $n = m$，可以考虑使用 $\varphi$。

##### GCD 7

&emsp;&emsp;利用一个神奇的等式后直接莫比乌斯反演，然后直接到最外层枚举，从内到外考虑贡献。