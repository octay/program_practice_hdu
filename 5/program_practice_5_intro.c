#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#define CluNum 3            // 簇群数
#define DimNum 4            // 维数
#define MaxRounds 100       // 最大迭代次数

struct Iris{
    double sepal_length, sepal_width, petal_length, petal_width;
    int cluster_id;         // 所属簇群的编号
};
int is_continue;            // 是否继续聚类
struct Iris iris[150];      // 记录鸢尾花数据集
struct Iris cluster_center[CluNum];         // 存储质心
struct Iris new_cluster_center[CluNum];     // 存储计算的新质心
int data_num;               // 存储数据集中的数据记录总数
int cluster_center_init[CluNum];            // 记录每个质心最初使用的数据点的编号
double distance_center[CluNum];             // 记录距质心的距离
int cluser_size[CluNum];    // 记录每个簇群的样本总数

bool input();
void init();
void kmeans();
void partition_one_point();
void partition_all_point();
void cal_new_cluster_center();
void compare_cluster_center();
void cal_distance_one();
void cal_distance_all();
void compare_cluster_center();

int main(int argc, char const *argv[]) {
    if(input() == false) return 0;
    init();
    kmeans();
    system("pause");
    return 0;
}

bool input(){
    char fname[256];
    char name[20];      // name of iris
    printf("input the file name \n");
    scanf("%s", fname);
    printf("\ninput the number of samples \n");
    scanf("%d", &data_num);

    FILE *fp = fopen(fname, "r");      // 二进制是吧
    if(fp == NULL){
        printf("open file error\n");
        return false;
    }

    for (int i = 0; i < data_num; i++){
        fscanf(fp, "%lf,%lf,%lf,%lf,%s", &iris[i].sepal_length, &iris[i].sepal_width, \
        &iris[i].petal_length, &iris[i].petal_width, name);
        iris[i].cluster_id = -1;
    }

    fclose(fp);
    return 1;
}

void init(){
    int random;
    for(int i = 0; i < CluNum; i++) cluster_center_init[i] = -1;
    for(int i = 0; i < CluNum; i++){
        srand(time(NULL));
        random = rand() % (data_num - 1);   // 生成所有质心编号 不重复
        int j = 0;
        while (j < i) {             // 与先前的编号判断
            if(random == cluster_center_init[j]){   // 重复的话就更改编号并重新判断
                srand(time(NULL));
                random = rand() % (data_num - 1);
                j = 0;
            }
            else j++;
        }
        // 生成质心编号用for也可以
        cluster_center_init[i] = random;

        for(int i = 0; i < CluNum; i++){    // 将cluster_center_init最初的质心信息给cluster_center
            cluster_center[i].sepal_length = iris[cluster_center_init[i]].sepal_length;
            cluster_center[i].sepal_width = iris[cluster_center_init[i]].sepal_width;
            cluster_center[i].petal_length = iris[cluster_center_init[i]].petal_length;
            cluster_center[i].petal_width = iris[cluster_center_init[i]].petal_width;
            cluster_center[i].cluster_id = i;
            iris[cluster_center_init[i]].cluster_id = i;
        }
    }
}

void kmeans(){
    int round;
    for(round = 0; round < MaxRounds; round ++){
        printf("\nround %d \n", round + 1);
        partition_all_point();
        cal_new_cluster_center();
        if(is_continue == 0){
            printf("\nfinished totally executed %d round(s) \n", round + 1);
            break;
        }
    }
}

void partition_all_point(){
    for (int i = 0; i < data_num; i++) {
        if(iris[i].cluster_id != -1) continue;      // 不处理在初始化后的质心
        else{
            cal_distance_all(i);        // 计算距离
            partition_one_point(i);     // 然后分配
        }
    }
}

void cal_distance_one(int i_point, int i_center){
    double x1 = pow((iris[i_point].sepal_length - cluster_center[i_center].sepal_length), 2.0);
    double x2 = pow((iris[i_point].sepal_width - cluster_center[i_center].sepal_width), 2.0);
    double x3 = pow((iris[i_point].petal_length - cluster_center[i_center].petal_length), 2.0);
    double x4 = pow((iris[i_point].petal_width - cluster_center[i_center].petal_width), 2.0);
    distance_center[i_center] = sqrt(x1 + x2 + x3 + x4);
}

void cal_distance_all(int i_point){
    for (int i = 0; i < CluNum; i++) cal_distance_one(i_point, i);
}

void partition_one_point(int i_point){
    int i_min = 0;
    double min_distance = distance_center[0];
    for (int i = 0; i < CluNum; i++) {
        if(distance_center[i] < min_distance){
            min_distance = distance_center[i];
            i_min = i;
        }
    }
    iris[i_point].cluster_id = i_min;
}

void cal_new_cluster_center(){
    memset(new_cluster_center, 0, sizeof(new_cluster_center));
    memset(cluser_size, 0, sizeof(cluser_size));    // 初始化全部0

    for(int i = 0; i < data_num; i++){      // 为计算新的质心做准备 并且统计每个簇群包含的个数
        new_cluster_center[iris[i].cluster_id].sepal_length += iris[i].sepal_length;
        new_cluster_center[iris[i].cluster_id].sepal_width += iris[i].sepal_width;
        new_cluster_center[iris[i].cluster_id].petal_length += iris[i].petal_length;
        new_cluster_center[iris[i].cluster_id].petal_width += iris[i].petal_width;
        cluser_size[iris[i].cluster_id] ++;
    }

    for(int i = 0; i < CluNum; i ++){
        if(cluser_size[i] != 0){
            new_cluster_center[i].sepal_length = new_cluster_center[i].sepal_length / (double)cluser_size[i];
            new_cluster_center[i].sepal_width = new_cluster_center[i].sepal_width / (double)cluser_size[i];
            new_cluster_center[i].petal_length = new_cluster_center[i].petal_length / (double)cluser_size[i];
            new_cluster_center[i].petal_width = new_cluster_center[i].petal_width / (double)cluser_size[i];
            // 计算然后打印
            printf("cluster %d includes %d point \n", i, cluser_size[i]);
            printf("cluster %d center: sepal_length: %.2f, sepal_width: %.2f, petal_length: %.2f, petal_width: %.2f \n", \
            i, new_cluster_center[i].sepal_length, new_cluster_center[i].sepal_width, \
            new_cluster_center[i].petal_length, new_cluster_center[i].petal_width);
        }
        else printf("cluser %d includes 0 point \n", i);
    }

    compare_cluster_center();       // 在此is_continue被修改

    for (int i = 0; i < CluNum; i++) {      // 将new_cluster_center新计算的质心信息赋给cluster_center
        cluster_center[i].sepal_length = new_cluster_center[i].sepal_length;
        cluster_center[i].sepal_width = new_cluster_center[i].sepal_width;
        cluster_center[i].petal_length = new_cluster_center[i].petal_length;
        cluster_center[i].petal_width = new_cluster_center[i].petal_width;
        cluster_center[i].cluster_id = i;
    }

    for (int i = 0; i < data_num; i++) {    // 各个点需要重新分配质心
        iris[i].cluster_id = -1;
    }
}

void compare_cluster_center(){
    is_continue = 0;    // 0停止 1继续
    for(int i = 0; i < CluNum; i++){
        if( new_cluster_center[i].sepal_length != cluster_center[i].sepal_length || \
            new_cluster_center[i].sepal_width != cluster_center[i].sepal_width || \
            new_cluster_center[i].petal_length != cluster_center[i].petal_length || \
            new_cluster_center[i].petal_width != cluster_center[i].petal_width  ){
                is_continue = 1;
                break;
            }
    }
}
