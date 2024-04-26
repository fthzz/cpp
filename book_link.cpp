#include <iostream>
#include <string>
#include <fstream>
#include<stdio.h>
#define MAXSIZE 100
typedef struct Book_Node
{
    std::string name;
    std::string score;
    double price;
    Book_Node *next = nullptr;
}booknode;

typedef struct Book_List
{
    booknode* head_node = new booknode;
    int length = 0;
} booklist;

std::string path = "/home/fthzzz/Desktop/ecar-vision/bookdata.txt";

void show(booklist *data)
{
    booknode *p = data->head_node->next;
    while (p->next != nullptr)
    {
        std::cout << p->score << " " << p->name << " " ;
        printf("%.2f\n", p->price);
        p = p->next;
    }
    std::cout << p->score << " " << p->name << " ";
    printf("%.2f\n", p->price);
}

void init_bookdata(booklist *b)
{
    int i = 0;
    std::cout << "已从文件中读取图书信息" << std::endl;
    std::ifstream fs;
    booknode *q = b->head_node;
    fs.open(path, std::ios::in);
    for (i = 0; i < MAXSIZE; i++)
    {
        booknode *node = new booknode;
        fs >> node->score >> node->name >> node->price;
        if(node->price==0){
            break;
        }
        else{
            q->next = node;
            q = node;
        }
    }
    b->length = i;
    fs.close();
    std::cout <<"图书的总数量："<< b->length<< std::endl;
    show(b);
}

void change_price(booklist* data){
    int i = 0;
    std::cout << "已从文件中读取图书信息" << std::endl;
    std::ifstream fs;
    booknode *q = data->head_node;
    fs.open(path, std::ios::in);
    for (i = 0; i < MAXSIZE; i++)
    {
        booknode *node = new booknode;
        fs >> node->score >> node->name >> node->price;
        if (node->price == 0)
        {
            break;
        }
        else
        {
            q->next = node;
            q = node;
        }
    }
    data->length = i;
    fs.close();
    double sum = 0;
    booknode *p = data->head_node->next;
    while (p->next != nullptr)
    {
        sum += p->price;
        p = p->next;
    }
    sum += p->price;
    double avg = 0;
    p = data->head_node->next;
    avg = sum / data->length;
    while (p->next != nullptr)
    {
        if(p->price<avg){
            p->price *= 1.2;
        }
        else{
            p->price *= 1.1;
        }
        p = p->next;
    }
    if (p->price < avg)
    {
        p->price *= 1.2;
    }
    else
    {
        p->price *= 1.1;
    }
    printf("%.2f\n", avg);
    show(data);
}

void nixu_init_bookdata(booklist* data){
    std::cout << "已从文件中读取图书信息" << std::endl;
    std::ifstream fs;
    booknode *q = data->head_node;
    fs.open(path, std::ios::in);
    fs >> data->length;
    for (int i = 0; i < data->length; i++)
    {
        booknode *node = new booknode;
        fs >> node->score >> node->name >> node->price;
        q->next = node;
        q = node;
    }
    fs.close();
    booknode *p = data->head_node;
    for (int i = 0; i < data->length-1; i++)
    {
        q = data->head_node;
        for (int j = 0; j < data->length;j++){
            q = q->next;
        }
        q->next = p->next;
        p->next = q;
        p = q;
    }
    q = data->head_node;
    for (int j = 0; j < data->length; j++)
    {
        q = q->next;
    }
    q->next = nullptr;
    show(data);
}

void find_expensive(booklist* data){
    std::ifstream fs;
    booknode *q = data->head_node;
    fs.open(path, std::ios::in);
    fs >> data->length;
    for (int i = 0; i < data->length; i++)
    {
        booknode *node = new booknode;
        fs >> node->score >> node->name >> node->price;
        q->next = node;
        q = node;
    }
    fs.close();
    double max = 0;
    int count = 0;
    booknode *p = data->head_node->next;
    while (p->next != nullptr)
    {
        if(p->price>max){
            max = p->price;
            count=1;
        }
        else if(p->price==max){
            count++;
        }
        p = p->next;
    }
    if (p->price > max)
    {
        max = p->price;
        count = 1;
    }
    else if (p->price == max)
    {
        count++;
    }
    std::cout << count << std::endl;
    p = data->head_node->next;
    while (p->next != nullptr)
    {
        if (p->price == max)
        {
            std::cout << p->score << " " << p->name << " " ;
            printf("%.2f\n", p->price);
        }
        p = p->next;
    }
    if (p->price == max)
    {
        std::cout << p->score << " " << p->name << " ";
        printf("%.2f\n", p->price);
    }
}

void insert(booklist* data){
    std::ifstream fs;
    booknode *q = data->head_node;
    fs.open(path, std::ios::in);
    fs >> data->length;
    for (int i = 0; i < data->length; i++)
    {
        booknode *node = new booknode;
        fs >> node->score >> node->name >> node->price;
        q->next = node;
        q = node;
    }
    int index = 0;
    fs >> index;
    booknode *p = data->head_node->next;
    booknode *node_in = new booknode;
    fs >> node_in->score >> node_in->name >> node_in->price;
    fs.close();
    if (index < 0 || index > data->length)
    {
        std::cout << "入库位置非法！";
    }
    else{
        for (int i = 2; i < index;i++){
            p = p->next;
        }
        node_in->next = p->next;
        p->next = node_in;
    }
    show(data);
}

void Delete(booklist* data){
    std::ifstream fs;
    booknode *q = data->head_node;
    fs.open(path, std::ios::in);
    fs >> data->length;
    for (int i = 0; i < data->length; i++)
    {
        booknode *node = new booknode;
        fs >> node->score >> node->name >> node->price;
        q->next = node;
        q = node;
    }
    int index = 0;
    fs >> index;
    booknode *p = data->head_node->next;
    q = data->head_node->next;
    if (index < 0 || index > data->length)
    {
        std::cout << "入库位置非法！";
    }
    else
    {
        for (int i = 2; i < index; i++)
        {
            p = p->next;
        }
        q = p->next;
        p->next = p->next->next;
        delete q;
    }
    fs.close();
    show(data);
}

void clear(booklist* data)
{
    std::ifstream fs;
    booknode *q = data->head_node;
    fs.open(path, std::ios::in); 
    fs >> data->length;
    for (int i = 0; i < data->length; i++)
    {
        booknode *node = new booknode;
        fs >> node->score >> node->name >> node->price;
        q->next = node;
        q = node;
    }
    booknode *p = data->head_node->next;
    q = data->head_node->next;
    booknode *goal = data->head_node->next;
    while(goal->next!=nullptr){
        p = goal;
        q = goal->next;
        while (q->next != nullptr)
        {
            if(q->name==goal->name){
                p->next = q->next;
                delete q;
                data->length--;
                q = p->next;
            }
            else{
                p = q;
                q=q->next;
            }
        }
        if (q->name == goal->name)
        {
            p->next =nullptr;
            delete q;
            data->length--;
        }
        goal = goal->next;
    }
    fs.close();
    std::cout << data->length<<std::endl;
    show(data);
}

int main()
{
    booklist *data = new booklist;
    // init_bookdata(data);
    // change_price(data);
    // nixu_init_bookdata(data);
    find_expensive(data);
    // insert(data);
    // Delete(data);
    // clear(data);
    delete data;
    return 0;
}