## 遇到的问题
刚开始时，我将定义文件.h与实现文件.cpp分开写，报错:  
```
undefined reference to seqList<int>::insertElement(int)
```

报错原因：**模板类不支持分离实现。**  
遂将.h与.cpp合并。

## 深度思考
* 模板只能放在头文件，如何实现比较复杂的功能？如何把复杂的操作不外漏？
* 模板的好处？

