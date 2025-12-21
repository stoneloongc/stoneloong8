#include <stdio.h> 
#include <string.h>
char* deleteCharacters(char* str, char* charSet) {
    int hash[256] = {0}; 
    if (charSet == NULL)
        return str;
    for (int i = 0; i < strlen(charSet); i++)
        hash[(unsigned char)charSet[i]] = 1; 
 
    int currentIndex = 0; 
    for (int i = 0; i < strlen(str); i++) {
        if (!hash[(unsigned char)str[i]])
            str[currentIndex++] = str[i];
    }
    str[currentIndex] = '\0'; 
    return str;
}
 
int main() {
    char s[] = "a";      
    char s2[] = "aca";   
    printf("%s\n", deleteCharacters(s2, s)); 
    return 0;
}
