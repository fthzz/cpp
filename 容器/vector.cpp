#include<iostream>
#include<vector>
#include<stack>
#include<queue> 

using namespace std;
/*
vector和数组形式上是差不多的，但数组长度固定，vector可以动态扩展（这个不是在原有空间上再接续新空间，而是找到一个更大的空间，释放原空间）。
数组储存在栈上，vector储存在堆上

*/ 


int main(){

    stack<int> s1;

    vector<int> v0 = {2, 32, 44, 1111};
    vector<int> v1;   // 在这里不写大小，即不写成v(n),它是空的
    cout<<v1.empty(); //判断是否为空 空返回1
    v1.capacity(); //返回其容量
    v1.size(); //容器的大小 即容器中元素的个数
    /*
    这里区分一下大小和容量，容量是大于等于大小的，表示这个vector的储量。大小单纯表示容器中有几个元素
    */
    v1.resize(8, 10); //前一个8表示容器长度变为8，如果变短，舍去后面数字；如果变长，默认为0补全。后面一个10，表示多出来的部分用10补全，可以不写，那就使用默认的0

    vector<double> v2(10);
    v2.push_back(11.1); //尾部插入一个元素
    v2.pop_back(); //删除一个元素
    v2.insert(v2.begin(), 21); //在指定位置插入21。v2.begin()表示头，v2.end()表示尾。
    v2.insert(v2.end(), 3, 11); //在尾部插入3个11
    v2.erase(v2.begin()); //删除指定位置元素
    v2.clear(); //清空

    vector<char> v3;
    v3.front(); //返回第一个元素
    v3.back(); //返回最后一个元素
    for (int i = 0; i < 10;i++){
        cout << v3[i] << ' '; //容器元素调用
    }

    vector<int> v4;
    v4.swap(v1); //交换两个容器内的数据
    /*
    这里有一个注意点，当你最开始开辟了一个大小为1000的容器，假设此时系统给它的容量是1100；你resize变为大小为100后，它的容量依旧不变，浪费了空间。此时用 vector<int> v.swap(v);新的v就会覆盖老的v，同时容量也会在这个操作下改变，变为110。这样就节省了空间
    */
    
    auto t = lower_bound(v4.begin(), v4.end(), 3);//这个函数是查找第一个大于等于3的数字，返回指针。
}