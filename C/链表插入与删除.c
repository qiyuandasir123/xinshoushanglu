#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
typedef struct node{
    int value;
    struct node *next;
}Node;
Node *createlist(int a);
void freelist(Node *head);
void printlist(Node *head);
void insertlist(Node *head,int i,int a);
void delete(Node *head,int i);
Node *createlist(int a){
    Node *head=(Node *)malloc(sizeof(Node));
    if (head==NULL){
        return NULL;
    }
    head->next=NULL;
    Node *tail=head;
    for (int i=0;i<a;i++){
        Node *s=(Node *)malloc(sizeof(Node));
        if (s==NULL){
            freelist(head);
            return NULL;
        }
        printf("请输入数据：");
        if (scanf("%d",&s->value)!=1){
            free(s);
            freelist(head);
            return NULL;
        }
        s->next=NULL;
        tail->next=s;
        tail=s;
    }
    return head;
}
void freelist (Node *head){
    while(head!=NULL){
        Node *p=head->next;
        free(head);
        head=p;
    }
}
void printlist(Node *head){
    head=head->next;
    while(head!=NULL){
        printf("%d ",head->value);
        head=head->next;
    }
    printf("\n");
}
void insertlist(Node *head,int i,int a){
    for (int j=0;j<i-1&&head->next!=NULL;j++){
        head=head->next;
    }
    Node *p=(Node *)malloc(sizeof(Node));
    if (p==NULL){
        return;
    }
    p->value=a;
    p->next=head->next;
    head->next=p;
}
void delete(Node *head,int i){
    for(int a=0;a<i-1&&head->next!=NULL;a++){
        head=head->next;
        if(head->next==NULL||head==NULL){
        return 1;
        }
    }
    Node*p=head->next;
    head->next=p->next;
    free(p);

}
int main(){
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    printf("请输入数据个数：\n");
    int n;
    scanf("%d",&n);
    if(n<0){
        printf("输入错误\n");
        return 1;
    }
    Node *head=createlist(n);
    if (head==NULL){
        printf("创建链表失败\n");
        return 1;
    }
    printlist(head);
    insertlist(head,2,1);
    printlist(head);
    delete(head,2);
    printlist(head);
    freelist(head);
    return 0;
}
