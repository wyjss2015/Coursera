##3. Which of the following statements is true?

1. Consider a TSP instance in which every edge cost is either 1 or 2. Then an optimal tour can be computed in polynomial time.
**这是一个np完全问题**
2. Consider a TSP instance in which every edge cost is negative. Deleting a vertex and all of its incident edges cannot increase the cost of the optimal (i.e., minimum sum of edge lengths) tour.

3. Consider a TSP instance in which every edge cost is the Euclidean distance between two points in the place (just like in Programming Assignment #5). Deleting a vertex and all of its incident edges cannot increase the cost of the optimal (i.e., minimum sum of edge lengths) tour.
**ANS** 利用三角不等式
**proof**假设删除点k,在origin graph的TSP解中和它相邻的点为i,j，则利用三角不等式，有dist(i,j)<dist(i,k)+dist(k,j)，所以删除点k后剩下点组成的tsp问题的解一定比原来的tsp问题的解小。

4. Consider a TSP instance in which every edge cost is negative. The dynamic programming algorithm covered in the video lectures might not correctly compute the optimal (i.e., minimum sum of edge lengths) tour of this instance.
**不正确回答 **
The algorithm and its correctness proof never uses the fact that edge costs are nonnegative.

##4. Let TSP1 denote the following problem: given a TSP instance in which all edge costs are positive integers, compute the value of an optimal TSP tour. Let TSP2 denote: given a TSP instance in which all edge costs are positive integers, and a positive integer T, decide whether or not there is a TSP tour with total length at most T. Let HAM1 denote: given an undirected graph, either return the edges of a Hamiltonian cycle (a cycle that visits every vertex exactly once), or correctly decide that the graph has no such cycle. Let HAM2 denote: given an undirected graph, decide whether or not the graph contains at least one Hamiltonian cycle.

**ANS** 
If TSP2 is polynomial-time solvable, then so is TSP1. If HAM2 is polynomial-time solvable, then so is HAM1.

**解析**
Given a polynomial-time algorithm for TSP2, use it repeatedly while binary searching over the choice of T to solve TSP1 (the number of iterations necessary is logarithmic in the sizes of the input numbers, which is polynomial in the input size). Use a polynomial-time algorithm for HAM2 to solve HAM1 as follows. First, run HAM2 on the graph. If it says "no", report "no". Otherwise, delete some edge (in effect, guessing that there is also a Hamiltonian cycle without it) and run HAM2 again. If it says "yes", iterate on the new smaller graph. If it says "no", restore the edge (it lies on every Hamiltonian cycle, do you see why?) and move on to the next edge. If HAM2 originally said "yes", you will identify (in O(m) iterations) a sequence of successful edge deletions, and the remaining edges will constitute a Hamiltonian cycle of the original graph.