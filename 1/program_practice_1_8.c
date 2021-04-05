#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

struct node{
    int digit;
    struct node *prev;
    struct node *next;
};

typedef struct ori_struct_big_num{
    int num_digits;
    struct node *p_head, *p_tail;
} big_num;

big_num input();                // 输入
void print(big_num bn);         // 打印
big_num add(big_num *pa, big_num *pb);              // 相加
big_num subtract(big_num *pa, big_num *pb);         // 相减
void destroy(big_num *bn);      // 销毁
void init(big_num *bn);         // 初始
void append_digit(big_num *bn, int digit);          // 追加
void append_front_digit(big_num *bn, int digit);    // 定置
void normalize(big_num *bn);    // 范化
struct node *create();          // 创建

big_num input(){
    big_num result;
    init(&result);

    char ch;
    do{
    	ch = getchar();
	}while(ch <'0'|| ch > '9');
    while(ch >= '0' && ch <= '9'){
        append_digit(&result, ch - '0');
        ch = getchar();
    }

    normalize(&result);
    return result;
}

void print(big_num bn){     // 不换行
    assert(bn.num_digits > 0 && bn.p_head -> next);
    struct node *p = bn.p_head -> next;
    while(p){
        printf("%d", p -> digit);
        p = p-> next;
    }
}

big_num add(big_num *pa, big_num *pb){
    big_num result, *p_res = &result;
    init(p_res);
    int carry = 0;
    struct node *p1, *p2;
    p1 = pa -> p_tail;
    p2 = pb -> p_tail;

    while(p1 != pa -> p_head && p2 != pb -> p_head){
        int digit = p1 -> digit + p2 -> digit + carry;
        carry = digit / 10;
        digit %= 10;
        append_front_digit(p_res, digit);
        p1 = p1 -> prev;
        p2 = p2 -> prev;
    }

    while(p1 != pa -> p_head){
        int digit = p1 -> digit + carry;
        carry = digit / 10;
        digit %= 10;
        append_front_digit(p_res, digit);
        p1 = p1 -> prev;
    }

    while(p2 != pb -> p_head){
        int digit = p2 -> digit + carry;
        carry = digit / 10;
        digit %= 10;
        append_front_digit(p_res, digit);
        p2 = p2 -> prev;
    }

    if(carry){
        append_front_digit(p_res, carry);
    }

    return result;
}

big_num subtract(big_num *pa, big_num *pb){
    big_num result, *p_res = &result;
    init(p_res);
    int borrow = 0;// 初值设为0,好像也没有用啊.
    struct node *p1, *p2;
    p1 = pa -> p_tail;
    p2 = pb -> p_tail;

    // 保证第一个大数不小于第二个大数,题目如是说.
    while(p1 != pa -> p_head && p2 != pb -> p_head){
        int digit = p1 -> digit - p2 -> digit + 10 + borrow;
        if (digit < 10) borrow = -1;
        else borrow = 0;    // 这段if-else语句用borrow = (digit < 10) * -1;也可以,但这实在是太反人类了.
        digit %= 10;
        append_front_digit(p_res, digit);
        p1 = p1 -> prev;
        p2 = p2 -> prev;
    }

    while(p1 != pa -> p_head){
        int digit = p1 -> digit + borrow + 10;
        if (digit < 10) borrow = -1;
        else borrow = 0;
        digit %= 10;
        append_front_digit(p_res, digit);
        p1 = p1 -> prev;
    }

    while(p2 != pb -> p_head){
        int digit = p2 -> digit + borrow + 10;
        if (digit < 10) borrow = -1;
        else borrow = 0;
        digit %= 10;
        append_front_digit(p_res, digit);
        p2 = p2 -> prev;
    }
    // 这样写肯定是错的,但是题目说保证第一个大数不小于第二个大数,所以理想地不会执行这个语句块.
    if(borrow){
        append_front_digit(p_res, borrow);
    }

    normalize(&result);
    // 在这里使用这个函数是因为防止出现如下情况的输出(如果没有调用)
    // 616 600      // 输入
    // 1216         // 输出
    // 016
    return result;
}

void destroy(big_num *bn){
    while(bn -> p_head != NULL){
        struct node *p = bn -> p_head;
        bn -> p_head = p -> next;
        free(p);
    }
}

void init(big_num *bn){
    struct node *p = create();
    bn -> p_head = bn -> p_tail = p;
    p -> next = p -> prev = NULL;
    bn -> num_digits = 0;
}

void append_digit(big_num *bn, int digit){
    if(bn -> num_digits == 1 && bn -> p_tail -> digit == 0){
        bn -> p_tail -> digit == digit;
        return;
    }
    struct node *p = create();
    p -> digit = digit;
    p -> next = NULL;
    p -> prev = bn -> p_tail;
    bn -> p_tail -> next = p;
    bn -> p_tail = p;
    ++ bn -> num_digits;
}

void append_front_digit(big_num *bn, int digit){
    struct node *p = create();
    p -> digit = digit;
    p -> next = bn -> p_head -> next;
    if(p -> next != NULL){
        p -> next -> prev = p;
    }
    p -> prev = bn -> p_head;
    bn -> p_head -> next = p;
    if(bn -> p_tail == bn -> p_head){
        bn -> p_tail = p;
    }
    ++ bn -> num_digits;
}

void normalize(big_num *bn){
    if(bn -> num_digits == 0) append_digit(bn, 0);
    while(bn -> num_digits > 1 && bn -> p_head -> next -> digit == 0){
        struct node *p;
        p = bn -> p_head -> next;
        bn -> p_head -> next = p -> next;
        p -> next -> prev = bn -> p_head;
        free(p);
        --bn -> num_digits;
    }
}

struct node *create(){
    struct node *p;
    p = (struct node *)malloc(sizeof(struct node));
    if(p == NULL){
        printf("error out of memory \n");
        exit(-1);
    }
    return p;
}

int main(void){
    big_num a, b, sum, dif;

    printf("input two numbers and make sure the former is greater than the latter \n");
    a = input();
    b = input();

    sum = add(&a, &b);
    print(sum);
    printf("\n");

    dif = subtract(&a, &b);
    print(dif);
    printf("\n");

    destroy(&a);
    destroy(&b);
    destroy(&sum);
    destroy(&dif);
    system("pause");
    return 0;
}
