#ifndef UNION_FIND_H
#define UNION_FIND_H
#include <vector>
using namespace std;
//lazy union_find by rank
struct data{
	int parent;
	int rank;
};

void init(vector<data> &arr, int size);
int find(vector<data> &arr, int i);
void runion(vector<data> &arr, int i, int j);
#endif
