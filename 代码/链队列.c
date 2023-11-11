//VS,devcpp编辑器同样可以运行   该代码是在linux环境下完成的,编译器是c17
//注释部分为c++版本,当然可以封装成类看上去更美观舒适,这里只是为了匹配编译器  注意c++版本需要改NULL为nullptr
//#include<iostream>
//using namespace std;
#include<stdio.h>
#include<stdlib.h>
typedef struct LinkNode     //链表节点
{
    int data;
    struct LinkNode* next;
}LinkNode;              
typedef struct LinkQueen    //链队列  结构体嵌套
{
    struct LinkNode *front,*tail; //使用链表节点(链表嵌套的体现)
}LinkQueen;


void init(LinkQueen*);      //初始化链队列,只是一个链表节点
void push_(LinkQueen*,int); //数据入队
void push_n(LinkQueen*);    //n个数据入队
void print_(LinkQueen*);    //打印队列所有元素
void pop_(LinkQueen*);      //元素出队
void print_top(LinkQueen*); //打印队首元素

int main()
{
    //LinkQueen *dequeen=new LinkQueen;
    //LinkNode* lnode=new LinkNode;
    LinkQueen *dequeen=(LinkQueen*)malloc(sizeof(LinkQueen));
    LinkNode* lnode=(LinkNode*)malloc(sizeof(LinkNode));
    init(dequeen);
    push_(dequeen,1); 
    push_(dequeen,2);
    push_(dequeen,3);
    //push_n(dequeen);//自定义元素入栈数量,自行启用
    print_(dequeen);
    pop_(dequeen);
    print_top(dequeen);
    return 0;
}

void init(LinkQueen* dequeen)
{
    if(dequeen==NULL)return;
    LinkNode *lnode=(LinkNode*)malloc(sizeof(LinkQueen));
    //LinkNode *lnode=new LinkNode;
    dequeen->front=dequeen->tail=lnode;
}
void push_(LinkQueen *dequeen,int data)
{
    LinkNode *lnode=(LinkNode*)malloc(sizeof(LinkNode));
    //LinkNode *lnode=new LinkNode;
    lnode->data=data;lnode->next=0;
    dequeen->tail->next=lnode;
    dequeen->tail=lnode;
    printf("%d 入队.\n",data);
    //cout<<data<<" 入队"<<endl;
}
void push_n(LinkQueen* dequeen)
{
    int cnt=0,data=0;
    printf("输入入队元素数量:");scanf("%d",&cnt);printf("\n");
    //int i=0;for(i=0;i<cnt;i++)//兼容写法 当然版本过低可能整型变量i的定义得放在第一行
    for(int i=0;i<cnt;i++)//c11及以上版本支持
    {
        scanf("%d",&data);
        LinkNode *lnode=(LinkNode*)malloc(sizeof(LinkNode));
        //LinkNode *lnode=new LinkNode;
        lnode->data=data;lnode->next=0;
        dequeen->tail->next=lnode;
        dequeen->tail=lnode;
        printf("%d 入队.\n",data);
        //cout<<data<<" 入队"<<endl;
    }
}
void print_(LinkQueen *dequeen)
{
    if(dequeen->front->next==NULL)return;
    LinkNode* tmp=dequeen->front->next;
    printf("栈中所有元素为:\n");
    //cout<<"栈中所有元素为:"<<endl;
    while(tmp!=0){  printf("%d ",tmp->data);/*cout<<tmp->data<<" ";*/tmp=tmp->next;}
    printf("\n");
}
void pop_(LinkQueen* dequeen)
{
    LinkNode* tmp=dequeen->front->next;
    printf("%d 出队\n",tmp->data);
    //cout<<tmp->data<<" 出队"<<endl;
    dequeen->front->next=dequeen->front->next->next;
    free(tmp);
    //delete tmp;
}
void print_top(LinkQueen* dequeen)
{
    printf("队头元素: %d\n",dequeen->front->next->data);
    //cout<<"队头元素: "<<dequeen->front->next->data<<endl;
}
