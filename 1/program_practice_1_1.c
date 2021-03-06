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

/*
void append(struct node *p, int n){      // 这是一开始编写的,不使用
    struct node *pnew = create();
    struct node *p_mr = p;
    while(p_mr -> next && n > p_mr -> next -> num){
        p_mr = p_mr -> next;
    }
    pnew -> num = n;
    pnew -> next = NULL;
    p_mr -> next = pnew;
};
*/

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
    struct node *ne_head = create();
    po_head -> next = NULL;
    ne_head -> next = NULL;         // po_head对应正数 ne_head对应负数
    int input_num;
/*  // 这是一开始编写的,不使用
    struct node *po = po_head, *ne = ne_node;
    while(1){
        scanf("%d", &input_num);
        if(!input_num) break;       // input_num为0时跳出循环
        else if(input_num>0) append(po, input_num);
        else append(ne, input_num);
    }
*/
    while (1){
        scanf("%d",&input_num);
        if(!input_num) break;       // input_num为0时跳出循环
        else if(input_num > 0) insert(po_head, input_num);
        else insert(ne_head, input_num);
    }

    printf("arranged series of positive number and negative number \n");
    print(po_head);
    destroy(po_head);
    print(ne_head);
    destroy(ne_head);

    return 0;
}
