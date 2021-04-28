#include <stdio.h>
#include <math.h>

#define alpha 0.04
#define training_times 10000

struct Data {
    double parameter[14];
    /*
    0   double crim;    // 城镇人均犯罪率
    1   double zn;      // 住宅用地所占比例
    2   double indus;   // 城镇非商业用地的比例
    3   int chas;       // 是否临近查尔斯河 边界是河流1
    4   double nox;     // 一氧化氮浓度
    5   double rm;      // 住宅平均房间数
    6   double age;     // 1940年之前建成的自用房屋比例
    7   double dis;     // 到波士顿5个中心区域的加权距离
    8   double rad;     // 距离高速公路的便利指数
    9   double tax;     // 每10000美元的全部财产税率
    10  double ptratio; // 城镇师生比例
    11  double b;       // 1000(Bk-0.63)^2 Bk指代城镇中黑人的比例
    12  double lstat;   // 低收入人群的比例
    13  double medv;    // 自住房的平均房价
    */
};
struct RefineK {
    double value;       // 值
    int parameter_tied; // 与之相绑定的参数
};
struct Data data[1000];
int train_num, test_num;
double k_parameter[14];         // 13 k 1 b     0~12 k 13 b
// k_crim, k_zn, k_indus, k_chas, k_nox, k_rm, k_age, k_dis, k_rad, k_tax, k_ptratio, k_b, k_lstat, b
double resu = 0, refine_resu = 0;
struct RefineK refine_k[4];

int input();    // 输入数据
void init();    // 归一化输入的数据并且初始化存储各参数加权的数组
void show_initiated();  // 打印归一化后的数据
void show_k();  // 打印各参数加权
void gd();      // 实现梯度下降算法
void model_access();    // 模型评估
void show_resu();       // 打印评估

void refine_select();   // 挑选靠前的权重 这就是优化
void show_refine_k();   // 打印靠前的各参数加权
void refine_model_access();     // 优化后的模型评估
void show_refine_resu();        // 打印优化后的评估

int input() {
    char fname[256];
    char first_line[100];
    printf("input the file name \n");
    scanf("%s", fname);
    FILE *fp = fopen(fname, "rb");
    if (fp == NULL) {
        printf("open file error\n");
        return 0;
    }

    printf("\ninput the number of samples for training and the number of samples for testing \n");
    scanf("%d%d", &train_num, &test_num);

    for (int i = 0; i < train_num + test_num; i++) {
        fgets(first_line, 100, fp);
        fscanf(fp, "%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf", \
        &data[i].parameter[0], &data[i].parameter[1], &data[i].parameter[2], \
        &data[i].parameter[3], &data[i].parameter[4], &data[i].parameter[5], \
        &data[i].parameter[6], &data[i].parameter[7], &data[i].parameter[8], \
        &data[i].parameter[9], &data[i].parameter[10], &data[i].parameter[11], \
        &data[i].parameter[12], &data[i].parameter[13]);
    }

    fclose(fp);
    return 1;
}

void init() {
    double max[14], min[14];    // 在init()中的数组
    // 不要归一化
    // 3   int chas;       // 是否临近查尔斯河 边界是河流1
    for (int i = 0; i < 14; i++) {
        if (i == 3) continue;
        max[i] = data[0].parameter[i];
        min[i] = data[0].parameter[i];
    }

    for (int i = 1; i < train_num + test_num; i++) {
        for (int j = 0; j < 14; j++) {
            if (j == 3) continue;
            max[j] = max[j] > data[i].parameter[j] ? max[j] : data[i].parameter[j];
            min[j] = min[j] < data[i].parameter[j] ? min[j] : data[i].parameter[j];
        }
    }

    for (int i = 0; i < train_num + test_num; i++) {
        for (int j = 0; j < 14; j++) {
            if (j == 3) continue;
            data[i].parameter[j] = (data[i].parameter[j] - min[j]) / (max[j] - min[j]);
        }
    }

    for (int i = 0; i < 14; i++) {
        k_parameter[i] = 0;
    }
}

void show_initiated() {
    printf("\ncheck if init() works as expected \n");
    for (int i = 0; i < train_num + test_num; i++) {
        for (int j = 0; j < 14; j++) {
            printf("%lf", data[i].parameter[j]);
            if (j == 13) printf("\n");
            else printf(" ");
        }
    }
}

