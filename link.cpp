#include<iostream>
#include<string>

template <typename T>
class SinglyLinkedList
{
private:
    struct Node
    {
        T data;
        Node *next;

        Node(T val) : data(val), next(nullptr) {}
    };

    Node *head;
    Node *tail;
    int length;

public:

    // 注意这种利用initializer_list的写法可以接受不定数量的参数
    SinglyLinkedList(initializer_list<T> initList) : length(0)
    {
        head = new Node(T());
        tail = head;

        for (auto &val : initList)
        {
            insertBackward(val);
        }
    }

    // 注意这里迭代器的类要自己重构
    class iterator
    {
    private:
        Node *ptr; // 指向当前节点的指针
    public:
        iterator(Node *p = nullptr) : ptr(p) {}

        // 重载操作符
        T &operator*() { return ptr->data; } // 解引用
        Node *operator->() { return ptr; }   // 成员访问
        iterator &operator++()
        { // 前置++
            ptr = ptr->next;
            return *this;
        }
        iterator operator++(int)
        { // 后置++
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        bool operator==(const iterator &other) { return ptr == other.ptr; }
        bool operator!=(const iterator &other) { return ptr != other.ptr; }

        friend class SinglyLinkedList<T>; // 允许SinglyLinkedList访问iterator的私有成员
    };

    iterator begin() { return iterator(head->next); }
    iterator end() { return iterator(nullptr); }

    void insertForward(T value)
    {
        Node *newNode = new Node(value);
        newNode->next = head->next;
        head->next = newNode;
        if (tail == head) // 前插法要注意判断头尾是否相同
        {
            tail = head->next;
        }
        length++;
    }
};