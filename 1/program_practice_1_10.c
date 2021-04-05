#include<stdio.h>
#include<stdlib.h>
#define MAX 100
struct node_s{      // 在一系列s_l中使用
    int data;
    struct node_s *next;
};

struct node_q{      // 在一系列q_l中使用
    int data;
    struct node_q *next;
};

typedef struct stack_array{
    int data[MAX];
    int top;    // 一个指向栈顶的变量
} s_a;

typedef struct queue_array{
    int data[MAX];
    int i_head;
    int i_rear;     // data[i_rear]不储存有效数值.
} q_a;

typedef struct stack_linked{
    struct node_s *p_top;
} s_l;

typedef struct queue_linked{
    struct node_q *p_head, *p_rear;
} q_l;
// 数组用函数创建倒也不必.
// s_a 栈用数组表示. q_a 队列用数组表示. s_l 栈用链表表示. q_l 队列用链表表示.
// q_a_2依然是队列用数组表示,对于某些q_a系列函数不太满意所以在q_a系列的基础上更新了一下
void init_s_a(s_a *a){
    a -> top = -1;  // 空栈
}

void init_q_a(q_a *a){
	int i;
    for(i=0; i < MAX; i++) a -> data[i] = 0;
    a -> i_head = 0;
    a -> i_rear = 0;
}

struct node_s *create_s_l(){
    struct node_s *p = (struct node_s *)malloc(sizeof(struct node_s));
    if(p == NULL){
        printf("error out of memory \n");
        exit(-1);
    }
    else return p;
}

void init_s_l(s_l *a){
    a -> p_top = create_s_l();
    a -> p_top -> next = NULL;
}

struct node_q *create_q_l(){
    struct node_q *p = (struct node_q *)malloc(sizeof(struct node_q));
    if(p == NULL){
        printf("error out of memory \n");
        exit(-1);
    }
    else return p;
}

void init_q_l(q_l *a, int ro){
    struct node_q *p_first = create_q_l();
    int i = 1;
    p_first -> next = p_first;
    for(i = 1; i <= ro; i++){
        struct node_q *pnew = create_q_l();
        pnew -> next = p_first -> next;
        p_first -> next = pnew;
    }
    a -> p_head = a -> p_rear = p_first;
}

void clear_s_a(s_a *a){
    a -> top = -1;
}

void clear_q_a(q_a *a){
	int i;
    for(i=0; i < MAX; i++) a -> data[i] = 0;
    a -> i_head = 0;
    a -> i_rear = 0;
}

void clear_s_l(s_l *a){
    struct node_s *p = a -> p_top;
    struct node_s *q, *r;
    while(p -> next){
        q = p -> next;
        r = p -> next -> next;
        free(q);
        p -> next = r;
    }
    a -> p_top -> next= NULL;
}

void clear_q_l(q_l *a){
    a -> p_head = a -> p_rear;
}

void destroy_s_l(s_l *a){       // s_l q_l有destroy函数,因为它们都是分配了动态储存空间.
    clear_s_l(a);
    struct node_s *p = a -> p_top;
    free(p);
}

void destroy_q_l(q_l *a){
    struct node_q *p = a -> p_head;
    struct node_q *q, *r;
    while(p -> next != p){
        q = p -> next;
        r = p -> next -> next;
        free(q);
        p -> next = r;
    }
    free(p);
}

int is_empty_s_a(s_a *a){
    return (a -> top == -1) ? 1: 0;
}

int is_empty_s_l(s_l *a){
    return (a -> p_top -> next)? 0: 1;
}

int is_empty_q_a(q_a *a){
    return (a -> i_head == a -> i_rear) ? 1: 0;
}

int is_empty_q_l(q_l *a){
    return (a -> p_head == a -> p_rear) ? 1: 0;
}

int is_full_s_a(s_a *a){
    return (a -> top == MAX - 1) ? 1: 0;
}

int is_full_q_a(q_a *a){
    return (a -> i_rear == MAX) ? 1: 0;
}

int is_full_q_a_2(q_a *a){
    return ((a -> i_rear + 1) % MAX == a -> i_head) ? 1: 0;
}

