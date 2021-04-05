#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
/*
大型前置推导,这个真的折磨人.不仅需要时不时对调来获得绝对值,还需要对绝对值添加符号
前者 后者 和 差 求和/差[绝对值]具体需要将两者的[绝对值]进行什么操作
正数-大 正数-小   正 两者加 正 前减后
正数-小 正数-大   正 两者加 负 后减前
正数-大 负数-小   正 前减后 正 两者加
正数-小 负数-大   负 后减前 正 两者加
负数-大 正数-小   负 前减后 负 两者加
负数-小 正数-大   正 后减前 负 两者加
负数-大 负数-小   负 两者加 负 前减后
负数-小 负数-大   负 两者加 正 后减前
*/
struct node{
    int digit;
    struct node *prev;
    struct node *next;
};

typedef struct ori_struct_big_num{
    int num_digits;
    int sign;       // 在init()函数中初赋值为0.用1提示这是负数,因为负数需要小心处理.
    struct node *p_head, *p_tail;
} big_num;

big_num input();                // 输入
void print(big_num bn);         // 打印
big_num add(big_num *pa, big_num *pb);              // 相加
big_num subtract(big_num *pa, big_num *pb);         // 相减
void destroy(big_num *bn);      // 销毁
void init(big_num *bn);         // 初始
void append_digit(big_num *bn, int digit);          // 追加
void append_front_digit(big_num *bn, int digit);    // 顶置
// void pop_digit(big_num *bn);    // 移后
int compare_absolute(big_num *pa, big_num *pb);     // 比较
void normalize(big_num *bn);    // 范化
struct node *create();          // 创建
// big_num multiply_ori(big_num *pa, big_num *pb);     // 相乘
big_num multiply_krtb(big_num *pa, big_num *pb);    // 唐唾
big_num multiply_digit(big_num *bn, int digit);     // 数乘
big_num fetch(big_num *pa, int start, int end);     // 画位



