##1.You are given as input an unsorted array of n distinct numbers, where n is a power of 2. Give an algorithm that identifies the second-largest number in the array, and that uses at most n+log2n−2 comparisons.

**Ans**
1. 类似merge sort 两组两组递归比较，生成“比较树”，其中顶点为最大数 （n-1 comparisons）
2. 第二大的数只能在生成“比较树”中与最大数比较过的点中，所以顺着顶点下来，最多log2n - 1 次比较（log(2n)-1 comparisons）

##2. You are a given a unimodal array of n distinct elements, meaning that its entries are in increasing order up until its maximum element, after which its elements are in decreasing order. Give an algorithm to compute the maximum element that runs in O(log n) time.

**Ans**
* 二分法

##3. You are given a sorted (from smallest to largest) array A of n distinct integers which can be positive, negative, or zero. You want to decide whether or not there is an index i such that A[i] = i. Design the fastest algorithm that you can for solving this problem.

**Ans**
* 二分法 log(n)