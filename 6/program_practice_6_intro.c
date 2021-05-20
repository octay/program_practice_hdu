#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define TrainNUm 380
#define TestNum 126
#define inNum 13
#define outNum 1
#define NeuronNum 40
#define TrainingTimes 40000
#define PerOverlook 1000
#define WAlta 0.1
#define VAlta 0.2
#define file_name_in "in.txt"
#define file_name_out "out.txt"
#define file_name_test "test.txt"
// 权值wv的学习率
double train_data_in[TrainNUm][inNum];
double train_data_out[TrainNUm][outNum];
double test_data_in[TestNum][inNum];
double test_data_out[TestNum][outNum];  // 存储样本输入与输出
double test_data_pre[TestNum][outNum];  // 预测输出
double v_in2neu[NeuronNum][inNum];      // 输入层 -> 隐含层 权重
double neu_output[NeuronNum];           // 隐含层的输出
double w_neu2out[outNum][NeuronNum];    // 隐含层 -> 输出层 权重
double max_in[inNum], min_in[inNum], max_out[outNum], min_out[outNum];
double out[outNum];      // 存储神经网络的输出
double dw[outNum][NeuronNum];
double dv[NeuronNum][inNum];            // wv的修正量
double mse;     // 存储均方误差
double rmse;    // 存储均方根误差

void input();

void init();

void train();

void test();

void comput_o(int var);

void back_update(int var);

void input4test();

void init4test();

int main(void) {
    input();
    init();
    train();
    input4test();
    init4test();
    test();
    return 0;
}

void input() {
    FILE *fp1, *fp2;
    char ch;

    if ((fp1 = fopen(file_name_in, "rb")) == NULL) {
        printf("open file %s error \n", file_name_in);
        exit(0);
    }
    for (int i = 0; i < TrainNUm; i++) {
        for (int j = 0; j < inNum; j++) {
            if (j) fscanf(fp1, "%c", &ch);
            fscanf(fp1, "%lf", &train_data_in[i][j]);
        }
    }
    fclose(fp1);

    if ((fp2 = fopen(file_name_out, "rb")) == NULL) {
        printf("open file %s error \n", file_name_out);
        exit(0);
    }
    for (int i = 0; i < TrainNUm; i++) {
        for (int j = 0; j < outNum; j++) {
            fscanf(fp2, "%lf", &train_data_out[i][j]);
        }
    }
    fclose(fp2);
}

void init() {
    srand((int) time(0));

    // 数据归一化
    for (int i = 0; i < inNum; ++i) {
        min_in[i] = max_in[i] = train_data_in[0][i];
        for (int j = 0; j < TrainNUm; ++j) {
            max_in[i] = max_in[i] > train_data_in[j][i] ? max_in[i] : train_data_in[j][i];
            min_in[i] = min_in[i] < train_data_in[j][i] ? min_in[i] : train_data_in[j][i];
        }
    }

    for (int i = 0; i < outNum; ++i) {
        min_out[i] = max_out[i] = train_data_out[0][i];
        for (int j = 0; j < TrainNUm; ++j) {
            max_out[i] = max_out[i] > train_data_out[j][i] ? max_out[i] : train_data_out[j][i];
            min_out[i] = min_out[i] < train_data_out[j][i] ? min_out[i] : train_data_out[j][i];
        }
    }

    for (int i = 0; i < inNum; ++i) {
        for (int j = 0; j < TrainNUm; ++j) {
            train_data_in[j][i] = (train_data_in[j][i] - min_in[i]) / (max_in[i] - min_in[i]);
        }
    }

    for (int i = 0; i < outNum; ++i) {
        for (int j = 0; j < TrainNUm; ++j) {
            train_data_out[j][i] = (train_data_out[j][i] - min_out[i]) / (max_out[i] - min_out[i]);
        }
    }

    // 各权值取[-1, 1] 权值修正量赋值为0 权值修正量为0
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
                double tmp1 = out[j] * (max_out[j] - min_out[j]) + min_out[j];  // 反归一化
                double tmp2 = train_data_out[i][j] * (max_out[j] - min_out[j]) + min_out[j];
                mse += (tmp1 - tmp2) * (tmp1 - tmp2);
            }
        }
        mse = mse / TrainNUm * outNum;      // 均方误差

        if (count % PerOverlook == 0) printf("%-7d %lf \n", count, mse);

        count++;
    } while (count <= TrainingTimes && mse >= 1);
    printf("\ntraining accomplished \n");
}

