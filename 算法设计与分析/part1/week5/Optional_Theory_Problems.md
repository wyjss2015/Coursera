##1. In lecture we define the length of a path to be the sum of the lengths of its edges. Define the bottleneck of a path to be the maximum length of one of its edges. A mininum-bottleneck path between two vertices s and t is a path with bottleneck no larger than that of any other s-t path. Show how to modify Dijkstra's algorithm to compute a minimum-bottleneck path between two given vertices. The running time should be O(mlogn), as in lecture.
**Ans:**
假设V为所有点，X为已处理完的点集， v属于V，w属于V-X，s为源点
原来的Dijkstra算法中每步处理的点为满足A(v)+l(v,w)最小的点w
(其中A为s到v的最短路径，（v,w）为v,w的边长)
本题中在Dijkstra算法的基础上修改每步处理点满足的上面条件，改成判断max(B(v), l(v,w))
(其中B为s到v的minimum-bottleneck path的瓶颈长度)
  
##2. We can do better. Suppose now that the graph is undirected. Give a linear-time (O(m)) algorithm to compute a minimum-bottleneck path between two given vertices.

参考文献[On the Bottleneck Shortest Path Problem](ZR-06-22.pdf)

##3. What if the graph is directed? Can you compute a minimum-bottleneck path between two given vertices faster than O(mlogn)?

参考文献[On the Bottleneck Shortest Path Problem](ZR-06-22.pdf)