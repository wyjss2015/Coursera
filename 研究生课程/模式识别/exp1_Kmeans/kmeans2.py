#! -*- coding:utf8 -*-

from __future__ import division
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import csv as csv
import copy

class kmeans(object):
	def __init__(self,data,k):
		self.data = np.array(data).astype(float)
		self.u = self.data[np.random.randint(0,self.data.shape[0],k),:]
		self.label = np.random.randint(0,k,self.data.shape[0])

	def EM(self):
		e = 1
		while e > 1e-16:
			#E step
			i=0
			while i < self.data.shape[0]:
				temp0 = (self.data[i,:]-self.u)**2
				temp1 = np.sqrt(np.sum(temp0, axis=1))
				self.label[i] = np.argmin(temp1)
				i += 1
			#M step
			preU = copy.deepcopy(self.u)
			j=0
			while j < self.u.shape[0]:
				n = self.label[self.label == j].size
				self.u[j] = np.sum(self.data[self.label==j,:], axis=0)/n
				j += 1
			e = np.sum((preU-self.u)**2)
	#		print e

def readData(data,file):
	csv_object = csv.reader(open(file,'rb'))
	for row in csv_object:
		data.append(row)
	
if __name__ == '__main__':
	data = []
	label = []
	readData(data,'ClusterSamples.csv')
	readData(label,'SampleLabels.csv')
	label = np.array(label).astype(int).transpose()
	label = label[0,:]

	test = kmeans(data, 10)
	test.EM()

	labelFrame = np.zeros((10,10)).astype(int)
	i = 0
	while i < 10:
		j = 0
		while j < 10:
			temp0 = np.arange(label.size)[label==i]
			temp1 = test.label[temp0]
			labelFrame[i,j] = temp1[temp1==j].size
			j += 1
		i += 1
	df = pd.DataFrame(labelFrame,index=range(10), columns=range(10))
	print df
