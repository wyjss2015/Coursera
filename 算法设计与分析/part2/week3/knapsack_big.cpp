#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

struct item{
	int size, value;
};
vector<item> items;
int total;
int nums;

void readItems(){
	ifstream in("knapsack_big.txt");
	string line;
	getline(in, line);
	istringstream record(line);
	record >> total >> nums;
	item temp;
	temp.value = temp.size = 0;
	items.push_back(temp);
	while(getline(in, line)){
		istringstream record(line);
		item temp;
		record >> temp.value >> temp.size;
		items.push_back(temp);
	}
}

map<pair<int, int>, long long> book;
long long knapsack_big(int itemidx, int capacity){
	if(itemidx == 0)
		return 0;
	if(book.find(pair<int,int>(itemidx,capacity))!=book.end())
		return book[pair<int,int>(itemidx,capacity)];
	long long case1 = knapsack_big(itemidx-1, capacity);
	if(capacity < items[itemidx].size){
		if(book.find(pair<int,int>(itemidx,capacity))==book.end())
			book.insert(pair<pair<int,int>, int>(pair<int,int>(itemidx, capacity), case1));
		return case1;
	}
	long long case2 = knapsack_big(itemidx-1, capacity-items[itemidx].size)+items[itemidx].value;
	if(case1>case2){
		if(book.find(pair<int,int>(itemidx,capacity))==book.end())
			book.insert(pair<pair<int,int>, int>(pair<int,int>(itemidx, capacity), case1));
		return case1;
	}else{
		if(book.find(pair<int,int>(itemidx,capacity))==book.end())
			book.insert(pair<pair<int,int>, int>(pair<int,int>(itemidx, capacity), case2));
		return case2;
	}
}
int main(){
	readItems();
	cout << knapsack_big(nums,total) <<endl;
	return 0;
}
