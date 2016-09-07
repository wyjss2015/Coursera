#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <climits>
using namespace std;
int n;

void readGraph(vector<vector<int>> &d, vector<vector<int>> &d1){
	ifstream in("g3.txt");
	string line;
	int m;
	getline(in, line);
	istringstream record(line);
	record >> n >> m;
	d = vector<vector<int>>(n+1, vector<int>(n+1, 100000));
	d1 = vector<vector<int>>(n+1, vector<int>(n+1, 100000));
	while(getline(in, line)){
		istringstream record(line);
		int tail, head, weight;
		record >> tail >> head >> weight;
		d[tail][head] = weight;
		d1[tail][head] = weight;
	}
	for(int i=1;i<=n;++i){
		d[i][i] = 0;
		d1[i][i] = 0;
	}

/*	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j)
			cout << d[i][j] << " ";
		cout << endl;
	}*/
}

void floydWarshall(vector<vector<int>> &d, vector<vector<int>> &d1){
	for(int k=1; k<=n; ++k){
		for(int u=1; u<=n; ++u){
			for(int v=1; v<=n; ++v){
				if(k%2==1){
					if(d[u][v]>d[u][k]+d[k][v])
						d1[u][v] = d[u][k]+d[k][v];
					else
						d1[u][v] = d[u][v];
				}else{
					if(d1[u][v]>d1[u][k]+d1[k][v])
						d[u][v] = d1[u][k]+d1[k][v];
					else
						d[u][v] = d1[u][v];
				}
			}
		}
	}
}

int minLen(vector<vector<int>> &d, vector<vector<int>> &d1, int &min){
	min=INT_MAX;
	if(n%2==1){
		for(int i=1;i<=n;++i)
			if(d1[i][i]<0)
				return 0;
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j){
				if(i!=j && min>d1[i][j])
					min = d1[i][j];
			//	cout << d1[i][j] << " ";
			}
		//	cout << endl << endl;
		}
	}else{
		for(int i=1;i<=n;++i)
			if(d[i][i]<0)
				return 0;
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j){
				if(i!=j && min>d[i][j])
					min = d[i][j];
		//		cout << d[i][j] << " ";
			}
		//	cout << endl;
		}
	}
	return 1;
}
int main(){
	//DP表,两表交替相互存储前一个状态的值
	vector<vector<int>> d;
	vector<vector<int>> d1;
	//初始化
	readGraph(d, d1);
	floydWarshall(d, d1);
	//cout << endl;
	int min=INT_MAX;
	int flag = minLen(d, d1, min);

	//cout <<endl;

	if(flag==1)
		cout << min <<endl;
	else
		cout << "存在负环"<<endl;
	return 0;
}
