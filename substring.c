#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// This code is a result of studying various material online about inline assemebly programming in C. I claim no right over certain extracts of code which were encountered in the research.
static inline char * sub_str(char * dest, char *src, int s_idx, int edix){
  int length = edix - s_idx + 1;
    int i;
     
    for(i = 0; i < length; i++)
    {
        *(dest + i) = *(src + s_idx + i);
    }
    *(dest + length) = '\0';
  return dest;
}

static inline char * asm_sub_str(char * dest, char *src, int s_idx, int edix){
  __asm__ __volatile__(   "cld\n\t"
                            "rep\n\t"
                            "movsb\n\t"
                            "xor %%al, %%al\n\t"
                            "stosb"
                            :
                            :"S"(src + s_idx), "D"(dest), "c"(edix - s_idx + 1)
                        );
  return dest;
}

int main(int argc,char **argv) {
  char* my_string = "Linux Kernel";
    char sub_string[100], asm_sub_string[100];
    sub_str(sub_string, my_string, 0, 5);
    asm_sub_str(asm_sub_string, my_string, 0, 5);
}
