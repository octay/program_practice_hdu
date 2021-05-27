#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define TrainNUm 110
#define TestNum 40
#define random_times 1000
#define TrainingTimes 40000
#define inNum 4
#define outNum 1
#define NeuronNum 40
#define PerOverlook 1000
#define WAlta 0.1
#define VAlta 0.2
// the suteppu of w and v
#define file_name "data.txt"
#define iris1 "Iris-setosa"
#define iris2 "Iris-versicolor"
#define iris3 "Iris-virginica"
// Iris-setosa 1
// Iris-versicolor 2
// Iris-virginica 3

struct Iris {
    double parameters[4];
    // sepal_length, sepal_width, petal_length, petal_width
    double variety_id[1];
} iris[150];    // store all the training and testing data 's info and real variety id
double pre_variety_id[150][1] = {0};    // predicted variety id
int wrong_judge = 0;        // judge whether each predicted one equals to the real one or not and ++ in the latter condition

double v_in2neu[NeuronNum][inNum];      // 输入层 -> 隐含层 权重
double neu_output[NeuronNum];           // 隐含层的输出
double w_neu2out[outNum][NeuronNum];    // 隐含层 -> 输出层 权重
double max_in[inNum], min_in[inNum];
double out[outNum];      // 存储神经网络的输出
double dw[outNum][NeuronNum];
double dv[NeuronNum][inNum];            // wv的修正量
double mse;     // 存储均方误差
double rmse;    // 存储均方根误差
double max_out[1] = {3};
double min_out[1] = {1};    // 其实不用数组

void input();

void random_order();

void print_iris_data();     // print the data in iris[] to check if input() and random_order() work as expected

void print_iris_data_train_only();  // check inited data

void init();

void train();

void comput_o(int var);

void back_update(int var);

void test();

int main(void) {
    input();
    random_order();
    // print_iris_data();
    init();
    // print_iris_data_train_only();
    train();
    test();
}

void input() {
    FILE *fp1;
    char name[20];      // name of iris
    char ch;

    if ((fp1 = fopen(file_name, "rb")) == NULL) {
        printf("open file %s error \n", file_name);
        exit(0);
    }

    for (int i = 0; i < TrainNUm + TestNum; i++) {
        fscanf(fp1, "%lf,%lf,%lf,%lf,%s", &iris[i].parameters[0], &iris[i].parameters[1], \
        &iris[i].parameters[2], &iris[i].parameters[3], name);
        if (strcmp(name, iris1) == 0) iris[i].variety_id[0] = 1;
        else if (strcmp(name, iris2) == 0) iris[i].variety_id[0] = 2;
        else if (strcmp(name, iris3) == 0) iris[i].variety_id[0] = 3;
    }

    fclose(fp1);
}

void random_order() {
    // void random_order() would be better to be updated to int random_order() return a flag
    // returned flag is about judging the random training data includes all kinds of iris or not
    int random1, random2;
    struct Iris temp;
    srand((unsigned) time(NULL));
    for (int i = 0; i < random_times; ++i) {
        random1 = rand() % (TrainNUm + TestNum);
        random2 = rand() % (TrainNUm + TestNum);
        temp = iris[random1];
        iris[random1] = iris[random2];
        iris[random2] = temp;
    }
}

void print_iris_data() {
    // format in printf all %lf
    for (int i = 0; i < TrainNUm + TestNum; ++i) {
        printf("%lf %lf %lf %lf %lf\n", iris[i].parameters[0], iris[i].parameters[1], iris[i].parameters[2],
               iris[i].parameters[3], iris[i].variety_id[0]);
    }
}

void print_iris_data_train_only() {
    for (int i = 0; i < TrainNUm; ++i) {
        printf("%lf %lf %lf %lf %lf\n", iris[i].parameters[0], iris[i].parameters[1], iris[i].parameters[2],
               iris[i].parameters[3], iris[i].variety_id[0]);
    }
}

void init() {
    srand((int) time(0));
    // 数据归一化
    for (int i = 0; i < inNum; ++i) {
        min_in[i] = max_in[i] = iris[0].parameters[i];
        for (int j = 0; j < TrainNUm + TestNum; ++j) {
            max_in[i] = max_in[i] > iris[j].parameters[i] ? max_in[i] : iris[j].parameters[i];
            min_in[i] = min_in[i] < iris[j].parameters[i] ? min_in[i] : iris[j].parameters[i];
        }
    }

    for (int i = 0; i < inNum; ++i) {
        for (int j = 0; j < TrainNUm + TestNum; ++j) {
            iris[j].parameters[i] = (iris[j].parameters[i] - min_in[i]) / (max_in[i] - min_in[i]);
        }
    }

    for (int i = 0; i < outNum; ++i) {
        for (int j = 0; j < TrainNUm; ++j) {
            iris[j].variety_id[i] = (iris[j].variety_id[i] - min_out[i]) / (max_out[i] - min_out[i]);
        }
    }

    // 各权值在一开始随机 权值修正量赋值为0 权值修正量为0
    for (int i = 0; i < NeuronNum; ++i) {
        for (int j = 0; j < inNum; ++j) {
            v_in2neu[i][j] = rand() * 2.0 / RAND_MAX - 1;
            dv[i][j] = 0;
            // double dv[NeuronNum][inNum];
        }
    }

    for (int i = 0; i < outNum; ++i) {
        for (int j = 0; j < NeuronNum; ++j) {
            w_neu2out[i][j] = rand() * 2.0 / RAND_MAX - 1;
            dw[i][j] = 0;
            // double dw[outNum][NeuronNum];
        }
    }
}

