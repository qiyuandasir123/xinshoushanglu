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
void zfind(Node * head,int g){
    Node *p=head-> next;
    int i;
    while (p!=NULL&&p->value!=g){
        p=p->next;
        i++;
    }
    if (p->value==g){
    printf("%d",p->value);
    printf("查找的位置为：%d\n",i+1);}
}
void wfind(Node * head,int i){
    Node *p=head-> next;
    for (int a=0;a<i;a++){
        p=p->next;
    }
    printf("第%d个节点的值为：%d\n",i,p->value);
}

int main(void){
    SetConsoleOutputCP(65001);
    Node *L=(Node*)malloc(sizeof(Node));   /* 头结点: 不放数据 */
    L->next=NULL;
    Node *tail=L;                          /* 尾巴从头结点开始 */
    int n;
    printf("请输入要存的数据个数：");
    scanf("%d",&n);
    for (int i=0;i<n;i++){
        int number;
        if(scanf("%d",&number)!=1)
            break;
        Node *s=(Node*)malloc(sizeof(Node));
        s->value = number;
        s->next=NULL;
        tail->next=s;
        tail=s;
    }
    int i=0;
    for (Node *s=L->next;s!=NULL;s=s->next){
        i++;
    }
    printf("节点数为：%d\n",i);
    zfind(L,25);
    wfind(L,1);
    freeList(L);
    return 0;
}