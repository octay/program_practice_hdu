#include<stdio.h>
#include<stdlib.h>
// 按照出列顺序输出原始编号顺序.
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

struct node *joseph_c3(struct node *p, int n){
    int count = 0;
    struct node *p_del;     //反正是实现删除的结点,命名随意一些也行吧...
    struct node *p_new_list_head = create(); // 理想地,新链的头结点
    struct node *p_new_list = p_new_list_head;
    while(p -> next){
        count++;
        if(count == n){
            count = 0;
            printf("%d ", p -> next -> num);    // 打印出列的数字
            p_del = p -> next;
            p -> next = p_del -> next;             // 删除出列的结点
            p_new_list -> next = p_del;
            p_del -> next = NULL;
            p_new_list = p_del;

            if(p -> num == p -> next -> num){
                // 如果删除出列的结点之后链表中只有一个结点,先打印后释放再跳出循环。
                // 如果不是用像这样的if-else语句的话,会一直打印最后一个数据.
                // 不过这样写可能会有bug,但没有找到其他解决办法,以后优化一下.
                printf("%d ", p -> num);
                p_new_list -> next = p;
                p -> next = NULL;
                break;
            }
        }
        else p = p -> next; // 若删除之后, p -> next 已经是新的数字了.
    }
    printf("\nowari \n");

    // 在返回p_new_list_head前,我们先把链表组成环形吧.
    p -> next = p_new_list_head -> next;    // 刚刚跳出循环的p是末尾结点.
    return p_new_list_head;
};

struct node *joseph_c3_violent(struct node *p, int n){
    // 暴力截取即将打印的数字,并添加到新的链表中.
    int count = 0, store_num;
    struct node *p_del;     //反正是实现删除的结点,命名随意一些也行吧...

    struct node *p_new_list_head = create(); // 理想地,新链的头结点
    p_new_list_head -> next = NULL;

    while(p -> next){
        count++;
        if(count == n){
            count = 0;
            printf("%d ", p -> next -> num);    // 打印出列的数字

            store_num = p -> next -> num;
            append(p_new_list_head, store_num);   // 直接append()好耶

            p_del = p -> next;
            p -> next = p_del -> next;             // 删除出列的结点

            if(p -> num == p -> next -> num){
                // 如果删除出列的结点之后链表中只有一个结点,先打印后释放再跳出循环。
                // 如果不是用像这样的if-else语句的话,会一直打印最后一个数据.
                // 不过这样写可能会有bug,但没有找到其他解决办法,以后优化一下.
                printf("%d ", p -> num);

                store_num = p -> num;
                append(p_new_list_head, store_num);

                free(p);
                break;
            }
            else free(p_del);
        }
        else p = p -> next; // 若删除之后, p -> next 已经是新的数字了.
    }
    printf("\nowari \n");

    // 在返回p_new_list_head前,我们先把链表组成环形吧.
    // 在violent版中,调用seek_tail()可以快速获取末尾结点.
    seek_tail(p_new_list_head) -> next = p_new_list_head -> next;
    return p_new_list_head;
};

int main(void){
    struct node *p_list = create();
    p_list -> next = NULL;
    int i, m, num4count = 0, each_count[100] = {0}, num_of_count = 0;
    // 定义了好多东西,集中说一下吧.
    // m 人数  num4count 存储输入的出列数  each_count 用数组来存储每一次的出列数  num_of_count 约瑟夫环轮数
    // 至于i?不过是用来控制循环的工具罢了(无情)

    printf("input the number of people and the number to be out of line in each round ");
    printf("then enter \'0\' to finish the input \n");

    scanf("%d", &m);
    if(m <= 0){     // m应该大于0.
        printf("overflow \n");
        exit(0);
    }

    while(~scanf("%d", &num4count)){
        if(num4count < 0){  // 不应该小于0
            printf("overflow \n");
            exit(0);
        }
        else if(num4count == 0){
            break;
        }
        else{
            each_count[num_of_count] = num4count;
    		num_of_count ++;
        }
	}
    if(num_of_count == 0){
        printf("owari \n");
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
    int exed = 0;  // 已经执行的次数
    struct node *p_after, *p_before = p_list;
    while(exed != num_of_count - 1){
        // 为什么用num_of_count - 1呢.因为最后一次需要joseph_c()来释放内存,所以已执行次数比轮数差1时停止while循环.
        p_after = joseph_c3(p_before, each_count[exed]);
        p_before = p_after;
        exed ++;
    }
    // 试试调用joseph_c3_violent()吧

/*
    // 测试是否正常存储
    struct node *p1 = p_after_n -> next;
    for(i = 1; i <= m; i++){
        printf("%d ",p1 -> num);
        p1 = p1 -> next;
    }
    printf("\n");
*/
    joseph_c(p_before, each_count[exed]);
    system("pause");
    return 0;
}
