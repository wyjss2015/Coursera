#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct item{
	int size;
	int value;
};
vector<item> items;
int total;
int nums;

vector<vector<long long>> book;

void readItems(){
	ifstream in("knapsack1.txt");
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
	book = vector<vector<long long>>(nums+1, vector<long long>(total+1, 0));
}

void knapsack(){
	for(int i=1;i<=nums;++i){
		for(int j=1;j<=total;++j){
			if(j>=items[i].size){
				if(book[i-1][j]>book[i-1][j-items[i].size]+items[i].value)
					book[i][j] = book[i-1][j];
				else
					book[i][j] = book[i-1][j-items[i].size]+items[i].value;
			}else
				book[i][j] = book[i-1][j];
		}
	}
}
int main(){
	readItems();
	knapsack();
	cout << book[nums][total] << endl;
	return 0;
}
