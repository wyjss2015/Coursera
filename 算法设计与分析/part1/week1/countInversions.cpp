#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

long long countInversions(vector<int> &arr, int l, int r){
	if(l == r)
		return 0;
	int mid, leftInversions, rightInversions;
	mid = (l+r)/2;
	leftInversions = countInversions(arr, l, mid);
	rightInversions = countInversions(arr, mid+1, r);

	vector<int> tempArr1(arr.begin()+l, arr.begin()+mid+1);
	vector<int> tempArr2(arr.begin()+mid+1, arr.begin()+r+1);
	int i, j, k;
	long long cnt=0;
	int leftSize, rightSize;
	leftSize = tempArr1.size();
	rightSize = tempArr2.size();
	for(i=0,j=0,k=l;i<leftSize&&j<rightSize;++k){
		if(tempArr1[i]<tempArr2[j])
			arr[k] = tempArr1[i++];
		else{
			arr[k] = tempArr2[j++];
			cnt += leftSize-i;
		}
	}
	if(i>=leftSize)
		for(;j<rightSize;++j,++k)
			arr[k] = tempArr2[j];
	if(j>=rightSize)
		for(;i<leftSize;++i,++k)
			arr[k] = tempArr1[i];
	return leftInversions+rightInversions+cnt;
}
int main(){
	vector<int> arr;
	int temp;
	ifstream in("integerArray.txt");
	while(in >> temp)
		arr.push_back(temp);
	cout << countInversions(arr, 0, arr.size()-1) << endl;
	return 0;
}
