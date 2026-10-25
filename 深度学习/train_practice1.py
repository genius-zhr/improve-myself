import numpy as np
import matplotlib.pyplot as plt
#原始数据，身高(cm)体重(kg)
raw_data=np.array([[172,74],[168,58],[178,80],[165,55],[180,84],[163,52],
[175,76],[166,56],[170,70],[160,50]])
labels=np.array([1,0,1,0,1,0,1,0,1,0])#1偏胖，0偏瘦
#展示初始数据
print("="*60)
print("原始数据:")
print("="*60)
print(f"{'编号':<5} {'身高 (cm)':<10} {'体重 (kg)':<10} {'标签':<5}")
for i in range(len(raw_data)):
    label_str = "偏胖" if labels[i] == 1 else "偏瘦"
    print(f"{i+1:<5} {raw_data[i][0]:<10} {raw_data[i][1]:<10} {label_str}")
#数据归一化
x_min=raw_data.min(axis=0)#axis=0表示按列取最小值，axis=1表示按行取最小值
x_max=raw_data.max(axis=0)
X=(raw_data-x_min)/(x_max-x_min)
#打印归一化后的数据
print("="*60)
print("归一化后的数据:")
print("="*60)
print(f"{'编号':<5} {'身高 (cm)':<10} {'体重 (kg)':<10} {'标签':<5}")
for i in range(len(X)):
    label_str = "偏胖" if labels[i] == 1 else "偏瘦"
    print(f"{i+1:<5} {X[i][0]:<10.4f} {X[i][1]:<10.4f} {label_str}")
#创建感知机类
class Perceptron:
    def __init__(self,learning_rate=1.0,n_iterations=100):
        self.lr = learning_rate      #学习率
        self.n_iter = n_iterations   #最大训练轮次
        self.weights = None          #权重
        self.bias = None             #偏置
        self.errors_per_epoch=[]     #每轮迭代的错误数
    def fit(self,X,y):
        n_samples,n_features=X.shape
        self.weights=np.zeros(n_features)#长度为特征数的权重向量
        self.bias=0
        self.errors_per_epoch=[]
        for epoch in range(self.n_iter):
            errors=0
            for idx in range(n_samples):
                x_i=X[idx]
                y_true=y[idx]
                #计算加权和
                z=np.dot(x_i,self.weights)+self.bias
                #激活判断
                y_pred=1 if z>=0 else 0
                #计算误差
                error=y_true-y_pred
                #如果预测错误,更新权重和偏置
                if error != 0:
                    self.weights+=self.lr*error*x_i
                    self.bias+=self.lr*error
                    errors+=1
                    print(f"第{epoch+1}轮，第{idx+1}个样本，预测错误，更新权重{self.weights}和偏置{self.bias}")
            self.errors_per_epoch.append(errors)
            #本轮零错误，收敛，训练结束
            if errors == 0:
                print(f"训练在第{epoch+1}轮收敛")
                break
        return self
    def predict(self,X):
        z=np.dot(X,self.weights)+self.bias
        return np.where(z>=0,1,0)

#开始训练
model=Perceptron(learning_rate=0.5,n_iterations=100)
model.fit(X,labels)
print(f"最终权重: {model.weights}")
print(f"最终偏置: {model.bias}")
#预测训练数据验证所有样本
predictions=model.predict(X)
for i in range(len(X)):
    true_label = "偏胖" if labels[i] == 1 else "偏瘦"
    pred_label = "偏胖" if predictions[i] == 1 else "偏瘦"
    print(f"样本{i+1}: 真实标签: {true_label}, 预测标签: {pred_label}")
