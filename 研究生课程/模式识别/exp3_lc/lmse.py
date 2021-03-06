# coding:utf-8
from __future__ import division
import numpy as np
import matplotlib.pyplot as plt
import csv as csv

class lmse(object):
    def __init__(self, X, y):
        self.X = np.concatenate((np.ones((X.shape[0], 1)), X), axis=1)
        self.y = y

    def train(self):
        self.w = np.dot(np.linalg.pinv(self.X), self.y)

    def predict(self, testData):
        testData = np.concatenate((np.ones((testData.shape[0], 1)), testData), axis=1)
        prediction = np.dot(testData, self.w)
        prediction = np.argmax(prediction, axis=1)
        return prediction

def plot(X, y, w):
    idx_1 = (y.flatten()==1)
    x1_1 = X[idx_1, 0]
    x2_1 = X[idx_1, 1]

    idx_2 = (y.flatten()==-1)
    x1_2 = X[idx_2, 0]
    x2_2 = X[idx_2, 1]

    plt.axis([-1, 3, -1, 3])

    plt.plot(x1_1, x2_1, 'o')
    plt.plot(x1_2, x2_2, 'x')

    plane_x = np.array([np.min(X[:, 1]), np.max(X[:, 1])])
    plane_y = (-w[0]-w[1]*plane_x)/w[2]
    plt.plot(plane_x, plane_y)

    plt.show()

def eval(prediction, label):
    total = label.shape[0]
    temp = np.ones(label.shape[0])
    error = np.sum(temp[prediction!=label])
    return (total-error)/total

def readData(sampleFile, labelFile):
    sampleReader = csv.reader(open(sampleFile, 'rb'))
    labelReader = csv.reader(open(labelFile, 'rb'))

    sample = []
    for line in sampleReader:
        sample.append(line)

    label = []
    for line in labelReader:
        label.append(line)

    return sample, label

if __name__ == '__main__':
    #仿真数据实验
    '''
    X = [[1,1],
        [2,2],
        [2,0],
        [0,0],
        [1,0],
        [0,1]]
    y = [1,1,1,-1,-1,-1]
    
    X = np.array(X).astype(float)
    y = np.array(y)
    y = y.reshape((y.shape[0], 1))

    model = lmse(X, y)
    model.train()
    w = model.w
    print w
    plot(X, y, w)
    '''
    #mnist数据实验
    trainData, trainLabel_temp = readData('TrainSamples.csv', 'TrainLabels.csv')
    trainData = np.array(trainData).astype(float)
    trainLabel_temp = np.array(trainLabel_temp).astype(int)
    trainLabel = np.zeros((trainLabel_temp.shape[0], 10))
    i = 0
    while i<trainLabel_temp.shape[0]:
        trainLabel[i][trainLabel_temp[i]] = 1
        i += 1

    testData, testLabel = readData('TestSamples.csv', 'TestLabels.csv')
    testData = np.array(testData).astype(float)
    testLabel = np.array(testLabel).astype(int).flatten()
        
    model = lmse(trainData, trainLabel)
    model.train()
    prediction = model.predict(testData)
    print eval(prediction, testLabel)
