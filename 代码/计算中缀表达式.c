#include<stdio.h>
#include<stdlib.h>
typedef struct node//链栈 
{
    char data;
    struct node *next;
}stack_node;
typedef struct node_float//链栈
{
    float data;
    struct node_float *next;
}stack_node_float;
char str[50];
//初始化链栈  带有头结点,头节点不存数据
stack_node* init_stack();
//初始化整形链栈 
stack_node_float* init_stack_float();
//压栈
void push_char(stack_node *opr_stack,char);
//压栈
void push_float(stack_node_float *opr_stack,float);
//出栈
char pop_char(stack_node *opr_stack);
//出栈
float pop_float(stack_node_float *opr_stack);
//打印栈   
void print_(stack_node *top);
//匹配函数  如果说匹配成功的话该栈最后为空
int sy_match(stack_node*);
//中缀转后缀
void covt(stack_node*,stack_node*);
//倒置栈
void invrn(stack_node*,stack_node*);
//计算后缀表达式
void clt(stack_node*);

int main()
{
    stack_node *opr_stack=init_stack(),*opd_stack=init_stack();//opr是运算符栈,opd是最后保存后缀表达式的栈
    covt(opr_stack,opd_stack);
    return 0;
}

stack_node* init_stack()
{
	stack_node *top=(stack_node*)malloc(sizeof(stack_node));
	top->next=NULL;
	return top;
}
stack_node_float* init_stack_float()
{
    stack_node_float *top=(stack_node_float*)malloc(sizeof(stack_node_float));
    top->next=NULL;
    return top;
}
void push_char(stack_node *opr_stack,char c)
{
    if(opr_stack==NULL)return;
    stack_node *newnode=(stack_node*)malloc(sizeof(stack_node));
    newnode->data=c;
    newnode->next=opr_stack->next;
    opr_stack->next=newnode;
}
void push_float(stack_node_float *opr_stack,float c)
{
    if(opr_stack==NULL)return;
    stack_node_float *newnode=(stack_node_float*)malloc(sizeof(stack_node_float));
    newnode->data=c;
    newnode->next=opr_stack->next;
    opr_stack->next=newnode;
}
char pop_char(stack_node *opr_stack)
{
    char tmp_char;
    if(opr_stack==NULL || opr_stack->next==NULL)return '\0';//栈空直接返回 也就是判断下溢
    stack_node *tmp=opr_stack->next;
    opr_stack->next=opr_stack->next->next;
    tmp_char=tmp->data;
    free(tmp);tmp=NULL;
    return tmp_char;
}
float pop_float(stack_node_float *opr_stack)
{
    float tmp_float;
    if(opr_stack==NULL || opr_stack->next==NULL)return '\0';//栈空直接返回 也就是判断下溢
    stack_node_float *tmp=opr_stack->next;
    opr_stack->next=opr_stack->next->next;
    tmp_float=tmp->data;
    free(tmp);tmp=NULL;
    return tmp_float;
}
void print_(stack_node *top)
{
    stack_node *tmp=top->next;
    while(tmp!=NULL)
    {printf("%c ",tmp->data);tmp=tmp->next;}
    printf("\n");
}
int sy_match(stack_node *opr_stack)
{
    if(opr_stack==NULL)return 0;
    int i=0;            //操作字符串用的标志符
	fgets(str,50,stdin);
    while(str[i]!='\0')
    {
        if(str[i]=='(' || str[i]=='[' || str[i]=='{')push_char(opr_stack,str[i]);
        else if(str[i]==')' || str[i]==']' || str[i]=='}')
        {
            switch (str[i])
            {
            case ')':
            if(pop_char(opr_stack)!='('){printf("匹配失败\n");return 0;}    
                break;
            case ']':
            if(pop_char(opr_stack)!='['){printf("匹配失败\n");return 0;}
                break;
            case '}':
            if(pop_char(opr_stack)!='{'){printf("匹配失败\n");return 0;}  
                break;
            default:
                break;
            }
        }
        i++;
    }
    if(opr_stack->next!=NULL){printf("匹配失败\n");return 0;}//如果栈中还有剩余的括号,匹配失败
    else {/*printf("匹配成功\n");*/return 1;}
}
void covt(stack_node* opr_stack,stack_node* opd_stack)//opr最终会是空栈.
{
    if(sy_match(opr_stack)==0)return;
    //if(opr_stack->next==NULL){printf("opr NULL\n");return;}
    int i=0;char c='\0';
    while(str[i]!='\0')                             //遍历表达式
    {
        if(str[i]>='0' && str[i]<='9')          //操作数的话直接压栈(opd)
        push_char(opd_stack,str[i]);
        else if(str[i]=='(' || str[i]=='[' || str[i]=='{' ) 
        push_char(opr_stack,str[i]);            //左括号的话直接压栈(opr)
        else if(str[i]=='+' || str[i]=='-' || str[i]=='*' || str[i]=='/')
        {
            if(opr_stack->next==NULL)push_char(opr_stack,str[i]);//如果opr栈是空的,直接入栈
            else if(str[i]=='+' || str[i]== '-')
            {
                while(opr_stack->next->data=='+' || opr_stack->next->data=='-' || opr_stack->next->data=='*' || opr_stack->next->data=='/')
                push_char(opd_stack,pop_char(opr_stack));//把opr栈中所有优先级大于等于当前操作符的操作符弹出,并且压入opd栈
                push_char(opr_stack,str[i]);              //然后把当前运算符压入opr栈
                // if(opr_stack->data=='(' || opr_stack->data=='[' || opr_stack->data=='{')
                // pop_char(opr_stack);
            }
            else if(str[i]=='*' || str[i]=='/')
            {
                while( opr_stack->next->data=='*' || opr_stack->next->data=='/')
                push_char(opd_stack,pop_char(opr_stack));//把opr栈中所有优先级大于等于当前运算符的运算符弹出,并且压入opd栈
                push_char(opr_stack,str[i]);             //然后把当前运算符压入opr栈
            }
            
        }
        else if(str[i]==')' || str[i]==']' || str[i]=='}')//弹出'('之前所有的运算符.
        {
            switch (str[i])
            {
            case ')':
            c=pop_char(opr_stack);
            while(c!='(')//出栈直到与之对应的左括号
            {
                push_char(opd_stack,c); 
                c=pop_char(opr_stack);//最后弹出左括号,且不会进入opd栈
            }
            break;
            case ']':
            if(pop_char(opr_stack)!='[')
            while(c!='[')//出栈直到与之对应的左括号
            {
                push_char(opd_stack,c);
                c=pop_char(opr_stack);//最后弹出左括号,且不会进入opd栈
            }
                break;
            case '}':
            if(pop_char(opr_stack)!='{')
            while(c!='{')//出栈直到与之对应的左括号
            {
                push_char(opd_stack,c);
                c=pop_char(opr_stack);//最后弹出左括号,且不会进入opd栈
            }
            break;
            default:
            break;
            }
        }
        i++;
    }
    invrn(opd_stack,opr_stack);
    //print_(opr_stack);//打印转置后的后缀表达式
    clt(opr_stack);
}
void invrn(stack_node* opd_stack,stack_node* opr_stack)
{
    stack_node *tmp=opd_stack->next;
    while(tmp!=NULL)
    {
        push_char(opr_stack,tmp->data);
        tmp=tmp->next;
    }
}
void clt(stack_node* top)
{
    stack_node* tmp=top->next;//第一个结点是空的
    stack_node_float* ttmp=init_stack_float();
    while(tmp!=NULL)
    {
        if(tmp->data>='0' && tmp->data<='9')//是数字就压栈
        push_float(ttmp,(tmp->data-'0'));
        else
        {
            switch (tmp->data)
            {
            case '+':
               push_float(ttmp,(pop_float(ttmp->next)+pop_float(ttmp)));break;
            case '-':
                push_float(ttmp,(pop_float(ttmp->next)-pop_float(ttmp)));break;
            case '*':
                push_float(ttmp,(pop_float(ttmp->next)*pop_float(ttmp)));break;
             case '/':
                push_float(ttmp,(pop_float(ttmp->next)/pop_float(ttmp)));break;
            default:break;
            }
        }
        tmp=tmp->next;
    }
    printf("%f\n",pop_float(ttmp));
}