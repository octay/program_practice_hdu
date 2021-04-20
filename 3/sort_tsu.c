# include<stdio.h>
# include<stdlib.h>
# include<time.h>
# include<windows.h>
# define SIZE_A 100
# define MAX_NUM 99
// 在此更改随机生成的数组的长度和随机数最大值,同时记得更改zen_print()中的打印模式

typedef int DataType;
void swap(DataType *a, DataType *b);
void random(DataType a[], int n, int range_max_num);
void zen_print(DataType a[], int n);        // n表示存放元素的个数
int sequential_search(DataType a[], int n, DataType key);   // 顺序查找
int binary_search(DataType a[], int n, DataType key);       // 二分查找 递增的数组可用

void bubble_sort(DataType a[], int n);      // 冒泡排序
void select_sort(DataType a[], int n);      // 简单选择排序
void insert_sort(DataType a[], int n);      // 直接插入排序

void merge_sort(DataType a[], DataType aux[], int bottom, int top);     // 归并排序
void merge(DataType a[], DataType aux[], int bottom, int mid, int top); // 归并排序中的归并部分

void quick_sort(DataType a[], int bottom, int top);         // 快速排序
int quick_pass(DataType a[], int bottom, int top);          // 快速排序中的划分部分
void quick_sort_bi(DataType a[], int bottom, int top);      // 快速排序 前两个整合成一个
void quick_sort_tsu(DataType a[], int bottom, int top);     // 快速排序非递归方法

// 以下三个函数来自program_practice_2_1中使用二分法排序的通常方法(1个函数)与递归算法(2个函数)
void order_tsu(int *a, int n);
void order_inter_re(int *a, int n);
int order_re(int *a, int num, int bottom, int top);

