# include<stdio.h>
# include<stdlib.h>
// 其实是组合数问题
// 可以转化选取一个数字作为第一个数字, 然后再按相同的方法处理以降位的数字
void combine_staff(int *a, int *b, char name[][15], int cur, int layer, int m, int n){    // m是组合所需数字的数量
    int i;
    if(layer == m){
        for (i = 0; i < m; i++) {
            printf("%-4d %s\n", b[i], name[b[i]]);
        }
        printf("\n");
    }
    else{
        for(i = cur; i < n; i++){   // cur表示当前处理的位置
            b[layer] = a[i];
            combine_staff(a, b, name, i + 1, layer + 1, m, n);    // cur为i + 1以在下一次调用时处理以降位的数字
        }
    }
};

int main(int argc, char const *argv[]) {
    int i, n, a_num = 1, m;
    int a[100], b[100];     // b用来存储排列后的数字
    char name[100][15];
    printf("input the number of staff and \'Enter\' \n");
    scanf("%d", &n);
    getchar();

    printf("input the names of staff and each with \'Enter\' \n");
    for(i = 0; i < n; i++) {
        a[i] = i + 1;
        gets(name[i + 1]);
        a_num *= i + 1;
    }

    printf("input the number of people the task need and \'Enter\' \n");
    scanf("%d", &m);
    if (n < 0 || m < 0 || m > n) {
        printf("overflow \n");
        exit(0);
    }

    for(i = 1; i <= m; i ++) a_num /= i;
    for(i = 1; i <= n - m; i ++) a_num /= i;
    printf("number of combination is %d \n", a_num);

    /*
    for (i = 0; i < n; i++) {
        printf("%-4d %s\n",a[i], name[i]);
    }
    */

    combine_staff(a, b, name, 0, 0, m, n);
    system("pause");
    return 0;
}
