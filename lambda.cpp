#include <iostream>
#include <vector>
#include <algorithm> //中文意思是算法

//vector可以实现动态扩展，这就是它和数组不一样的地方。
//当我们压入数据后，超过了vector的初始容量，它就会自动扩展，一般是成倍扩展。2-》4 4-》8
//它扩展的过程是先找一个更大的空间，将数据复制一份进入新空间，释放原空间，所以不会占用过多空间

bool cmp(int a, int b)
{
    return a - 10 > b + 5;
}


int main(int argc, char *argv[])
{
    std::vector<int> v0 = {12, 22, 1, 100, 78};

    //sort有三个参数，第一个元素的指针，最后一个元素的指针，排序准则

    // std::sort(v0.begin(), v0.end(), std::greater<int>()); //默认升序，这里是降序
    std::sort(v0.begin(), v0.end(), cmp); //可以使用自己的排序规则


    //使用lambda函数
    //这个是lambda函数的标准形式，其中[]是用于捕获变量，（）中是需要输入的变量，->bool是返回值的类型
    //最后f1是返回值，从return得到
    auto f1 = [](int a, int b) -> bool{ 
        return a > b;
    };

    int m = 10;
    int n = 11;

    //但是这个返回值可以编译器自动推断，所以可以省略，写成这个形式
    //[捕获变量] 用于捕获程序内的变量 例如:[m, &n] 前者按值捕获类似形参，后者是引用捕获，所以n在lambda函数中变化的话，外部也会变化 
    //[&]引用捕获所有变量 [=]按值捕获所有变量
    auto f2 = [](int a, int b){
        return a > b;
    };

    //使用auto的话更加方便和通用
    auto f3 = [](auto x, auto y){
        return x * y;
    };

    std::sort(v0.begin(), v0.end(), f2);
    
    std::cout << v0.front() << std::endl;

    return 0;
}