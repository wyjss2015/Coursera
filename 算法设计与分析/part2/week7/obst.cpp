#include <iostream>
#include <vector>
#include <climits>
using namespace std;
/*
Consider an instance of the optimal binary search tree problem with 7 keys (say 1,2,3,4,5,6,7 in sorted order) and frequencies w1=.2,w2=.05,w3=.17,w4=.1,w5=.2,w6=.03,w7=.25. What is the minimum-possible average search time of a binary search tree with these keys?
*/
void init(double a[][8]){
	a[1][1] = .2;
	a[2][2] = .05;
	a[3][3] = .17;
	a[4][4] = .1;
	a[5][5] = .2;
	a[6][6] = .03;
	a[7][7] = .25;
}
void obst(double a[][8]){
	for(int k=1;k<7;++k){
		for(int i=1;i<8-k;++i){
			double min = 100.0;
			int j = i+k;
			double temp=0.0;
			for(int p=i;p<=j;++p)
				temp += a[p][p];
			for(int l=i;l<=j;++l){
				if(temp+a[i][l-1]+a[l+1][j]<min)
					min = temp+a[i][l-1]+a[l+1][j];
			}
			a[i][j] = min;
		}
	}
}
int main(){
	double a[8][8];
	for(int i=0;i<8;++i)
		for(int j=0;j<8;++j)
			a[i][j] = .0;
	init(a);
	obst(a);
	cout << a[1][7]<<endl;
	for(int i=1;i<8;++i){
		for(int j=1; j<8; ++j)
			cout << a[i][j] << " ";
		cout << endl;
	}
	return 0;
}
