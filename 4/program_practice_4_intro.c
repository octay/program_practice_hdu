#include <stdio.h>
#include <stdlib.h>
#define bool int
#define true 1
#define false 0

struct Data{
    double x,y;
};
struct Data data[50];
int data_num;
double a, b, sum_xy, sum_x, sum_y, sum_xx;

bool input(){
    char fname[256];
    printf("input the file name \n");
    scanf("%s", fname);
    printf("\ninput the number of samples \n");
    scanf("%d", &data_num);

    FILE *fp = fopen(fname, "rb");
    if(fp == NULL){
        printf("open file error\n");
        return false;
    }

    for (int i = 0; i < data_num; i++){
        fscanf(fp, "%lf,%lf", &data[i].x, &data[i].y);
    }

    fclose(fp);
    return true;
};

void init(){
    a = b = sum_xy = sum_x = sum_y = sum_xx = 0;
};

void line_reg(){
    for (int i = 0; i < data_num; i++){
        sum_xy += data[i].x * data[i].y;
        sum_x += data[i].x;
        sum_y += data[i].y;
        sum_xx += data[i].x * data[i].x;
    }
    b = (sum_xy * data_num - sum_x * sum_y) / (sum_xx * data_num - sum_x * sum_x);
    a = sum_y / data_num - b * sum_x / data_num;
    printf("y = %.2fx + %.2f \n", b, a);
};

void outputs(){
    double x, y;
    printf("input the area of apart \n");
    scanf("%lf", &x);
    y = b * x + a;
    printf("the price should be %.2f as predicted \n", y);
};

int main(int argc, char const *argv[]) {
    if(input() == false) return 0;
    init();
    line_reg();
    outputs();
    return 0;
}
