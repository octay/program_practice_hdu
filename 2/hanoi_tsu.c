#include<stdio.h>
#include<stdlib.h>
#define MAX 100
// 用解决问题栈好像和递归一样,难以理解.
// 每个问题使用单独的struct结构体,储存处理个数以及初始位 缓冲位 目标位
// 当然,这里使用数组来存放所有的struct prob或者说是problem
// 所以不需要在实现操作主体的函数hanoi_tsu()中销毁栈
void hanoi_tsu(int n, char x, char y, char z);

typedef struct prob{
    int n;
    char x;
    char y;
    char z;
} problem;

typedef struct stack_array{
    problem data[MAX];
    int top;    // 一个指向栈顶的变量
} s_a;

void init_s_a(s_a *a){
    a -> top = -1;  // 空栈
}

int is_empty_s_a(s_a *a){
    return (a -> top == -1) ? 1: 0;
}

int is_full_s_a(s_a *a){
    return (a -> top == MAX - 1) ? 1: 0;
}

void push_prob(s_a *a, problem e){
    if(is_full_s_a(a)){
        printf("overflow push_prob() execute not \n");
        exit(-1);
    }
    else{
        a -> top ++;
        a -> data[a -> top] = e;
    }
}

void pop_prob(s_a *a){
    if(is_empty_s_a(a)){
        printf("overflow pop_prob() execute not \n");
        exit(-1);
    }
    else{
        a -> top --;
    }
}

problem get_top_prob(s_a *a){        // 最后输入的元素
    if(is_empty_s_a(a)){
        printf("overflow get_top_prob() execute not \n");
        exit(-1);
    }
    else return (a -> data[a -> top]);
}

int count = 0;
int main(void) {
    int n;
    scanf("%d", &n);
    hanoi_tsu(n, 'A', 'B', 'C');
    system("pause");
    return 0;
}

void hanoi_tsu(int n, char x, char y, char z){
    s_a st_prob;
    init_s_a(&st_prob);
    problem s = {n, x, y, z};
    push_prob(&st_prob, s);

    while (! is_empty_s_a(&st_prob)){
        problem prob2solve = get_top_prob(&st_prob);
        pop_prob(&st_prob);
        if(prob2solve.n == 1){
            printf("%c -> %c   %d\n", prob2solve.x, prob2solve.z, ++count);
        }
        else{
            problem sub1 = {prob2solve.n - 1, prob2solve.x, prob2solve.z, prob2solve.y};
            problem sub2 = {1, x, y, z};
            problem sub3 = {prob2solve.n - 1, prob2solve.y, prob2solve.x, prob2solve.z};
            push_prob(&st_prob, sub3);
            push_prob(&st_prob, sub2);
            push_prob(&st_prob, sub1);
        }
    }
}
