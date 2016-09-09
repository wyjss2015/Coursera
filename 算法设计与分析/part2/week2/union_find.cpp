#include "union_find.h"

void init(vector<data> &arr, int size){
	arr = vector<data>(size+1);
	for(int i=1;i<=size;++i){
		arr[i].parent = i;
		arr[i].rank = 0;
	}
}

int find(vector<data> &arr, int i){
	if(arr[i].parent==i)
		return i;
	return find(arr, arr[i].parent);
}

void runion(vector<data> &arr, int i, int j){
	int rooti = find(arr, i);
	int rootj = find(arr, j);
	if(arr[rooti].rank>arr[rootj].rank)
		arr[rootj].parent = rooti;
	else if(arr[rooti].rank<arr[rootj].rank)
		arr[rooti].parent = rootj;
	else{
		arr[rootj].parent = rooti;
		arr[rooti].rank++;
	}
}
