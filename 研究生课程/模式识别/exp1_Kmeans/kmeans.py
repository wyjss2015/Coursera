#! -*- coding:utf8 -*-

from __future__ import division
import numpy as np
import matplotlib.pyplot as plt
import copy

class kmeans(object):
	def __init__(self,data):
		self.data = np.array(data).astype(float)
		self.u = self.data[np.random.randint(0,self.data.shape[0],2),:]
		self.label = np.random.randint(0,2,self.data.shape[0])

	def plot(self):
		x0 = self.data[self.label==0, 0]
		y0 = self.data[self.label==0, 1]
		x1 = self.data[self.label==1, 0]
		y1 = self.data[self.label==1, 1]
		
		plt.axis([-1,10,-1,10])
		plt.plot(x0,y0,'ro')
		plt.plot(x1,y1,'bo')
		plt.plot(self.u[0][0],self.u[0][1],'rx',ms=10)
		plt.plot(self.u[1][0],self.u[1][1],'bx',ms=10)
		plt.show()
	
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
	
if __name__ == '__main__':
	data = [[0,0],[1,0],[0,1],[1,1],
			[2,1],[1,2],[2,2],[3,2],
			[6,6],[7,6],[8,6],[7,7],
			[8,7],[9,7],[7,8],[8,8],
			[9,8],[8,9],[9,9]]
	test = kmeans(data)
	test.EM()
	test.plot()
	print test.label
