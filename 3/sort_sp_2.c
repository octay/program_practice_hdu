# include<stdio.h>
# include<stdlib.h>
# include<time.h>
# include<windows.h>
# include<assert.h>
# define SIZE_A 100
// 在此更改随机生成的数组的长度
# define BK_NUM 10
// 桶的数量,请随着随机数最大值更改,同时更改bucket_sort()中的存入桶部分

typedef double DataType;
struct bucket{
    DataType a[SIZE_A];
    int num;
};
void swap(DataType *a, DataType *b);
void random_r(DataType a[], int n);         // 生成[0,1)的实数
void zen_print(DataType a[], int n);        // n表示存放元素的个数

void bubble_sort(DataType a[], int n);      // 冒泡排序

void bucket_sort(DataType a[], DataType sorted_a[], int n, int num_bucket);     // 桶排序

int main(int argc, char const *argv[]) {
    DataType a[SIZE_A], sorted_a[SIZE_A];
    int i;
    time_t start_t, end_t;
    double diff_t;

    srand(time(0));
    random_r(a, SIZE_A);

    time(&start_t);
    bucket_sort(a, sorted_a, SIZE_A, BK_NUM);
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

void random_r(DataType a[], int n){
    int i;
    for(i = 0; i < n; i++) a[i] = rand() / (RAND_MAX + 1.0);
}

void zen_print(DataType a[], int n){
    int i;
    for(i = 0; i < n; i++){
        printf("%f ", a[i]);
    }
    printf("\n");
}

void bubble_sort(DataType a[], int n){
    int i, j;
    for(i = 0; i < n - 1; i++) for(j = 0; j < n - i - 1; j++){
        if(a[j] > a[j + 1]) swap(a + j, a + j + 1);
    }
}

void bucket_sort(DataType a[], DataType sorted_a[], int n, int num_bucket){
    struct bucket bk[num_bucket];
    int i, j;
    double standard = 1.0 / num_bucket;
    int i4s = 0;    // i4s i for sorted_a

    for (i = 0; i < num_bucket; i++) {  // 初始化
        bk[i].num = 0;
    }

    for (i = 0; i < n; i++) {           // 存入桶
        int k = (int)(a[i] / standard);
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
