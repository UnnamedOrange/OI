##### 1. 定义

######仙人掌

​	无向连通图，每条边最多在一个环上，（可能有重边）

###### 圆方树

​	圆点：连到对应的方点上

​	方点：一个环对应一个方点

​	边的顺序确定后圆方树和仙人掌意义对应。

##### 2. [BZOJ 2125 仙人掌的带权最短路](http://www.lydsy.com/JudgeOnline/problem.php?id=2125)

​	方点：环上：对每个环做前缀和。

#####3. [BZOJ 4316 仙人掌的最大独立集](http://www.lydsy.com/JudgeOnline/problem.php?id=4316)

​	圆方树上做最大独立集。

​	环套树：设三个状态。

#####4. [BZOJ 1023 仙人掌直径](http://www.lydsy.com/JudgeOnline/problem.php?id=1023)

​	用 DP。

​	方点用单调队列维护。

#####5. [UOJ 87](http://uoj.ac/problem/87)

#####6. [UOJ 23](http://uoj.ac/problem/23)

##### 7. 圆方树同构

​	