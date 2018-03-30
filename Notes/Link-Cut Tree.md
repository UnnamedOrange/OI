[TOC]

> 开局一个 Markdown，内容全靠编。——Orange

# Link-Cut Tree

[参考资料](https://www.cnblogs.com/BLADEVIL/p/3510997.html)

[参考资料](https://www.cnblogs.com/candy99/p/6271344.html)

&emsp;&emsp;不保证能看懂，但保证讲清楚所有细节。

## 总览

##### 1. 动态树问题

&emsp;&emsp;动态树问题是一类要求维护森林的连通性的题的总称。这类问题要求：

1. 维护某个点到根的某些数据。
2. 对树进行切分。
3. 对树进行合并。
4. 操作子树。
5. ……

&emsp;&emsp;解决这一问题的的子问题（**不包括操作子树**）的基础数据结构就是 *Link-Cut Tree（LCT）*。

##### 2. 树链剖分

&emsp;&emsp;静态的树链剖分将树分成了若干条链[^链]。最简单有效的剖分方式为*重链剖分*：对于某个结点，将连向最大子树的边称为重边，其余边称为轻边，每一条链都由重边组成（称为重链），而每两条链之间由轻边连接。这样可以保证任意一个结点到根结点的路径上经过的轻边数量为 $O(\log n)$，因此我们可以用数据结构维护每条重链，每次至多修改 $O(\log n)$ 次数据结构。

[^链]: 如果没有特殊说明，链指一条包含至少一个点的且深度单调的简单路径，即*祖先后代链*。

##### 3. LCT

&emsp;&emsp;LCT 的核心思想也是**将树分成若干条链**，对于每一条链，我们都用 Splay 来进行维护。由于 LCT 解决的是动态树问题，所以链并不是一成不变的，而是需要不断地进行拼接，因此 Splay 是我们的不二之选。

##### 4. Splay

&emsp;&emsp;复习一下，为什么使用 Splay：虽然说 Splay 是一棵二叉搜索树，但是它不一定非要用作一棵二叉搜索树，而是可以看作一个支持均摊 $O(\log n)$ 进行分裂和合并的数组。

## 入门

##### 1. LCT 的形态

&emsp;&emsp;我们有一棵树：

![](pic\LCT 1.png)

&emsp;&emsp;看上去它是一棵以 $1$ 为根的树，但是没有关系，在 LCT 中，**我们不管原树有根还是无根，我们只需要知道原树的根的编号就可以了**，换句话说，原树的根是哪个和 LCT 要做的事情无关。

&emsp;&emsp;那我们怎么维护原树呢？刚刚说了，我们将原树分成了一条条链，我们只需要维护每条链和链之间的关系就好了。对于每一条重链，我们用一棵 Splay 来维护；将 Splay 看作一个数组，我们保存的结点在原树中的深度和在 Splay 中的下标的增减性是一致的：

![](pic\LCT 2.png)

<center>

拆分成的三条链

</center>

![](pic\LCT 3.png)

<center>

三条链对应的 Splay 可能的形态

</center>

&emsp;&emsp;例如，上图中，结点 $1$，$2$，$3$ 构成一棵 Splay，中序遍历后的深度是递增的。注意，Splay 的形态可能和链在原树中的形态不一样（可能不再是链）。

------

&emsp;&emsp;那么 LCT 的链之间用什么维护呢？还记得树链剖分中的 $top$ 吗？我们称一条链中深度最小的点为这条链的 $top$。在 LCT 中，对于每棵 Splay，**我们从 Splay 的根结点（没错，Splay 的根结点）向与原树中这棵 Splay 对应重链的 $top$ 相邻[^相邻]的结点连一条有向边（这个结点不在这条链上）**。

[^相邻]: 到目前为止，你可以认为相邻的结点就是 $top$ 的父结点，但实际上 LCT 需要进行换根操作，原树是否有根无关紧要，所以说成相邻才是正确的。

![](pic\LCT 4.png)

<center>

LCT 的实际形态。上图中，双向边代表 Splay 的边，单向边代表连接 Splay 的边。

</center>

&emsp;&emsp;不难发现，如果将每一个 Splay 缩成一个点，那么各点之间的关系仍然是树形关系。我们称这棵 Splay 组成的树的根结点（注意它是棵 Splay）的中序遍历的第一个点为*对应连通块在 LCT 中的根结点 $root$*。再次强调，这个“LCT 中的根结点”和原树中的根结点没有一点关系，哪怕原树是棵无根树，还是有 LCT 中的根结点一说。当然，如果我们维护的是一个森林，那么森林中的每一个连通块在 LCT 中都会存在一个对应的根结点。

##### 2. 概念与操作

###### ①偏爱子结点/边/路径

&emsp;&emsp;根据上面的描述，LCT 实际上也是对原树进行了树链剖分。对于一个结点，我们称原树中与它在同一条链上的它的儿子（如果存在）为*偏爱子结点（preferred child）*；称连接一个结点和它的偏爱子结点的边为*偏爱边（preferred edge）*；称一条链为*偏爱路径（preferred path）*。

&emsp;&emsp;以上概念和轻重链剖分中的重儿子、重边和重链完全类似，且在 [LCT 的形态](#1.-lct-的形态)中说得很清楚了，所以我们立马可以得到以下结论：

1. 每个点在且仅在一条偏爱路径上。
2. 所有的偏爱路径包含了这棵树上所有的点。

（上面不是废话吗，[LCT 的形态](#1.-lct-的形态)中已经说得很清楚了）

###### ②访问操作：access

&emsp;&emsp;*访问（access）*操作是 LCT 的核心操作，也是体现 LCT “动态”的操作。

&emsp;&emsp;假设现在的 LCT 中只有一个连通块，且根是 $root$，我们定义 $\mathrm{access}(x)$ 为：令 $x$ 到 $root$ 的路径成为一条偏爱路径，且令 $x$ 的子结点和 $root$ 的其它子结点都不在这条偏爱路径上。 

![](pic\LCT 2.png)

<center>

假设的一开始的偏爱路径（原树为[前面的那棵树](#1.-lct-的形态)，忽略了非偏爱边）

</center>

![](pic\LCT 5.png)

<center>

$\mathrm{access}(6)$ 后的偏爱路径（忽略了非偏爱边）

</center>

&emsp;&emsp;然而实际上，我们是如何实现 access 操作的呢？

&emsp;&emsp;假设我们正在进行 $\mathrm{access}(x)$，我们通过旋转 $x$ 让 $x$ 成为 Splay 的根结点，这样，$x$ 的右子树便是它的重儿子了，将它断开，然后让它向 $x$ 连一条非偏爱边。

&emsp;&emsp;根据之前 LCT 的形态，我们是可以知道 $x$ 在原树中的父结点的（因为现在它是它所在的 Splay 的根，保存了它在原树中相邻的结点）。它的父结点对应的偏爱路径无非就样：

![](pic\LCT 6.png)

<center>

除了 $x$ 到 $3$ 的边不是偏爱边，其它边都是偏爱边

</center>

&emsp;&emsp;我们找到 $3$ 结点，对它进行 Splay 操作[^splay]，那么 $3$ 的右子树就是 $3$ 之前的偏爱儿子了（$4$ 结点）。我们断开它，从 $4$ 向 $3$ 连一条非偏爱边，然后把 $x$ 接到 $3$ 的右子树上，就得到了新的 Splay。不断重复这个过程，直到对 $x$ 进行 Splay 操作后发现不存在一条从 $x$ 出发的非偏爱边。

[^splay]: 如无特殊说明，对某个点进行 Splay 操作表示将它旋转至它所在的 Splay 的根结点。

&emsp;&emsp;需要注意的是，在 access 途中要随时维护信息，不过现在还没有说到代码，所以就暂时不用管啦。另外，**$\mathrm{access}(x)$ 之后 $x$ 并不是对应 Splay 的根，如果需要，可以对 $x$ 进行 Splay 操作。**

###### ③置根操作：makeroot

&emsp;&emsp;前面的注释和 access 的介绍中也提到过，LCT 中的每一个连通块都有一个根结点，且需要支持换根操作。假设目前 LCT 的根为 $root$（再次强调是 LCT 的根，与原树的根无关，原树甚至没有根），我们想让 $x$ 成为新的根，那么我们首先 $\mathrm{access}(x)$。

&emsp;&emsp;在此操作后，我们发现只需要将 $x$ 所在的偏爱路径进行翻转就可以了。因为这样做之后， $x$ 所在偏爱路径各个结点的深度正好调换了顺序，**而其它偏爱路径各结点的相对深度并不发生改变**，因此我们利用 Splay 的翻转操作，将 $x$ 所在的整个偏爱路径翻转即可。

![](pic\LCT 7.png)

<center>

翻转 $x$ 所在偏爱路径后，其它偏爱路径的相对深度不改变

</center>

&emsp;&emsp;为了方便，我们直接对 $x$ 进行 Splay 操作，**则 $x$ 成为了当前 Splay 的根**，我们对它打上翻转标记[^翻转标记]即可。

[^翻转标记]: 不知道什么东西？你可以出门右转先学一下 Splay，不过不保证你学的代码能用在接下来 LCT 的实现上。

###### ④link 操作 

&emsp;&emsp;顾名思义，link 操作将两个**不在同一连通块**的点连接起来。

&emsp;&emsp;假设这两个点为 $x$ 和 $y$，我们首先调用 $\mathrm{makeroot}(x)$，然后我们实际上令 $x$ 成为 $y$ 的子结点就好了。我们从 $x$ 向 $y$ 连一条非偏爱边即可。[^实际]

[^实际]: 实际上还需要做一些别的操作，以方便维护信息，这将在后面提到。

###### ⑤cut 操作

&emsp;&emsp;顾名思义，cut 操作将两个**相邻结点**断开。

&emsp;&emsp;假设这两个点为 $x$ 和 $y$，我们首先调用 $\mathrm{makeroot}(x)$，然后我们再调用 $\mathrm{access}(y)$，然后实际上我们只需要把 $x$ 到 $y$ 的偏爱边断开就好了。我们对 $y$ 进行 Splay 操作，则 $x$ 一定为 $y$ 的左儿子。将这条边断开，维护 $y$ 的信息即可。

##### 3. e.g. [Luogu 2147 [SDOI 2008] 洞穴勘测](https://www.luogu.org/problemnew/show/P2147)

&emsp;&emsp;我们通过一道例题来引入具体实现和基本应用。

题目大意：有一个结点数为 $n$ 的森林，有 $m$ 次操作，操作分为三种：连接两个结点，删去两条边，查询两个点的连通性。保证操作合法，任意一次操作后森林还是森林。

------

&emsp;&emsp;这道题要我们做的是动态维护森林的连通性，支持加边删边，这正是 LCT 擅长的。

###### findroot 操作

&emsp;&emsp;findroot 操作允许我们找到某个结点所在连通块在 LCT 中的根结点。思路也很简单：直接 $\mathrm{access}(x)$，然后对 $x$ 进行 Splay 操作，然后沿着 Splay 结点的左儿子走，找到 Splay 中序遍历的第一个结点就好了。

&emsp;&emsp;那么这道题的做法就是：对于 Query 操作，我们调用 findroot，检查两点在 LCT 中的根结点是否一样（一样就说明在同一连通块，否则就说明在不同连通块）；对于 Connect 和 Destroy 操作，我们使用 link 和 cut 就好了。

##### 4. 实现

&emsp;&emsp;至此，我们已经完全可以口胡通过上面的例题了。但是怎么写？？？

###### ①Splay 结点

&emsp;&emsp;我们将 LCT 中的所有结点都定义为 Splay 结点：

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

&emsp;&emsp;也就是说，LCT 中的 Splay 结点和普通的 Splay 结点没有太大差异，**~~只是~~多了一个 parent 指针**。但另外，可以发现 Splay 结点少了两个成员函数[^习惯]：`maintain` 和 `comp`，前者用于维护一个结点对应子树的 size，后者用来判断应该选择左子树还是右子树。

[^习惯]: 这只是我的习惯，如果你并不习惯在 Splay 结点中直接写成员函数也没关系，我只是想告诉你 LCT 的 Splay 结点不需要引入 size，**因为我们都是从下至上操作**。

###### ②parent 指针

&emsp;&emsp;Splay 结点的 parent 指针有什么用呢？[^模板]

[^模板]: 因为 LCT 的实现有很多，选择最适合自己的就好。如果你不会具体实现，又觉得我太弱代码太丑，请跳过实现这一部分。我的代码将会大量使用指针。

&emsp;&emsp;事实上，**我们在维护 LCT 时并不真正的连接非偏爱边，而是直接将 parent 指针当作保存非偏爱边的容器**。当一个点不是 Splay 的根结点时，parent 指针指向它在 Splay 中的父结点；当一个点是 Splay 的根结点时，parent 指针会被当作非偏爱边。如何判断 parent 指针是非偏爱边还是真正指向 Splay 中的父结点的指针呢？只需要判断这个点是不是 Splay 的根结点就好了：

```c++
int isRoot(Node* node)
{
	return node->parent->ch[0] != node && node->parent->ch[1] != node;
}
```

###### ③rotate 操作和 Splay 操作

&emsp;&emsp;由于我们并不知道要操作的结点在 Splay 的中序遍历中到底是第几个元素，所以我们不能像以前的 Splay 那样从上往下旋转，我们只能从当前结点不断往上旋转，直到当前结点为 Splay 的根。

&emsp;&emsp;首先考虑如何判断当前结点是它父结点的左儿子还是右儿子：

```c++
int trace(Node* node)
{
	return node->parent->ch[1] == node; // 左 0 右 1
}
```

&emsp;&emsp;然后我们考虑旋转。由于是自底向上的，所以我们定义 $\mathrm{rotate}(x)$ 为**将 $x$ 旋转至 $x$ 的父结点的位置**：

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

&emsp;&emsp;在此过程中，除了过去需要维护的东西，我们还需要维护一个结点的父结点。父结点发生改变的有 $3$ 个结点：被旋转的结点，它的某个子结点和它的父结点。

&emsp;&emsp;同理，我们定义 $\mathrm{Splay}(x)$ 表示**将 $x$ 旋转至它所在 Splay 的根结点**：

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

&emsp;&emsp;如果需要将 Splay 对应序列反转（reverse），只需要调用：

```c++
void reverse(Node* r)
{
	r->flag ^= 1;
}
```

&emsp;&emsp;不过需要保证 `r` 为 Splay 的根结点，所以反转操作都需要紧跟在 splay 操作之后。

------

&emsp;&emsp;需要注意的是，上面的参数全部都是指针类型的（`Node*`)，而非指针的引用（`Node*&`）。为什么呢？我们在 LCT 中是这样保存结点的：

```c++
Node nodes[maxn];
```

&emsp;&emsp;也就是说，**结点之间的关系（`parent`，`ch` 指针）可能会变，但是结点本身是不会改变的**，换句话说，**变的是结点的内容，而结点的位置却没有改变**，所以不需要（也不能）传入引用。

###### ④access 操作

&emsp;&emsp;在知道了如何进行 Splay 相关的操作后，问题也就变得简单了：

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

&emsp;&emsp;我们保存上一条链的指针 `pre`，一开始为 `null`。我们每次首先对当前结点进行 Splay 操作，然后让它的右子树从之前的变成 `pre`，相当于是接上了上一条链（我们是从下往上接的，上一条链指上次进行了操作的下面那条链，看代码吧），断开了之前的右子树。但是由于之前的右子树的 `parent` 并未改变（根据定义，非偏爱边从 Splay 的根结点指向 $top$ 的相邻结点的 Splay 结点），所以我们不用管它。最后令 `pre = node`，`node = node->parent`，往上跳即可。直到不能再往上跳（`node == null`），说明我们已经跳到了根结点的父结点（`null`），退出即可。

###### ⑤makeroot 和 findroot 操作

&emsp;&emsp;终于，我们写完了最底层的代码，所以下面的代码就不用解释了，参考[前面的描述](#③置根操作：makeroot)。

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
	return node - nodes;
}
```

###### ⑥link 和 cut 操作

&emsp;&emsp;无需解释，参考[前面的描述](#④link-操作)。

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

&emsp;&emsp;LCT 的初始形态是怎样的呢？如果一开始树没有边，我们让每个结点都单独成为一个连通块即可。为了安全，我们为 `null` 结点实际分配内存。

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

&emsp;&emsp;完整代码见代码仓库。

##### 5. 时间复杂度

&emsp;&emsp;可以证明，使用 Splay 维护 LCT 的均摊时间复杂度是 $O(n \log n)$ 的。很明显的是，LCT 常数巨大。

&emsp;&emsp;具体的证明高深莫测，限于水平和偏重点，我就不证了~~，建议你也不要入坑去证~~。