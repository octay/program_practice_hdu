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
    // 但为什么我用了一个返回值呢,我也说不清.但这样做在主函数中更加直观.
};

struct node *split_even(struct node *p){    // 一开始想用osu来代替even,我不对劲...
    struct node *even_head = create();
    even_head -> next = NULL;           // 把末尾设置成NULL很必要,新添的元素放在NUll之前就好
    struct node *even = even_head;
    //struct code *even_t = even -> next; // even_t是指向even的末尾的.理想地,even_t始终是NULL
    struct node *p_mr = p;              // mr是mirror镜像的意思
    struct node *prspnn;
    // 反正是实现删除结点的指针,定义变量可以随意一些吧(被打)
    // prspnn用来保存(preserve) p_mr -> next -> next的地址,懒得想一个更好的变量名了.
    while(p_mr -> next){
        if(p_mr -> next -> num % 2 == 0){
            prspnn = p_mr -> next -> next;
            // 用prspnn保存p_mr -> next -> next的地址,后面再把prspnn接到p_mr -> next
            p_mr -> next -> next = even -> next;    // 理想地,这里调用even -> next始终是NULL.
            even -> next = p_mr -> next;            // 添加到even_head开头的链表中
            p_mr -> next = prspnn;
            even = even -> next;
        }
        else p_mr = p_mr -> next;
        // 这里一开始没有写else,即
        // p_mr = p_mr -> next
        // 这是错的,因为if语句块执行后,p_mr -> next -> num已经是新的待识别对象了.
    }
    return even_head;
    // 感觉这个函数会有难以捉摸的bug,不管了先这样写吧.
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

    // 没有定义combined_head的话,直接用ne_head来打印就行.
    combined_head = combine(ne_head, po_head);
    printf("arranged and combined series of number \n");
    print(combined_head);

    struct node *odd, *even;
    // 定义odd其实可有可无,因为split的作用是用来拆掉所有存有偶数的结点的,直接使用combined_head就好.但是,再定义一个odd会更加直观.
    odd = combined_head;
    even = split_even(combined_head);

    printf("arranged series of odd number and even number \n");
    print(odd);
    print(even);
    destroy(odd);
    destroy(even);

    return 0;
}
