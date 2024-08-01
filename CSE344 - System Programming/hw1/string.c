#include "string.h"
#include <stdio.h>

int strcmpp(const char* s1, const char* s2){
    while(*s1 && *s2 && (*s1 == *s2)){
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

int strln(const char* s1){
    
    if(s1[0] == '\0'){
        return 0;
    }

    return 1 + strln(s1 + 1);
}

char* strchrr(const char *str, int character) {
    while (*str != '\0') {
        if (*str == character) {
            return (char *)str;
        }
        str++;
    }

    return NULL;
}

char* strtokk(char* str, char delimeter)
{
    static char* input = NULL;
    char *ret;

    if (str != NULL)
        input = str;
 
    if (input == NULL)
        return NULL;
 
    char result[1000];
    for (int i = 0; i < 1000; i++)
    {
        result[i] = 'z';
    }
    
    int i = 0;
 
    for (; input[i] != '\0'; i++) {
 
        if (input[i] != delimeter)
            result[i] = input[i];
 
        else {
            result[i] = '\0';
            input = input + i + 1;
            ret = result;
            return ret;
        }
    }
 
    result[i] = '\0';
    input = NULL;

    ret = result;
    return ret;
}

void  *my_memset(void *b, int c, int len)
{
  unsigned char *p = b;
  while(len > 0)
    {
      *p = c;
      p++;
      len--;
    }
  return(b);
}

char* strcpyy(char* destination, const char* source) {
    char* originalDestination = destination;

    while (*source != '\0') {
        *destination = *source;
        destination++;
        source++;
    }
    *destination = '\0';

    return originalDestination;
}
