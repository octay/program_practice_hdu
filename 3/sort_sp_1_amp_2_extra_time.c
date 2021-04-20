# include<stdio.h>
# include<stdlib.h>
# include<time.h>
# include<windows.h>
# include<assert.h>
# define SIZE_A 100
# define MAX_NUM 99
// 在此更改随机生成的数组的长度和随机数最大值,同时记得更改zen_print()中的打印模式
# define BK_NUM 10
// 桶的数量,请随着随机数最大值更改,同时更改bucket_sort()中的存入桶部分

typedef int DataType;
struct bucket{
    DataType a[SIZE_A];
    int num;
};
void swap(DataType *a, DataType *b);
void random(DataType a[], int n, int range_max_num);
void zen_print(DataType a[], int n);        // n表示存放元素的个数

void bubble_sort(DataType a[], int n);      // 冒泡排序

void counter_sort(DataType a[], DataType sorted_a[], int n, int maxkey);        // 计数排序
void counter_sort_clear(DataType a[], DataType sorted_a[], int n, int maxkey);  // 更简明的计数排序

void bucket_sort_extra(DataType a[], DataType sorted_a[], int n, int num_bucket);     // 桶排序
// 对于桶排序, 进行了一些修改,使得它可以完成与计数排序差不多的功能

int main(int argc, char const *argv[]) {
    DataType a[SIZE_A], sorted_a[SIZE_A];
    int i;
    time_t start_t, end_t;
    double diff_t;

    time(&start_t);
    for(int i = 1; i <= 1000000; i++){
        srand(time(0));
        random(a, SIZE_A, MAX_NUM);
        // 计数排序和桶排序
        counter_sort(a, sorted_a, SIZE_A, MAX_NUM);
        // bucket_sort_extra(a, sorted_a, SIZE_A, BK_NUM);
    }
    time(&end_t);
    diff_t = difftime(end_t, start_t);  // 求函数运行前后的时间差

    zen_print(sorted_a, SIZE_A);
    printf("time of executing is %f sec \n", diff_t);

    system("pause");
    return 0;
}

void swap(DataType *a, DataType *b){
    DataType temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void random(DataType a[], int n, int range_max_num){
    int i;
    for(i = 0; i < n; i++) a[i] = rand() % (range_max_num + 1);    // 随机数存入数组
}

void zen_print(DataType a[], int n){
    int i;
    for(i = 0; i < n; i++){
        printf("%4d", a[i]);
    }
    printf("\n");
}

void bubble_sort(DataType a[], int n){
    int i, j;
    for(i = 0; i < n - 1; i++) for(j = 0; j < n - i - 1; j++){
        if(a[j] > a[j + 1]) swap(a + j, a + j + 1);
    }
}

void counter_sort(DataType a[], DataType sorted_a[], int n, int maxkey){
    int key, i;
    int count[maxkey + 1];
    for (key = 0; key <= maxkey; key++) count[key] = 0;
    for (i = 0; i < n; i++) count[a[i]]++;

    int start = 0, next;
    for (key = 0; key <= maxkey; key++){
        next = start + count[key];
        count[key] = start;
        start = next;
    }
    assert(start == n);

    for (i = 0; i < n; i++) sorted_a[count[a[i]]++] = a[i]; // 相同的元素会放在下一位
}

void counter_sort_clear(DataType a[], DataType sorted_a[], int n, int maxkey){
    int key, i;
    int count[maxkey + 1];
    for (key = 0; key <= maxkey; key++) count[key] = 0;
    for (i = 0; i < n; i++) count[a[i]]++;

    int pos = 0;
    for (key = 0; key <= maxkey; key++){
        for(i = 1; i <= count[key]; i++){
            sorted_a[pos++] = key;
        }
    }
}

void bucket_sort_extra(DataType a[], DataType sorted_a[], int n, int num_bucket){
    struct bucket bk[num_bucket];
    int i, j;
    int i4s = 0;    // i4s i for sorted_a

    for (i = 0; i < num_bucket; i++) {  // 初始化
        bk[i].num = 0;
    }

    for (i = 0; i < n; i++) {           // 存入桶
        int k = a[i] / 10;
        bk[k].a[bk[k].num] = a[i];
        bk[k].num ++;
    }

    for (i = 0; i < num_bucket; i++) {  // 处理每个桶
        if(bk[i].num == 0) continue;
        else if(bk[i].num == 1) sorted_a[i4s++] = bk[i].a[0];
        else{
            bubble_sort(bk[i].a, bk[i].num);    // 对于每个桶(数据2个及以上)使用了冒泡排序
            for(j = 0; j < bk[i].num; j++) sorted_a[i4s++] = bk[i].a[j];
        }
    }
}
