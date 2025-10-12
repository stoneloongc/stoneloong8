//  Created by www.runoob.com on 15/11/9.
//  Copyright © 2015年 菜鸟教程. All rights reserved.
//
 
#include <stdio.h> 
#include <string.h>
 
// 删除字符串中指定字母函数
char* deleteCharacters(char* str, char* charSet) {
    // 用于存储要删除的字符的哈希表
    int hash[256] = {0}; // 使用256大小的数组来存储ASCII字符，初始化为0
    // 如果要删除的字符集为空，则直接返回原字符串
    if (charSet == NULL)
        return str;
    
    // 标记要删除的字符
    for (int i = 0; i < strlen(charSet); i++)
        hash[(unsigned char)charSet[i]] = 1; // 将要删除的字符的ASCII码位置标记为1
 
    int currentIndex = 0; // 用于追踪当前的字符串索引
    // 通过遍历字符串来删除指定的字符
    for (int i = 0; i < strlen(str); i++) {
        // 如果当前字符不在要删除的字符集中，则保留该字符
        if (!hash[(unsigned char)str[i]])
            str[currentIndex++] = str[i];
    }
    str[currentIndex] = '\0'; // 在字符串的末尾添加空字符，以表示字符串的结束
    return str;
}
 
int main() {
    char s[] = "a";      // 要删除的字母
    char s2[] = "aca";   // 目标字符串
    printf("%s\n", deleteCharacters(s2, s)); // 打印删除指定字符后的字符串
    return 0;
}
