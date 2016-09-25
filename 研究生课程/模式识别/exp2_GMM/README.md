#GMM实验
##仿真数据
* [Train1.csv](Train1.csv)
* [Train2.csv](Train2.csv)
* [Test1.csv](Test1.csv)
* [Test2.csv](Test2.csv)

##MNIST数据集（17维）
* [TrainSamples.csv](TrainSamples.csv)
* [TrainLabels.csv](TrainLabels.csv)
* [TestSamples.csv](TestSamples.csv)
* [TestLabels.csv](TestLabels.csv)

##文件夹[para](para)说明
* 该文件夹保存的是仿真训练数据训练得到的参数

##文件夹[MnistPara](MnistPara)
* 保存高斯数分别为1,2,3,4和5训练得到的参数
* a 表示隐变量估计
* mu 表示高斯均值估计
* sigma 表示方差估计
* 后缀，例如1_2表示高斯数为1，数字类别为2的参数

##MNIST数据实验结果
| 高斯数 | 正确识别率 |
|-------|--------|
|1|91.78|
|2|93.31|
|3|94.1|
|4|94.22|
|5|94.27|