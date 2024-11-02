#include <iostream>
#include <list>
#include <string>
using namespace std;

//容器通用的访问方式是使用迭代器，但有些容器重载了其他访问方法

/*
模板类list是一个容器，list是由双向链表来实现的，每个节点存储1个元素。list支持前后两种移动方向。

优势： 任何位置执行插入和删除动作都非常快
*/



int main(){
    //上定义双向队列
	list<string> mylist_string;
	list<double> mylist_double(6);
	
	//---------初始化mylist_string
	mylist_string.push_front("1:  Jack");
	mylist_string.push_front("2:  Tom");
	mylist_string.push_front("3:  Mike");
 
	//---------初始化mylist_double
	mylist_double.push_front(10.0);
	mylist_double.push_front(20.0);
	mylist_double.push_front(30.0);
	mylist_double.push_front(40.0);
	mylist_double.push_front(50.0);
 
	//下述是三种容器定义形式
	list<int> mylist_int(6,0);			// 6个0：0 0 0 0 0 0
	list<double>mylist_double2(6,0.0);	// 6个0.0：0.0 0.0 0.0 0.0 0.0 0.0
	list<int>elselist(mylist_int);		// 以其它双向队列初始化

    list<string>::iterator iter_String;	// 迭代器
	for(iter_String=mylist_string.begin();iter_String!=mylist_string.end();iter_String++)
	{
		string temp=*iter_String;
		cout<<temp<<endl;
	}

    //各容器的容量
	int size=mylist_string.size();
	int maxsize=mylist_string.size();
	mylist_string.resize(5);


    //剩余很多方法用到的时候查



    return 0;
}