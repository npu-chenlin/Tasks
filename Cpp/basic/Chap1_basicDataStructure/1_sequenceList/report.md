刚开始时，我将定义文件.h与实现文件.cpp分开写，报错：
'
undefined reference to `seqList<int>::insertElement(int)
'
**模板类不支持分离实现。**
遂将.h与.cpp合并。
