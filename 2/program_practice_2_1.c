#include<stdio.h>

void order_tsu(int *a, int n);
void order_inter_re(int *a, int n);
int order_re(int *a, int num, int bottom, int top);
// tsu表示通常. re表示回溯.
int main(void) {
    int n, i = 0;

    printf("input length and numbers \n");
    scanf("%d", &n);
    int a[n];

    for(i = 0; i < n; i++){
        scanf("%d", a + i);
    }           // 建立链表

    order_tsu(a, n);
    //order_inter_re(a, n);

    // 任意选择一条语句即可,上方为通常方法,下方为递归方法.
    printf("min = %d, max = %d\n", *a, *(a + n - 1));

    return 0;
}

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
