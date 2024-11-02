
#include <unordered_map>
#include <string>
#include<iostream>
#include<string>

//unordered_map是基于哈希表实现的

//哈希表（又叫散列表）有两种：线性探测哈希表和哈希桶哈希表
//线性探测哈希表存在哈希冲突问题，如果位于同一位置，则往后放一个

//为了解决这个冲突问题，产生了哈希桶哈希表，同一个位置可以存放多个数据



/*umap特点
unordered_map底层存储的是<key,value>键值对，可以通过key快速的索引到value
unordered_map内部因为是数据是通过映射存入哈希桶内的，所以对unordered_map进行遍历得到的是一个无序的序列。
unordered_map通过key进行访问的速度比map快，但是遍历元素的迭代效率就要低于map了。
unordered_map也实现了operator[] 可以通过key直接访问到value
unordered_map因为是无序的，所以key不可以重复
*/


 
int main() {
    // 使用初始化列表
    std::unordered_map<std::string, int> umap = {
        {"apple", 3},
        {"banana", 5},
        {"orange", 2}
    };
    
    //用迭代器也是可以遍历的

    // 输出内容
    //因为是随机存储的，所以输出结果的顺序是不一定的
    for (const auto& pair : umap) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
 
    //查找
    //方法1 operator[]
    int apple_count = umap["apple"];
    //方法2 at()
    try {
    int banana_count = umap.at("banana");
    } catch (const std::out_of_range& e) {
    std::cerr << "Key not found!" << std::endl;
    }
    //方法3 find()
    auto it = umap.find("orange");
    if (it != umap.end()) {
    std::cout << "Found orange: " << it->second << std::endl;
    }

    return 0;
}