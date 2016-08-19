#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
//pivot equal the first element of given arr
int choosePivot1(vector<int> &arr, int l, int r){
	return arr[l];
}
//pivot equal the final element of given arr
int choosePivot2(vector<int> &arr, int l, int r){
	int temp;
	temp = arr[l];
	arr[l] = arr[r];
	arr[r] = temp;
	return arr[l];
}
//pivot choosen using the "median-of-three" pivot rule
int choosePivot3(vector<int> &arr, int l, int r){
	int first, median, last;
	int medianIdx;
	int pivotIdx;
	int temp;

	first = arr[l];
	last = arr[r];
	medianIdx = (l+r)/2;
	median = arr[medianIdx];
	if((median<=first&&first<=last)||(last<=first&&first<=median))
		pivotIdx = l;
	else if((first<=median&&median<=last)||(last<=median&&median<=first))
		pivotIdx = medianIdx;
	else
		pivotIdx = r;
	if(pivotIdx!=l){
		temp = arr[l];
		arr[l] = arr[pivotIdx];
		arr[pivotIdx] = temp;
	}
	return arr[l];
}
void count_quickSort(vector<int> &arr, int l, int r, long long &counts, int (*pf)(vector<int>&arr, int, int)){
	int pivot;
	int i, j;
	int temp;
	if(r <= l)
		return;
	pivot = pf(arr, l, r);
	for(i=l+1,j=l+1;i<=r&&arr[i]<pivot;++i,++j)
		;
	if(i<=r){
		for(;j<=r;++j){
			if(arr[j]<pivot){
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
				++i;
			}
		}
	}
	temp = arr[i-1];
	arr[i-1] = arr[l];
	arr[l] = temp;
	counts = counts + r - l;
	count_quickSort(arr, l, i-2, counts, pf);
	count_quickSort(arr, i, r, counts, pf);
}


void countComparisons(vector<int> &arr){
	long long counts1, counts2, counts3;
	counts1 = counts2 = counts3 = 0;
	vector<int> arr1(arr.begin(), arr.end());
	vector<int> arr2(arr.begin(), arr.end());
	count_quickSort(arr, 0, arr.size()-1, counts1, choosePivot1);
	count_quickSort(arr1, 0, arr.size()-1, counts2, choosePivot2);
	count_quickSort(arr2, 0, arr.size()-1, counts3, choosePivot3);
	cout<<counts1<<'\n'<<counts2<<'\n'<<counts3<<endl;
}

int main(){
	ifstream in("QuickSort.txt");
	vector<int> arr;
	int temp;
	while(in>>temp)
		arr.push_back(temp);
	countComparisons(arr);
	return 0;
}
