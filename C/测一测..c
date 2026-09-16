#include <stdio.h>
#include <stdlib.h>
int main() {
    int i=1;
    int const *p=&i;
    printf("*p=%d\n",*p);
    printf("p=%d\n",p);
    *p++;
    printf("*p++=%d\n",*p);
    p++;
    printf("p++=%d\n",p);
    return 0;
}
