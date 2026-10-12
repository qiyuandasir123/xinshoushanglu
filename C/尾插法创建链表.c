#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
typedef struct _node{
    int value;
    struct _node *next;
}Node;
void freeList(Node *head)
{
    while (head!= NULL) {
        Node *next = head->next;   // ① 先存住下一个
        free(head);                // ② 再释放当前
        head = next;               // ③ 移到下一个
    }
}
int main(void){
    SetConsoleOutputCP(65001);
    int n;
    char line[128];
    scanf("%d%*c",&n);
    Node *head=NULL;
    Node *tail=NULL;
    printf("尾插法创建链表");
    for (int i=0;i<n;i++){
        int number;
        if(fgets(line,sizeof(line),stdin)==NULL||line[0]=='\n'||line[0]==' '){
            break;
        }
        sscanf(line,"%d",&number);
        Node*p=(Node *)malloc(sizeof(Node));
        p->value=number;
        p->next=NULL;
        if(head==NULL){
            head=tail=p;
        }
        else{
            tail->next=p;
            tail=p;
        }   
    }
    freeList(head);
    return 0;
}


