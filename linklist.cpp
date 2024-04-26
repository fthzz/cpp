#include <iostream>
#include <string>
//初始化节点
typedef struct LinkList_Node{
    int data;
    struct LinkList_Node *next;
    LinkList_Node(int val):data(val),next(nullptr){}
} Linknode;

//初始化链表
typedef struct LinkList{
    Linknode *node_head = new Linknode(-1);
    int length = 0;
} Linklist;

// 生成链表
void init_list(Linklist* list_head,int n){
    int val;
    Linknode* p = list_head->node_head;
    for (int i = 0; i < n; i++)
    {
        std::cout << "请输入第" << i+1<< "个节点的数据:"<<std::endl;
        std::cin >> val;
        Linknode *node = new Linknode(val);
        p->next = node;
        p = node;
        (list_head->length)++;
    }
}
// 前插 插入节点
void insert(Linklist* list_head, Linknode* node_p,int val){
    Linknode* p = list_head->node_head->next;
    Linknode* q = list_head->node_head;
    int flag = 0;
    if(list_head->length==1)
        q->next = node_p;

    while (p->next != nullptr)
    {
        if (p->data == val)
        {
            node_p->next = p;
            q->next = node_p;
            flag = 1;
            std::cout << "successfully insert";
            break;
        }
        else
        {
            q = p;
            p = p->next;
        }
    }

    if (!flag)
    {
        if (p->data == val)
        {
            node_p->next = p;
            q->next = node_p;
            std::cout << "successfully insert";
        }
        else
            std::cout << "not find";
    }
}

// 删除指定节点
void delet_node(Linklist* list_head,int val){
    Linknode* p = list_head->node_head->next;
    Linknode* q = list_head->node_head;
    int flag = 0;
    while (p->next != nullptr)
    {
        if (p->data == val){
            q->next = p->next;
            delete p;
            flag = 1;
            std::cout << "successfully delete";
            break;
        }
        else{
                q = p;
                p = p->next;
        }
    }

    if(!flag){
        if(p->data==val){
            q->next = nullptr;
            std::cout<<"successfully delete";
        }
        else
            std::cout << "not find";
    }
}

//修改数据值
void change_node_data(Linklist *list_head, int val,int pre_val){
    Linknode *p = list_head->node_head->next;
    Linknode *q = list_head->node_head;
    int flag = 0;
    while (p->next != nullptr)
    {
        if (p->data == pre_val)
        {
            p->data = val;
            std::cout << "successfully change";
            flag = 1;
            break;
        }
        else
        {
            q = p;
            p = p->next;
        }
    }

    if (!flag)
    {
        if (p->data ==pre_val)
        {
            p->data = val;
            std::cout << "successfully change";
        }
        else
            std::cout << "not find";
    }
}
//遍历显示链表
void show(Linklist* list_head){
    Linknode *p = list_head->node_head->next;
    while (p->next!=nullptr)
    {
        std::cout << p->data << "->";
        p = p->next;
    }
    std::cout << p->data;
}

int main(){
    Linklist* list_head = new Linklist;
    init_list(list_head, 3);
    show(list_head);
    return 0;
}