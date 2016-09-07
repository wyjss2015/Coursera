##3. Recall our dynamic programming algorithm for computing the maximum-weight independent set of a path graph. Consider the following proposed extension to more general graphs. Consider an undirected graph with positive vertex weights. For a vertex v, obtain the graph G′(v) by deleting v and its incident edges from G, and obtain the graph G′′(v) from G by deleting v, its neighbors, and all of the corresponding incident edges from G. Let OPT(H) denote the value of a maximum-weight independent set of a graph H. Consider the formula OPT(G)=max{OPT(G′(v)),wv+OPT(G′′(v))}, where v is an arbitrary vertex of G of weight wv. Which of the following statements is true?

**CHOICES**
1. The formula is correct in path graphs but is not always correct in trees.
2. The formula is always correct in trees, but does not lead to an efficient dynamic programming algorithm.
3. The formula is always correct in general graphs, and it leads to an efficient dynamic programming algorithm.
不正确回答 
All you need is an ordering on the subproblems. Root the tree at an arbitrary vertex, now subproblems correspond to subtrees and size = number of nodes in the subtree.
4. The formula is always correct in trees, and it leads to an efficient dynamic programming algorithm.

##5.Consider an instance of the optimal binary search tree problem with 7 keys (say 1,2,3,4,5,6,7 in sorted order) and frequencies w1=.05,w2=.4,w3=.08,w4=.04,w5=.1,w6=.1,w7=.23. What is the minimum-possible average search time of a binary search tree with these keys?

**ANS**
[obst.cpp](obst.cpp)