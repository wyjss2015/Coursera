#! -*- coding:utf8 -*-
from __future__ import division
import numpy as np
import matplotlib.pyplot as plt
import csv as csv
import copy

class GMM(object):
	def __init__(self,data,label,k,dim):
		self.data = np.array(data).astype(float)
		self.label = np.array(label).T[0].astype(float)
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
			self.sigma[i] = np.diag(np.random.rand(dim)+1e+10)
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

		self.gmmLabel = np.random.randint(0,k,self.data.shape[0])

		self.gmmLabel2label = np.arange(k)
	
	#=============================
	#结合标签对聚类结果进行分类
	#包含两步:
	# 1:归类
	# 2:每一类归到标签较多的类
	#============================
	def tagger(self):
		#1st step
		tempLabel = np.argmax(self.pLabel,axis=1)
		#2nd step
		i=0
		while i<self.k:
			l = np.zeros(self.k)
			temp = self.label[tempLabel==i]
			for c in temp:
				l[c] += 1
			self.gmmLabel[tempLabel==i] = np.argmax(l)
			self.gmmLabel2label[i] = np.argmax(l)
			i += 1

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
		e = self.data.shape[0]
		tempE = e+4
		iter = 0
		while e>0 and (tempE-e>3 or iter<5):
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
			tempE = e
			self.tagger()
			tmp = np.ones(self.data.shape[0])
			e = np.sum(tmp[self.gmmLabel!=self.label])
			if tempE-e <=3:
				iter += 1
			else:
				iter = 0
			#e = np.sum((self.a-tempA)**2) + np.sum((self.mu-tempMu)**2) + np.sum((self.sigma-tempSigma)**2)
			print e
	
	def predict(self,data,label):
		testData = np.array(data).astype(float)
		testLabel = np.array(label).T[0].astype(int)

		tempPredictLabel = np.zeros((testData.shape[0],self.k))
		i = 0
		while i<testData.shape[0]:
			tempPredictLabel[i] = self.calNormal(testData[i])
			i += 1
		predictLabel = np.argmax(tempPredictLabel,axis=1)
		predictLabel = self.gmmLabel2label[predictLabel]

		tmp = np.ones(testData.shape[0])
		error = np.sum(tmp[predictLabel!=testLabel])
		return error

	def essemblePredict(self,data):
		testData = np.array(data).astype(float)

		tempPredictLabel = np.zeros((testData.shape[0],self.k))
		i = 0
		while i<testData.shape[0]:
			tempPredictLabel[i] = self.calNormal(testData[i])
			i += 1
		predictLabel = np.argmax(tempPredictLabel,axis=1)
		predictLabel = self.gmmLabel2label[predictLabel]
		return predictLabel

	def loadPara(self,aFile,muFile,sigmaFile,ml2lFile):
		tempA = []
		tempMu = []
		tempSigma = []
		tempMl2l = []
		readData(tempA,aFile)
		readData(tempMu,muFile)
		readData(tempSigma,sigmaFile)
		readData(tempMl2l,ml2lFile)

		self.a = np.array(tempA[0]).astype(float)
		self.mu = np.array(tempMu).astype(float)
		#self.sigma = np.array(tempSigma).astype(float)
		i=0
		while i<self.k:
			self.sigma[i] = np.array(tempSigma[i]).reshape(self.dim,self.dim)
			i += 1
		self.sigma.astype(float)

		i=0
		while i<self.k:
			self.sigmaI[i] = np.array(np.mat(self.sigma[i]).I)
			i += 1

		self.gmmLabel2label = np.array(tempMl2l[0]).astype(int)
	

def readData(data,file):
	csv_object = csv.reader(open(file,'rb'))
	for row in csv_object:
		data.append(row)

def savePara(para,outputFile,flag):
	writer = csv.writer(open(outputFile,'wb'))
	if flag == 1:
		writer.writerow(para)
	elif flag == 2:
		for row in para:
			writer.writerow(row)
	else:
		for row in para:
			row = row.reshape(1,row.size)[0]
			writer.writerow(row)

def essemble(tileLabel,testLabel, k):
	testLabel = np.array(testLabel).T[0].astype(int)
	temp = np.zeros((k, tileLabel.shape[1]))
	i=0
	while i<tileLabel.shape[1]:
		j = 0
		while j<tileLabel.shape[0]:
			temp[tileLabel[j,i],i] += 1
			j += 1
		i += 1
	predictLabel = np.argmax(temp,axis=0)

	tmp = np.ones(testLabel.size)
	return np.sum(tmp[predictLabel!=testLabel])

if __name__ == '__main__':
	trainData = []
	trainLabel = []
	readData(trainData,'TrainSamples.csv')
	readData(trainLabel,'TrainLabels.csv')

	testData = []
	testLabel = []
	readData(testData,'TestSamples.csv')
	readData(testLabel,'TestLabels.csv')

	model = GMM(trainData,trainLabel,10,17)
#	a = np.array([1,2,3])
#	b = np.arange(9).reshape(3,3)
#	c = np.arange(8).reshape(2,2,2)
#	savePara(a,'a.csv',1)
#	savePara(b,'b.csv',2)
#	savePara(c,'c.csv',3)

#	model.train()
#	savePara(model.a,'a4.csv',1)
#	savePara(model.mu,'mu4.csv',2)
#	savePara(model.sigma,'sigma4.csv',3)
#	savePara(model.gmmLabel2label,'ml2l4.csv',1)
	
	model.loadPara('a.csv','mu.csv','sigma.csv','ml2l.csv')
	print model.predict(testData,testLabel)
#	print '\n'
#	print model.a
#	print '\n'
#	print model.mu
#	print '\n'
#	print model.sigma
#	print '\n'
#	print model.gmmLabel2label

#	model = GMM(trainData, trainLabel, 10, 17)
#	model1 = GMM(trainData, trainLabel, 10, 17)
#	model2 = GMM(trainData, trainLabel, 10, 17)
#	model3 = GMM(trainData, trainLabel, 10, 17)
#	model4 = GMM(trainData, trainLabel, 10, 17)

#	model.loadPara('a.csv','mu.csv','sigma.csv','ml2l.csv')
#	model1.loadPara('a1.csv','mu1.csv','sigma1.csv','ml2l1.csv')
#	model2.loadPara('a2.csv','mu2.csv','sigma2.csv','ml2l2.csv')
#	model3.loadPara('a3.csv','mu3.csv','sigma3.csv','ml2l3.csv')
#	model4.loadPara('a4.csv','mu4.csv','sigma4.csv','ml2l4.csv')

#	label = model.essemblePredict(testData)
#	label1 = model1.essemblePredict(testData)
#	label2 = model2.essemblePredict(testData)
#	label3 = model3.essemblePredict(testData)
#	label4 = model4.essemblePredict(testData)
	
#	tileLabel = np.array([label,label1,label2,label3,label4])
	#print tileLabel
#	print essemble(tileLabel,testLabel, 10)
