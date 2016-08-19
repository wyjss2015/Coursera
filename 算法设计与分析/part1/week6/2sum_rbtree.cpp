#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
using namespace std;

set<long long> hashTable;

void createHashTable(){
	ifstream in("2sum.txt");
	long long val;
	while(in >> val)
		if(hashTable.find(val)==hashTable.end())
			hashTable.insert({val});
}

int count(long long l, long long r){
	int cnt = 0;
	for(long long i=l; i<=r; ++i){
		auto val = hashTable.cbegin();
		while(val!=hashTable.cend()){
			if(hashTable.find(i-*val)!=hashTable.end()){
				cout << ++cnt <<i<<" " <<*val<<" "<<i-*val<< endl;
				break;
			}
			++val;
		}
	}
	return cnt;
}

int main(){
	createHashTable();
	cout << count(-10000, 10000) << endl;
	return 0;
}
