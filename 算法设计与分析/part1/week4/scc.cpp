#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;
#define N 875714
//邻接表
vector<int> vecList[N+1];
//反向邻接表
vector<int> reverseVecList[N+1];

//magical order 映射表
int order[N+1];

void readGraph(){
	ifstream in("SCC.txt");
	string line;
	while(getline(in, line)){
		istringstream record(line);
		int tail, head;
		record >> tail >> head;
		vecList[tail].push_back(head);
		reverseVecList[head].push_back(tail);
	}
}

//第一轮DFS作用在反向邻接表上生成magical order,保存于order映射表
int counts = 0;
int explored[N+1];

void DFS_1(int i){
	explored[i] = 1;
	for(vector<int>::size_type j=0;j<reverseVecList[i].size();++j)
		if(explored[reverseVecList[i][j]] == 0)
			DFS_1(reverseVecList[i][j]);
	order[++counts] = i;
}

void DFS_loop_1(){
	for(int i=N;i>0;--i)
		explored[i] = 0;
	for(int i=N;i>0;--i)
		if(explored[i]==0)
			DFS_1(i);
}

//第二轮DFS作用于邻接表上，输出the size of SCCs
vector<int> cnt;
void DFS_2(int i, int &c){
	explored[i] = 1;
	++c;
	for(vector<int>::size_type j=0;j<vecList[i].size();++j)
		if(explored[vecList[i][j]]==0)
			DFS_2(vecList[i][j], c);
}

void DFS_loop_2(){
	for(int i=N;i>0;--i)
		explored[i] = 0;
	for(int i=N,k=0;i>0;--i)
		if(explored[order[i]]==0){
			int temp=0;
			DFS_2(order[i], temp);
			if(k<5)
				cnt.push_back(temp);
			else{
				for(auto &c: cnt)
					if(c<temp){
						int temp1 = c;
						c = temp;
						temp = temp1;
					}
			}
			++k;
		}
}
int main(){
	readGraph();
	DFS_loop_1();
	DFS_loop_2();
	for(auto &c: cnt)
		cout<<c<<endl;
	return 0;
}
