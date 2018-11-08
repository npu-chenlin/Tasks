import torch as t
import numpy as np
from torch.autograd import Variable
import matplotlib.pyplot as plt
# 读入数据 x 和 y
x_train = np.array([[3.3], [4.4], [5.5], [6.71], [6.93], [4.168],
                    [9.779], [6.182], [7.59], [2.167], [7.042],
                    [10.791], [5.313], [7.997], [3.1]], dtype=np.float32)

y_train = np.array([[1.7], [2.76], [2.09], [3.19], [1.694], [1.573],
                    [3.366], [2.596], [2.53], [1.221], [2.827],
                    [3.465], [1.65], [2.904], [1.3]], dtype=np.float32)
x_train = t.from_numpy(x_train)
y_train = t.from_numpy(y_train)
w = Variable(t.randn(1),requires_grad = True)
b = Variable(t.zeros(1),requires_grad = True)

rate = 0.01

def loss_func(x):
    return t.mean((y_train - w*x - b)**2)
for i in range(100):
    loss = loss_func(x_train)
    loss.backward()
    w.data = w.data - w.grad.data*rate
    b.data = b.data - b.grad.data*rate
    y_p = w*x_train + b
    plt.cla()
    plt.scatter(x_train.data.numpy(), y_train.data.numpy(), label='real')
    plt.scatter(x_train.data.numpy(), y_p.data.numpy(), label='estimated')
    plt.pause(0.1)
    w.grad.zero_()
    b.grad.zero_()
