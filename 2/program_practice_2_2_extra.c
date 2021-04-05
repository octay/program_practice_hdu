# include<stdio.h>
# include<stdlib.h>
# define MAX 100
// 尝试用一下非递归算法
int a[MAX][MAX];
int mark[MAX][MAX];
int mo = 0;    // mark 1

void markmo(int r_cur, int c_cur, int r_sum, int c_sum);
int main(int argc, char const *argv[]) {
    int r, c, each_num, i, j;
    printf("input the number of rows and the number of cols \n");
    printf("then input all the numbers in order \n");
    printf("and plz make sure all the numbers is positive \n");
    scanf("%d%d", &r, &c);
    int num_block = 0;

    for(i = 0; i < r; i++){
        for (j = 0; j < c; j++) {
            scanf("%d", &each_num);
            if(each_num <= 0){
                printf("error no zero or negative number");
                exit(0);
            }
            a[i][j] = each_num;
            mark[i][j] = 0;
        }
    }

/*
    for(i = 0; i < r; i++){     // 用来检验是否正常输入
        for (j = 0; j < c; j++) {
            if(j) printf(" %d", a[i][j]);
            else printf("%d", a[i][j]);
        }
        printf("\n");
    }
*/
    int i2, j2;
    for(i = 0; i < r; i++){
        for (j = 0; j < c; j++) {
            if(mark[i][j] == 0){
                mark[i][j] = 1;     // 待找的标记成1
                mo = 1;             // mo来记录标记为1的格子数
                while (mo) {
                // 这个while语句就是一遍一遍扫描标记为1的格子然后调用markmo()
                    for (i2 = 0; i2 < r && mo; i2++){
                        for (j2 = 0; j2 < c && mo; j2++){
                            if(mark[i2][j2] == 1){
                                markmo(i2, j2, r, c);
                            }
                        }
                    }
                }
                num_block ++;
            }
        }
    }

    printf("%d\n", num_block);
    return 0;
}

void markmo(int r_cur, int c_cur, int r_sum, int c_sum){
    int ele;
	ele = a[r_cur][c_cur];
    mark[r_cur][c_cur] = -1;    // 已经找过的标记成-1 待找的标记成1
    mo --;
    if(r_cur - 1 >= 0 && mark[r_cur - 1][c_cur] == 0 && a[r_cur - 1][c_cur] == ele){
        mark[r_cur - 1][c_cur] = 1;
        mo ++;
    }   // mae
    if(r_cur + 1 <= r_sum - 1 && mark[r_cur + 1][c_cur] == 0 && a[r_cur + 1][c_cur] == ele){
        mark[r_cur + 1][c_cur] = 1;
        mo ++;
    }
    if(c_cur - 1 >= 0 && mark[r_cur][c_cur - 1] == 0 && a[r_cur][c_cur - 1] == ele){
        mark[r_cur][c_cur - 1] = 1;
        mo ++;
    }
    if(c_cur + 1 <= c_sum - 1 && mark[r_cur][c_cur + 1] == 0 && a[r_cur][c_cur + 1] == ele){
        mark[r_cur][c_cur + 1] = 1;
        mo ++;
    }
}
