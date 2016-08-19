##1. Give the best upper bound that you can on the solution to the following recurrence: T(1)=1 and T(n)≤T([√n])+1 for n>1. (Here [x] denotes the "floor" function, which rounds down to the nearest integer.)

**Ans**
T(n)≤T([√n])+1<=T(n/2)+1  for n>1
T(n) = O(log(n))

##2. You are given an n by n grid of distinct numbers. A number is a local minimum if it is smaller than all of its neighbors. (A neighbor of a number is one immediately above, below, to the left, or the right. Most numbers have four neighbors; numbers on the side have three; the four corners have two.) Use the divide-and-conquer algorithm design paradigm to compute a local minimum with only O(n) comparisons between pairs of numbers. (Note: since there are n2 numbers in the input, you cannot afford to look at all of them. Hint: Think about what types of recurrences would give you the desired upper bound.)

**Ans**

> **引论**：观察到从任何一点出发，每次从上下左右相邻的四块中选择比当前值小的方向前进一步，如此走下去直到满足局部最小，该方法最终能得到局部最小点。时间复杂度O(n^2)

分治法：
1. 中间横竖两行把整体分成四块，每块规模为原来的1/2
2. 找出横竖两行中的最小值(O(n))，假设最小值v在竖线上，假如v左右都比v大，则v为要求的局部最小,假如v的左侧比v小，则根据引论，在v左侧的象限中一定存在局部最小（因为利用引论的方法从v开始走，一定不会走出横竖轴线边界，因为轴线上的值都比v大，终点一定禁止在象限内。）
3. 递归处理第二步中选择的象限，规模只有原来1/2

时间复杂度分析:T(n) <= T(n/2)+O(n)， 所以T(n)=O(n)