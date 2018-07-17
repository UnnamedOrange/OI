[TOC]

> 开局一个 Markdown，内容全靠编。——Orange

# Link-Cut Tree

[参考资料](https://www.cnblogs.com/BLADEVIL/p/3510997.html)

[参考资料](https://www.cnblogs.com/candy99/p/6271344.html)

不保证能看懂，但保证讲清楚所有细节。

## 总览

##### 1. 动态树问题

动态树问题是一类要求维护森林的连通性的题的总称。这类问题要求：

1. 维护某个点到根的某些数据。
2. 对树进行切分。
3. 对树进行合并。
4. 操作子树。
5. ……

解决这类问题的子问题（**不包括操作子树**）的基础数据结构就是 *Link-Cut Tree（LCT）*。

##### 2. 树链剖分

静态的树链剖分将树分成了若干条链[^chain]。最简单有效的剖分方式为*重链剖分*：对于某个结点，将连向最大子树的边称为重边，其余边称为轻边，每一条链都由重边组成（称为重链），而每两条链之间由轻边连接。这样可以保证任意一个结点到根结点的路径上经过的轻边数量为 $O(\log n)$，因此我们可以用数据结构维护每条重链，每次至多修改 $O(\log n)$ 次数据结构。

[^chain]: 如果没有特殊说明，链指一条包含至少一个点的且深度单调的简单路径，即*祖先后代链*。

##### 3. LCT

LCT 的核心思想也是**将树分成若干条链**，对于每一条链，我们都用 Splay 来进行维护。由于 LCT 解决的是动态树问题，所以链并不是一成不变的，而是需要不断地进行拼接，因此 Splay 是我们的不二之选。

##### 4. Splay

复习一下，为什么使用 Splay：虽然说 Splay 是一棵二叉搜索树，但是它不一定非要用作一棵二叉搜索树，而是可以看作一个支持均摊 $O(\log n)$ 进行分裂和合并的数组。

## 入门

##### 1. LCT 的形态

我们有一棵树：

<img src="pic\LCT 1.png" style="zoom:75%">

看上去它是一棵以 $1$ 为根的树，但是没有关系，在 LCT 中，**我们不管原树有根还是无根，我们只需要知道原树的根的编号就可以了**，换句话说，原树的根是哪个和 LCT 要做的事情无关。

那我们怎么维护原树呢？刚刚说了，我们将原树分成了一条条链，我们只需要维护每条链和链之间的关系就好了。对于每一条重链，我们用一棵 Splay 来维护；将 Splay 看作一个数组，我们保存的结点在原树中的深度和在 Splay 中的下标的增减性是一致的：

<img src="pic\LCT 2.png" style="zoom:75%">

<center>拆分成的三条链</center>

<img src="pic\LCT 3.png" style="zoom:75%">

<center>三条链对应的 Splay 可能的形态</center>

例如，上图中，结点 $1$，$2$，$3$ 构成一棵 Splay，中序遍历后的深度是递增的。注意，Splay 的形态可能和链在原树中的形态不一样（可能不再是链）。

------

那么 LCT 的链之间用什么维护呢？还记得树链剖分中的 $top$ 吗？我们称一条链中深度最小的点为这条链的 $top$。在 LCT 中，对于每棵 Splay，**我们从 Splay 的根结点（没错，Splay 的根结点）向与原树中这棵 Splay 对应重链的 $top$ 相邻[^neighbor]的结点连一条有向边（这个结点不在这条链上）**。

[^neighbor]: 到目前为止，你可以认为相邻的结点就是 $top$ 的父结点，但实际上 LCT 需要进行换根操作，原树是否有根无关紧要，所以说成相邻才是正确的。

<img src="pic\LCT 4.png" style="zoom:75%">

<center>LCT 的实际形态。上图中，双向边代表 Splay 的边，单向边代表连接 Splay 的边</center>

不难发现，如果将每一个 Splay 缩成一个点，那么各点之间的关系仍然是树形关系。我们称这棵 Splay 组成的树的根结点（注意它是棵 Splay）的中序遍历的第一个点为*对应连通块在 LCT 中的根结点 $root$*。再次强调，这个“LCT 中的根结点”和原树中的根结点没有一点关系，哪怕原树是棵无根树，还是有 LCT 中的根结点一说。当然，如果我们维护的是一个森林，那么森林中的每一个连通块在 LCT 中都会存在一个对应的根结点。

##### 2. 概念与操作

###### ①偏爱子结点/边/路径

根据上面的描述，LCT 实际上也是对原树进行了树链剖分。对于一个结点，我们称原树中与它在同一条链上的它的儿子（如果存在）为*偏爱子结点（preferred child）*；称连接一个结点和它的偏爱子结点的边为*偏爱边（preferred edge）*；称一条链为*偏爱路径（preferred path）*。

以上概念和轻重链剖分中的重儿子、重边和重链完全类似，且在 [LCT 的形态](#1.-lct-的形态)中说得很清楚了，所以我们立马可以得到以下结论：

1. 每个点在且仅在一条偏爱路径上。
2. 所有的偏爱路径包含了这棵树上所有的点。

（上面不是废话吗，[LCT 的形态](#1.-lct-的形态)中已经说得很清楚了）

###### ②访问操作：access

*访问（access）*操作是 LCT 的核心操作，也是体现 LCT “动态”的操作。

假设现在的 LCT 中只有一个连通块，且根是 $root$，我们定义 $\mathrm{access}(x)$ 为：令 $x$ 到 $root$ 的路径成为一条偏爱路径，且令 $x$ 的子结点和 $root$ 的其它子结点都不在这条偏爱路径上。 

<img src="pic\LCT 2.png" style="zoom:75%">

<center>假设的一开始的偏爱路径（原树为[前面的那棵树](#1.-lct-的形态)，忽略了非偏爱边）</center>

<img src="pic\LCT 5.png" style="zoom:75%">

<center>$\mathrm{access}(6)$ 后的偏爱路径（忽略了非偏爱边）</center>

然而实际上，我们是如何实现 access 操作的呢？

假设我们正在进行 $\mathrm{access}(x)$，我们通过旋转 $x$ 让 $x$ 成为 Splay 的根结点，这样，$x$ 的右子树便是它的重儿子了，将它断开，然后让它向 $x$ 连一条非偏爱边。

根据之前 LCT 的形态，我们是可以知道 $x$ 在原树中的父结点的（因为现在它是它所在的 Splay 的根，保存了它在原树中相邻的结点）。它的父结点对应的偏爱路径无非就样：

<img src="pic\LCT 6.png" style="zoom:75%">

<center>除了 $x$ 到 $3$ 的边不是偏爱边，其它边都是偏爱边</center>

我们找到 $3$ 结点，对它进行 Splay 操作[^splay]，那么 $3$ 的右子树就是 $3$ 之前的偏爱儿子了（$4$ 结点）。我们断开它，从 $4$ 向 $3$ 连一条非偏爱边，然后把 $x$ 接到 $3$ 的右子树上，就得到了新的 Splay。不断重复这个过程，直到对 $x$ 进行 Splay 操作后发现不存在一条从 $x$ 出发的非偏爱边。

[^splay]: 如无特殊说明，对某个点进行 Splay 操作表示将它旋转至它所在的 Splay 的根结点。

需要注意的是，在 access 途中要随时维护信息，不过现在还没有说到代码，所以就暂时不用管啦。另外，**$\mathrm{access}(x)$ 之后 $x$ 并不是对应 Splay 的根，如果需要，可以对 $x$ 进行 Splay 操作。**

###### ③置根操作：makeroot

前面的注释和 access 的介绍中也提到过，LCT 中的每一个连通块都有一个根结点，且需要支持换根操作。假设目前 LCT 的根为 $root$（再次强调是 LCT 的根，与原树的根无关，原树甚至没有根），我们想让 $x$ 成为新的根，那么我们首先 $\mathrm{access}(x)$。

在此操作后，我们发现只需要将 $x$ 所在的偏爱路径进行翻转就可以了。因为这样做之后， $x$ 所在偏爱路径各个结点的深度正好调换了顺序，**而其它偏爱路径各结点的相对深度并不发生改变**，因此我们利用 Splay 的翻转操作，将 $x$ 所在的整个偏爱路径翻转即可。

<img src="pic\LCT 7.png" style="zoom:75%">

<center>翻转 $x$ 所在偏爱路径后，其它偏爱路径的相对深度不改变</center>

为了方便，我们直接对 $x$ 进行 Splay 操作，**则 $x$ 成为了当前 Splay 的根**，我们对它打上翻转标记[^翻转标记]即可。

[^翻转标记]: 不知道什么东西？你可以出门右转先学一下 Splay，不过不保证你学的代码能用在接下来 LCT 的实现上。

###### ④link 操作 

顾名思义，link 操作将两个**不在同一连通块**的点连接起来。

假设这两个点为 $x$ 和 $y$，我们首先调用 $\mathrm{makeroot}(x)$，然后我们实际上令 $x$ 成为 $y$ 的子结点就好了。我们从 $x$ 向 $y$ 连一条非偏爱边即可。

###### ⑤cut 操作

顾名思义，cut 操作将两个**相邻结点**断开。

假设这两个点为 $x$ 和 $y$，我们首先调用 $\mathrm{makeroot}(x)$，然后我们再调用 $\mathrm{access}(y)$，然后实际上我们只需要把 $x$ 到 $y$ 的偏爱边断开就好了。我们对 $y$ 进行 Splay 操作，则 $x$ 一定为 $y$ 的左儿子。将这条边断开，维护 $y$ 的信息即可。

##### 3. e.g. [Luogu 2147 [SDOI 2008] 洞穴勘测](https://www.luogu.org/problemnew/show/P2147)

我们通过一道例题来引入具体实现和基本应用。

题目大意：有一个结点数为 $n$ 的森林，有 $m$ 次操作，操作分为三种：连接两个结点，删去一条边，查询两个点的连通性。保证操作合法，任意一次操作后森林还是森林。

------

这道题要我们做的是动态维护森林的连通性，支持加边删边，这正是 LCT 擅长的。

###### findroot 操作

findroot 操作允许我们找到某个结点所在连通块在 LCT 中的根结点。思路也很简单：直接 $\mathrm{access}(x)$，然后对 $x$ 进行 Splay 操作，然后沿着 Splay 结点的左儿子走，找到 Splay 中序遍历的第一个结点就好了。

那么这道题的做法就是：对于 Query 操作，我们调用 findroot，检查两点在 LCT 中的根结点是否一样（一样就说明在同一连通块，否则就说明在不同连通块）；对于 Connect 和 Destroy 操作，我们使用 link 和 cut 就好了。

##### 4. 实现[^template]

[^template]: LCT 的实现有很多，选择最适合自己的就好。如果你不会具体实现，又觉得我太弱或者代码太丑，请跳过这一部分。我的代码在访问元素时将以指针为主。

至此，我们已经完全可以口胡通过上面的例题了。但是怎么写？？？

###### ①Splay 结点

我们将 LCT 中的所有结点都定义为 Splay 结点：

```c++
typedef struct SplayNode
{
	bool flag; // reverse
	SplayNode* ch[2];
	SplayNode* parent;
	SplayNode() : flag() {}
	void pushdown()
	{
		if (flag)
		{
			std::swap(ch[0], ch[1]);
			ch[0]->flag ^= 1;
			ch[1]->flag ^= 1;
			flag = false;
		}
	}
} Node;
```

也就是说，LCT 中的 Splay 结点和普通的 Splay 结点没有太大差异，**~~只是~~多了一个 parent 指针**。但另外，可以发现 Splay 结点少了两个成员函数[^habit]：`maintain` 和 `comp`，前者用于维护一个结点对应子树的 size，后者用来判断应该选择左子树还是右子树。

[^habit]: 这只是我的习惯，如果你并不习惯在 Splay 结点中直接写成员函数也没关系，我只是想告诉你 LCT 的 Splay 结点**在不用维护别的数据的情况下**不需要引入 size。

###### ②parent 指针

Splay 结点的 parent 指针有什么用呢？

事实上，**我们在维护 LCT 时并不真正地连接非偏爱边，而是直接将 parent 指针当作保存非偏爱边的容器**。当一个点不是 Splay 的根结点时，parent 指针指向它在 Splay 中的父结点；当一个点是 Splay 的根结点时，parent 指针会被当作非偏爱边。如何判断 parent 指针是非偏爱边还是真正指向 Splay 中的父结点的指针呢？只需要判断这个点是不是 Splay 的根结点就好了：

```c++
int isRoot(Node* node)
{
	return node->parent->ch[0] != node && node->parent->ch[1] != node;
}
```

###### ③rotate 操作和 Splay 操作

由于我们并不知道要操作的结点在 Splay 的中序遍历中到底是第几个元素，所以我们不能像以前的 Splay 那样从上往下旋转，我们只能从当前结点不断往上旋转，直到当前结点为 Splay 的根。

首先考虑如何判断当前结点是它父结点的左儿子还是右儿子：

```c++
int trace(Node* node)
{
	return node->parent->ch[1] == node; // 左 0 右 1
}
```

然后我们考虑旋转。由于是自底向上的，所以我们定义 $\mathrm{rotate}(x)$ 为**将 $x$ 旋转至 $x$ 的父结点的位置**：

```c++
void rotate(Node* r) // 旋转至 r 的父结点的位置
{
	Node* father = r->parent; // 父结点
	Node* grand = father->parent; // 爷结点
	int d = trace(r);
	if (!isRoot(father)) grand->ch[grand->ch[1] == father] = r; // 爷结点的儿子变成了 r
	father->ch[d] = r->ch[d ^ 1];
	father->ch[d]->parent = father; // r 的子结点的 parent 发生了变化
	father->parent = r; // r 的父结点的 parent 发生了变化
	r->ch[d ^ 1] = father;
	r->parent = grand; // r 的父结点发生了变化
}
```

在此过程中，除了过去需要维护的东西，我们还需要维护一个结点的父结点。父结点发生改变的有 $3$ 个结点：被旋转的结点，它的某个子结点和它的父结点。

同理，我们定义 $\mathrm{Splay}(x)$ 表示**将 $x$ 旋转至它所在 Splay 的根结点**：

```c++
void pushdown(Node* r) // 下传根到 r 这条链上的标记
{
	if (isRoot(r)) return void(r->pushdown());
	pushdown(r->parent);
	r->pushdown();
}
void splay(Node* r) // 旋转 r 至根 
{
	pushdown(r);
	while (!isRoot(r)) // 从下往上旋转
	{
		Node* father = r->parent;
		// 如果是一字型，先旋转上面；如果是之字形，先旋转下面
		if (!isRoot(father)) rotate(trace(r) == trace(father) ? father : r); 
		rotate(r);
	}
}
```

如果需要将 Splay 对应序列反转（reverse），只需要调用：

```c++
void reverse(Node* r)
{
	r->flag ^= 1;
}
```

不过需要保证 `r` 为 Splay 的根结点，所以反转操作都需要紧跟在 splay 操作之后。

------

需要注意的是，上面的参数全部都是指针类型的（`Node*`)，而非指针的引用（`Node*&`）。为什么呢？我们在 LCT 中是这样保存结点的：

```c++
Node nodes[maxn];
```

也就是说，**结点之间的关系（`parent`，`ch` 指针）可能会变，但是结点本身是不会改变的**，换句话说，**变的是结点的内容，而结点的位置却没有改变**，所以不需要（也不能）传入引用。

###### ④access 操作

在知道了如何进行 Splay 相关的操作后，问题也就变得简单了：

```c++
void access(int code) // 之前的 node->ch[1] 的 parent 没变
{
	Node* pre = null;
	Node* node = nodes + code;
	while (node != null)
	{
		splay(node);
		node->ch[1] = pre;
		pre = node;
		node = node->parent;
	}
}
```

我们保存上一条链的指针 `pre`，一开始为 `null`。我们每次首先对当前结点进行 Splay 操作，然后让它的右子树从之前的变成 `pre`，相当于是接上了上一条链（我们是从下往上接的，上一条链指上次进行了操作的下面那条链，看代码吧），断开了之前的右子树。但是由于之前的右子树的 `parent` 并未改变（根据定义，非偏爱边从 Splay 的根结点指向 $top$ 的相邻结点的 Splay 结点），所以我们不用管它。最后令 `pre = node`，`node = node->parent`，往上跳即可。直到不能再往上跳（`node == null`），说明我们已经跳到了根结点的父结点（`null`），退出即可。

###### ⑤makeroot 和 findroot 操作

终于，我们写完了最底层的代码，所以下面的代码就不用解释了，参考[前面的描述](#③置根操作：makeroot)。

```c++
void makeroot(int code) // 指定结点成为对应连通块在 LCT 中的根
{
	Node* node = nodes + code;
	access(code);
	splay(node); // 注意这个点也是 Splay 的根
	reverse(node);
}
int findroot(int code) // 寻找某个结点对应连通块在 LCT 中的根
{
	Node* node = nodes + code;
	access(code);
	splay(node);
	while (node->ch[0] != null)
		node = node->ch[0];
	return splay(node), node - nodes; // note
}
```

需要注意要在最后对根结点进行 Splay 操作，以保证时间复杂度。

###### ⑥link 和 cut 操作

无需解释，参考[前面的描述](#④link-操作)。

```c++
void link(int x, int y)
{
	makeroot(x); // x 已是 Splay 的根结点
	(nodes + x)->parent = nodes + y;
}
void cut(int x, int y)
{
	Node* node = nodes + y;
	makeroot(x);
	access(y);
	splay(node);
	(nodes + x)->parent = node->ch[0] = null;
}
```

###### ⑦初始化

LCT 的初始形态是怎样的呢？如果一开始树没有边，我们让每个结点都单独成为一个连通块即可。为了安全，我们为 `null` 结点实际分配内存。

```c++
LinkCutTree()
{
	null = new Node;
	null->parent = null->ch[0] = null->ch[1] = null;
}
void init()
{
	for (int i = 1; i <= n; i++)
		nodes[i].ch[0] = nodes[i].ch[1] = nodes[i].parent = null;
}
```

完整代码见代码仓库。

##### 5. 时间复杂度

可以证明，使用 Splay 维护 LCT 的均摊时间复杂度是 $O(n \log n)$ 的。很明显的是，LCT 常数巨大。

具体的证明高深莫测，限于水平和偏重点，我就不证了~~，建议你也不要入坑去证~~。

## 进阶

##### e.g. [Luogu 3203 弹飞绵羊](https://www.luogu.org/problemnew/show/P3203)

分块经典题目，同时也是 LCT 经典题目。

------

对于每一个位置，我们将它看作一个结点，另外我们虚拟一个 $n + 1$ 号结点，表示一条就跳出去的情况。由于每一个点只能跳到唯一的位置，因此我们可以建成一棵树。这样，询问就等价于问每一个点到根结点的距离。

如何使用 LCT 来搞呢？如果我们额外维护子树大小，我们就可以知道有多少个结点的中序遍历在当前结点的前面，也就可以做了。

###### ①维护 size

这道题需要维护子树大小，虽然子树大小不是 LCT 的必需品，但是它是做题的必需品。下面是新的结点定义：

```c++
struct Node
{
	int size;
	bool flag;
	Node* parent;
	Node* ch[2];
	Node() : size() {}
	void pushdown()
	{
		if (flag)
		{
			ch[0]->flag ^= 1;
			ch[1]->flag ^= 1;
			std::swap(ch[0], ch[1]);
			flag = false;
		}
	}
	void maintain()
	{
		size = ch[0]->size + ch[1]->size + 1;
	}
	void reverse()
	{
		flag ^= 1;
	}
};
```

（把 reverse 写进 `Node` 中与写外面没有区别）

最主要需要维护 size 的地方是 rotate 操作：

```c++
void rotate(Node* r)
{
	Node* father = r->parent;
	Node* grand = father->parent;
	int d = trace(r);
	if (!isRoot(father)) grand->ch[trace(father)] = r;
	r->parent = grand;
	father->ch[d] = r->ch[d ^ 1];
	r->ch[d ^ 1]->parent = father;
	father->maintain();
	r->ch[d ^ 1] = father;
	father->parent = r;
	r->maintain();
}
```

其它地方，仅当需要连接或者删去 Splay 中的边时，才需要维护 size。**由于 link 操作连接的是非偏爱边，所以不需要维护 size；**access 和 cut 操作需要断开或者连上 Splay 中的边，所以也需要维护 size：

```c++
void access(int code)
{
	Node* pre = null;
	Node* node = nodes + code;
	while (node != null)
	{
		splay(node);
		node->ch[1] = pre;
		node->maintain();
		pre = node;
		node = node->parent;
	}
}
void cut(int x, int y)
{
	Node* node = nodes + y;
	makeroot(x);
	access(y);
	splay(node);
	(nodes + x)->parent = node->ch[0] = null;
	node->maintain();
}
```

###### ②获取结点在原树中的深度

首先需要对原树的根结点进行 makeroot 操作，然后对需要计算的结点进行 access 和 splay 操作，这样它的左子树大小就是深度比自己浅的结点个数，正是本题需要求的东西。

```c++
int depth(int x)
{
	makeroot(n);
	access(x);
	splay(nodes + x);
	return (nodes + x)->ch[0]->size;
}
```

##### e.g. [Luogu 3690 [模板] Link-Cut Tree](https://www.luogu.org/problemnew/show/P3690)

题目大意：给你一个森林，要你维护森林连通性，不保证删边或者加边操作合法。森林中的点有点权，有查询路径上点权异或和的询问，还要求支持单点修改点权。

------

首先我们解决 link 操作不合法的问题，很简单，只需要用 findroot 判断是否在同一连通块就好了。

```c++
void link(int x, int y)
{
	makeroot(x);
	if (findroot(y) == x) return;
	(nodes + x)->parent = nodes + y;
}
```

###### ①解决 cut 的合法性问题

**cut 操作合法的先决条件是待操作结点要相邻。**我们首先 $\mathrm{makeroot}(x)$，然后检查 $\mathrm{findroot}(y)$ 是否为 $x$，如果不是，显然它们不在同一连通块。否则我们 $\mathrm{Splay}(y)$（注意在 findroot 中已经 $\mathrm{access}(y)$ 了），然后检查 $x$ 和 $y$ 的中序遍历之间是否有别的结点，只需要看 $y$ 的左子树大小是否为 $1$ 即可。如果不需要维护大小呢？那就检查两个地方：一看 $y$ 的左儿子是不是 $x$，二看 $x$ 是不是没有右儿子。检查之后我们才能 cut。

```c++
void cut(int x, int y)
{
	makeroot(x);
	if (findroot(y) != x) return;
	Node* node = nodes + y;
	splay(node);
	if (node->ch[0] != nodes + x || (nodes + x)->ch[1] != null) return; // note
	(nodes + x)->parent = node->ch[0] = null; // note
	node->maintain();
}
```

注意别写错了。

###### ②维护异或和

事实上，**我们只需要维护 Splay 中对应子树的异或和就行了，而且只需要沿用[之前那道题](#①维护-size)的做法，改一下 maintain 函数就好了**。

```c++
void maintain()
{
	sum = weight ^ ch[0]->sum ^ ch[1]->sum;
}
```

就是说，调用 maintain 函数的时机是一样的，只是 maintain 函数的内容变了。**这启示我们，LCT 可以很方便地维护点上的信息**。

相比之下，修改点权和查询点权异或和就很简单了，随便写写都能过。记住在 Splay 发生改变时进行 maintain 操作。

```c++
void change(int pos, int val)
{
	access(pos);
	Node* node = nodes + pos;
	splay(node);
	node->weight = val;
	node->maintain();
}
int query(int x, int y)
{
	makeroot(x);
	access(y);
	Node* node = nodes + y;
	splay(node);
	return node->sum;
}
```
##### e.g. [Luogu 2387 [NOI 2014] 魔法森林](https://www.luogu.org/problemnew/show/P2387)

题目大意：给定一张 $n$ 个点 $m$ 条边的图，每条边有两个边权 $a$ 和 $b$。找一条 $1$ 到 $n$ 的路径使得 $\max\{ a \} + \max \{ b \}$ 最小，如果不存在输出 $-1$。

------

很容易往最小生成树上面去想，然后考虑一个套路做法。我们枚举 $a$ 的最大权值，然后看对于每个 $a$ 答案是多少。具体地说，我们可以把边按照 $a$ 从小到大排序，依次加入图中，每次再看看 $1$ 到 $n$ 的最优答案。

如何看呢？我们直接令 $a$ 为当前的最大边权，然后找一条从 $1$ 到 $n$ 的路径使得路径上最大的 $b$ 最小就好了。利用非法解不会最优的思想，我们可以用 SPFA 在 $O(n m^2)$ 的时间复杂度内解决这个问题。然后恭喜 TLE。（我不会打大优化，所以就不讨论如何优化这个算法了）

------

我们考虑使用 LCT 来维护这个东西。

###### ①边权转点权

一个不可否认的事实是，**LCT 真的没有办法维护边上的信息，所以我们要想个办法把边上的信息换到点上**。

由于树有 $n$ 个点，$n - 1$ 条边，所以我们自然会想到把边的信息放到儿子结点上，但是这在 LCT 中是行不通的，**因为 LCT 本身可以换根，一条边连接的两个点的父子关系会发生变化**。

正确的做法是**为每一条边都虚拟一个结点，点权为原边权，而原点权为 $0$**。加边时，我们从原来的两个端点分别向边对应的端点连边即可。

###### ②维护最小生成树

事实上，原问题已经被转换成了一个动态维护最小生成树的问题：只不过原始的动态维护最小生成树需要首先求一次 MST，但这道题是从零开始维护的。

如何维护 MST 呢？稍微有点经验的人都知道，加入一条边时，如果两点不在同一连通块，那么直接连上就行；如果两点在同一连通块，那么一定会形成一个环。我们删去环上的最大边即可。

如何使用 LCT 来维护呢？对于每个 Splay 结点，我们保存它所在子树的最大边权以及相应的编号即可。

```c++
struct Node
{
	Node* parent;
	Node* ch[2];
	bool flag;
	int weight;
	int max;
	int idx;
	int maxIdx;
	void pushdown()
	{
		if (flag)
		{
			std::swap(ch[0], ch[1]);
			ch[0]->flag ^= 1;
			ch[1]->flag ^= 1;
			flag = false;
		}
	}
	void maintain()
	{
		if (weight >= std::max(ch[0]->max, ch[1]->max))
		{
			max = weight;
			maxIdx = idx;
		}
		else if (ch[0]->max > ch[1]->max)
		{
			max = ch[0]->max;
			maxIdx = ch[0]->maxIdx;
		}
		else
		{
			max = ch[1]->max;
			maxIdx = ch[1]->maxIdx;
		}
	}
	void reverse() { flag ^= 1; }
};
```

maintain 操作的执行时机和之前完全一样。剩下查询信息的代码就很简单了，善用 makeroot，access 和 splay 即可。详见代码仓库。

------

最小生成树加边：

```c++
if (e.from == e.to) continue; // note
if (tree.findroot(e.from) != tree.findroot(e.to))
{
	tree.link(e.from, n + i);
	tree.link(e.to, n + i);
}
else
{
	int code = tree.qMax(e.from, e.to) - n;
	if (edges[code].b <= e.b) continue;
	tree.cut(code + n, edges[code].from);
	tree.cut(code + n, edges[code].to);
	tree.link(n + i, e.from);
	tree.link(n + i, e.to);
}
```

##### e.g. [Luogu 4219 [BJOI 2014] 大融合](https://www.luogu.org/problemnew/show/P4219)

题目大意：有 $n$ 个点，一开始没有边。有 $m$ 个操作，操作分两种：增加一条边 $(u, v)$；询问经过某一条边 $(u, v)$ 的简单路径数量。保证询问合法，保证原图始终是一个森林。

------

对于第一个操作，我们使用 LCT 进行维护。对于第二个操作，我们先转换一下，把问题变成“断开 $(u, v)$ 后 $u$ 的子树大小乘以 $v$ 的子树大小”，则我们的首要任务为维护子树大小。

###### ①附加点权

一开始就说了，LCT 对于操作子树的问题本身不是特别擅长，那么这道题怎么做呢？

之前，对于一个点，我们设它的点权为 $1$，则 LCT 根结点的 size 表示的是某一条链的结点数。

<img src="pic\LCT 8.png" style="zoom:75%">

<center>$1$ 为根结点，加粗的结点为根结点所在链</center>

如上图，若将每个点的权值设为 $1$，则 $size_1 = 4$。

如何让 $size_1 = 8$，即让 $size$ 代表子树大小呢？上图中，如果 $weight_4 = 2$，$weight_3 = 3$，$weight_2 = 1$，$weight_1 = 2$，那么 $size_1 = 8$。不难发现，以上权重代表的是**非偏爱边**所连接的**子树大小**之和加 $1$。只要我们能够维护每个点在这个意义下的权值，那么我们的问题就迎刃而解了。

###### ②虚实变幻

回忆一下几个关键操作：

1. access：会将一些偏爱边变成非偏爱边，以及将一些非偏爱边变成偏爱边。
2. link：会连接一条非偏爱边。
3. cut：会断开一条偏爱边。

以上操作中，只有 access 操作和 link 操作会改变非偏爱边的情况，我们称这种操作为*虚实变换*，**我们只在虚实变幻时修改点权**，也就是说在 cut 时我们不需要改变点权。

下面给出了维护附加点权的方法：

```c++
void init()
{
	for (int i = 1; i <= n; i++)
	{
		Node* t = nodes + i;
		t->parent = t->ch[0] = t->ch[1] = null;
		t->size = t->virt = 1; // note
	}
}
```

```c++
void access(int code)
{
	Node* node = nodes + code;
	Node* pre = null;
	while (node != null)
	{
		splay(node);
		node->virt += node->ch[1]->size; // note
		node->ch[1] = pre;
		node->virt -= node->ch[1]->size; // note
		node->maintain();
		pre = node;
		node = node->parent;
	}
}
```

```c++
void link(int x, int y)
{
	makeroot(x);
	Node* X = nodes + x;
	Node* Y = nodes + y;
	X->parent = Y;
	makeroot(y);
	Y->virt += X->size; // note
	Y->maintain();
}
```

现在 LCT 的根结点的 $size$ 的含义就不再是某条链对应的结点数了，而是某棵子树对应的结点数。下面的代码用于查询这道题所需要的答案，它能让你更深刻地理解改变点权后我们的 $size$ 到底维护的是什么。

```c++
LL query(int x, int y)
{
	Node* X = nodes + x;
	Node* Y = nodes + y;
	makeroot(x);
	access(y);
	splay(X);
	LL a = Y->size;

	makeroot(y);
	access(x);
	splay(Y);
	LL b = X->size;
	return a * b;
}
```

##### [mincost]()

###### 题目大意

给定一张 $n$ 个点 $m$ 条边的无向图，点编号 $1$ 到 $n$，每个点 $x$ 有两个权值 $a_x$ 和 $b_x$，给定一个值 $k$，求在图中选出大小为 $k$ 的点集 $S$，使得 $S$ 中任意两个点之间存在仅经过在 $S$ 中的点的路径。$S$ 集合也有两个权值 $A_S$ 和 $B_S$，$A_S$ 的值为 $S$ 中所有点的 $a$ 权值最大值，$B_S$ 的值为 $S$ 中所有点的 $b$ 权值最大值，求一个合法的 $S$ 使得 $A_S + B_S$ 最小，并输出这个最小值。

$n \le 3 \times 10^5$，有部分分 $n, m \le 5 \times 10^3$；有部分分保证图是一棵树。

------

如果你记得前面的例题[魔法森林](#e.g.-[luogu-2387-[noi-2014]-魔法森林](https://www.luogu.org/problemnew/show/p2387))，那么这个题的基本思路就不难想到。我们枚举 $a$ 和 $b$，仅保留 $a_i < a$ 且 $b_i < b$ 的点 $i$，然后检查是否存在大小至少为 $k$ 的连通块即可。

###### ①对于小数据

我们先枚举 $a$，然后可以从小到大枚举 $b$，逐个**加入点**，用并查集维护连通块大小。

相反地，我们可以枚举 $a$ 后从大到小枚举 $b$，逐个**删除点**，只是好像没有简单的数据结构能够做到。

虽然前者能够帮助我们得到部分分，但是它的时间复杂度下界是 $O(n^2)$ 的（枚举 $a$ 和 $b$）。稍微分析下，就能发现后者有个优势：若某个时刻有 $a_x$ 和 $b_y$ 能够形成大小至少为 $k$ 的连通块，当枚举的 $a$ 变大时，使得存在大小至少为 $k$ 的连通块的 $b$ 一定小于等于 $b_y$。这启发我们可以使用双指针扫描，时间复杂度下界是 $O(n)$ 的（不考虑维护）。

###### ②对于一棵树的情况

我们可以用 LCT 来维护这棵树。当 $a$ 增大时，我们连边，且只向点权同时小于等于枚举的 $a$ 和 $b$ 的点连边。若此时存在大小至少为 $k$ 的连通块，我们更新一下答案，并减小 $b$，在图中删除点权大于 $b$ 的点（以及以它为端点的边）。则问题转换为使用 LCT 求子树（连通块）大小，使用上例“虚实变幻”的方法即可。

###### ③对于 100% 的数据

现在问题转换为了：支持加边和删边操作，维护图的连通块大小。如果强制在线，这个问题似乎不是那么容易（我不会），但在这道题中这个问题显然是离线的，这可以使用 LCT 来维护。

###### 使用 LCT 维护图的连通性（需要离线）

当我们加入一条边时，我们首先检查两个端点是否在同一连通块中，如果不是，直接 link 即可。如果是，那么肯定会有一条起点和终点分别为这两个端点的路径，加上新的边后形成一个环。

我们看这条路径上的边以及这条新加入的边谁最先被删除，如果新加入的边先被删除，我们无需做任何操作，否则我们删掉最先被删除的那条边，再加入新的边。由于需要维护边上的信息（删除时间的最小值），因此我们需要将边变成点以 LCT 中进行维护（见[前面的例题](#①边权转点权)）。

删除时，我们只删除存在的边，不存在的边我们不用管。

------

对于这道题，可以发现，一条边被删除的时间取决于两个端点的 $b$ 的最大值，所以我们令一条边的边权为它的两个端点的 $b$ 的较大值，如果需要删除环上的边，我们就删除边权最大的边即可。这样，问题就解决了。