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
    Node *L=(Node*)malloc(sizeof(Node));   /* 头结点: 不放数据 */
    if (L==NULL){
        return 1;
    }
    L->next=NULL;
    Node *tail=L;                          /* 尾巴从头结点开始 */
    int n; 
    printf("请输入要存的数据个数：\n");
    while (scanf("%d",&n)!=1 || n<0){
        if (feof(stdin)){                 /* 输入已结束，再循环就是死循环 */
            printf("输入结束，退出\n");
            freeList(L);
            return 1;
        }
        printf("请重新输入：");
        int ch;                           /* 清掉这一行的非法内容，否则 scanf 会反复读到它 */
        while ((ch=getchar())!='\n' && ch!=EOF) { }
        if (ch==EOF){
            printf("输入结束，退出\n");
            freeList(L);
            return 1;
        }
    }
    for (int i=0;i<n;i++){
        int number;
        if(scanf("%d",&number)!=1)
            break;
        Node *s=(Node*)malloc(sizeof(Node));
        if (s==NULL){
            freeList(L);
            return 1;
        }
        s->value=number;
        s->next=L->next;
        L->next=s;
    }
    int i=0;
    for (Node *s=L->next;s!=NULL;s=s->next){
        i++;
    }
    printf("节点数为：%d\n",i);
    int cnt=0;
    for (Node *s=L->next;s!=NULL;s=s->next){
        printf("%d:%d\n",cnt,s->value);
        cnt++;
    }
    freeList(L);
    return 0;
}