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

void reverse(struct node *ori){
    struct node *ori_mr = ori;         // mr是mirror镜像的意思
    struct node *p, *q;                 // Atom的Tab对齐好烦,该换一个编辑器了
	p = ori_mr -> next;
	ori_mr -> next = NULL;
/*
    大概是这样实现的.先将p定义到ori_mr(简称o)后一个结点(简称ol),这是一个有具体数据的结点除非已经在链表末尾了.
    随后将ol赋NULL,这是暂时的,后面就不再是NULL啦.这个NULL会成为reversed链表的末尾
    q指向p p移至后一个 q指向的o的后一个 将q插入o与ol之间,当然啦,插入之后q就变成了ol
*/
	while(p){
		q = p;
		p = p -> next;
		q -> next = ori_mr -> next;
		ori_mr -> next = q;
    }
};

void reverse_ver2(struct node *ori) {
    struct node *ori_mr = ori;  // 在本程序中 ori_mr是在变化的，使用元ori来找到原先的链表头结点
    struct node *p, *q;
    struct node *r = ori_mr -> next;    // 第一个有数据的结点
    while (r -> next) {
        p = ori_mr;
        q = ori_mr;
        while(p -> next){
            q = p;
            p = p -> next;
        }
        q -> next = p -> next;  // NULL end of l
        p -> next = ori_mr -> next;
        ori_mr -> next = p;
        ori_mr = p;     // 下一个需要做插入处理的点就是在新处理的结点之后了就是说
    }
};

int main(void){
    struct node *po_head = create();
    struct node *ne_head = create();
    po_head -> next = NULL;
    ne_head -> next = NULL;         // po_head对应正数 ne_head对应负数
    int input_num;

    while (1){
        scanf("%d",&input_num);
        if(!input_num) break;       // input_num为0时跳出循环
        else if(input_num > 0) insert(po_head, input_num);
        else insert(ne_head, input_num);
    }

    printf("arranged series of positive number \n");
    print(po_head);
    reverse(po_head);
    printf("arranged and reversed series of positive number \n");
    print(po_head);
    destroy(po_head);

    printf("arranged series of negative number \n");
    print(ne_head);
    reverse(ne_head);
    printf("arranged and reversed series of negative number \n");
    print(ne_head);
    destroy(ne_head);

    return 0;
}
