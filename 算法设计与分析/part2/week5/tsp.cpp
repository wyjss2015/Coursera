#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
#include <cfloat>
using namespace std;


/*
 * 1. 生成顶点集的所有子集
 * 2. 对该子集的集合进行排序
 * 3. 运行动态规划算法
 *
 * 注意:25点4G内存不足，点集（0,1,...,24）由于删除点10和点9分别计算剩下的24的tour lastNode都为11，利用9,10,11三点三角形可计算出最终结果
 *
 */
struct vertex{
	float x, y;
};
vector<vertex> vertexs;
int n;

void readData(){
	ifstream in("test.txt");
	string line;
	getline(in, line);
	istringstream record(line);
	record >> n;
	while(getline(in, line)){
		istringstream record(line);
		vertex temp;
		record >> temp.x >> temp.y;
		vertexs.push_back(temp);
	}
}

map<pair<int, int>, float> dist;

void calDist(){
	for(int i=0;i<n;++i){
		for(int j=i+1;j<n;++j){
			float diffX = vertexs[i].x - vertexs[j].x;
			float diffY = vertexs[i].y - vertexs[j].y;
			float distance = sqrt(pow(diffX,2)+pow(diffY,2));
			auto temp1 = pair<int ,int>(i,j);
			auto temp2 = pair<int, int>(j,i);
			dist.insert(pair<pair<int,int>,float>(temp1,distance));
			dist.insert(pair<pair<int,int>,float>(temp2,distance));
		}
	}
}


//利用24位bit表示路径中的点集

struct path{
	int p;
	int nums;
};
vector<path> paths;

//计算多少bit等于1
int count1Nums(int num){
	int count = 0;
	while(num){
		++count;
		num &= (num-1);
	}
	return count;
}

//得到所有子集包含的点数

bool comp(const path &temp1, const path &temp2){
	return temp1.nums < temp2.nums;
}
void genPath(){
	int max = 1;
	max <<= n;
	max -= 1;
	for(int i=0;i<=max;++i){
		path temp;
		temp.p = i;
		temp.nums = count1Nums(i);
		paths.push_back(temp);
	}
	sort(paths.begin(), paths.end(), comp);
}

float tsp_dp(){
	map<pair<int,int>,float> dpList, dpList1;

	//base case
	int limit = 1;
	limit <<= n;
	int i, j;
	for(i=0;i<limit&&paths[i].nums<2;++i)
		;
	for(;i<limit&&paths[i].nums<3;++i){
		if(paths[i].p&1){
			for(j=1;j<n;++j){
				int w = 1;
				w <<= j;
				if(w&paths[i].p)
					break;
			}
			dpList[pair<int,int>(paths[i].p, j)] = dist[pair<int,int>(0,j)];
		}
	}
	int flag = 0;
	float min;
	for(int m=4;m<=n+1;++m){
		for(;i<limit&&paths[i].nums<m;++i){
			if(paths[i].p&1){
				for(j=1;j<n;++j){
					int w=1;
					w <<= j;
					if(w&paths[i].p){
						int tempP = paths[i].p ^ w;
						min = DBL_MAX;
						for(int k=1;k<n;++k){
							int w2 = 1;
							w2 <<= k;
							if(flag==0&&(w2&tempP) && (min>dist[pair<int,int>(k,j)]+dpList[pair<int,int>(tempP,k)]))
								min = dist[pair<int,int>(k,j)]+dpList[pair<int,int>(tempP,k)];
							else if(flag==1&&(w2&tempP) && (min>dist[pair<int,int>(k,j)]+dpList1[pair<int,int>(tempP,k)]))
								min = dist[pair<int,int>(k,j)]+dpList1[pair<int,int>(tempP,k)];

						}
						if(flag==0)
							dpList1[pair<int,int>(paths[i].p,j)] = min;
						else if(flag==1)
							dpList[pair<int,int>(paths[i].p,j)] = min;
					}
				}
			}
		}
		if(flag == 0){
			dpList.clear();
			flag = 1;
			cout << m-1 << " " << dpList1.size() << endl;
		}
		else{
			dpList1.clear();
			flag = 0;
			cout << m-1 << " " << dpList.size() << endl;
		}
	}
	float result = DBL_MAX;
	int temp = 1;
	temp <<= n;
	temp -= 1;
	int lastNode;
	for(int l=1;l<n;++l){
		if(flag == 0 && dpList[pair<int,int>(temp,l)]+dist[pair<int,int>(l,0)]<result){
			result = dpList[pair<int,int>(temp,l)] + dist[pair<int,int>(l,0)];
			lastNode = l;
		}
		else if(flag == 1 && dpList1[pair<int,int>(temp,l)]+dist[pair<int,int>(l,0)]<result){
			result = dpList1[pair<int,int>(temp,l)]+dist[pair<int,int>(l,0)];
			lastNode = l;
		}
	}
	cout << "最后一个点是:" << lastNode << endl;
	return result;
}
int main(){
	readData();
	calDist();
	genPath();
	cout << tsp_dp() << endl;
	return 0;
}
