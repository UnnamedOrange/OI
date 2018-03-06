[TOC]

# Aho-Corasick Automation

（粗体为重点内容）

## AC 自动机

##### 1. 问题定义

&emsp;&emsp;给定一个模板串集合，要求在一个字符串中找到所有模板的位置。这个问题又叫做多模式匹配问题。

##### 2. AC 自动机

&emsp;&emsp;AC 自动机由一个 Trie 和一个失配边集合组成。

&emsp;&emsp;由于 AC 自动机的底层是一个 Trie，那么它自然有一个 Trie 结点。

```c++
struct Node
{
 	Node* c[alpha_size];
 	Node* fail;
 	Node* suffix;
 	INT count;
};
```

&emsp;&emsp;可以看出，AC 自动机的结点在 Trie 的基础上多出了个 fail 指针，还多了个 suffix 指针。它们到底怎么用呢？我们一会儿来讲解。

###### ①Trie 的结构

&emsp;&emsp;我们一般认为，Trie 是一棵结点上没有字符，而在边上有字符的树。AC 自动机也类似，根结点是一个虚拟的结点，但是可以认为字符存在在其它结点上，**这样有助于理解“状态”一词。**实际上，AC 自动机的结点中不保存字符，我们仍然把字符“存”在边上。

![Trie](pic\AC 自动机 1.png)

&emsp;&emsp;回忆 KMP 算法，在某个地方失配后我们要让模板串往前移，通过记录一个失配函数来实现这个功能。事实上 KMP 的失配函数是一个状态机，由于它很简单，所以可以用一个 f 数组来实现。AC 自动机是一棵树，所以必须要用指针，**但是它的功能和 KMP 的失配函数是完全一样的，**其物理含义也是一样的：指向最长的与后缀相同的前缀的尾部。

&emsp;&emsp;与 KMP 算法类似，AC 自动机也是边走边匹配，但是有这么一个区别：若找到了一个串，同时也就说明了找到了这个串的后缀；**如果一个模板是另一个模板的后缀，说不定会出现同时找到两个串或更多串的情况。**一个最简单的想法是沿着失配边走，直到走到根结点，但是**当模板串只由一种字符组成时，时间复杂度就悲剧了：失配边边数与模板串长度同阶。**所以我们需要一个更优秀的东西，它就是 suffix 指针，中文名叫做后缀链接。它的作用就是在**每一个**状态处（并不一定非要是匹配的一个状态）往回走，保证只会走到匹配点或者根结点。这样时间复杂度就得到了保证。

###### ②构建 AC 自动机

&emsp;&emsp;工欲善其事，必先利其器。建立 AC 自动机前，你要先建好 Trie 树。**这就意味着你不能边插入模板串边维护 AC 自动机，只能把模板串插入完后再一次建成。**

&emsp;&emsp;步骤（1）：用 AC 自动机的结点，建立一棵一般的 Trie 树。

&emsp;&emsp;受题目影响，**可能会有相同的模板串。**这时要根据题目要求确定记一次还是记多次，count 就起作用了。

&emsp;&emsp;步骤（2）：构造 fail 指针，同时构造 suffix 指针。

&emsp;&emsp;**由于我们肯定是用之前的数据推出之后的目标，所以 BFS 是我们的不二选择。**我们先将根结点放进队列中，每次通过出队的去更新它的儿子，而不是在出队时更新自己。这样一不用特判根结点，二我们能**知道子结点对应的字符是什么。**

&emsp;&emsp;suffix 的计算与 fail 的计算息息相关。得到 fail 指针后，我们先检查 fail 指向的结点是否代表一个字符串，如果是，就指向 fail，否则指向 fail 的 suffix。 

&emsp;&emsp;就这样，AC 自动机就建好了。

![构造 AC 自动机](pic\AC 自动机 2.png)

（上图没有 suffix 指针）

###### ③向自动机输入

&emsp;&emsp;然后就和 KMP 几乎一模一样了，唯一的区别是**每次**都要跑一次 suffix 到根结点。

##### 3. 时空复杂度

&emsp;&emsp;设文本串长度为 n，模板串总长度为 m。

&emsp;&emsp;**Trie 结点占用的大小不能忽视**，其空间复杂度为 $O(α)$，代表字母表大小。很明显整体空间复杂度为 $O(mα)$。

&emsp;&emsp;时间复杂度是线性的。

##### 4. 参考代码

```c++
struct ACAutomation
{
	static const int alphabet = 26;
	static inline int code(char ch)
	{
		return ch - 'a';
	}
	struct Node
	{
		Node* c[alphabet];
		Node* fail;
		Node* suffix;
		int cnt;
		Node() : c(), fail(), suffix(), cnt() {}
	};
	struct Pool
	{
		std::stack<Node*> p;
		Node* alloc()
		{
			Node* ret;
			if (p.empty()) ret = new Node;
			else
			{
				ret = p.top();
				p.pop();
				new(ret) Node;
			}
			return ret;
		}
		void release(Node* x)
		{
			p.push(x);
		}
	};
	static Pool pool;

	Node* root;
	ACAutomation()
	{
		isInitialized = false;
		root = pool.alloc();
	}
	~ACAutomation()
	{
		clear(root);
	}
	void clear(Node* node)
	{
		for (int i = 0; i < alphabet; i++)
			if (node->c[i]) clear(node->c[i]);
		pool.release(node);
	}
	void reset()
	{
		clear(root);
		new(this) ACAutomation;
	}

	bool isInitialized;

	void insert(const char* str)
	{
		if (isInitialized) throw;
		Node* cnt = root;
		for (; *str != '\0'; str++)
		{
			Node* &p = cnt->c[code(*str)];
			if (!p) p = pool.alloc();
			cnt = p;
		}
		cnt->cnt++;
	}
	void initialize()
	{
		if (isInitialized) throw;
		isInitialized = true;
		std::queue<Node*> q;
		q.push(root);
		while (!q.empty())
		{
			Node* cnt = q.front();
			q.pop();
			for (int i = 0; i < alphabet; i++)
			{
				if (!cnt->c[i]) continue;
				Node* t = cnt->fail;
				while (t && !t->c[i]) t = t->fail;
				cnt->c[i]->fail = t ? t->c[i] : root;
				cnt->c[i]->suffix = cnt->c[i]->fail->cnt ? cnt->c[i]->fail :
					cnt->c[i]->fail->suffix;
				q.push(cnt->c[i]);
			}
		}
	}
	int match(const char* str)
	{
		if (!isInitialized) throw;
		int ret = 0;
		Node* cnt = root;
		for (; *str != '\0'; str++)
		{
			int c = code(*str);
			while (cnt && !cnt->c[c]) cnt = cnt->fail;
			cnt = cnt ? cnt->c[c] : root;
			for (Node* t = cnt; t; t = t->suffix)
			{
				ret += t->cnt;
				t->cnt = 0;
			}
		}
		return ret;
	}
};
ACAutomation::Pool ACAutomation::pool;
```

