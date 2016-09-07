#include <iostream>
#include <vector>
#include <climits>
using namespace std;
/*
该程序是测试题第五题的答案
计算7个点（带频率，keys为1到7排序顺序）最优二叉查找树时间
*/
void init(double a[][8]){
	a[1][1] = .05;
	a[2][2] = .4;
	a[3][3] = .08;
	a[4][4] = .04;
	a[5][5] = .1;
	a[6][6] = .1;
	a[7][7] = .23;
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
