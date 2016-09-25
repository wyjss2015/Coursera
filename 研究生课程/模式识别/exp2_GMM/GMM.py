#! -*- coding:utf8 -*-
from __future__ import division
import numpy as np
import csv as csv
import copy

class GMM(object):
	#==============
	#@parameter
	#data: 训练数据
	#k: 高斯数
	#dim: 维度
	#==============
	def __init__(self, data, k, dim):
		self.data = np.array(data).astype(float)
		self.k = k
		self.dim = dim

		self.a = np.random.rand(k)
		self.a /= np.sum(self.a)
		if len(self.data) > 0:
			tempMax = np.amax(self.data)
			tempMin = np.amin(self.data)
			self.mu = np.random.uniform(tempMin-1, tempMax+1, k*dim).reshape(k,dim)
		
		self.sigma = np.zeros((k,dim,dim))
		self.sigmaI = np.zeros((k,dim,dim))
		i=0
		while i<k:
			self.sigma[i] = np.diag(np.random.rand(dim)+1e+10)
			i += 1

		i=0
		while i<k:
			self.sigmaI[i] = np.array(np.mat(self.sigma[i]).I)
			i += 1

		self.P = np.random.rand(self.data.shape[0], k)
		tempSum = np.sum(self.P, axis=1)
		self.P = np.divide(self.P.T, tempSum).T
	
	#计算P(w|x)
	def calP(self, x):
		tempP = np.zeros(self.k)
		tempSum = 0.0
		i=0
		while i<self.k:
			tempP[i] = 1.0/((2*np.pi)**(self.dim/2)*(np.linalg.det(self.sigma[i])**0.5))*\
			np.exp((-0.5)*np.dot(np.dot((x-self.mu[i]),self.sigmaI[i]),(x-self.mu[i])))*\
			self.a[i]
			tempSum += tempP[i]
			i += 1
		tempP /= tempSum
		return tempP

	def train(self):
		e = 1
		while e > 1e-10:
			#E step
			i = 0
			while i < self.data.shape[0]:
				self.P[i] = self.calP(self.data[i])
				i += 1
			#M step
			tempA = copy.deepcopy(self.a)
			self.a = np.mean(self.P, axis=0)

			tempMu = copy.deepcopy(self.mu)
			i = 0
			while i<self.k:
				self.mu[i] = (np.sum(self.P[:, i].reshape(self.P.shape[0],1)*self.data, axis=0) / np.sum(self.P[:, i]))[0]
				i += 1

			tempSigma = copy.deepcopy(self.sigma)
			i = 0
			while i<self.k:
				tempDif = self.data - self.mu[i]
				self.sigma[i] = np.dot(tempDif.T, tempDif*self.P[:,i].reshape(self.P.shape[0], 1)) / np.sum(self.P[:,i])
				i += 1

			i = 0
			while i<self.k:
				self.sigmaI[i] = np.array(np.mat(self.sigma[i]).I)
				i += 1

			#终止条件判断
			e = np.sum((self.a-tempA)**2) + np.sum((self.mu-tempMu)**2)+np.sum((self.sigma-tempSigma)**2)
			print e
	#计算概率
	def calPro(self, x):
		tempSum = 0.0
		i = 0
		while i < self.k:
			tempSum += 1.0/((2*np.pi)**(self.dim/2)*(np.linalg.det(self.sigma[i])**0.5))*\
			np.exp((-0.5)*np.dot(np.dot((x-self.mu[i]),self.sigmaI[i]),(x-self.mu[i])))*\
			self.a[i]
			i += 1
		return tempSum

	#保存参数
	def savePara(self, aFile, muFile, sigmaFile):
		writer1 = csv.writer(open(aFile, 'wb'))
		writer1.writerow(self.a)
		writer2 = csv.writer(open(muFile, 'wb'))
		for row in self.mu:
			writer2.writerow(row)
		writer3 = csv.writer(open(sigmaFile, 'wb'))
		for row in self.sigma:
			row = row.reshape(1, row.size)[0]
			writer3.writerow(row)

	#加载参数
	def loadPara(self, aFile, muFile, sigmaFile):
		tempA = []
		tempMu = []
		tempSigma = []
		readData(tempA, aFile)
		readData(tempMu, muFile)
		readData(tempSigma, sigmaFile)

		self.a = np.array(tempA[0]).astype(float)
		self.mu = np.array(tempMu).astype(float)
		i = 0
		while i<self.k:
			self.sigma[i] = np.array(tempSigma[i]).reshape(self.dim, self.dim)
			i += 1
		self.sigma.astype(float)
		i = 0
		while i<self.k:
			self.sigmaI[i] = np.array(np.mat(self.sigma[i]).I)
			i += 1

