#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <climits>
using namespace std;

#define N 500

struct arc{
	int end;
	int weight;
};

void readGraph(vector<arc> *vertexList){
	ifstream in("edges.txt");
	string line;
	getline(in, line);
	while(getline(in, line)){
		istringstream record(line);
		arc temp1, temp2;
		int start, end, weight;
		record >> start >> end >> weight;
		temp1.end = end;
		temp1.weight = weight;
		temp2.end = start;
		temp2.weight = weight;
		vertexList[start].push_back(temp1);
		vertexList[end].push_back(temp2);
	}
}
int flag[N+1]; //记录点是否在T中
int weight[N+1]; //记录点当前连接到T的最短边
int pos[N+1]; //记录点在heap中的位置

vector<int> heap(N, 0);
int size = 0;

void heap_up(int v){
	int cur, par;
	for(cur=pos[v], par=cur/2; par>0&&weight[v]<weight[heap[par]];cur=par,par/=2){
		heap[cur] = heap[par];
		pos[heap[par]] = cur;
	}
	heap[cur] = v;
	pos[v] = cur;
}
void heap_insert(int v){
	int cur, par;
	for(cur=++size, par=cur/2; par>0&&weight[v]<weight[heap[par]]; cur=par, par/=2){
		heap[cur] = heap[par];
		pos[heap[par]] = cur;
	}
	heap[cur] = v;
	pos[v] = cur;
}

int heap_pop(){
	if(size == 0)
		return 0;
	int min = heap[1];
	pos[min] = 0;
	int temp = heap[size--];
	int cur, child;
	for(cur=1,child=2; child<=size; cur=child,child*=2){
		if(child<size&&weight[heap[child]]>weight[heap[child+1]])
			child++;
		if(weight[heap[child]]<weight[temp]){
			heap[cur] = heap[child];
			pos[heap[child]] = cur;
		}else
			break;
	}
	heap[cur] = temp;
	pos[temp] = cur;
	return min;
}
void prim(vector<arc> *vertexList, vector<int> &T_weight){
	flag[1] = 1;
	for(auto &v: vertexList[1]){
		weight[v.end] = v.weight;
		heap_insert(v.end);
	}
	while(int v = heap_pop()){
		flag[v] = 1;
		T_weight.push_back(weight[v]);
		for(auto &temp: vertexList[v]){
			if(flag[temp.end]==0){
				if(pos[temp.end]==0){
					weight[temp.end] = temp.weight;
					heap_insert(temp.end);
				}
				else if(pos[temp.end]!=0&&weight[temp.end]>temp.weight){
					weight[temp.end] = temp.weight;
					heap_up(temp.end);
				}
			}
		}
	}
}

int main(){
	vector<arc> vertexList[N+1];
	vector<int> T_weight; //记录MST权重
	readGraph(vertexList);

	for(int i=1;i<=N;++i){
		flag[i] = 0;
		weight[i] = INT_MAX;
		pos[i] = 0;
	}
	prim(vertexList, T_weight);

	long long sum=0;
	for(auto &w: T_weight)
		sum += w;
	cout << sum << endl;
	cout << T_weight.size() <<endl;
	return 0;
}
