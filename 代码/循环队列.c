//输入给定的10个数据建立循环队列，显示循环队列中所有数据元素；
//从键盘输入出队元素个数n（1<=n<=10），将n个元素出队后显示队中剩余元素。
//进行简单的修改就可以实现任意数量的插入,删除
#include<stdio.h>
#define max 11
typedef int emtype;
typedef struct 
{
    emtype data[max];
    int front,rear;
}xqueun;


//初始化循环队列
void initQueun(xqueun*);
//插入num个元素
void enqueue(xqueun*,int num);
//打印所有元素
void print_(xqueun);
//出队num个元素
void pop_n(xqueun*);
//打印队头元素
void print_top(xqueun*);

int main()
{
    xqueun Q;
    initQueun(&Q);
    enqueue(&Q,10);
    print_(Q);
    pop_n(&Q);
    //print_(Q);
    print_top(&Q);
    return 0;
}

void initQueun(xqueun* Q)
{
    Q->front=Q->rear=max-1;
}
void enqueue(xqueun* Q,int num)
{
    emtype tmp=0;
    while(num>0)
    {
        if((Q->rear+1)%max==Q->front){printf("上溢\n");return;}
        scanf("%d",&tmp);Q->data[Q->rear]=tmp;
        Q->rear=(Q->rear+1)%max;//队列实际长度等于rear-1
        num--;
    }
    //Q->rear--;  //------
}
void print_(xqueun Q)//不能改变原队列
{
    if(Q.front==Q.rear){printf("队列为空\n");return;}
    //printf("front:%d rear:%d\n",Q.front,Q.rear);
    while(Q.front!=Q.rear)
    {
        printf("%d ",Q.data[Q.front]);
        Q.front=(Q.front+1)%max;
    }
    printf("\n");
}
void pop_n(xqueun* Q)//需要改动队列
{
    if(Q->front==Q->rear){printf("队列为空\n");return;}
    int num=0;scanf("%d",&num);//printf("出队元素数量:%d\n",num);
    while(num-- && (Q->front!=Q->rear) )
    {
        printf("%d ",Q->data[Q->front]);
        Q->front=(Q->front+1)%max;
    }
    printf("\n");
}
void print_top(xqueun* Q)
{
    printf("%d\n",Q->data[Q->front]);
}