#include<stdio.h>
#include<stdlib.h>
// 按照原始编号顺序输出出列顺序.
struct node{
    int num;
    int order;  // order存储出列的顺序
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

struct node *seek_tail(struct node *p){
    struct node *p_mr = p;
    while(p_mr -> next) p_mr = p_mr -> next;
    return p_mr;        //  既然是判断p_mr -> next是否为空,那么返回的就是末尾结点辣
};

void destroy(struct node *p){
    while(p){
        struct node *q = p -> next;
        free(p);                        // 逐个清空
        p = q;
    }
};

void destroy2(struct node *p){  // 对于环链表更加友好.但总感觉会有巨大bug,没有使用
    struct node *q = p -> next, *r = p -> next -> next;
    q -> next = NULL;           // 先在第一个存储有效数据的结点后断开,成为结点的末尾.可以抽象地理解成r指向了断后链表的头结点
    while(r){
        q = r -> next;
        free(r);                // 逐个清空
        r = q;
    }
    free(p);
};

void append(struct node *p, int n){
    struct node *pnew = create();
    struct node *p_mr = seek_tail(p);
    pnew -> num = n;
    pnew -> next = NULL;
    p_mr -> next = pnew;
};

void append2(struct node *p, int n){
    struct node *pnew = create();
    struct node *p_mr = seek_tail(p);
    pnew -> num = n;
    pnew -> order = -1;     // order设置成了-1,表示还没有出列
    pnew -> next = NULL;
    p_mr -> next = pnew;
};

struct node *locate(struct node *p, int n){
    struct node *p_mr = p;
    while(p_mr -> next && p_mr -> next -> num != n) p_mr = p_mr -> next;
    // 如果p_mr -> next不为空,那么说明p_mr是所需查找的所在结点的前一个结点,因为理想地只有这两种可能
    if(p_mr -> next) return p_mr -> next;   // 返回所在结点
    else {
        printf("find element not \n");
        exit(-1);
    }
};

void joseph_c(struct node *p, int n){
    int count = 0;
    struct node *p_del;     //反正是实现删除的结点,命名随意一些也行吧...
    while(p -> next){
        count++;
        if(count == n){
            count = 0;
            printf("%d ", p -> next -> num);    // 打印出列的数字
            p_del = p -> next;
            p -> next = p_del -> next;             // 删除出列的结点

            if(p -> num == p -> next -> num){
                // 如果删除出列的结点之后链表中只有一个结点,先打印后释放再跳出循环。
                // 如果不是用像这样的if-else语句的话,会一直打印最后一个数据.
                // 不过这样写可能会有bug,但没有找到其他解决办法,以后优化一下.
                printf("%d ", p -> num);
                free(p);
                break;
            }
            else free(p_del);
        }
        else p = p -> next; // 若删除之后, p -> next 已经是新的数字了.
    }
    printf("\nowari \n");
};

void joseph_c2(struct node *p, int m, int n){
    // m为人数 n为出列条件数
    int c_order = 0, c_time = 0;    // c_order 用来记出列次数 c_time 用来记报数
    p = p -> next;          // 直接跳过op(?不是)
    while(p){
        if(p -> order == -1){   // 先判断是否还在队列中,若在则报数
            c_time++;
        }
        if(c_time == n){        // 判断是否应该出列
            c_time = 0;
            c_order ++;
            p -> order = c_order;
        }
        if(c_order == m) break;   // 都出列了,就大胆用break;
        p = p -> next;
    }
};

int main(void){
    struct node *p_list = create();
    p_list -> next = NULL;
    int i, m, n;

    scanf("%d%d", &m, &n);
    if( !(m > 0 && n > 0) ){   // m和n应该大于0.
        printf("overflow \n");
        exit(0);
    }

    for(i = 1; i <= m; i++){    // 把序号添加到链表中
        append2(p_list, i);     // order设置成了-1,表示还没有出列
    }

    locate(p_list, m) -> next = locate(p_list, 1);
    // seek_tail(p_list) -> next = p_list -> next; 也可以.
    // 因为这一部分就是要找到链表的末尾,再与头部相接.
/*
    // 测试是否正常存储
    struct node *p = p_list -> next;
    for(i = 1; i <= m; i++){
        printf("%d ",p -> num);
        p = p -> next;
    }
    printf("\n");
*/

    joseph_c2(p_list, m, n);       // joseph_c2()只排序,没有打印,所以在结束后再打印.

    struct node *p1 = p_list -> next, *q1;
    for(i = 1; i <= m; i++){
        printf("%d ",p1 -> order);
        q1 = p1 -> next;
        free(p1);
        p1 = q1;
    }

    printf("\nowari \n");
    system("pause");
    return 0;
}
