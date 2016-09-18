1. You are given a connected undirected graph G with distinct edge costs, in adjacency list representation. You are also given the edges of a minimum spanning tree T of G. This question asks how quickly you can recompute the MST if we change the cost of a single edge. Which of the following are true? [RECALL: It is not known how to deterministically compute an MST from scratch in O(m) time, where m is the number of edges of G.] [Check all that apply.]

	**A:**Suppose e∉T and we increase the cost of e. Then, the new MST can be recomputed in O(m) deterministic time.
	正确回答 
	The MST does not change (by the Cycle Property of the previous problem), so no re-computation is needed.

	**B:**Suppose e∈T and we increase the cost of e. Then, the new MST can be recomputed in O(m) deterministic time.
	正确回答 
	Let A,B be the two connected components of T−{e}. Edge e no longer belongs to the new MST if and only if it is no longer the cheapest edge crossing the cut (A,B) (this can be checked in O(m) time). If f is the new cheapest edge crossing (A,B), then the new MST is T−{e}∪{f}.

	**C:**Suppose e∈T and we decrease the cost of e. Then, the new MST can be recomputed in O(m) deterministic time.
	正确回答 
	The MST does not change (by the Cut Property), so no re-computation is needed.

	**D:**Suppose e∉T and we decrease the cost of e. Then, the new MST can be recomputed in O(m) deterministic time.
	不正确回答 
	Let C be the cycle of T∪{e}. Edge e belongs to the new MST if and only if it is no longer the most expensive edge of C (this can be checked in O(n) time). If f is the new most expensive edge of C, then the new MST is T∪{e}−{f}.
    
2. Which of the following problems reduce, in a straightforward way, to the minimum spanning tree problem? [Check all that apply.]

	**A:**The maximum-cost spanning tree problem. That is, among all spanning trees of a connected graph with edge costs, compute one with the maximum-possible sum of edge costs.
	正确回答 
	Just negate all edge costs and run an MST algorithm.

	**B:**The single-source shortest-path problem.
	正确回答 
	There is no obvious way of using a minimum spanning tree subroutine to solve the single-source shortest-path problem.

	**C:**The minimum bottleneck spanning tree problem. That is, among all spanning trees of a connected graph with edge costs, compute one with the minimum-possible maximum edge cost.
	正确回答 
	As discussed in the problem sets, every MST is also a minimum bottleneck spanning tree.

	**D:**Given a connected undirected graph G=(V,E) with positive edge costs, compute a minimum-cost set F⊆E such that the graph (V,E−F) is acyclic.
	不正确回答 
	The optimal such set is the complement of a maximum-cost spanning tree.
    
3. Which of the following statements are true about the tractability of the Knapsack problem? [Check all that apply.]

	**A:**If there is a polynomial-time algorithm for the Knapsack problem in general, then P=NP.
	正确回答 
	Yes, the (decision version of) the Knapsack problem is NP-complete.

	**B:**Assume that P≠NP. The special case of the Knapsack problem in which all item values are positive integers less than or equal to n5, where n is the number of items, can be solved in polynomial time.
	正确回答 
	Our second dynamic programming algorithm for the Knapsack problem proves this.

	**C:**Assume that P≠NP. The special case of the Knapsack problem in which all item values, item sizes, and the knapsack capacity are positive integers, can be solved in polynomial time.
	不正确回答 
	No, only when either the item values or the item sizes are polynomially bounded.

	**D:**Assume that P≠NP. The special case of the Knapsack problem in which all item sizes are positive integers less than or equal to n5, where n is the number of items, can be solved in polynomial time.
	不正确回答 
	Our first dynamic programming algorithm for the Knapsack problem proves this. (Note one can assume that the capacity W is less than the sum of the item sizes, otherwise the instance is trivial.)
    
4. Assume that P≠NP. Which of the following extensions of the Knapsack problem can be solved in time polynomial in n, the number of items, and M, the largest number that appears in the input? [Check all that apply.]

	**A:**You are given n items with positive integer values and sizes, and a positive integer capacity W, as usual. The problem is to compute the max-value set of items with total size exactly W. If no such set exists, the algorithm should correctly detect that fact.
	正确回答 
	Requires only minor modifications to the standard Knapsack dynamic programming algorithm.

	**B:**You are given n items with positive integer values and sizes, as usual, and two positive integer capacities, W1 and W2. The problem is to pack items into these two knapsacks (of capacities W1 and W2) to maximize the total value of the packed items. You are not allowed to split a single item between the two knapsacks.
	正确回答 
	Add another dimension to the array to keep track of the residual capacity of the second knapsack, this increases the running time by a factor of at most W.

	**C:**You are given n items with positive integer values and sizes, as usual, and m positive integer capacities, W1,W2,…,Wm . These denote the capacities of m different Knapsacks, where m could be as large as Θ(n). The problem is to pack items into these knapsacks to maximize the total value of the packed items. You are not allowed to split a single item between two of the knapsacks.
	正确回答 
	Every straightforward dynamic programming approach has running time exponential in m. More generally, this problem is NP-hard even if all of the numbers are polynomially bounded (non-trivial exercise: can you prove this?).

	**D:**You are given n items with positive integer values and sizes, and a positive integer capacity W, as usual. You are also given a budget k≤n on the number of items that you can use in a feasible solution. The problem is to compute the max-value set of at most k items with total size at most W.
	正确回答 
	Add another dimension to the array to keep track of how many items you've used so far, this increases the running time by a factor of at most n.
    
