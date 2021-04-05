#include<stdio.h>
#include<stdlib.h>
// 按照出列顺序输出原始编号顺序. extra付按照原始编号顺序输出出列顺序.
struct node{        // 写了半天才想起来可以用typedef
    int num;        // 这里的num是存储顺序的,但是有很多函数可以从之前的题目复制所以就写num了
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

void append(struct node *p, int n){
    struct node *pnew = create();
    struct node *p_mr = seek_tail(p);
    pnew -> num = n;
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
        append(p_list, i);
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

    joseph_c(p_list, n);
    system("pause");
    return 0;
}
