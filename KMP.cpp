#include <iostream>
#include <string>

int* next_build(std::string patt){
    int next[patt.length()]={0};
    int *p = next;

    int prefix_len = 0; // 当前公共前后缀长度
    int i = 1;// 表示子串长度
    int j = 0;
    while (i < patt.length())
    {
        if(patt[prefix_len]==patt[i]){
            prefix_len += 1;
            j++;
            next[j] = prefix_len;
            i++;
        }
        else{
            if(prefix_len==0){
                j++;
                next[j] =0;
                i++;
            }
            else{
                prefix_len = next[prefix_len - 1];
            }
        }
    }
    return p;
}

void KMP(std::string str,std::string patt){
    int *p = next_build(patt);

    int i = 0;
    int j = 0;
    while(i<str.length()){
        if(str[i]==patt[j]){
            i++;
            j++;
        }
        else if(j>0){
            j = *(p+j-1);//不相同时 回退到前一个匹配成功的字符的next值
        }
        else{//第一个字符就匹配失败
            i++;
        }

        if(j==patt.length()){
            return;
        }
    }   
}