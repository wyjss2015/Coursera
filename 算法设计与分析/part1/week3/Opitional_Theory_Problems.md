##1.Prove that the worst-case expected running time of every randomized comparison-based sorting algorithm is Ω(nlogn). (Here the worst-case is over inputs, and the expectation is over the random coin flips made by the algorithm.)

##2.Suppose we modify the deterministic linear-time selection algorithm by grouping the elements into groups of 7, rather than groups of 5. (Use the "median-of-medians" as the pivot, as before.) Does the algorithm still run in O(n) time? What if we use groups of 3?

##3.Given an array of n distinct (but unsorted) elements x1,x2,…,xn with positive weights w1,w2,…,wn such that ∑ni=1wi=W, a weighted median is an element xk for which the total weight of all elements with value less than xk (i.e., ∑xi<xkwi) is at most W/2, and also the total weight of elements with value larger than xk (i.e., ∑xi>xkwi) is at most W/2. Observe that there are at most two weighted medians. Show how to compute all weighted medians in O(n) worst-case time.

##4.We showed in an optional video lecture that every undirected graph has only polynomially (in the number n of vertices) different minimum cuts. Is this also true for directed graphs? Prove it or give a counterexample.

##5.For a parameter α≥1, an α-minimum cut is one for which the number of crossing edges is at most α times that of a minimum cut. How many α-minimum cuts can an undirected graph have, as a function of α and the number n of vertices? Prove the best upper bound that you can.
