# include<stdio.h>
# include<stdlib.h>
# define MAX 100
int a[MAX][MAX];
int mark[MAX][MAX];
void seek(int r_cur, int c_cur, int r_sum, int c_sum);
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
    for(i = 0; i < r; i++){
        for (j = 0; j < c; j++) {
            if(mark[i][j] == 0){
                seek(i, j, r, c);
                num_block ++;
            }
        }
    }

    printf("%d\n", num_block);
    return 0;
}

void seek(int r_cur, int c_cur, int r_sum, int c_sum){  // 寻找标记的过程, 已经找过的标记成1
    int ele;
	ele = a[r_cur][c_cur];
    mark[r_cur][c_cur] = 1;
    if(r_cur - 1 >= 0 && *(*(mark + r_cur - 1) + c_cur) == 0 && *(*(a + r_cur - 1) + c_cur) == ele){
        seek(r_cur - 1, c_cur, r_sum, c_sum);
    }
    if(r_cur + 1 <= r_sum - 1 && *(*(mark + r_cur + 1) + c_cur) == 0 && *(*(a + r_cur + 1) + c_cur) == ele){
        seek(r_cur + 1, c_cur, r_sum, c_sum);
    }
    if(c_cur - 1 >= 0 && *(*(mark + r_cur) + c_cur - 1) == 0 && *(*(a + r_cur) + c_cur - 1) == ele){
        seek(r_cur, c_cur - 1, r_sum, c_sum);
    }
    if(c_cur + 1 <= c_sum - 1 &&  *(*(mark + r_cur) + c_cur + 1) == 0 && *(*(a + r_cur) + c_cur + 1) == ele){
        seek(r_cur, c_cur + 1, r_sum, c_sum);
    }
}