int is_full_q_l(q_l *a){
    return (a -> p_head == a -> p_rear -> next) ? 1: 0;
}

int length_s_a(s_a *a){
    return (a -> top + 1);
}

int length_s_l(s_l *a){
    struct node_s *p = a -> p_top;
    int length = 0;
    while(p -> next){
        length ++;
        p = p -> next;
    }
    return length;
}

int length_q_a(q_a *a){
    return a -> i_rear - a -> i_head;
}

int length_q_a_2(q_a *a){
    int e = a -> i_rear - a -> i_head;
    return (e > 0) ? e: e + MAX;
}

int length_q_l(q_l *a){
    struct node_q *p = a -> p_head;
    int length = 0;
    while(p -> next != a -> p_rear){
        length ++;
        p = p -> next;
    }
    return length;
}

int get_top_s_a(s_a *a){        // 最后输入的元素
    if(is_empty_s_a(a)) return 0;
    else return (a -> data[a -> top]);
}

int get_first_q_a(q_a *a){      // 第一个输入的元素
    if(is_empty_q_a(a)) return 0;
    else return a -> data[a -> i_head];
}

int get_top_s_l(s_l *a){        // 最后输入的元素
    if(is_empty_s_l(a)) return 0;
    else return a -> p_top -> next -> data;
}

int get_last_q_a(q_a *a){       // 最后输入的元素
    if(is_empty_q_a(a)) return 0;
    else return a -> data[a -> i_rear - 1];
}

int get_last_q_a_2(q_a *a){
    if(is_empty_q_a(a)) return 0;
    else{
        int e = a -> i_rear - 1;
        if(e < 0) e += MAX;
        return a -> data[e];
    }
}

void pop_s_a(s_a *a){           // 最后输入的元素
    if(is_empty_s_a(a)){
        printf("overflow pop_s_a() execute not \n");
        exit(-1);
    }
    else{
        a -> top --;
    }
}

void pop_s_l(s_l *a){           // 最后输入的元素
    if(is_empty_s_l(a)){
        printf("overflow pop_s_l() execute not \n");
        exit(-1);
    }
    else{
        struct node_s *p = a -> p_top -> next;
        struct node_s *q = p -> next;
        free(p);
        a -> p_top -> next = q;
    }
}

void pop_q_a(q_a *a){
    // 最后输入的元素. 由于它由数组表示这一性质允许q_a删除最后输入的元素. 稍后会有删除q_a第一个输入的元素的函数.
    if(is_empty_q_a(a)){
        printf("overflow pop_q_a() execute not \n");
        exit(-1);
    }
    else{
        a -> i_rear --;
    }
}

void pop_q_a_2(q_a *a){
    if(is_empty_q_a(a)){
        printf("overflow pop_q_a_2() execute not \n");
        exit(-1);
    }
    else{
        if(a -> i_rear == 0) a -> i_rear = MAX -1;
        else a -> i_rear --;
    }
}

void pop_q_l(q_l *a){       // 第一个输入的元素
    if(is_empty_q_l(a)){
        printf("overflow pop_q_l() execute not \n");
        exit(-1);
    }
    else{
        a -> p_head = a -> p_head -> next;
    }
}

void del_front_q_a(q_a *a){     // 第一个输入的元素. 其实这个函数才应该被命名为pop_q_a.
    if(is_empty_q_a(a)){
        printf("overflow del_front_q_a() execute not \n");
        exit(-1);
    }
    else{
        a -> i_head ++;
    }
}

void del_front_q_a_2(q_a *a){
    if(is_empty_q_a(a)){
        printf("overflow del_front_q_a_2() execute not \n");
        exit(-1);
    }
    else{
        if(a -> i_head == MAX - 1) a -> i_head = 0;
        else a -> i_head ++;
    }
}

void push_s_a(s_a *a, int e){
    if(is_full_s_a(a)){
        printf("overflow push_s_a() execute not \n");
        exit(-1);
    }
    else{
        a -> top ++;
        a -> data[a -> top] = e;
    }
}