#读取数据
def readData(data, file):
	reader = csv.reader(open(file,'rb'))
	for row in reader:
		data.append(row)

#预测
def predict(testData, modelSet, w):
	testData = np.array(testData).astype(float)
	predictPro = np.zeros((testData.shape[0], len(w)))
	i = 0
	while i < testData.shape[0]:
		j = 0
		while j < len(w):
			predictPro[i, j] = modelSet[j].calPro(testData[i])*w[j]
			j += 1
		i += 1
	return np.argmax(predictPro, axis=1)

def getAccuracy(l):
	idx0 = l==0
	idx1 = l==1
	temp = np.ones(len(l))
	total0 = np.sum(temp[idx0])
	total1 = np.sum(temp[idx1])
	if total0 > total1:
		return total0 / (total0+total1)
	else:
		return total1 / (total1+total0)

def MnistDataDivide(MnistData, MnistLabel):
	MnistData = np.array(MnistData).astype(float)
	MnistLabel = np.array(MnistLabel).T[0].astype(float)
	data = []
	i = 0
	while i<10:
		idx = MnistLabel == i
		data.append(MnistData[idx])
		i += 1
	return data

#比较预测标签和真实标签，返回正确识别率
def compare(predictMnistLabel, MnistLabel):
	MnistLabel = np.array(MnistLabel).T[0].astype(float)
	temp = np.ones(MnistLabel.shape[0])
	return np.sum(temp[predictMnistLabel == MnistLabel]) / MnistLabel.shape[0]

if __name__ == '__main__':
#==========================
#仿真数据测试部分
#==========================
	#trainData1 = []
	#trainData2 = []
	#testData1 = []
	#testData2 = []
#	readData(trainData1, 'Train1.csv')
#	readData(trainData2, 'Train2.csv')
	#readData(testData1, 'Test1.csv')
	#readData(testData2, 'Test2.csv')

	#model1 = GMM(trainData1, 2, 2)
	#model2 = GMM(trainData2, 2, 2)

#	model1.train()
#	model2.train()

#	model1.savePara('para/a1.csv','para/mu1.csv','para/sigma1.csv')
#	model2.savePara('para/a2.csv','para/mu2.csv','para/sigma2.csv')

	#model1.loadPara('para/a1.csv','para/mu1.csv','para/sigma1.csv')
	#model2.loadPara('para/a2.csv','para/mu2.csv','para/sigma2.csv')

	#modelSet = [model1, model2]
	#w = np.array([0.5, 0.5])

	#print getAccuracy(predict(testData1, modelSet, w))
	#print getAccuracy(predict(testData2, modelSet, w))

#==========================
#MNIST数据集测试部分
#==========================
	trainMnistData = []
	trainMnistLabel = []
	testMnistData = []
	testMnistLabel = []

	readData(trainMnistData, 'TrainSamples.csv')
	readData(testMnistData, 'TestSamples.csv')
	readData(trainMnistLabel, 'TrainLabels.csv')
	readData(testMnistLabel, 'TestLabels.csv')
	
	trainMnistDataSet = MnistDataDivide(trainMnistData, trainMnistLabel)
	
	model0 = GMM(trainMnistDataSet[0], 5, 17)
	model1 = GMM(trainMnistDataSet[1], 5, 17)
	model2 = GMM(trainMnistDataSet[2], 5, 17)
	model3 = GMM(trainMnistDataSet[3], 5, 17)
	model4 = GMM(trainMnistDataSet[4], 5, 17)
	model5 = GMM(trainMnistDataSet[5], 5, 17)
	model6 = GMM(trainMnistDataSet[6], 5, 17)
	model7 = GMM(trainMnistDataSet[7], 5, 17)
	model8 = GMM(trainMnistDataSet[8], 5, 17)
	model9 = GMM(trainMnistDataSet[9], 5, 17)

