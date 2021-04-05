# include<stdio.h>
# include<stdlib.h>
# define MAX 100
struct maze{
    int r, c;
    int inr, inc;
    int outr, outc;
    int map[MAX][MAX];
    int count;
};
void initlist(struct maze *p, int r, int c, int inr, int inc, int outr, int outc);
void dfs(struct maze *p, int curr, int curc);
void print_map(struct maze *p);
void print_route(struct maze *p);

int main(int argc, char const *argv[]) {
    struct maze *p = (struct maze *)malloc(sizeof(struct maze));
    int r, c, inr, inc, outr, outc;

    printf("input the pattern of maze and the coordinates of start and exit \n");
    scanf("%d%d%d%d%d%d", &r, &c, &inr, &inc, &outr, &outc);
    // r和c是从1开始计数的, 旨在记录行数和列数, 而坐标则从(0,0)开始.
    initlist(p, r, c, inr, inc, outr, outc);
    if(inr == outr && inc == outc) {
        printf("the start and exit shouldn\'t be the same position \n");
        exit(0);
    }

    printf("then input the whole maze \n");
    printf("with 1 for obstacles and 0 for channels \n");
    int i, j, n;
    for(i = 0; i < r; i++) for(j = 0; j < c; j++){
        scanf("%d", &n);
        p -> map[i][j] = n;
    }
    if(p -> map[inr][inc] != 0 || p -> map[outr][outc] != 0){
        printf("the start and exit shouldn\'t be obstacles \n");
        exit(0);
    }

    dfs(p, inr, inc);
    if(p -> count == 0) printf("find solution not \n");

    return 0;
}

void initlist(struct maze *p, int r, int c, int inr, int inc, int outr, int outc){
    p -> r = r;
    p -> c = c;
    p -> inr = inr;
    p -> inc = inc;
    p -> outr = outr;
    p -> outc = outc;
    p -> count = 0;
}

void dfs(struct maze *p, int curr, int curc){
    if(curr == p -> outr && curc == p -> outc){
        p -> count ++;
        p -> map[curr][curc] = 2;
        print_route(p);
        // 也可选print_map()来打印
        p -> map[curr][curc] = 0;
        return;
    }
    else{
        p -> map[curr][curc] = 2;
        if (curr > 0 && p -> map[curr - 1][curc] == 0) dfs(p, curr - 1, curc);
        if (curr < p -> r && p -> map[curr + 1][curc] == 0) dfs(p, curr + 1, curc);
        if (curc > 0 && p -> map[curr][curc - 1] == 0) dfs(p, curr, curc - 1);
        if (curr < p -> c && p -> map[curr][curc + 1] == 0) dfs(p, curr, curc + 1);
        p -> map[curr][curc] = 0;   // 从这里出发无法到达出口，或者在下一次规划路线时避开.
    }
}

void print_map(struct maze *p){
    int i, j;
	printf("solution %d:\n", p -> count);
	for(i = 0; i < p->r; i++){
		for(j = 0;j < p -> c; j++) printf("%4d", p -> map[i][j]);
		printf("\n");
	}
	putchar('\n');
}

void print_route(struct maze *p){
    int i, j;
    int route = 0, not_route = 1;
    printf("solution %d:\n", p -> count);
    for(i = 0; i < p->r; i++){
		for(j = 0;j < p -> c; j++){
            if(p -> map[i][j] == 2) printf("%4d", route);
            else printf("%4d", not_route);
        }
		printf("\n");
	}
    putchar('\n');
}
