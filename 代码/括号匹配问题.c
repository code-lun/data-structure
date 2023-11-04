//栈:后进先出
//注意边界问题,起始以及结束位置
//核心逻辑:
//读到左括号压栈,读到右括号就出栈一个元素,如果与读到的括号不匹配,失败
//最后栈不为空的话,失败(有单身左括号存在)  如:([()] 
//注意:此代码仅仅只是括号匹配,该代码注释偏多,因为我保留了调试代码,在某种程度上来说
//可以体现写代码的思路
#include<stdio.h>
#include<stdlib.h>
typedef struct node//链栈 
{
    char data;
    struct node *next;
}stack_node;

char str[50];

//初始化链栈
stack_node* init_stack();    
//压栈
void push_cahr(stack_node *top,char);
//出栈
char pop_char(stack_node *top);
//打印栈   
void print_(stack_node *top);
//匹配函数 
void sy_match(stack_node*);

int main()
{
	stack_node *top=init_stack();
    //push_cahr(top,'c');push_cahr(top,'b');push_cahr(top,'a');//调试代码
    //pop_char(top);pop_char(top);pop_char(top);pop_char(top);
    //print_(top);
    sy_match(top);
    return 0;
}

stack_node* init_stack()
{
	stack_node *top=(stack_node*)malloc(sizeof(stack_node));
	top->next=NULL;
	return top;
}
void push_cahr(stack_node *top,char c)
{
    if(top==NULL)return;
    stack_node *newnode=(stack_node*)malloc(sizeof(stack_node));
    newnode->data=c;
    newnode->next=top->next;
    top->next=newnode;
    printf("%c压栈\n",c);
}
char pop_char(stack_node *top)
{
    char tmp_char;
    if(top==NULL || top->next==NULL)return '\0';//栈空直接返回 也就是判断下溢
    stack_node *tmp=top->next;
    top->next=top->next->next;
    tmp_char=tmp->data;
    free(tmp);tmp=NULL;
    printf("%c出栈\n",tmp_char);
    return tmp_char;
}
void print_(stack_node *top)
{
    stack_node *tmp=top->next;
    while(tmp!=NULL)
    {printf("%c ",tmp->data);tmp=tmp->next;}
    printf("\n");
}
void sy_match(stack_node *top)
{
    if(top==NULL)return;
    int i=0;            //操作字符串用的标志符
	fgets(str,50,stdin);
    //printf("%s\n",str);
    //while(str[i]!='\0'){printf("%c ",str[i]);i++;}
    //pop_char(top);pop_char(top);return;  脑抽了,都没有压栈,怎么出栈,当时还在这里看了一会儿;
    //if(str[0]==')' || str[0]==']' || str[0]=='}'){printf("匹配失败\n");return;}
    while(str[i]!='\0')
    {
        if(str[i]=='(' || str[i]=='[' || str[i]=='{')push_cahr(top,str[i]);
        else if(str[i]==')' || str[i]==']' || str[i]=='}')
        {
            switch (str[i])
            {
            case ')':
            if(pop_char(top)!='('){printf("匹配失败\n");return;}    
                break;
            case ']':
            if(pop_char(top)!='['){printf("匹配失败\n");return;}
                break;
            case '}':
            if(pop_char(top)!='{'){printf("匹配失败\n");return;}  
                break;
            default:
                break;
            }
        }
        i++;
    }
    if(top->next!=NULL)printf("匹配失败\n");//如果栈中还有剩余的括号,匹配失败
    else printf("匹配成功\n");
}
