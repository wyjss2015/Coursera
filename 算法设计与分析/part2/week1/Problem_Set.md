#Problem set
1. We are given as input a set of n requests (e.g., for the use of an auditorium), with a known start time si and finish time ti for each request i. Assume that all start and finish times are distinct. Two requests conflict if they overlap in time --- if one of them starts between the start and finish times of the other. Our goal is to select a maximum-cardinality subset of the given requests that contains no conflicts. (For example, given three requests consuming the intervals [0,3], [2,5], and [4,7], we want to return the first and third requests.) We aim to design a greedy algorithm for this problem with the following form: At each iteration we select a new request i, including it in the solution-so-far and deleting from future consideration all requests that conflict with i.

**ANS** At each iteration, pick the remaining request with the earliest finish time.

##**proof**
> **引理1：** 任意一个request，与其冲突的request的可能性有4种
  1. [【]】
  2. [【】]
  3. 【[]】
  4. 【[】]

> **引理2：** 假设request是当前所有requests中结束时间最早的,则与其冲突的request的可能性只有1种
  1. 【[】]

> **推论2：** 由引理2可知，引理2中的request和与其冲突的所有requests只能选一个，因为都横跨共同的边界'】'

**准备工作**：
1. 不妨考察任意两个request,一个是当前所有requests中结束时间最早的记为A，另一个在剩下的中任取记为B
2. A和B有两种可能关系
	1. 冲突
	2. 不冲突
3. 除A和B外其他所有requests可以分成4类
	1. 和A，B都不冲突，记为X
	2. 和A，B都冲突，记为Y
	3. 和A冲突，和B不冲突，记为V
	4. 和A不冲突，和B冲突，记为W

**反证法论证：**
假设当前步选择B使得所得结果最优，则有如下两种可能
1. 假设A和B不冲突
	* 选择B剩下的requests个数为|X|+|V|（V包括A）
	* 选择A剩下的requests个数为|X|+|W|（W包括B）
	* 由推论2知V和A最终只能剩下一个
	* W和B最终至少剩下一个
	* 所以选择A至少和选择B的结果一样好，因此与假设矛盾
2. 假设A和B冲突
	* 选择B剩下的requests个数为|X|+|V|（V不包括A）
	* 选择A剩下的requests个数为|X|+|W|(W不包括B)
	* 同1
	* 同1
	* 同1， 因此与假设矛盾
3. 得证