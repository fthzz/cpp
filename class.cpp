#include<string>
#include<iostream>

class student
{
    //友元需要注意两点：第一，单向。第二，不可继承。


    //全局友元函数
    //作用是可以访问类中的所有变量。这个函数位置放在哪里都没关系，不受public等影响，一般放在开头。它是使类外函数变为友元函数。
    friend int main();
    
    //友元类
    //作用是在另一个类中，可以调用这个类的所有变量
    friend class teacher;

    //友元成员函数
    //比较麻烦，用到再说

private:
    int age;
    std::string name;
    std::string student_number;
    //枚举的作用就在于可以直接使用具体内容作为变量，不容易忘记1、2等指代什么
    enum sex
    {
        girl = 1,
        boy = 2
    };

public:
    //构造函数
    student(){
        age = 18;
        name = 'zzz';
        student_number = '2306';
    }
    //构造函数可以有多个，具体调用哪一个，看你在实例化时，给了几个实参进来
    student(std::string name)
    {
        age = 18;
        name = name;
        student_number = '2306';
    }
    //在这里调用了初始化列表，调用后就可以不写下面的两句代码
    //初始化列表和赋值存在差异：特别是在成员变量是类的时候，前者调用的是拷贝构造函数，而后者是先创建成员类的对象，再进行赋值
    student(std::string name1,int age1):name(name1),age(age1)
    {
        // age = age1;
        // name = name;
        student_number = '2306';
    }
    //针对这个程序，没有动态开辟内存，不需要释放
    ~student(){
        std::cout << 'aaa';
    }

    int get_age(){
        return age;
    }

    void set_age(int age1){
        age = age1;
    }

    void get_sex(int sex1){
        if (sex1==sex::girl){
            std::cout << 'she';
        }
        else{
            std::cout << 'he';
        }
    }

    //在一个类对象作为实参传入时，返回值要返回自己，该如何去表示，这时候就要用到this指针，它储存了自己这个类对象的地址
    student compare_age(student stu1){
        if (stu1.age<age){
            return stu1;
        }
        else{
            return *this;
        }
    }
};

class teacher{
public:
private:
};

int main(){
    student stu;
}