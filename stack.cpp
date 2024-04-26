#include<iostream>
#define MAXSIZE 50

typedef struct Stack
{
    double data[MAXSIZE];
    char data_c[MAXSIZE];
    int top;
} stack;


void init_stack(stack *s)
{
    s->top=-1;
}

bool is_full(stack* s){
    if(s->top==MAXSIZE-1)return true;
    return false;
}

bool is_empty(stack* s){
    if(s->top==-1)return true;
    return false;
}

void push(stack* s,double val){
    if(is_full(s))std::cout<<"failed because of full"<<std::endl;
    else{
        s->top++;
        s->data[s->top] = val;
    }
}

void pop(stack* s){
    if(is_empty(s))std::cout<<"failed because of empty"<<std::endl;
    else{
        s->top--;       
    }
}

bool is_sign(char ch){
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        return true;
    return false;
}

int getPriority(char ch)
{
    int level = 0; // 优先级

    switch (ch)
    {
    case '(':
        level = 1;
        break;
    case '+':
    case '-':
        level = 2;
        break;
    case '*':
    case '/':
        level = 3;
        break;
    default:
        break;
    }
    return level;
}

double cal(char ch, double a, double b)
{
    double result = 0;

    switch (ch)
    {
    case '+':
        result = b + a;
        break;
    case '-':
        result = b - a;
        break;
    case '*':
        result = b * a;
        break;
    case '/':
        if (a == 0)
        {
            std::cerr << "除数不能为0。\n";
            exit(1); // 强制终结程序
        }
        else
            result = b / a;
        break;
    default:
        break;
    }

    return result;
}

bool calculate()
{
    std::cout << "请输入中缀表达式：" << std::endl;
    stack* number = new stack;
    stack *sign = new stack;
    init_stack(number);
    init_stack(sign);

    int flag = 0;
    char ch;
    int num;
    std::cin.get(ch);
    while (ch != '\n')
    {
        if(ch=='='){
            std::cin.get(ch);
        }
        else if (isdigit(ch))
        {
            flag = 1;
            num = 0;
            do{
                num = num * 10 + (ch - '0');
                std::cin.get(ch);
            } while (isdigit(ch));
            push(number, num);
        }
        else if (ch == '(')
        {
            sign->top++;
            sign->data_c[sign->top] = ch;
            // std::cout<<"读入一个 ("<<std::endl;
            std::cin.get(ch);
        }
        else if (is_sign(ch))
        {
            if (is_empty(sign))
            {
                sign->top++;
                sign->data_c[sign->top] = ch;
                std::cin.get(ch);
            }
            else
            {
                // 比较栈op顶的操作符与ch的优先级
                // 如果ch的优先级高，则直接压入栈
                // 否则，推出栈中的操作符，直到操作符小于ch的优先级，或者遇到（，或者栈已空
                while (!is_empty(sign))
                {
                    char c = sign->data_c[sign->top];
                    if (getPriority(ch) <= getPriority(c))
                    {
                        // 优先级低或等于
                        // 取出栈中操作符和数栈中两个数进行运算，再将结果放回数栈
                        double result;
                        double a = number->data[number->top]; // 第二个操作数
                        pop(number);
                        double b = number->data[number->top];
                        pop(number); // 第一个操作数

                        result = cal(c, a, b);

                        push(number, result);
                        pop(sign); // 操作符出栈
                    }
                    else // ch优先级高于栈中操作符
                        break;
                }
                sign->top++;
                sign->data_c[sign->top] = ch;
                std::cin.get(ch);
            }
        }
        else if (ch == ')')
        {
            while (sign->data_c[sign->top] != '(')
            {
                char c = sign->data_c[sign->top];
                double result;
                double a = number->data[number->top];
                pop(number);
                double b = number->data[number->top];
                pop(number);
                result = cal(c, a, b);
                push(number, result);
                pop(sign);
            }
            pop(sign); // 把左括号推出栈
            std::cin.get(ch);
        }
    }
    while (!is_empty(sign))
    {   // 当栈不空，继续取出操作符进行计算
        char c = sign->data_c[sign->top];
        double result;
        double a = number->data[number->top];
        pop(number);
        double b = number->data[number->top];
        pop(number);
        result = cal(c, a, b);
        push(number, result);
        pop(sign);
    }
    if(flag){
        printf("%.2lf\n", number->data[number->top]);
    }
    delete number;
    delete sign;
    return flag;
}

int main(){
    while(1){
        if(!calculate())
            break;
    }
    return 0;
}