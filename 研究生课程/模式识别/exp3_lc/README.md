#线性判别分类器
##仿真数据
**c1:**(1,1),(2,2),(2,0)
**c2:**(0,0),(1,0),(0,1)

##MNIST数据
###训练数据：30000个17维特征手写数字样本
* [TrainSamples](TrainSamples.csv)
* [TrainLabels](TrainLabels.csv)

###测试数据: 10000个
* [TestSamples](TestSamples.csv)
* [TestLabels](TestLabels.csv)

##感知器算法
###[CODE](perceptron.py)

###[仿真数据结果](perceptron.png)
|params|value|
|--------|--------|
|w0|-2.4550027|
|w1|1.71767852|
|w2|1.41506832|

##最小平方误差算法
###[CODE](lmse.py)

###[仿真数据结果](lmse.png)
|params|value|
|-|-|
|w0|-1.13513514|
|w1|0.91891892|
|w2|0.32432432|

###MNIST数据实验结果
* 10类别分类准确率: **0.7751**
* 多类别解决方案: 每个类别对应一个线性函数，判别准则为线性函数输出最大的类别