## Trie 图

##### 1. 定义

&emsp;&emsp;可以发现，如果我们知道了当前状态和下一个字符，那么我们能够转移到的状态是一定的。为什么一定要在匹配的时候每次去算呢？直接预处理好不是更好吗？

![Trie 图](pic\AC 自动机 3.png)

&emsp;&emsp;我们索性**在匹配时**不用 fail 指针，而是直接使用计算出的在每个状态中接收到每个字符后会转移到的状态。

##### 2. 计算方法

&emsp;&emsp;首先回忆一下 MP 算法到 KMP 算法的是如何进行改进的：直接通过**递推**求出真正可能继续匹配的位置。AC 自动机也要用到类似的思路。首先，如果下一个位置有结点，我们并不需要使用循环来计算下一个位置的 fail 指针。**因为 Trie 图保证所有已经计算过的点是有后继边的（裸的 AC 自动机可不一定有），所以我们直接让下一个结点的 fail 指针等于当前结点的 fail 指针对应的后继状态就可以了**。如果下一个位置没有结点，就直接让它等于**当前结点的 fail 指针所对应的后继状态**。特别地，根结点需要进行特判。

```c++
Node* &to = cnt->c[i];
Node* t = cnt == root ? root : cnt->fail->c[i]; // 由于是递推，所以 cnt->fail->c[i] 一定是已经算了的
if (!to)
    to = t; // 没有的话直接 = cnt->fail->c[i] 构建 Trie 图
else
{
    to->fail = t; // 有的话把它作为 fail 指针
    to->suffix = to->fail->cnt ? to->fail : to->fail->suffix; //记住算出 suffix
    q.push(to);
}
```

&emsp;&emsp;匹配时，因为所有边都存在，所以直接往下走即可：

```c++
cnt = cnt->c[c]; // 直接走
```

&emsp;&emsp;最后，因为变成图了，所以释放内存并不容易，对内存池进行一些改进即可。

##### 3. 参考代码

```c++
struct ACAutomation
{
	static const int alphabet = 26;
	static inline int code(char ch)
	{
		return ch - 'a';
	}
	struct Node
	{
		Node* c[alphabet];
		Node* fail;
		Node* suffix;
		int cnt;
		Node() : c(), fail(), suffix(), cnt() {}
	};
	struct Pool
	{
		std::stack<Node*> p;
		std::stack<Node*> used;
		Node* alloc()
		{
			Node* ret;
			if (p.empty()) ret = new Node;
			else
			{
				ret = p.top();
				p.pop();
				used.push(ret);
				new(ret) Node;
			}
			return ret;
		}
		void reset()
		{
			while (!used.empty())
			{
				p.push(used.top());
				used.pop();
			}
		}
	};
	static Pool pool;

	Node* root;
	ACAutomation()
	{
		isInitialized = false;
		root = pool.alloc();
	}
	void reset()
	{
		pool.reset(); // 需要改造内存池
		new(this) ACAutomation;
	}

	bool isInitialized;

	void insert(const char* str)
	{
		if (isInitialized) throw;
		Node* cnt = root;
		for (; *str != '\0'; str++)
		{
			Node* &p = cnt->c[code(*str)];
			if (!p) p = pool.alloc();
			cnt = p;
		}
		cnt->cnt++;
	}
	void initialize()
	{
		if (isInitialized) throw;
		isInitialized = true;
		std::queue<Node*> q;
		q.push(root);
		while (!q.empty())
		{
			Node* cnt = q.front();
			q.pop();
			for (int i = 0; i < alphabet; i++)
			{
				Node* &to = cnt->c[i];
				Node* t = cnt == root ? root : cnt->fail->c[i]; // 由于是递推，所以 cnt->fail->c[i] 一定是已经算了的
				if (!to)
					to = t; // 没有的话直接 = cnt->fail->c[i] 构建 Trie 图
				else
				{
					to->fail = t; // 有的话把它作为 fail 指针
					to->suffix = to->fail->cnt ? to->fail : to->fail->suffix; //记住算出 suffix
					q.push(to);
				}
			}
		}
	}
	int match(const char* str)
	{
		if (!isInitialized) throw;
		int ret = 0;
		Node* cnt = root;
		for (; *str != '\0'; str++)
		{
			int c = code(*str);
			cnt = cnt->c[c]; // 直接走
			for (Node* t = cnt; t; t = t->suffix)
			{
				ret += t->cnt;
				t->cnt = 0;
			}
		}
		return ret;
	}
};
ACAutomation::Pool ACAutomation::pool;
```

