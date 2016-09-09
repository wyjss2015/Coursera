#include "quickSort.h"

void swap(vector<edge> &arr, int i, int j){
	edge temp;
	temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void pivot(vector<edge> &arr, int begin, int end){
	int bval = arr[begin].weight;
	int eval = arr[end].weight;
	int m = (begin+end)/2;
	int mval = arr[m].weight;
	if((mval>=bval&&mval<=mval)||(mval>=eval&&mval<=bval))
		swap(arr, begin, m);
	else if((eval>=bval&&eval<=mval)||(eval>=mval&&eval<=bval))
		swap(arr, begin, end);
}

int partition(vector<edge> &arr, int begin, int end){
	int i = begin, j = begin+1;
	for(;j<=end&&arr[j].weight<=arr[begin].weight;++i,++j)
		;
	for(;j<=end;++j)
		if(arr[j].weight<=arr[begin].weight)
			swap(arr, ++i, j);
	swap(arr, i, begin);
	return i;
}

void quickSort(vector<edge> &arr, int begin, int end){
	if(begin>=end)
		return;
	pivot(arr, begin, end);
	int i = partition(arr, begin, end);
	quickSort(arr, begin, i-1);
	quickSort(arr, i+1, end);
}
