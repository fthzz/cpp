#include<iostream>
#include<string>
#include<fstream>
#include<stdio.h>
#define MAXSIZE 100
typedef struct book{
    std::string name;
    std::string score;
    double price;
    // book(std::string name,std::string score,double val):name(name),score(score),price(val){}
}book;

void show(book *data)
{
    int i = 0;
    while ((data + i)->price != 0)
    {
        i++;
    }
    std::cout << "图书总数量：" << i << std::endl;
    for (int j = 0; j < i; j++)
    {
        std::cout << (data + j)->score << ' ' << (data + j)->name << ' ';
        printf("%.2f\n", (data + j)->price);
    }
}

int init_bookdata(book *data)
{
    std::cout << "已从文件内读入图书信息" << std::endl;
    int i = 0;
    std::ifstream fs;
    fs.open("/home/fthzzz/Desktop/ecar-vision/bookdata.txt", std::ios::in);
    while (fs >> data[i].score >> data[i].name >> data[i].price)
    {
        if (data[i].price == 0)
        {
            break;
        }
        i++;
    }
    fs.close();
    return i;
}

void change_price(book* data,int length){
    double sum = 0;
    for (int i = 0; i < length;i++){
        sum += (data + i)->price;
    }
    double avg = 0;
    avg = sum / length;
    // std::cout << avg << std::endl;
    printf("%.2f\n", avg);
    for (int i = 0; i < length; i++)
    {
        if((data+i)->price<avg){
            (data + i)->price *= 1.2;
        }
        else{
            (data + i)->price *= 1.1;
        }
    }
    show(data);
}

void init_bookdata_nixu(book* data){
    std::ifstream fs;
    fs.open("/home/fthzzz/Desktop/ecar-vision/bookdata.txt", std::ios::in);
    int length = 0;
    fs >> length;
    for (int i = length-1; i >=0;i--)
        fs >> data[i].score >> data[i].name >> data[i].price;
    fs.close();
    show(data);
}

void find_expensive(book* data){
    std::ifstream fs;
    fs.open("/home/fthzzz/Desktop/ecar-vision/bookdata.txt", std::ios::in);
    int length = 0;
    fs >> length;
    for (int i = 0; i <length ; i++)
        fs >> data[i].score >> data[i].name >> data[i].price;
    fs.close();
    double max = 0;
    int count = 0;
    for (int i = 0; i < length; i++)
    {
        if(max<(data+i)->price){
            max = (data+i)->price;
            count = 1;
        }
        else if((data+i)->price==max){
            count++;
        }
    }
    std::cout << count << std::endl;
    for (int i = 0; i < length; i++)
    {
        if ((data + i)->price==max)
        {
            std::cout << (data + i)->score << ' ' << (data + i)->name << ' ';
            printf("%.2f\n", (data + i)->price);
        }
    }
}

void insert(book* data){
    std::ifstream fs;
    fs.open("/home/fthzzz/Desktop/ecar-vision/bookdata.txt", std::ios::in);
    int length = 0;
    fs >> length;
    for (int i = 0; i < length; i++)
        fs >> data[i].score >> data[i].name >> data[i].price;
    int index;
    fs>> index;
    if (length == MAXSIZE)
    {
        std::cout << "书库已满，无法插入"<<std::endl;
    }
    else if (index<0 || index>MAXSIZE){
        std::cout << "抱歉,入库位置非法!"<<std::endl;
    }
    else{
        for (int i = length; i >=index;i--){
            *(data + i) = *(data + i - 1);
        }
        fs>> (data + index-1)->score >> (data + index-1)->name >> (data + index-1)->price;
        show(data);
    }
    fs.close();
}

void Delete(book *data)
{
    std::ifstream fs;
    fs.open("/home/fthzzz/Desktop/ecar-vision/bookdata.txt", std::ios::in);
    int length = 0;
    fs >> length;
    for (int i = 0; i < length; i++)
        fs >> data[i].score >> data[i].name >> data[i].price;
    int index;
    fs >> index;
    if (index < 0 || index > MAXSIZE)
    {
        std::cout << "抱歉,出库位置非法!" << std::endl;
    }
    else
    {
        for (int i = index-1; i < length; i++)
        {
            *(data + i ) = *(data + i+1);
        }
        show(data);
    }
    fs.close();
}

void clear(book* data){
    std::ifstream fs;
    fs.open("/home/fthzzz/Desktop/ecar-vision/bookdata.txt", std::ios::in);
    int length = 0;
    fs >> length;
    for (int i = 0; i < length; i++)
        fs >> data[i].score >> data[i].name >> data[i].price;
    for (int i = 0; i < length;i++){
        for (int j = i + 1; j < length;j++){
            if((data+i)->score==(data+j)->score){
                for (int u = j; u <= length; u++)
                {
                    *(data + u) = *(data + u + 1);
                }
            }
        }
    }
    show(data);
}

int main(){
    book* data = new book[MAXSIZE+1];
    int length;
    // length=init_bookdata(data);
    // show(data);
    // change_price(data, length);
    // init_bookdata_nixu(data);
    // find_expensive(data);
    // insert(data);
    // Delete(data);
    clear(data);
    delete[] data;
    return 0;
}