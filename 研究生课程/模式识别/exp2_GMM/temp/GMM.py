#! -*- coding:utf8 -*-
from __future__ import division
import numpy as np
import matplotlib.pyplot as plt
import csv as csv
import copy

class GMM(object):
	def __init__(self,data,k,dim):
		self.data = np.array(data).astype(float)
		self.k = k
		self.dim = dim

		self.a = np.random.rand(k)
		self.a /= np.sum(self.a)

		tempMax = np.amax(self.data)
		tempMin = np.amin(self.data)
		self.mu = np.random.uniform(tempMin-1,tempMax+1,k*dim).reshape(k,dim)

		self.sigma = np.zeros((k,dim,dim))
		self.sigmaI = np.zeros((k,dim,dim))
		i=0
		while i<k:
			self.sigma[i] = np.diag(np.random.rand(dim)+0.5)
			#self.sigma[i] = np.triu(self.sigma[i])
			#self.sigma[i] += self.sigma[i].T - np.diag(self.sigma[i].diagonal())
			i += 1
		i=0
		while i<k:
			self.sigmaI[i] = np.array(np.mat(self.sigma[i]).I)
			i += 1

		self.pLabel = np.random.rand(self.data.shape[0],k)
		tempSum = np.sum(self.pLabel,axis=1)
		self.pLabel = np.divide(self.pLabel.transpose(),tempSum).transpose()

	def calNormal(self, x):
		tempLabel = np.zeros(self.k)
		tempSum = 0.0
		i=0
		while i<self.k:
			tempLabel[i] = 1.0/((2*np.pi)**(self.dim/2)*(np.linalg.det(self.sigma[i])**0.5))*\
			np.exp((-0.5)*np.dot(np.dot((x-self.mu[i]),self.sigmaI[i]),(x-self.mu[i])))*\
			self.a[i]
			tempSum += tempLabel[i]
			i += 1
		tempLabel /= tempSum
		return tempLabel

	def train(self):
		e = 1
		while e > 1e-30:
			#E step
			i = 0
			while i<self.data.shape[0]:
				self.pLabel[i] = self.calNormal(self.data[i])
				i += 1
			#M step
			tempA = copy.deepcopy(self.a)
			self.a = np.mean(self.pLabel,axis=0)

			tempMu = copy.deepcopy(self.mu)
			i=0
			while i<self.k:
				self.mu[i] = (np.sum(self.pLabel[:,i].reshape(self.pLabel.shape[0],1)*self.data,axis=0) / np.sum(self.pLabel[:,i]))[0]
				i += 1
		
			tempSigma = copy.deepcopy(self.sigma)
			i=0
			while i<self.k:
				tempDif = self.data - self.mu[i]
				self.sigma[i] = np.dot(tempDif.T, tempDif*self.pLabel[:,i].reshape(self.pLabel.shape[0],1)) / np.sum(self.pLabel[:,i])
				i += 1

			i=0
			while i<self.k:
				self.sigmaI[i] = np.array(np.mat(self.sigma[i]).I)
				i += 1
			#终止条件判断
			e = np.sum((self.a-tempA)**2) + np.sum((self.mu-tempMu)**2) + np.sum((self.sigma-tempSigma)**2)
			print e
	
	def plot(self,data,label):
		num = data.shape[0]
		idx1 = label[:,0].reshape(num)>0.5
		idx2 = label[:,0].reshape(num)<=0.5
		x1 = data[idx1,0]
		y1 = data[idx1,1]
		x2 = data[idx2,0]
		y2 = data[idx2,1]
	#	plt.axis([-5,25,0,25])
		plt.plot(x1,y1,'ro',ms=2)
		plt.plot(x2,y2,'bo',ms=2)
		plt.plot(self.mu[0,0],self.mu[0,1],'rx',ms=15)
		plt.plot(self.mu[1,0],self.mu[1,1],'bx',ms=15)
		plt.show()

	def predict(self,data):
		testData = np.array(data).astype(float)
		predictLabel = np.zeros((testData.shape[0],self.k))
		i = 0
		while i<testData.shape[0]:
			predictLabel[i] = self.calNormal(testData[i])
			i += 1
		return predictLabel
	

def readData(data,file):
	csv_object = csv.reader(open(file,'rb'))
	for row in csv_object:
		data.append(row)

if __name__ == '__main__':
	trainData = []
	testData = []
	readData(trainData,'Train2.csv')
	readData(testData,'Test2.csv')

	model = GMM(trainData,2,2)
	model.train()
	print '\n'
	print model.a
	print '\n'
	print model.mu
	print '\n'
	print model.sigma
#	model.plot(model.data,model.pLabel)
	testData = np.array(testData).astype(float)
	label = model.predict(testData)
	model.plot(testData,label)
