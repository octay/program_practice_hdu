#include<stdio.h>
#include<stdlib.h>

struct node{
    int num;
    struct node *next;
};

struct node *create(){
    struct node *p;
    p = (struct node*)malloc(sizeof(struct node));
    if(p == NULL){
        printf("create node error. \n");
        exit(-1);
    }
    return p;
};

void insert(struct node *p, int n){
    struct node *pnew = create();
    struct node *p_mr;                  // mr是mirror镜像的意思
    p_mr = p;
    pnew -> num = n;
    while(p_mr -> next && n > p_mr -> next -> num){
        p_mr = p_mr -> next;
    }
    pnew -> next = p_mr -> next;
    p_mr -> next = pnew;
};

struct node *combine(struct node *mae, struct node *ushiro){
    // mae 在前面的链表头结点地址 ushiro 在后面的链表头结点地址
    // 本程序实现 mae是存储负数的链表头结点地址 ushiro是存储正数的链表头结点地址
    struct node *p_s_mae_t = mae;
    // 寻找mae链表的末端,莫名有一种春节挨家挨户拜年的感觉
    while(p_s_mae_t -> next){
        p_s_mae_t = p_s_mae_t -> next;
    }
    p_s_mae_t -> next = ushiro -> next; // 因为头结点是空的所以直接-> next
    return mae;
    // 其实没有必要返回什么,如果是void类型，在主函数直接使用mae的实参(一个指针)
    // 在主函数中也有相应的一系列的注释,可以找一下.
    // 但为什么我用了一个返回值呢,我也说不清.但这样做在主函数中更加直观一些.
};

void destroy(struct node *p){
    while(p){
        struct node *q = p -> next;
        free(p);                        // 逐个清空
        p = q;
    }
};

void print(struct node *p){
    p = p -> next;
    while(p){
        printf("%d ", p -> num);
        p = p -> next;
    }
    printf("\n");
};

int main(void){
    struct node *po_head = create();
    struct node *ne_head = create();    // po_head对应正数 ne_head对应负数
    struct node *combined_head;         // 合并后的,不定义也可以
    po_head -> next = NULL;
    ne_head -> next = NULL;
    int input_num;

    while (1){
        scanf("%d",&input_num);
        if(!input_num) break;       // input_num为0时跳出循环
        else if(input_num > 0) insert(po_head, input_num);
        else insert(ne_head, input_num);
    }

    printf("arranged series of positive number and negative number \n");
    print(po_head);
    print(ne_head);
    // 没有定义combined_head的话,直接用ne_head来打印或者销毁就行.

    combined_head = combine(ne_head, po_head);
    printf("arranged and combined series of number \n");
    print(combined_head);
    destroy(combined_head);

    return 0;
}
