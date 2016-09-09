#include "union_find.h"
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
/*
idea:
1. map bits to label using hash table
2. for each node:
	flip 1 bit and check
	flip 2 bits and check
*/
vector<data> arr;
vector<int> VtoBit;
map<int, int> bitToV;
int n, bitnums;
int k;
//读取过程中顺带处理hamming distance == 0 的情况
void readData(){
	ifstream in("clustering_big.txt");
	string line;
	getline(in, line);
	istringstream record(line);
	record >> n >> bitnums;
	k = n;
	VtoBit.push_back(0);
	int cnt = 0;
	while(getline(in, line)){
		istringstream record(line);
		int temp;
		int val = 0;
		while(record >> temp){
			val <<= 1;
			val += temp;
		}
		if(bitToV.find(val)==bitToV.end()){
			VtoBit.push_back(val);
			bitToV.insert(pair<int, int>(val, ++cnt));
		}else{
			--k;
			--n;
		}
	}
}

int kruskal_big(){
	init(arr, n);
	int l=0;
	for(auto &bit: VtoBit){
		if(l==0){
			++l;
			continue;
		}
		for(int i=0;i<bitnums;++i){
			int x = 1;
			x <<= i;
			int temp = x ^ bit;
			if(bitToV.find(temp)!=bitToV.end() && find(arr,bitToV[temp])!=find(arr,bitToV[bit])){
				runion(arr, bitToV[temp], bitToV[bit]);
				--k;
			}
		}
	}

	l=0;
	for(auto &bit: VtoBit){
		if(l==0){
			++l;
			continue;
		}
		for(int i=0;i<bitnums;++i){
			for(int j=i+1;j<bitnums;++j){
				int x = 1, y = 1;
				x <<= i;
				y <<= j;
				int temp = x ^ bit;
				temp ^= y;
				if(bitToV.find(temp)!=bitToV.end() && find(arr,bitToV[temp])!=find(arr, bitToV[bit])){
					runion(arr, bitToV[temp], bitToV[bit]);
					--k;
				}
			}
		}
	}
	return k;
}
int main(){
	readData();
	cout << kruskal_big() << endl;
	return 0;
}