void train() {
    int count = 1;
    do {
        mse = 0;
        for (int i = 0; i < TrainNUm; ++i) {
            comput_o(i);
            back_update(i);

            for (int j = 0; j < outNum; ++j) {
                double tmp1 = out[j] * (max_out[j] - min_out[j]) + min_out[j];
                double tmp2 = iris[i].variety_id[j] * (max_out[j] - min_out[j]) + min_out[j];
                mse += (tmp1 - tmp2) * (tmp1 - tmp2);
            }
        }
        mse = mse / TrainNUm * outNum;      // 均方误差

        if (count % PerOverlook == 0) printf("%-7d %lf \n", count, mse);

        count++;
    } while (count <= TrainingTimes && mse >= 0.03);
    printf("\ntraining accomplished \n");
}

void comput_o(int var) {
    double sum;

    for (int i = 0; i < NeuronNum; ++i) {   // 每个隐藏层神经元的输出
        sum = 0;
        for (int j = 0; j < inNum; ++j) sum += v_in2neu[i][j] * iris[var].parameters[j];
        neu_output[i] = 1 / (1 + exp(-1 * sum));
        // exp(x)是指数函数$e^x$
        // 所以这个算式本质上是$\frac{1}{1+e^{-x}}$ 也就是sigmoid函数
    }

    for (int i = 0; i < outNum; ++i) {      // 每个输出层神经元的输出
        sum = 0;
        for (int j = 0; j < NeuronNum; ++j) sum += w_neu2out[i][j] * neu_output[j];
        out[i] = 1 / (1 + exp(-1 * sum));
    }
}

void back_update(int var) {
    double sum;

    for (int i = 0; i < NeuronNum; ++i) {   // 每个隐藏层神经元的输出
        sum = 0;

        // 隐藏层与输出层
        for (int j = 0; j < outNum; ++j) {
            dw[j][i] = WAlta * (iris[var].variety_id[j] - out[j]) * out[j] * (1 - out[j]) * neu_output[i];
            w_neu2out[j][i] += dw[j][i];
            sum += (iris[var].variety_id[j] - out[j]) * out[j] * (1 - out[j]) * w_neu2out[j][i];
        }

        // 隐藏层与输入层
        for (int j = 0; j < inNum; ++j) {
            dv[i][j] = VAlta * sum * neu_output[i] * (1 - neu_output[i]) * iris[var].parameters[j];
            v_in2neu[i][j] += dv[i][j];
        }
    }
}

void test() {
    double sum;

    // 计算预期结果
    for (int k = TrainNUm; k < TrainNUm + TestNum; ++k) {
        // 隐含层
        for (int i = 0; i < NeuronNum; ++i) {
            sum = 0;
            for (int j = 0; j < inNum; ++j) sum += v_in2neu[i][j] * iris[k].parameters[j];
            neu_output[i] = 1 / (1 + exp(-1 * sum));
        }

        // 输出层
        for (int i = 0; i < outNum; ++i) {
            sum = 0;
            for (int j = 0; j < NeuronNum; ++j) sum += w_neu2out[i][j] * neu_output[j];
            pre_variety_id[k][i] = 1 / (1 + exp(-1 * sum));
        }

        // 打印内容
        printf("num : %d pre : ", k + 1);
        for (int i = 0; i < outNum; ++i)
            printf("%d %f", (int) (pre_variety_id[k][i] * (max_out[i] - min_out[i]) + min_out[i] + 0.5),
                   pre_variety_id[k][i]); // 反归一化
        printf("act : ");
        for (int i = 0; i < outNum; ++i) printf("%d ", (int) iris[k].variety_id[i]);
        printf("\n");
        for (int i = 0; i < outNum; ++i)
            if ((int) (pre_variety_id[k][i] * (max_out[i] - min_out[i]) + min_out[i] + 0.5) !=
                (int) iris[k].variety_id[i]) {
                wrong_judge++;
            }
    }

    rmse = 0.0;
    for (int k = 0; k < TestNum; ++k) {
        double sum1 = 0;
        for (int i = 0; i < outNum; ++i) {
            sum1 += (pre_variety_id[k][i] - iris[k].variety_id[i]) * (pre_variety_id[k][i] - iris[k].variety_id[i]);
        }
        // 上方的处理是否合适?对此不确定
        rmse += sum1 / outNum;
    }
    rmse = sqrt(rmse / TestNum);
    printf("\nrmse : %lf\nwrong judge : %d\naccuracy : %lf\n", rmse, wrong_judge, ((double) wrong_judge )/ TestNum);
    //        rmse        wrong judge       accuracy
}