void show_k() {
    printf("\ncheck if gd() works as expected \n");
    for (int i = 0; i < 14; i++) {
        printf("k_parameter %d = %lf \n", i, k_parameter[i]);
    }
}

void gd() {
    for (int k = 0; k < training_times; k++) {
        double sum1[1000] = {0};
        double sum2[14] = {0};
        for (int i = 0; i < train_num; i++) {
            for (int j = 0; j < 14; j++) {
                if (j == 13) sum1[i] += k_parameter[13];
                else sum1[i] += k_parameter[j] * data[i].parameter[j];
            }
            sum1[i] -= data[i].parameter[13];
        }
        for (int j = 0; j < 14; j++) {
            sum2[j] = 0;
            for (int i = 0; i < train_num; i++) {
                if (j == 13) sum2[j] += sum1[i];
                else sum2[j] += sum1[i] * data[i].parameter[j];
            }
            k_parameter[j] -= alpha * sum2[j] / train_num;
        }
    }
}

void model_access() {
    double y;
    for (int i = train_num; i < train_num + test_num; i++) {
        // data array :
        // 0 ~ train_num-1 (all train_num)
        // train_num ~ train_num + test_num -1 (all test_num)
        y = 0;
        for (int j = 0; j < 14; j++) {
            if (j == 13) y += k_parameter[13];
            else y += k_parameter[j] * data[i].parameter[j];
        }
        resu += (y - data[i].parameter[13]) * (y - data[i].parameter[13]);
    }
    resu = sqrt(resu / test_num);
}

void show_resu() {
    printf("\n%lf%%\n", resu * 100);
}

void refine_select() {
    for (int i = 0; i < 4; ++i) {
        refine_k[i].value = 0;
        refine_k[i].parameter_tied = -1;
    }
    for (int i = 0; i <= 3; i++) {
        double max = 0;
        int i_max = -1;
        for (int j = 0; j < 14; ++j) {
            if (k_parameter[j] * k_parameter[j] > max * max && j != refine_k[0].parameter_tied &&
                j != refine_k[1].parameter_tied && j != refine_k[2].parameter_tied && j != refine_k[3].parameter_tied) {
                // 这里的条件需要更改可能
                max = k_parameter[j];
                i_max = j;
            } else continue;
        }
        refine_k[i].value = max;
        refine_k[i].parameter_tied = i_max;
    }
}

void show_refine_k() {
    printf("\ncheck if refine_select() works as expected \n");
    for (int i = 0; i < 4; ++i) {
        printf("k_parameter %d = %lf \n", refine_k[i].parameter_tied, refine_k[i].value);
    }
}

void refine_model_access() {
    double y;
    for (int i = train_num; i < train_num + test_num; i++) {
        // 4 selected k of parameter
        y = 0;
        for (int j = 0; j < 4; j++) {
            if (refine_k[j].parameter_tied == 13) y += refine_k[j].value;
            else y += refine_k[j].value * data[i].parameter[refine_k[j].parameter_tied];
        }
        refine_resu += (y - data[i].parameter[13]) * (y - data[i].parameter[13]);
    }
    refine_resu = sqrt(refine_resu / test_num);
}

void show_refine_resu() {
    printf("\n%lf%%\n", refine_resu * 100);
}

int main(void) {
    if (input() == 0) return 0;
    init();
    // show_initiated();
    gd();
    // show_k();
    model_access();
    show_resu();

    printf("\nrefine the model \n");
    refine_select();
    // show_refine_k();
    refine_model_access();
    show_refine_resu();
    return 0;
}


