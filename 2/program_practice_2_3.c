# include<stdio.h>
# include<stdlib.h>
// n个数字全排列可以转化成n-1个数字全排列而剩下的一个数字作为前缀
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
};

void arrange(int *a, int layer, int n){    // 盗梦空间是吧...
    int i;  // 其实也可以不用i
    if(layer == n - 1){
        for (i = 0; i < n; i++) {   // layer达到最深的那个元素的时候打印最后的元素
            printf("%d ", a[i]);
        }
        printf("\n");
    }
    else{
        for(i = layer; i < n; i++){
            swap(a + layer, a + i);     // 使首位数字(对于当前的layer而言)常新
            arrange(a, layer + 1, n);   // 然后安排其他的位
            swap(a + layer, a + i);     // 还原数组, 否则可能会有重复打印的问题.
        }
    }
};

int main(int argc, char const *argv[]) {
    int n, i, a_num = 1;
    scanf("%d", &n);
    int a[n];
    for (i = 0; i < n; i++) {
        a[i] = i + 1;
        a_num *= i + 1;
    }
    printf("number of arrangement is %d \n", a_num);
    arrange(a, 0, n);
    system("pause");
    return 0;
}