#	model0.train()
#	model1.train()
#	model2.train()
#	model3.train()
#	model4.train()
#	model5.train()
#	model6.train()
#	model7.train()
#	model8.train()
#	model9.train()

#	model0.savePara('MnistPara/a5_0.csv', 'MnistPara/mu5_0.csv', 'MnistPara/sigma5_0.csv')
#	model1.savePara('MnistPara/a5_1.csv', 'MnistPara/mu5_1.csv', 'MnistPara/sigma5_1.csv')
#	model2.savePara('MnistPara/a5_2.csv', 'MnistPara/mu5_2.csv', 'MnistPara/sigma5_2.csv')
#	model3.savePara('MnistPara/a5_3.csv', 'MnistPara/mu5_3.csv', 'MnistPara/sigma5_3.csv')
#	model4.savePara('MnistPara/a5_4.csv', 'MnistPara/mu5_4.csv', 'MnistPara/sigma5_4.csv')
#	model5.savePara('MnistPara/a5_5.csv', 'MnistPara/mu5_5.csv', 'MnistPara/sigma5_5.csv')
#	model6.savePara('MnistPara/a5_6.csv', 'MnistPara/mu5_6.csv', 'MnistPara/sigma5_6.csv')
#	model7.savePara('MnistPara/a5_7.csv', 'MnistPara/mu5_7.csv', 'MnistPara/sigma5_7.csv')
#	model8.savePara('MnistPara/a5_8.csv', 'MnistPara/mu5_8.csv', 'MnistPara/sigma5_8.csv')
#	model9.savePara('MnistPara/a5_9.csv', 'MnistPara/mu5_9.csv', 'MnistPara/sigma5_9.csv')

	model0.loadPara('MnistPara/a5_0.csv', 'MnistPara/mu5_0.csv', 'MnistPara/sigma5_0.csv')
	model1.loadPara('MnistPara/a5_1.csv', 'MnistPara/mu5_1.csv', 'MnistPara/sigma5_1.csv')
	model2.loadPara('MnistPara/a5_2.csv', 'MnistPara/mu5_2.csv', 'MnistPara/sigma5_2.csv')
	model3.loadPara('MnistPara/a5_3.csv', 'MnistPara/mu5_3.csv', 'MnistPara/sigma5_3.csv')
	model4.loadPara('MnistPara/a5_4.csv', 'MnistPara/mu5_4.csv', 'MnistPara/sigma5_4.csv')
	model5.loadPara('MnistPara/a5_5.csv', 'MnistPara/mu5_5.csv', 'MnistPara/sigma5_5.csv')
	model6.loadPara('MnistPara/a5_6.csv', 'MnistPara/mu5_6.csv', 'MnistPara/sigma5_6.csv')
	model7.loadPara('MnistPara/a5_7.csv', 'MnistPara/mu5_7.csv', 'MnistPara/sigma5_7.csv')
	model8.loadPara('MnistPara/a5_8.csv', 'MnistPara/mu5_8.csv', 'MnistPara/sigma5_8.csv')
	model9.loadPara('MnistPara/a5_9.csv', 'MnistPara/mu5_9.csv', 'MnistPara/sigma5_9.csv')

	modelSet = [model0, model1, model2, model3, model4, model5, model6, model7, model8, model9]
	w = np.array([0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1])
	predictLabel = predict(testMnistData, modelSet, w)
	print compare(predictLabel, testMnistLabel)