void push_s_l(s_l *a, int e){
    struct node_s *p = create_s_l();
    p -> data = e;
    p -> next = a -> p_top -> next;
    a -> p_top -> next = p;
}

void push_q_a(q_a *a, int e){
    if(is_full_q_a(a)){
        printf("overflow push_q_a() execute not \n");
        exit(-1);
    }
    else{
        a -> data[a -> i_rear] = e;
        a -> i_rear ++;
    }
}

void push_q_a_2(q_a *a, int e){
    if(is_full_q_a_2(a)){
        printf("overflow push_q_a_2() execute not \n");
        exit(-1);
    }
    else{
        a -> data[a -> i_rear] = e;
        if(a -> i_rear == MAX -1) a -> i_rear = 0;
        else a -> i_rear ++;
    }
}

void push_q_l(q_l *a, int e){
    if(is_full_q_l(a)){
        printf("overflow push_q_l() execute not \n");
        exit(-1);
    }
    else{
        a -> p_rear -> next -> data = e;
        a -> p_rear = a -> p_rear -> next;
    }
}

void add_front_q_a(q_a *a, int e){  // 由于它由数组表示这一性质允许q_a在最前输入.
    if(a -> i_head == 0){
        printf("overflow add_front_q_a() execute not \n");
        exit(-1);
    }
    else{
        a -> i_head --;
        a -> data[a -> i_head] = e;
    }
}

void add_front_q_a_2(q_a *a, int e){
    if(a -> i_head == 0){
        printf("overflow add_front_q_a_2() execute not \n");
        exit(-1);
    }
    else{
        if(a -> i_head == 0) a -> i_head = MAX - 1;
        else a -> i_head --;
        a -> data[a -> i_head] = e;
    }
}

void print_s_a(s_a *a){
    int top_mr = a -> top;
    while(top_mr != -1){
        printf("%d ", a -> data[top_mr]);
        top_mr --;
    }
    printf("\nowari \n");
}

void print_s_l(s_l *a){
    struct node_s *p = a -> p_top;
    while(p -> next){
        printf("%d ", p -> next -> data);
        p = p -> next;
    }
    printf("\nowari \n");
}

void print_q_a(q_a *a){
    int i = a -> i_head;
    while(i != a -> i_rear){
        printf("%d ", a -> data[i]);
        i ++;
    }
    printf("\nowari \n");
}

void print_q_a_2(q_a *a){
    int i = a -> i_head;
    while(i != a -> i_rear){
        if(i == MAX) i = 0;

        printf("%d ", a -> data[i]);
        i ++;
    }
    printf("\nowari \n");
}

void print_q_l(q_l *a){
    struct node_q *p;
    p = a -> p_head;
    while(p != a -> p_rear){
        printf("%d ", p -> next -> data);
        p = p -> next;
    }
    printf("\nowari\n");
}

// 有两种main()函数可供选择.第一种是使用s_a和q_a,第二种是使用s_l和a_l.
// 也就是,第一种是使用 栈用数组表示 和 队列用数组表示 ,第二种是使用 栈用链表表示 和 q_l 队列用链表表示.
// 在main()函数上下添加 /* */ 即可.默认第一种,因为数组不容易出错.

int main(void){
    s_a po;
    q_a ne;
    int inputed;
    init_s_a(&po);
    init_q_a(&ne);

    while(~scanf("%d", &inputed)){
        if(inputed > 0){
            push_s_a(&po, inputed);
        }
        else if(inputed < 0){
            push_q_a_2(&ne, inputed);
        }
        else break;
	}

    print_s_a(&po);
    print_q_a_2(&ne);
    return 0;
}

/*
int main(void){
    s_l po;
    q_l ne;
    int inputed;
    init_s_l(&po);
    init_q_l(&ne, MAX);

    while(~scanf("%d", &inputed)){
        if(inputed > 0){
            push_s_l(&po, inputed);
        }
        else if(inputed < 0){
            push_q_l(&ne, inputed);
        }
        else break;
	}

    print_s_l(&po);
    print_q_l(&ne);

    destroy_s_l(&po);
    destroy_q_l(&ne);

    return 0;
}
*/
