#点滴感悟

> Can we do better?

##数据结构
* 数据结构总是维持一个invariant
* 数据结构关注两点：1.支持什么操作。2.这些操作渐进时间复杂度

###堆
* 当发现算法需要反复计算最小值或最大值时，可以考虑利用优先队列进行优化

###union-find
* 维持集合划分

##算法
* 教授的讲解都是从high level使用伪代码讲清楚算法的原理，看书上很多的代码都包含了实现的细节处理，因此应分清原理和实现细节
* 切入的角度很关键
* 分析算法时可以从单个元素的角度入手.
	1. 比如quicksort时间复杂度不好分析，利用期望的性质转化成从任意一对元素的比较次数的分析。
	2. 再比如union-find，粗看起来一次union的渐进时间为O（n）,但是单个元素在整个程序过程中可能的update次数仅为O(logn)
* 目标函数的定义没能导出算法没有意义（sequence align）
* 要清楚目标是啥，不同的目标函数催生不同的算法(比较k-means clustering和single-link clustering)

###贪婪算法
* 问题模式：需要一序列决策过程

###动态规划
* lemma只说明了optimal sub-problem 的必要条件，因此candidates是所有满足必要条件的substrcut

##解决问题之道
###P
1. reduce(降解)
2. devide and conquer
3. greedy
4. DP
5. graph (search 、cut)
6. randomize

###NP
* 证明是否NP完全问题 
	1. 找到合适已知NP完全问题P
	2. P是否能归约(reduce to)成当前问题
* 求解策略
	1. Focus on computationally tractable special cases
	2. Heuristics - fast algorithms that are not always correct
		2.1 基于greedy或DP的启发式算法
		2.2 local search
			2.2.1 solution space X
			2.2.2 neighborhood define y
			2.2.3 三个问题：
				2.2.3.1 起始点的选择：1.随机；2.best heruistic
				2.2.3.2 当存在多个更好的邻居y时：1.随机；2.选提高最多的；3.更复杂的启发
				2.2.3.3 怎么定义邻居y，或说定义多大的邻居空间：1.note bigger neighborhoods slower to verity local optimality but fewer (bad) local opimal 2.find "sweet spot" between solution quality and efficient searchability
	3. Solve in exponential time but faster than brute-force search.

##证明之道
1. induction
2. contradiction
3. exchange argument

###证明最优的两种方法
1. 证明算法得到的解比解空间任何其他解都优（可以结合exchange argument）
2. 反证法，假设存在比算法的解更优的解，证矛盾（可以结合exchange argument）
	* 因为假如存在比算法的解更优的解，则该解一定违背算法本身的某个性质，利用该性质结合exchange argument 容易得到矛盾。