void comput_o(int var) {
    double sum;

    for (int i = 0; i < NeuronNum; ++i) {   // 每个隐藏层神经元的输出
        sum = 0;
        for (int j = 0; j < inNum; ++j) sum += v_in2neu[i][j] * train_data_in[var][j];
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
            dw[j][i] = WAlta * (train_data_out[var][j] - out[j]) * out[j] * (1 - out[j]) * neu_output[i];
            w_neu2out[j][i] += dw[j][i];
            sum += (train_data_out[var][j] - out[j]) * out[j] * (1 - out[j]) * w_neu2out[j][i];
        }

        // 隐藏层与输入层
        for (int j = 0; j < inNum; ++j) {
            dv[i][j] = VAlta * sum * neu_output[i] * (1 - neu_output[i]) * train_data_in[var][j];
            v_in2neu[i][j] += dv[i][j];
        }
    }
}

void test() {
    double sum;

    // 计算预期结果
    for (int k = 0; k < TestNum; ++k) {
        // 隐含层
        for (int i = 0; i < NeuronNum; ++i) {
            sum = 0;
            for (int j = 0; j < inNum; ++j) sum += v_in2neu[i][j] * test_data_in[k][j];
            neu_output[i] = 1 / (1 + exp(-1 * sum));
        }

        // 输出层
        for (int i = 0; i < outNum; ++i) {
            sum = 0;
            for (int j = 0; j < NeuronNum; ++j) sum += w_neu2out[i][j] * neu_output[j];
            test_data_pre[k][i] = 1 / (1 + exp(-1 * sum)) * (max_out[i] - min_out[i]) + min_out[i];
        }

        // 打印内容
        printf("num : %d pre : ", k + 1);
        for (int i = 0; i < outNum; ++i) printf("%lf ", test_data_pre[k][i]);
        printf("act : ");
        for (int i = 0; i < outNum; ++i) printf("%lf ", test_data_out[k][i]);
        printf("\n");
    }

    rmse=0.0;
    for (int k = 0; k < TestNum; ++k) {
        double sum1 = 0;
        for (int i = 0; i < outNum; ++i) {
            sum1 += (test_data_pre[k][i] - test_data_out[k][i])*(test_data_pre[k][i] - test_data_out[k][i]);
        }
        // 上方的处理是否合适?对此不确定
        rmse += sum1 / outNum;
    }
    rmse= sqrt(rmse/TestNum);
    printf("\nrmse : %lf", rmse);
}

void input4test() {
    FILE *fp;
    char ch;

    if ((fp = fopen(file_name_test, "rb")) == NULL) {
        printf("open file %s error \n", file_name_test);
        exit(0);
    }
    for (int i = 0; i < TestNum; i++) {
        for (int j = 0; j < inNum + outNum; j++) {
            if (j) fscanf(fp, "%c", &ch);

            if (j < inNum) fscanf(fp, "%lf", &test_data_in[i][j]);
            else fscanf(fp, "%lf", &test_data_out[i][j - inNum]);
        }
    }
    fclose(fp);
}

void init4test() {
    // 数据归一化
    for (int i = 0; i < inNum; ++i) {
        for (int j = 0; j < TestNum; ++j) {
            test_data_in[j][i] = (test_data_in[j][i] - min_in[i]) / (max_in[i] - min_in[i]);
        }
    }
}
