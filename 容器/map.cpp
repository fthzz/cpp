//数据的插入--第一种：用insert函数插入pair数据  
#include <map>  
  
#include <string>  
  
#include <iostream>  
  
using namespace std;  
  

/*
map是一类关联式容器。它的特点是增加和删除节点对迭代器的影响很小，除了那个操作节点，对其他的节点都没有什么影响。

对于迭代器来说，可以修改实值，而不能修改key。

Map是STL的一个关联容器，它提供一对一（其中第一个可以称为关键字，每个关键字只能在map中出现一次，第二个可能称为该关键字的值）的数据 处理能力.
由于这个特性，它完成有可能在我们处理一对一数据的时候，在编程上提供快速通道。

底层是一颗红黑树，所以是有序的 
*/


int main()  
  
{  
  
    map<int, string> mapStudent;  
  
    mapStudent.insert(pair<int, string>(1, "student_one"));  
  
    mapStudent.insert(pair<int, string>(2, "student_two"));  
  
    mapStudent.insert(pair<int, string>(3, "student_three"));  
  
    map<int, string>::iterator iter;  
  
    for(iter = mapStudent.begin(); iter != mapStudent.end(); iter++)  
  
       cout<<iter->first<<' '<<iter->second<<endl;  
  
}  