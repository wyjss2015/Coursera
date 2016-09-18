#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
using namespace std;

#define True 1
#define False 0

vector<vector<int>> list;
vector<vector<int>> rlist;
int n;

vector<int> reOrder;

void readData(){
	ifstream in("2sat6.txt");
	string line;
	getline(in, line);
	istringstream record(line);
	record >> n;
	list = vector<vector<int>>(2*n+1, vector<int>());
	rlist = vector<vector<int>>(2*n+1, vector<int>());
	reOrder = vector<int>(2*n+1);
	while(getline(in, line)){
		istringstream record(line);
		int v1, v2;
		record >> v1 >> v2;
		if(v1>0 && v2>0){
			list[v1+n].push_back(v2);
			list[v2+n].push_back(v1);
			rlist[v2].push_back(v1+n);
			rlist[v1].push_back(v2+n);
		}else if(v1>0 && v2<0){
			list[v1+n].push_back(n-v2);
			list[-v2].push_back(v1);
			rlist[n-v2].push_back(v1+n);
			rlist[v1].push_back(-v2);
		}else if(v1<0 && v2>0){
			list[-v1].push_back(v2);
			list[v2+n].push_back(n-v1);
			rlist[v2].push_back(-v1);
			rlist[n-v1].push_back(v2+n);
		}else{
			list[-v1].push_back(n-v2);
			list[-v2].push_back(n-v1);
			rlist[n-v2].push_back(-v1);
			rlist[n-v1].push_back(-v2);
		}
	}
}

vector<int> flag;
set<int> SCCset;
//generate magic order
void DFS_11(int v, int &count){
	flag[v] = 1;
	for(int i=0; i<rlist[v].size();++i)
		if(flag[rlist[v][i]] == 0)
			DFS_11(rlist[v][i],count);
	reOrder[++count] = v;
}
void DFS_1(){
	flag = vector<int>(2*n+1,0);
	int count = 0;
	for(int i=2*n;i>0;--i)
		if(flag[i] == 0)
			DFS_11(i, count);
}

//SCC
int DFS_22(int v){
	flag[v] = 1;
	if((v<=n&&SCCset.find(v+n)==SCCset.end())||(v>n&&SCCset.find(v-n)==SCCset.end()))
		SCCset.insert({v});
	else
		return False;
	for(int i=0;i<list[v].size();++i){
		if(flag[list[v][i]]==0)
			if(!DFS_22(list[v][i]))
				return False;
	}
	return True;
}
int DFS_2(){
	flag = vector<int>(2*n+1,0);
	for(int i=2*n;i>0;--i){
		if(flag[reOrder[i]]==0){
			SCCset.clear();
			if(!DFS_22(reOrder[i]))
				return False;
		}
	}
	return True;
}
int main(){
	readData();
	DFS_1();
	cout << DFS_2() << endl;
	return 0;
}
