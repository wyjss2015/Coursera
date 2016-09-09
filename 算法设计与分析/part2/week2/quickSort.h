#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

struct edge{
	int node1, node2;
	int weight;
};

void swap(vector<edge> &arr, int i, int j);
void pivot(vector<edge> &arr, int begin, int end);
int partition(vector<edge> &arr, int begin, int end);
void quickSort(vector<edge> &arr, int begin, int end);

#endif
