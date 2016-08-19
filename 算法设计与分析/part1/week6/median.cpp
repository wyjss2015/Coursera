#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
#define N 10000

//大顶堆
vector<int> maxHeap(N, 0);
int aSize = 0;

//小顶堆
vector<int> minHeap(N, 0);
int bSize = 0;

void maxInsert(int e){
	maxHeap[++aSize] = e;
	int cur, par;
	for(cur=aSize, par=aSize/2;par>0&&maxHeap[par]<e;cur=par, par/=2)
		maxHeap[cur] = maxHeap[par];
	maxHeap[cur] = e;
}
void minInsert(int e){
	minHeap[++bSize] = e;
	int cur, par;
	for(cur=bSize, par=bSize/2;par>0&&minHeap[par]>e;cur=par,par/=2)
		minHeap[cur] = minHeap[par];
	minHeap[cur] = e;
}
int delMin(){
	int min = minHeap[1];
	int temp = minHeap[bSize--];
	int cur, child;
	for(cur=1, child=2;child<=bSize;cur=child,child*=2){
		if(child<bSize&&minHeap[child]>minHeap[child+1])
			child += 1;
		if(temp>minHeap[child]){
			minHeap[cur] = minHeap[child];
		}else{
			break;
		}
	}
	minHeap[cur] = temp;
	return min;
}

int delMax(){
	int max = maxHeap[1];
	int temp = maxHeap[aSize--];
	int cur, child;
	for(cur=1, child=2; child<=aSize;cur=child,child*=2){
		if(child<aSize&&maxHeap[child]<maxHeap[child+1])
			child += 1;
		if(temp<maxHeap[child]){
			maxHeap[cur] = maxHeap[child];
		}else{
			break;
		}
	}
	maxHeap[cur] = temp;
	return max;
}

void balance(){
	int dif = aSize - bSize;
	int temp;
	while(dif>1){
		minInsert(delMax());
		dif = aSize - bSize;
	}
	while(dif<0){
		maxInsert(delMin());
		dif = aSize - bSize;
	}
}
int getMedian(){
	if(aSize==0)
		return 0;
	return maxHeap[1];
}

int process(){
	ifstream in("Median.txt");
	int val;
	int sum=0;
	while(in >> val){
		int median = getMedian();
		if(median!=0&&median<val)
			minInsert(val);
		else
			maxInsert(val);
		balance();
		sum += getMedian();
	}
	return sum % 10000;
}

int main(){
	cout << process() << endl;
	return 0;
}
