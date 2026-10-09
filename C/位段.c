#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
struct Uo{
    unsigned int a:1;
    unsigned int b:1;
    unsigned int c:2;
    //int d:4;
};
void printiner(unsigned int number ){
    unsigned changer=1u<<31;
    for (;changer;changer=changer>>1){
        if(number&changer){
            printf("1");
        }else{
            printf("0");
        }
    }
    printf("\n");

}
int main(void)
{
    SetConsoleOutputCP(65001);
    struct Uo uo;
    uo.a=1;
    uo.b=1;
    uo.c=3;
    //uo.d=0;
    printf("sizeof(uo)=%d\n",sizeof(uo));
    printiner(*(int*)&uo);
    return 0;
}