int main(int argc, char const *argv[]) {
    DataType a[SIZE_A], aux[SIZE_A];
    int i;
    time_t start_t, end_t;
    double diff_t;

    srand(time(0));
    random(a, SIZE_A, MAX_NUM);

    time(&start_t);
    // 任选一种即可
    bubble_sort(a, SIZE_A);
    // select_sort(a, SIZE_A);
    // insert_sort(a, SIZE_A);
    // merge_sort(a, aux, 0, SIZE_A - 1);
    // quick_sort(a, 0, SIZE_A - 1);
    // quick_sort_bi(a, 0, SIZE_A - 1);
	
    time(&end_t);
    diff_t = difftime(end_t, start_t);  // 求函数运行前后的时间差

    zen_print(a, SIZE_A);
    printf("time of executing is %f sec \n", diff_t);
    printf("start %f	 end %f\n",(double)start_t,(double)end_t);

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

int sequential_search(DataType a[], int n, DataType key){
    int i;
    for (i = 0; i <n; i++) {
        if(a[i] == key) return i;
    }
    return -1;
}

int binary_search(DataType a[], int n, DataType key){
    int bottom = 0, top = n - 1;
        int mid;

        while(bottom <= top){
            mid = (top + bottom) / 2;
            if(a[mid] == key) return mid;
            if(a[mid] > key) top = mid - 1;
            if(a[mid] < key) bottom = mid + 1;
        }
        return -1;
}

void bubble_sort(DataType a[], int n){
    int i, j;
    for(i = 0; i < n - 1; i++) for(j = 0; j < n - i - 1; j++){
        if(a[j] > a[j + 1]) swap(a + j, a + j + 1);
    }
}

void select_sort(DataType a[], int n){
    int i, j, min;
    for(i = 0; i < n - 1; i++){
        min = i;
        for(j = i + 1; j < n; j++){
            if(a[min] > a[j]) min = j;  // 排查i标后最小的元素
        }
        swap(a + min, a + i);
    }
}

void insert_sort(DataType a[], int n){
    int i, j, d2i;  // d2i data to insetr
    for (i = 0; i < n; i++) {
        d2i = a[i];
        j = i - 1;
        while (j >= 0 && d2i < a[j]) {
            a[j + 1] = a[j];
            j --;
        }
        a[j + 1] = d2i;
    }
}

void merge_sort(DataType a[], DataType aux[], int bottom, int top){
    if(bottom >= top) return;   // 只有1个别排了，也别分了

    int i;
    int mid = (top + bottom) / 2;

    merge_sort(a, aux, bottom, mid);    // 前半排序
    merge_sort(a, aux, mid + 1, top);   // 后半排序

    merge(a, aux, bottom, mid ,top);    // 归并

    for(i = bottom; i <= top; i++) a[i] = aux[i];
}

void merge(DataType a[], DataType aux[], int bottom, int mid, int top){
    int i = bottom;     // 前部分的起点
    int k = bottom;     // 单纯地控制aux[]
    int j = mid + 1;    // 后部分的起点

    while (i <= mid && j <= top) {
        if(a[i] <= a[j]) aux[k++] = a[i++];
        else aux[k++] = a[j++];
    }   // 拷贝较小的元素

    while(i <= mid) aux[k++] = a[i++];
    while(j <= top) aux[k++] = a[j++];  // 处理剩余的元素
}

void quick_sort(DataType a[], int bottom, int top){
    if(bottom >= top) return;   // 只有1个别排了，也别分了

    int pivot = quick_pass(a, bottom, top);     // 划分并返回枢轴位置

    quick_sort(a, bottom, pivot - 1);
    quick_sort(a, pivot + 1, top);
}

int quick_pass(DataType a[], int bottom, int top){
    DataType x = a[bottom];     // 先选第一个
    while(bottom < top){
        while(bottom < top && x <= a[top]) top--;       // 从右向左扫描
        if(bottom == top) break;
        a[bottom++] = a[top];

        while(bottom < top && x >= a[bottom]) bottom++; // 从左向右扫描
        if(bottom == top) break;
        a[top--] = a[bottom];
    }
    a[bottom] = x;
    return bottom;
}

void quick_sort_bi(DataType a[], int bottom, int top){
    if(bottom >= top) return;

    DataType ib = bottom, it = top;
    DataType x = a[ib];
    while(ib < it){
        while(ib < it && x <= a[it]) it--;      // 从右向左扫描
        if(ib == it) break;
        a[ib++] = a[it];

        while(ib < it && x >= a[ib]) ib++;      // 从左向右扫描
        if(ib == it) break;
        a[it--] = a[ib];
    }
    a[ib] = x;
    int pivot = ib;

    quick_sort(a, bottom, pivot - 1);
    quick_sort(a, pivot + 1, top);
}

// 反正默认的DataType是int, 所以先不改了
void order_tsu(int *a, int n){
    int bottom = 0, top, mid, i, j; // i j 是用来控制循环的
    int temp;   // to store per number

    for(i = 0; i < n; i++){
        // 每一次在for中调用while以保持在这个元素之前都是已经排好序了的
        temp = *(a + i);
        bottom = 0;
        top = i - 1;

        while(bottom <= top){
            mid = (top + bottom) / 2;
            if(*(a + mid) > *(a + i)) top = mid - 1;
            else bottom = mid + 1;      // 不管两者是否相等总之插在后方就行了
        }

        for(j = i - 1; j >= bottom; j--) *(a + j + 1) = *(a + j); 	// 后移中...
        *(a + bottom) = temp;
    }
}

int order_re(int *a, int num, int bottom, int top){
    if(bottom <= top){
        int mid = (top + bottom) / 2;
        if(*(a + mid) > num) return order_re(a, num, bottom, mid - 1);
        else return order_re(a, num, mid + 1, top);
    }
    else return bottom;
}

void order_inter_re(int *a, int n){
    int bottom = 0, top, mid, i, j; // i j 是用来控制循环的
    int temp;   // to store per number

    for(i = 0; i < n; i++){
        temp = *(a + i);
        bottom = 0;
        top = i - 1;

        mid = order_re(a, temp, bottom, top);

        for(j = i - 1; j >= mid; j++) *(a + j + 1) = *(a + j); 	// 后移中...
        *(a + mid) = temp;
    }
}
