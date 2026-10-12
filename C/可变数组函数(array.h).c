#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
struct Array{
    int *array;
    int size;
}array1;
struct Array arraycreate(int size){
    struct Array a;
    a.array=NULL;
    a.size=0;
    if(size>0){
        a.array=(int *)malloc(sizeof(int)*size);
        if(a.array==NULL){
            return a;
        }
        a.size=size;
    }
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
void array_inflate(struct Array *a,int moresize);

int* arrayat(struct Array *a,int index){
    if (index>=a->size){                    /*越界才扩容*/
        int grow=index+1-a->size;
        array_inflate(a,grow>20?grow:20);
    }
    return &(a->array[index]);              /*封装,指针形式可以赋值*/
}
void array_inflate(struct Array *a,int moresize){
    int *p=(int *)realloc(a->array,sizeof(int)*(a->size+moresize));
    if(p==NULL){                            /*失败时保留原缓冲区,避免泄漏*/
        return;
    }
    a->array=p;
    a->size+=moresize;
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
    printf("\n");
    int cnt=0;
    int number=0;
    struct Array b=arraycreate(10);
    while(1){
        scanf("%d",&number);
       if(number==-1){
           break;
       }
       cnt++;
       *arrayat(&b,cnt-1)=number;
    }
    for (int i=0;i<cnt;i++){
        printf("%d ",*arrayat(&b,i));
    }
    arrayfree(&b);

    return 0;
}