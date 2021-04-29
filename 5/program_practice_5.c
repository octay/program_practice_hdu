#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>

#define iris1 "Iris-setosa"
#define iris2 "Iris-versicolor"
#define iris3 "Iris-virginica"
// Iris-setosa 1
// Iris-versicolor 2
// Iris-virginica 3

struct Iris {
    double sepal_length, sepal_width, petal_length, petal_width;
    int variety_id;
};
struct JudgeIris {
    int id;     // 储存采样点iris[]中的编号
    int variety_id;
};
struct Iris iris[150];      // 记录鸢尾花数据集
struct JudgeIris judge_iris[4]; // 距离最近的四个采样点的数据 如果前三个采样点都是不同的品种 则以第四个的品种为准
int train_num, test_num;
int wrong_judge = 0;

int input();    // 输入数据
void print_iris_data(); // 打印iris[]中的数据已验证input()是否正常工作
void judge();   // 判断并评估
double cal_distance();      // 计算距离
void print_accuracy();

int main(void) {
    if (input() == 0) return 0;
    // print_iris_data();
    judge();
    print_accuracy();
    return 0;
}

int input() {
    char fname[256];
    char name[20];      // name of iris
    printf("input the file name \n");
    scanf("%s", fname);
    printf("\ninput the number of samples for training and the number of samples for testing \n");
    scanf("%d%d", &train_num, &test_num);

    FILE *fp = fopen(fname, "r");      // 二进制是吧
    if (fp == NULL) {
        printf("open file error\n");
        return 0;
    }

    for (int i = 0; i < train_num + test_num; i++) {
        fscanf(fp, "%lf,%lf,%lf,%lf,%s", &iris[i].sepal_length, &iris[i].sepal_width, \
        &iris[i].petal_length, &iris[i].petal_width, name);
        if (strcmp(name, iris1) == 0) iris[i].variety_id = 1;
        if (strcmp(name, iris2) == 0) iris[i].variety_id = 2;
        if (strcmp(name, iris3) == 0) iris[i].variety_id = 3;
    }

    fclose(fp);
    return 1;
}

void print_iris_data() {
    for (int i = 0; i < train_num + test_num; ++i) {
        printf("%lf %lf %lf %lf %d\n", iris[i].sepal_length, iris[i].sepal_width, iris[i].petal_length,
               iris[i].petal_width, iris[i].variety_id);
    }
}

void judge() {
    for (int i = 0; i < 4; ++i) {
        judge_iris[i].id = -1;
        judge_iris[i].variety_id = 0;
    }

    for (int k = train_num; k < train_num + test_num; ++k) {
        for (int i = 0; i < 4; i++) {
            double closest_distance = DBL_MAX;
            int i_close = -1;
            for (int j = 0; j < train_num; ++j) {
                double each_distance = cal_distance(j, k);
                if (each_distance < closest_distance && j != judge_iris[0].id && j != judge_iris[1].id &&
                    j != judge_iris[2].id && j != judge_iris[3].id) {
                    // 这里的条件需要更改可能
                    closest_distance = each_distance;
                    i_close = j;
                } else continue;
            }
            judge_iris[i].id = i_close;
            judge_iris[i].variety_id = iris[i_close].variety_id;
        }

        // 距离最近的四个采样点已经找到后就可以开始判断了
        int count_variety_id[4] = {0};    // 只用123会更清晰一些
        int final_judge_variety_id = 0;
        for (int i = 0; i < 3; ++i) {   // 先看前三个
            if (judge_iris[i].variety_id == 1) count_variety_id[1]++;
            else if (judge_iris[i].variety_id == 2) count_variety_id[2]++;
            else if (judge_iris[i].variety_id == 3) count_variety_id[3]++;
        }

        if (count_variety_id[1] == 1 && count_variety_id[2] == 1 && count_variety_id[3] == 1)
            final_judge_variety_id = judge_iris[3].variety_id;
        else if (count_variety_id[1] == 2 || count_variety_id[1] == 3) final_judge_variety_id = 1;
        else if (count_variety_id[2] == 2 || count_variety_id[2] == 3) final_judge_variety_id = 2;
        else if (count_variety_id[3] == 2 || count_variety_id[3] == 3) final_judge_variety_id = 3;

        if (final_judge_variety_id == iris[k].variety_id) continue;
        else wrong_judge++;
    }
}

double cal_distance(int i1, int i2) {
    double x1 = pow((iris[i1].sepal_length - iris[i2].sepal_length), 2.0);
    double x2 = pow((iris[i1].sepal_width - iris[i2].sepal_width), 2.0);
    double x3 = pow((iris[i1].petal_length - iris[i2].petal_length), 2.0);
    double x4 = pow((iris[i1].petal_width - iris[i2].petal_width), 2.0);
    double distance = sqrt(x1 + x2 + x3 + x4);
    return distance;
}

void print_accuracy() {
    double accuracy = 100.0 * wrong_judge / test_num;
    printf("\naccuracy : %lf%%\n", accuracy);
}