// 原先的init()函数 写完瞬间弃
/*
void init(){
    double crim_max, crim_min;
    double zn_max, zn_min;
    double indus_max,indus_min;
    double nox_max, nox_min;
    double rm_max, rm_min;
    double age_max, age_min;
    double dis_max, dis_min;
    double rad_max, rad_min;
    double tax_max, tax_min;
    double ptratio_max, ptratio_min;
    double b_max, b_min;
    double lstat_max, lstat_min;
    double medv_max, medv_min;

    crim_max = crim_min = data[0].crim;
    zn_max = zn_min = data[0].zn;
    indus_max =indus_min = data[0].indus;
    nox_max = nox_min = data[0].nox;
    rm_max = rm_min = data[0].rm;
    age_max = age_min = data[0].age;
    dis_max = dis_min = data[0].dis;
    rad_max = rad_min = data[0].rad;
    tax_max = tax_min = data[0].tax;
    ptratio_max = ptratio_min = data[0].ptratio;
    b_max = b_min = data[0].b;
    lstat_max = lstat_min = data[0].lstat;
    medv_max = medv_min = data[0].medv;
    for (int i = 1; i < train_num; i++){
        crim_max = crim_max > data[i].crim ? crim_max : data[i].crim;
        crim_min = crim_min < data[i].crim ? crim_min : data[i].crim;
        zn_max = zn_max > data[i].zn ? zn_max : data[i].zn;
        zn_min = zn_min < data[i].zn ? zn_min : data[i].zn;
        indus_max = indus_max > data[i].indus ? indus_max : data[i].indus;
        indus_min = indus_min < data[i].indus ? indus_min : data[i].indus;
        nox_max = nox_max > data[i].nox ? nox_max : data[i].nox;
        nox_min = nox_min < data[i].nox ? nox_min : data[i].nox;
        rm_max = rm_max > data[i].rm ? rm_max : data[i].rm;
        rm_min = rm_min < data[i].rm ? rm_min : data[i].rm;
        age_max = age_max > data[i].age ? age_max : data[i].age;
        age_min = age_min < data[i].age ? age_min : data[i].age;
        dis_max = dis_max > data[i].dis ? dis_max : data[i].dis;
        dis_min = dis_min < data[i].dis ? dis_min : data[i].dis;
        rad_max = rad_max > data[i].rad ? rad_max : data[i].rad;
        rad_min = rad_min < data[i].rad ? rad_min : data[i].rad;
        tax_max = tax_max > data[i].tax ? tax_max : data[i].tax;
        tax_min = tax_min < data[i].tax ? tax_min : data[i].tax;
        ptratio_max = ptratio_max > data[i].ptratio ? ptratio_max : data[i].ptratio;
        ptratio_min = ptratio_min < data[i].ptratio ? ptratio_min : data[i].ptratio;
        b_max = b_max > data[i].b ? b_max : data[i].b;
        b_min = b_min < data[i].b ? b_min : data[i].b;
        lstat_max = lstat_max > data[i].lstat ? lstat_max : data[i].lstat;
        lstat_min = lstat_min < data[i].lstat ? lstat_min : data[i].lstat;
        medv_max = medv_max > data[i].medv ? medv_max : data[i].medv;
        medv_min = medv_min < data[i].medv ? medv_min : data[i].medv;
    }

    for (int i = 0; i < train_num; i++){
        data[i].crim = (data[i].crim - crim_min) / (crim_max - crim_min);
        data[i].zn = (data[i].zn - zn_min) / (zn_max - zn_min);
        data[i].indus = (data[i].indus - indus_min) / (indus_max - indus_min);
        data[i].nox = (data[i].nox - nox_min) / (nox_max - nox_min);
        data[i].rm = (data[i].rm - rm_min) / (rm_man - rm_min);
        data[i].age = (data[i].age - age_min) / (age_max - age_min);
        data[i].dis = (data[i].dis - dis_min) / (dis_max - dis_min);
        data[i].rad = (data[i].rad - rad_min) / (rad_max - rad_min);
        data[i].tax = (data[i].tax - tax_min) / (tax_max - tax_min);
        data[i].ptratio = (data[i].ptratio - ptratio_min) / (ptratio_max - ptratio_min);
        data[i].b = (data[i].b - b_min) / (b_max - b_min);
        data[i].lstat = (data[i].lstat - lstat_min) / (lstat_max - lstat_min);
        data[i].medv = (data[i].medv - medv_min) / (medv_max - medv_min);
    }
    k_crim = k_zn = k_indus = k_chas = k_nox = k_rm = k_age = k_dis = k_rad = \
    k_tax = k_ptratio = k_b = k_lstat = b = 0;
};
*/
