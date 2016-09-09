#include "quickSort.h"
#include "union_find.h"

/*
准备工作:
	点数: n
	计数器: cnt=0
	所有点在parent point指向自己
1. sort edges
2. for sorted edges as i:
		if find边的两端点不在同一类中:
			union两端点所在的两类
			if(++cnt==n-1) break
	return i+1条边长度
*/
vector<data> arr;
vector<edge> edges;
int n;
void readData(){
	ifstream in("clustering1.txt");
	string line;
	getline(in,line);
	istringstream record(line);
	record >> n;
	while(getline(in, line)){
		istringstream record(line);
		edge temp;
		record >> temp.node1 >> temp.node2 >> temp.weight;
		edges.push_back(temp);
	}
}

int kruskal(int k){
	int cnt = 0;
	init(arr, n);
	int totalEdges = static_cast<int>(edges.size());
	int i;
	for(i=0;i<totalEdges;++i){
		if(find(arr, edges[i].node1)!=find(arr, edges[i].node2)){
			runion(arr, edges[i].node1, edges[i].node2);
			if(++cnt==n-k)
				break;
		}
	}
	return ++i;
}

int maxSpacing(int a){
	int totalEdges = static_cast<int>(edges.size());
	int max = 0;
	for(int i=a;i<totalEdges;++i){
		if(find(arr, edges[i].node1)!=find(arr, edges[i].node2))
			return edges[i].weight;
	}
}
int main(){
	readData();
	quickSort(edges, 0, static_cast<int>(edges.size()-1));
	int i = kruskal(4);
	cout << maxSpacing(i) << endl;
	return 0;
}
