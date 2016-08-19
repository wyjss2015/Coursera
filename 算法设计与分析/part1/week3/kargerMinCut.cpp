#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include <map>
#include <utility>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

struct vecArc{
	int vec;
	vector<int> arc;
};
vector<pair<int, int>> uArc;
map<int, vector<int>> vecList;

void createGraph(){
	ifstream in("kargerMinCut.txt");
	string line;
	set<pair<int, int>> isinuArc;
	while(getline(in, line)){
		istringstream record(line);
		int temp, node;
		record >> node;
		vecList[node] = vector<int>();
		while(record >> temp){
			vecList[node].push_back(temp);
			if(isinuArc.find(pair<int, int>(node, temp))==isinuArc.end()&&isinuArc.find(pair<int, int>(temp, node))==isinuArc.end()){
				isinuArc.insert(pair<int, int>(node, temp));
				uArc.push_back(pair<int, int>(node, temp));
			}
		}
	}
}
default_random_engine e;
int countMinCutEdges(){	
	int n = static_cast<int>(vecList.size());
	for(int i=0;i<n-2;++i){
		uniform_int_distribution<int> u(0, n-1);
		int arc = u(e);
		int v1, v2;
		v1 = uArc[arc].first;
		v2 = uArc[arc].second;
		//del v1->v2 arc
		vecList[v1].erase(remove(vecList[v1].begin(), vecList[v1].end(), v2), vecList[v1].end());
		//del v2->v1 arc
		vecList[v2].erase(remove(vecList[v2].begin(), vecList[v2].end(), v1), vecList[v2].end());
		//link  node adjected to v2 to v1 (equal to combine the two nodes), then delete v2
		for(const auto &temp : vecList[v2]){
			vecList[v1].push_back(temp);
			for(auto &temp2 : vecList[temp])
				if(temp2 == v2)
					temp2 = v1;
		}
		vecList.erase(v2);
		//fix uArc
		for(vector<pair<int, int>>::iterator iter=uArc.begin(); iter!=uArc.end();){
			if(iter->first==v2)
				iter->first = v1;
			else if(iter->second == v2)
				iter->second = v1;
			if(iter->first == iter->second)
				iter = uArc.erase(iter);
			else
				++iter;
		}
	}
	return uArc.size();
}

void clearup(){
	vecList.clear();
	uArc.clear();
}
int main(){
	int min = 100;
	int temp;
	for(int i=0;i<40000;++i){
		createGraph();
		e.seed(i);
		temp = countMinCutEdges();
		clearup();
		if(temp<min){
			min = temp;
			cout<<min<<endl;
		}
	}
	cout<<min<<endl;
	return 0;
	
}
