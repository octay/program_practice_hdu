/*
 * based on utf-8
 * program practice final assignment in hdu
 * management system for in and out
 * authors' github : @hphuimen @octay @yeshuimuhua
 * ver0.2
 */

#include <stdio.h>      // 执行输入和输出
#include <stdlib.h>     // 各种通用工具函数
#include <string.h>     // 处理字符串
#include <windows.h>    // windows的一些系统功能
#include <limits.h>     // 查看一些变量的范围
#include <ctype.h>      // 处理字符
#include <conio.h>      // 控制台输入输出

// starting x-coordinates
#define POS_X1 35       // 菜单 第一列 & 输出提示 排序后
#define POS_X2 40       // 输入模块的提示语句
#define POS_X3 50       // 第一次调用输入模块或磁盘数据读入模块功能以外的其他功能 报错
#define POS_X4 65       // 菜单 第二列
// starting y-coordinates
#define POS_Y 3         // 输出提示 排序后

#define HITO_NUM 140    // num of hito
#define NAME_LEN 10     // length of name
#define COM_LEN 10      // length of company's name
#define PARTICULAR_LEN 140  // length of particular
#define INPUT_FILE_NAME "input.txt"     // default file name to get data conveniently
#define OUTPUT_FILE_NAME "output.txt"   // default file name to store data

struct time_info {
    int year;
    int mon;
    int day;
    int hour;
    int min;
    int sec;
};

struct hito_info {
    int accomplish;
    // -1 application applied only
    // 0 checked in only
    // 1 application applied and checked in and checked out, a round of in and out accomplished
    char name[NAME_LEN];
    int sex;        // 1 male 2 female
    char tel[11 + 1];   // + 1 means to leave room for '\0' based on the ori
    char id[18 + 1];
    char company[COM_LEN];
    char car_num[10 + 1];
    char particular[PARTICULAR_LEN];
    char guarantee_name[NAME_LEN];
    char guarantee_tel[11 + 1];
    char health_code;   // green 'g' yellow 'y' red 'r'
    int is_area;        // have been to epidemic area or not
    int is_symptom;     // have symptom of cough and fever or not
    struct time_info in_time_app, out_time_app, in_time_act, out_time_act;  // in_ 入校 out_ 出校 _app 申请时间 _act 实际时间
};

int Menu();     // 菜单 返回选择
void AppendRecord();        // 信息录入
void DeleteRecord();        // 信息删除
void SortPrintTime();       // 时间顺序索引
void SortByTime(int k, int m);
void SortPrintOrder();      // 录入顺序索引
void SearchName();          // 按名字查找
void SearchTel();           // 按手机号查找
void SearchID();            // 按身份证号查找
void SearchCarNum();        // 按车牌号查找
void SearchDay();           // 按日期查找 精确到天 默认以实际出入时间为准
void SearchPeriod();        // 按时间段查找 可精确到日时分三个模式 默认以实际出入时间为准
void StoreRecord();         // 保存记录到文件中

int SearchName4IO(int accomplish_state);

void SubmitApp();           // 申请
void CheckI();              // 登入
void CheckO();              // 登出

void Hide();    // 隐藏光标
void SetPosition(int x, int y);     // 设置起始位置
void InitHitoArray(int length);     // 初始化数组 为一些成员赋值
int TxtLine(char *fname);   // txt文件中的换行符数量
