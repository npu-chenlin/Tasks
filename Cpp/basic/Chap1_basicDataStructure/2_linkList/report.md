在类 listNode中声明友元类linkList<T> ，但是用linkList<T>实例化的list 无法使用list->data/list->next来访问private元素。  
解决方法：不应当直接用->访问private元素，而应该创建getXXX函数来获得private元素  

！！** 声明的友元类只能用作定义类时访问private元素， 不能用于实例化后的类去访问private元素。**
