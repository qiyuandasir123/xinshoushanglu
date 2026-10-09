#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
struct Array{
    int *array;
    int size;
}array1;
struct Array arraycreate(int size){
    struct Array a;
    a.array=(int *)malloc(sizeof(int)*size);
    a.size=size;
    return a;
}
void arrayfree(struct Array *a){
    free(a->array);
    a->array=NULL;
    a->size=0;
}
int arraysize(struct Array *a){
    return a->size;                     /*封装*/
}
int* arrayat(struct Array *a,int index){
    return &(a->array[index]);              /*封装,指针形式可以赋值*/
}
int main(void)
{
    SetConsoleOutputCP(65001);
    struct Array a=arraycreate(10);
    for(int i=0;i<arraysize(&a);i++){
        *arrayat(&a,i)=i;
    }
    for(int i=0;i<arraysize(&a);i++){
        printf("%d ",*arrayat(&a,i));
    }
    arrayfree(&a);

    return 0;
}