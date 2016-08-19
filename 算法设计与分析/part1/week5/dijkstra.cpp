#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;
#define N 200
struct arc{
	int length;
	int ver;
};
//邻接表
vector<arc> verList[N+1];

//标记处理过的点
int flag[N+1];

//记录当前各点到源点的最短距离
int A[N+1];

void readGraph(){
	ifstream in("dijkstraData.txt");
	string line;
	while(getline(in, line)){
		istringstream record(line);
		int len, nextver, vertex;
		char pass;
		record >> vertex;
		while(record >> nextver >> pass >> len){
			arc temp;
			temp.ver = nextver;
			temp.length = len;
			verList[vertex].push_back(temp);
		}
	}
}

//堆
vector<int> heap(N+1, 0);
int size = 0;

//记录元素在堆中的位置
int pos[N+1];

//上浮
void heap_up(int position){
	int temp = heap[position];
	int cur, par;
	for(cur=position, par=position/2;par>0&&A[heap[par]]>A[temp];cur=par,par/=2){
		heap[cur] = heap[par];
		pos[heap[cur]] = cur;
	}
	heap[cur] = temp;
	pos[temp] = cur;

}
//堆插入， 同步pos
void heap_insert(int v){
	heap[++size] = v;
	heap_up(size);
}
//删除最小元素
int heap_delMin(){
	if(size==0)
		return 0;
	int min = heap[1];
	pos[min] = 0;
	int temp = heap[size--];
	int cur, child;
	for(cur=1, child=2;child<=size;cur=child,child*=2){
		if(child<size&&A[heap[child]]>A[heap[child+1]])
			child += 1;
		if(A[temp]>A[heap[child]]){
			heap[cur] = heap[child];
			pos[heap[cur]] = cur;
		}else
			break;
	}
	heap[cur] = temp;
	pos[temp] = cur;
	return min;
}

void dijkstra(int s){
	flag[s] = 1;
	A[s] = 0;
	for(const auto &next: verList[s]){
		int temp = A[s] + next.length;
		if(temp < A[next.ver])
			A[next.ver] = temp;
		heap_insert(next.ver);
	}
	while(int v = heap_delMin()){
		flag[v] = 1;
		for(const auto &next: verList[v]){
			if(flag[next.ver]==0){
				int val = A[v] + next.length;
				if(val < A[next.ver]){
					A[next.ver] = val;
					if(pos[next.ver]==0)
						heap_insert(next.ver);
					else
						heap_up(pos[next.ver]);
				}
			}
		}
	}
}

int main(){
	//初始化
	for(int i=N;i>0;--i){
		flag[i] = 0;
		A[i] = 1000000;
		pos[i] = 0;
	}
	//读入图;
	readGraph();
	//dijkstra, 源点为1
	dijkstra(1);
	//for(int i=1;i<=N;++i)
	//	cout << A[i]<<endl;
	cout<<A[7]<<" "\
	<<A[37]<<" "\
	<<A[59]<<" "
	<<A[82]<<" "
	<<A[99]<<" "
	<<A[115]<<" "
	<<A[133]<<" "
	<<A[165]<<" "
	<<A[188]<<" "
	<<A[197]<<endl;
	return 0;
}
