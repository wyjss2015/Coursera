#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

struct job{
	double dif;
	int weight;
	int length;
};

void readData(vector<job> &jobs){
	ifstream in("jobs.txt");
	string total;
	getline(in, total);
	string line;
	while(getline(in, line)){
		istringstream record(line);
		job temp;
		record >> temp.weight >> temp.length;
		//temp.dif = temp.weight - temp.length;
		temp.dif = static_cast<double>(temp.weight) / temp.length;
		jobs.push_back(temp);
	}
}

void swap(vector<job> &jobs, int i, int j){
	job temp;
	temp = jobs[i];
	jobs[i] = jobs[j];
	jobs[j] = temp;
}
void pivot(vector<job> &jobs, int l, int r){
	int lvalue = jobs[l].dif;
	int rvalue = jobs[r].dif;
	int m = (l+r)/2;
	int mvalue = jobs[m].dif;
	if((mvalue>=lvalue&&mvalue<=rvalue)||(mvalue>=rvalue&&mvalue<=lvalue))
		swap(jobs, l, m);
	else if((rvalue>=lvalue&&rvalue<=mvalue)||(rvalue>=mvalue&&rvalue<=lvalue))
		swap(jobs, l, r);
}
int partition(vector<job> &jobs, int l, int r){
	int i=l, j=l+1;
	for(;j<=r&&(jobs[j].dif>jobs[l].dif||(jobs[j].dif==jobs[l].dif&&jobs[j].weight>jobs[l].weight));++i, ++j)
		;
	for(;j<=r;++j)
		if(jobs[j].dif>jobs[l].dif||(jobs[j].dif==jobs[l].dif&&jobs[j].weight>jobs[l].weight))
			swap(jobs, ++i, j);
	swap(jobs, l, i);
	return i;
}
void quickSort(vector<job> &jobs, int l, int r){
	if(l>=r) return;
	pivot(jobs, l, r);
	int i = partition(jobs, l, r);
	quickSort(jobs, l, i-1);
	quickSort(jobs, i+1, r);
}
long long weightedSum(vector<job> &jobs){
	long long sum = 0;
	long long length = 0;
	for(auto &job: jobs){
		length += job.length;
		sum = sum + job.weight * length;
	}
	return sum;
}
int main(){
	vector<job> jobs;
	readData(jobs);
	int r = jobs.size();
	quickSort(jobs, 0, r-1);
	cout << weightedSum(jobs) << endl;
	return 0;
}
