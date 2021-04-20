# include<stdio.h>
# include<stdlib.h>
# include<time.h>
# include<windows.h>
# include<assert.h>
# include<math.h>
# define SIZE_A 100
# define MAX_NUM 99
// 在此更改随机生成的数组的长度和随机数最大值,同时记得更改zen_print()中的打印模式
# define BK_NUM 10
// 桶的数量,请随着随机数最大值更改,同时更改bucket_sort()中的存入桶部分
# define DEF_BASE 10
# define NUM_MAX_NUM 2

typedef int DataType;
struct bucket{
    DataType a[SIZE_A];
    int num;
};
void swap(DataType *a, DataType *b);
void random(DataType a[], int n, int range_max_num);
void zen_print(DataType a[], int n);        // n表示存放元素的个数

void radix_sort(DataType a[], int n, int base, int num_maxkey);    // 基数排序
int digit_unit(int num, int base, int unit);    // 提取从右向左数第j位

int main(int argc, char const *argv[]) {
    DataType a[SIZE_A];
    int i;
    time_t start_t, end_t;
    double diff_t;

    time(&start_t);
    for(int i = 1; i <= 1000000; i++){
        srand(time(0));
        random(a, SIZE_A, MAX_NUM);
        radix_sort(a, SIZE_A, DEF_BASE, NUM_MAX_NUM);
    }
    time(&end_t);
    diff_t = difftime(end_t, start_t);  // 求函数运行前后的时间差

    zen_print(a, SIZE_A);
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

void radix_sort(DataType a[], int n, int base, int num_maxkey){
    int i, j, k;

    for (j = 1; j <= num_maxkey; j++){
        struct bucket bk[base];     // 0 ~ base - 1
        int i4s = 0;    // i4s i for sorted_a
        for (i = 0; i < base; i++) {  // 初始化
            bk[i].num = 0;
        }
        for (i = 0; i < n; i++) {
            k = digit_unit(a[i], base, j);  // 提取从右向左数第j位
            bk[k].a[bk[k].num] = a[i];
            bk[k].num ++;
        }
        for (i = 0; i < base; i++) {        // 按顺序收集元素
            if(bk[i].num == 0) continue;
            else if(bk[i].num == 1) a[i4s++] = bk[i].a[0];
            else for (k = 0; k < bk[i].num; k++) a[i4s++] = bk[i].a[k];
        }
    }
}

int digit_unit(int num, int base, int unit){
    int a = pow(base, unit - 1);
    return (num / a) % 10;
}