5. Assume that P≠NP. The following problems all take as input two strings X and Y, of length m and n, over some alphabet Σ. Which of them can be solved in O(mn) time? [Check all that apply.]

	**A:**Compute the length of a longest common substring of X and Y. (A substring is a consecutive subsequence of a string. So "bcd" is a substring of "abcdef", whereas "bdf" is not.)
	正确回答 
	Similar dynamic programming to sequence alignment, with one subproblem for each Xi and Yj.

	**B:**Assume that X and Y have the same length n. Does there exist a permutation f, mapping each i∈{1,2,…,n} to a distinct f(i)∈{1,2,…,n}, such that Xi=Yf(i) for every i=1,2,…,n?
	不正确回答 
	This problem can be solved in O(n) time, without dynamic programming. Just count the frequency of each symbol in each string. The permutation f exists if and only if every symbol occurs exactly the same number of times in each string.

	**C:**Compute the length of a longest common subsequence of X and Y. (Recall a subsequence need not be consecutive. For example, the longest common subsequence of "abcdef" and "afebcd" is "abcd".)
	正确回答 
	Similar dynamic programming to sequence alignment, with one subproblem for each Xi and Yj. Alternatively, this reduces to sequence alignment by setting the gap penalty to 1 and making the penalty of matching two different characters to be very large.

	**D:**Consider the following variation of sequence alignment. Instead of a single gap penalty αgap, you're given two numbers a and b. The penalty of inserting k gaps in a row is now defined as ak+b, rather than kαgap. Other penalties (for matching two non-gaps) are defined as before. The goal is to compute the minimum-possible penalty of an alignment under this new cost model.
	不正确回答 
	Variation on the original sequence alignment dynamic program. With each subproblem, you need to keep track of what gaps you insert, since the costs you incur in the current position depend on whether or not the previous subproblems inserted gaps. Blows up the number of subproblems and running time by a constant factor.
    
6. Assume that P≠NP. Which of the following problems can be solved in polynomial time? [Check all that apply.]

	**A:**Given a directed graph with real-valued edge lengths, compute the length of a longest cycle-free path between any pair of vertices (i.e., maxu,v∈VmaxP∈Puv∑e∈Pce, where Puv denotes the set of cycle-free u-v paths).
	正确回答 
	The NP-complete Hamiltonian Path problem (recall PSet #6) reduces easily to this problem, so it cannot be solved in polynomial time assuming P≠NP.

	**B:**Given a directed graph with nonnegative edge lengths, compute the length of a maximum-length shortest path between any pair of vertices (i.e., maxu,v∈Vd(u,v), where d(u,v) is the shortest-path distance between u and v).
	正确回答 
	Since edge lengths are nonnegative, there are no negative cycles. Thus, this problem reduces to all-pairs shortest paths.

	**C:**Given a directed graph with nonnegative edge lengths, compute the length of a longest cycle-free path between any pair of vertices (i.e., maxu,v∈VmaxP∈Puv∑e∈Pce, where Puv denotes the set of cycle-free u-v paths).
	正确回答 
	The NP-complete Hamiltonian Path problem (recall PSet #6) reduces easily to this problem, so it cannot be solved in polynomial time assuming P≠NP.

	**D:**Given a directed acyclic graph with real-valued edge lengths, compute the length of a longest path between any pair of vertices.
	不正确回答 
	By multiplying all edge lengths by -1, the problem reduces to computing the shortest path between any pair of vertices. Since the graph is acyclic, there are no negative-cost cycles, and this problem can be solved in polynomial time (e.g., via Floyd-Warshall or Johnson).
    
7. Of the following problems, which can be solved in polynomial time by directly applying algorithmic ideas that were discussed in lecture and/or the homeworks? [Check all that apply.]

	**A:**Given an undirected graph G and a value for k such that k=Θ(logn), where n is the number of vertices of G, does G have an independent set of size at least k?
	正确回答 
	There is a reduction between the vertex cover and independent set problems where you take the complement of one to get the other (see PSet #5). Unfortunately, this transforms vertex covers of size k to independent sets of size n−k and thus is not useful here. Also, it is not clear how to adapt the Vertex Cover algorithm from lecture to the Independent Set problem. In fact, it is conjectured that this problem cannot be solved in polynomial time at all.

	**B:**Given an undirected graph G and a constant value for k (i.e., k=O(1), independent of the size of G), does G have an independent set of size at least k?
	正确回答 
	Brute-force search (checking each subset of k vertices) runs in time O(nk), which is polynomial when k=O(1).

	**C:**Given an undirected graph G and a constant value for k (i.e., k=O(1), independent of the size of G), does G have a vertex cover of size at most k?
	正确回答 
	Brute-force search (checking each subset of k vertices) runs in time O(nk), which is polynomial when k=O(1).

	**D:**Given an undirected graph G and a value for k such that k=Θ(logn), where n is the number of vertices of G, does G have a vertex cover of size at most k?
	不正确回答 
	The Vertex Cover algorithm covered in lecture has running time O(2km) and hence runs in polynomial time in this case.