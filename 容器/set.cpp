#include <iostream>
#include <set>
using namespace std;

/*
set/multiset

元素放入时会自动排序
是一种关联式容器，关联式容器是一类容器，它们能够根据键（key）来存储和检索元素，并且保持元素的有序性。
set的底层原理是二叉树


set和multiset区别:
set不允许容器中有重复的元素. multiset允许容器中有重复的元素
*/

//set默认是从小到大排序

class MyCompare
{
  public:
  	bool operator()(int v1,int v2)
	  {
  		 return v1>v2;
	  }
};
// 容器排序
void test01()
{
	set<int>s1;
	
    s1.insert(30);
	s1.insert(20);
	s1.insert(10);
	s1.insert(40);
	s1.insert(50);
	
	for(set<int>::iterator it = s1.begin();it != s1.end();it++)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
	
	//指定排序规则从大到小
	set<int,MyCompare>s2;
	s2.insert(30);
	s2.insert(20);
	s2.insert(10);
	s2.insert(40);
	s2.insert(50);
	
	for(set<int,MyCompare>::iterator it = s2.begin();it != s2.end();it++)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
	
	 
}



int main(){
	test01();
}