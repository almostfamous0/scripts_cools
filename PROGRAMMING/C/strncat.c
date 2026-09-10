#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

#define DEBUGGING 1

int slen(char *s)
{
    register int i = 0;
    while (s[i++]);
    return i-1;
}

char *strlcat_diff(char *src, char *dst)
{
    register short size = slen(src);
    register int size2 = slen(dst);

    if (size2 > size){
       if (DEBUGGING)
          fprintf(stderr, "[!!!] NOT POSSIBLE BY SIZE CONCERNS!");
        return NULL;
      }    

    char *ptr = (char*) malloc(size);
    char *s = ptr;

    while (size2-- != 0){
        *s++ = *dst++;
        src++;
    }
    while (*src){
      *s++ = *src++;
    }

    *s = '\0';
    //while();  // ptr ---> dst ----> '\0';
        // return ptr - dst;  // Len of both src and dst  (or no...)
  return ptr;
}

void main()
{
  char *ptr1 = "VITOR";
  char *hey = "_VITOR_AND_MORE";

  char *p = strlcat_diff(hey, ptr1);
    printf("%s\n", p);
}