big_num input(){
    big_num result;
    init(&result);

    char ch;
    do{
    	ch = getchar();
        if(ch == '-') result.sign = 1;  // 负数的表示
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
    if(bn.sign) putchar('-');
    struct node *p = bn.p_head;
    while(p-> next){
        printf("%d", p -> next -> digit);
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
        int digit = p1 -> digit - p2 -> digit + borrow;
        borrow = 0;
        if (digit < 0){
            digit += 10;
            borrow = -1;
        }
        append_front_digit(p_res, digit);
        p1 = p1 -> prev;
        p2 = p2 -> prev;
    }

    while(p1 != pa -> p_head){
        int digit = p1 -> digit + borrow;
        borrow = 0;
        if (digit < 0){
            digit += 10;
            borrow = -1;
        }
        append_front_digit(p_res, digit);
        p1 = p1 -> prev;
    }

    assert(borrow == 0);
    normalize(&result);
    // 在这里使用这个函数是因为防止出现如下情况的输出(如果没有调用)
    // 616 600      // 输入
    // 1216         // 输出
    // 016
    return result;
}

/*
// 存在未知bug
big_num multiply_ori(big_num *pa, big_num *pb){
    big_num result, store_mul_digit;
    init(&result);
    append_digit(&result, 0);
    int each_pb_num;

    while(! (pb -> num_digits == 1 && pb -> p_tail -> digit == 0) ){
        // ! (pb -> num_digits == 1 && pb -> p_tail -> digit == 0) 其实是pb储存不为0
        each_pb_num = pb -> p_tail -> digit;
        store_mul_digit = multiply_digit(pa, each_pb_num);
        result = add(&result, &store_mul_digit);
        destroy(&store_mul_digit);
        append_digit(pa, 0);
        pop_digit(pb);      // 就当是除以10
    }
    return result;
}
*/
big_num multiply_krtb(big_num *pa, big_num *pb){    //////////////////////
    if (pb -> num_digits == 1) return multiply_digit(pa, pb -> p_tail -> digit);
    else if(pa -> num_digits == 1) return multiply_digit(pb, pa -> p_tail -> digit);

    int m = pa -> num_digits;
    int n = pb -> num_digits;
    int h = (m > n ? m : n) / 2;    // 对半分罢了
    // x = a * base ^ h + b * base ^ h; y = c * base ^ h + d * base ^ h;
    big_num a, b, c, d;
    a = fetch(pa, 0, m - h);
    b = fetch(pa, m - h, m);
    c = fetch(pb, 0, n - h);
    d = fetch(pb, n - h, n);

    big_num z0, z1, z2;
    // z0 = b * d; z1 = a * d + c * b = (a + b) * (c + d) - (z2 + z0); z2 = a * c;
    z0 = multiply_krtb(&b, &d);
    z2 = multiply_krtb(&a, &c);

    big_num apb, cpd, apbmcpd, z0pz2, zp, result;       // p +; m *;
    apb = add(&a, &b);
    cpd = add(&c, &d);

    destroy(&a);
    destroy(&b);
    destroy(&c);
    destroy(&d);

    apbmcpd = multiply_krtb(&apb, &cpd);
    z0pz2 = add(&z0, &z2);
    z1 = subtract(&apbmcpd, &z0pz2);

    int i;
    for(i = 0; i < 2 * h; ++ i) append_digit(&z2, 0);   // z2 * 10 ^ 2h
    for(i = 0; i < h; ++ i) append_digit(&z1, 0);       // z1 * 10 ^ 2h
    zp = add(&z2, &z1);
    result = add(&zp, &z0);     // result = z2 * 10 ^ 2h + z1 * 10 ^ 2h + z0

    destroy(&z0);
    destroy(&z1);
    destroy(&z2);
    destroy(&apb);
    destroy(&cpd);
    destroy(&apbmcpd);
    destroy(&z0pz2);
    destroy(&zp);
    return result;
}

big_num fetch(big_num *pa, int start, int end){
    big_num result;
    init(&result);
    int i = 0;
    struct node *p = pa -> p_head -> next;
    while (i < start && p != NULL) {
        p = p -> next;
        ++ i;
    }
    while (i < end && p != NULL) {
        append_digit(&result, p -> digit);
        p = p -> next;
        ++ i;
    }
    normalize(&result);
    return result;
}

big_num multiply_digit(big_num *bn, int digit){
    big_num result;
    init(&result);
    if(digit == 0){
        append_digit(&result, 0);
        return result;
    }

    int carry = 0;
    struct node *p = bn -> p_tail;
    int digit4res;
    while (p != bn -> p_head) {
        digit4res = p -> digit * digit + carry;
        carry = digit4res / 10;
        digit4res %= 10;
        append_front_digit(&result, digit4res);
        p = p-> prev;
    }
    if(carry != 0) append_front_digit(&result, carry);
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
    bn -> sign = 0;
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

/*
// 存在未知bug
void pop_digit(big_num *bn){    // 相当于是数/10的操作了吧
    struct node *p = bn -> p_tail;
    bn -> p_tail = bn -> p_tail -> prev;
    bn -> p_tail -> next = NULL;
    free(p);
    -- bn -> num_digits;
}
*/

int compare_absolute(big_num *pa, big_num *pb){
    int flag = 0;   // 用来标记前者和后者的大小.1 前者更大. -1 后者更大. 0 两者一样大
    struct node *p1, *p2;
    p1 = pa -> p_head;
    p2 = pb -> p_head;

    if(pa -> num_digits > pb -> num_digits){
        flag = 1;
        return flag;
    }

    else if(pa -> num_digits < pb -> num_digits){
        flag = -1;
        return flag;
    }

    else{
        while(p1 -> next && p2 -> next){    // 同位的两个数字理想地不会出现一方NULL的情况
            p1 = p1 -> next;
            p2 = p2 -> next;
            if(p1 -> digit > p2 -> digit){
                flag = 1;
                return flag;
            }
            else if(p1 -> digit < p2 -> digit){
                flag = -1;
                return flag;
            }
            else{
                continue;
            }
            return flag;
        }
    }
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
    big_num a, b, sum, dif, pro;
    int flag = 0;

    printf("input two numbers \n");
    a = input();
    b = input();
    flag = compare_absolute(&a, &b);
/*  // 测试能否正常存储符号
    print(a);
    printf("\n");
    print(b);
    printf("\n");
*/
/*  // 测试是否能正确判断两者的绝对值大小
    printf("%d\n", flag);
*/
    if(a.sign == 0 && b.sign == 0 && flag == 0){
    // 正数 正数 同绝对值
        sum = add(&a, &b);
        dif = subtract(&a, &b);     // subtract(&a, &b) 就是一般通过的数字0
    }
    else if(a.sign == 0 && b.sign == 1 && flag == 0){
    // 正数 负数 同绝对值
        sum = subtract(&a, &b);
        dif = add(&a, &b);
    }
    else if(a.sign == 1 && b.sign == 0 && flag == 0){
    // 负数 正数 同绝对值
        sum = subtract(&a, &b);
        dif = add(&a, &b);
        dif.sign = 1;
    }
    else if(a.sign == 1 && b.sign == 1 && flag == 0){
    // 负数 负数 同绝对值
        sum = add(&a, &b);
        sum.sign = 1;
        dif = subtract(&a, &b);
    }
    else if(a.sign == 0 && b.sign == 0 && flag == 1){
    // 正数-大 正数-小   正 两者加 正 前减后
        sum = add(&a, &b);
        dif = subtract(&a, &b);
    }
    else if(a.sign == 0 && b.sign == 0 && flag == -1){
    // 正数-小 正数-大   正 两者加 负 后减前
        sum = add(&a, &b);
        dif = subtract(&b, &a);
        dif.sign = 1;
    }
    else if(a.sign == 0 && b.sign == 1 && flag == 1){
    // 正数-大 负数-小   正 前减后 正 两者加
        sum = subtract(&a, &b);
        dif = add(&a, &b);
    }
    else if(a.sign == 0 && b.sign == 1 && flag == -1){
    // 正数-小 负数-大   负 后减前 正 两者加
        sum = subtract(&b, &a);
        sum.sign = 1;
        dif = add(&a, &b);
    }
    else if(a.sign == 1 && b.sign == 0 && flag == 1){
    // 负数-大 正数-小   负 前减后 负 两者加
        sum = subtract(&a, &b);
        sum.sign = 1;
        dif = add(&a, &b);
        dif.sign = 1;
    }
    else if(a.sign == 1 && b.sign == 0 && flag == -1){
    // 负数-小 正数-大   正 后减前 负 两者加
        sum = subtract(&b, &a);
        dif = add(&a, &b);
        dif.sign = 1;
    }
    else if(a.sign == 1 && b.sign == 1 && flag == 1){
    // 负数-大 负数-小   负 两者加 负 前减后
        sum = add(&a, &b);
        sum.sign = 1;
        dif = subtract(&a, &b);
        dif.sign = 1;
    }
    else if(a.sign == 1 && b.sign == 1 && flag == -1){
    // 负数-小 负数-大   负 两者加 正 后减前
        sum = add(&a, &b);
        sum.sign = 1;
        dif = subtract(&b, &a);
    }

    if(flag == -1) pro = multiply_krtb(&b, &a);  // 还是需要和sum dif运算一样调换顺序.
    else pro = multiply_krtb(&a, &b);

    if(a.sign != b.sign) pro.sign = 1;

    print(sum);
    printf("\n");
    print(dif);
    printf("\n");
    print(pro);
    printf("\n");

    destroy(&a);
    destroy(&b);
    destroy(&sum);
    destroy(&dif);
    destroy(&pro);

    system("pause");
    return 0;
}
