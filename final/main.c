/*
 * based on utf-8
 * program practice final assignment in hdu
 * management system for in and out
 * authors' github : @hphuimen @octay @yeshuimuhua
 * ver0.1
 */

#include "ms4io.h"

struct hito_info hito[HITO_NUM];    // 所有的数据都在这里 新增 删除 保存 查找 ...
int count_record = 0;       // 记录条数

int main() {
    int dept_ch;
    system("mode con cols=130 lines=60");
    system("COLOR F9");
    InitHitoArray(HITO_NUM);
    while (1) {
        system("cls");
        dept_ch = Menu();
        switch (dept_ch) {
            case 1:
                system("cls");
                AppendRecord();
                break;
            case 2:
                system("cls");
                DeleteRecord();
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                system("cls");
                SearchName();
                break;
            case 6:
                system("cls");
                SearchTel();
                break;
            case 7:
                system("cls");
                SearchID();
                break;
            case 8:
                break;
            case 0:
                system("cls");
                exit(0);
                break;
            default:
                break;
        }
    }
    return 0;
}

int Menu() {
    int pos_y = 5;  // starting y-coordinates
    int dept_ch;
    SetPosition(POS_X3, pos_y);
    printf("外来人员出入管理\n");

    for (int i = 0; i < 2; i++) {   // '-' * 55
        SetPosition(POS_X1, ++pos_y);
        for (int j = 0; j < 55; j++) {
            printf("-");
        }   // for ... j
    }       // for ... i
    // dept
    /*
     1. 信息录入
         1.1 从控制台录入
         1.2 从文件录入
     2. 信息删除
     3. 时间顺序索引
         3.1 选定时间范围
         3.2 focus on 健康码
         3.3 focus on 有无经过疫区
         3.4 focus on 有无症状
         3.5 升序降序
     4. 录入顺序索引
         4.1 focus on 健康码
         4.2 focus on 有无经过疫区
         4.3 focus on 有无症状
         4.4 升序降序
     5. 按名字查找
         5.1 精准查找
         5.2 模糊搜索
     6. 按手机号查找
         6.1 精准查找
         6.2 模糊搜索
     7. 按身份证号查找
         7.1 精准查找
         7.2 模糊搜索
     8. 按车牌号查找
         8.1 精准查找
     */
    SetPosition(POS_X1, ++pos_y);
    printf("1. 信息录入");
    SetPosition(POS_X4, pos_y);
    printf("2. 信息删除");
    SetPosition(POS_X1, pos_y += 2);
    printf("3. 时间顺序索引");
    SetPosition(POS_X4, pos_y);
    printf("4. 录入顺序索引");
    SetPosition(POS_X1, pos_y += 2);
    printf("5. 按名字查找");
    SetPosition(POS_X4, pos_y);
    printf("6. 按手机号查找");
    SetPosition(POS_X1, pos_y += 2);
    printf("7. 按身份证号查找");
    SetPosition(POS_X4, pos_y);
    printf("8. 按车牌号查找");
    SetPosition(POS_X1, pos_y += 2);
    printf("0. 退出");
    for (int i = 0; i < 2; i++) {   // '-' * 55
        SetPosition(POS_X1, ++pos_y);
        for (int j = 0; j < 55; j++) {
            printf("-");
        }   // for ... j
    }       // for ... i
    SetPosition(POS_X1, ++pos_y);
    printf("请选择 [  ]\b\b\b");
    scanf("%d", &dept_ch);
    return dept_ch;
}

void AppendRecord() {
    int pos_y = 6;
    struct hito_info temp_hito;
    int how_to_input_ch;
    SetPosition(POS_X2, pos_y);
    printf("1. 从控制台录入 2. 从文件录入 [  ]\b\b\b");
    scanf("%d", &how_to_input_ch);
    if (how_to_input_ch == 1) {         // 从控制台录入
        SetPosition(POS_X2, pos_y += 2);
        printf("输入 姓名");
        scanf("%s", temp_hito.name);

        SetPosition(POS_X2, pos_y += 2);
        printf("输入 身份证号");
        scanf("%s", temp_hito.id);
        if (strlen(temp_hito.id) != 18) return;     // judge id
        for (int i = 0; i < 17; ++i) if (!isdigit(temp_hito.id[i])) return;
        if (isdigit(temp_hito.id[17] == 0 || temp_hito.id[17] == 'x' || temp_hito.id[17] == 'X')) return;
        temp_hito.sex = (temp_hito.id[16] - '0' % 2 == 0) ? 2 : 1;  // judge sex from id

        SetPosition(POS_X2, pos_y += 2);
        printf("输入 手机号码");
        scanf("%s", temp_hito.tel);
        for (int i = 0; temp_hito.tel[i] != '\0'; ++i) if (!isdigit(temp_hito.tel[i])) return;  // judge tel

        SetPosition(POS_X2, pos_y += 2);
        printf("输入 公司");
        scanf("%s", temp_hito.company);

        SetPosition(POS_X2, pos_y += 2);
        printf("输入 车牌号");
        scanf("%s", temp_hito.car_num);

        SetPosition(POS_X2, pos_y += 2);
        printf("输入 担保人姓名");
        scanf("%s", temp_hito.guarantee_name);

        SetPosition(POS_X2, pos_y += 2);
        printf("输入 担保人电话号码");
        scanf("%s", temp_hito.guarantee_tel);
        for (int i = 0; temp_hito.guarantee_tel[i] != '\0'; ++i) if (!isdigit(temp_hito.guarantee_tel[i])) return;

        SetPosition(POS_X2, pos_y += 2);
        char str_to_get_char[10];
        printf("输入 健康码颜色 g.绿 y.黄 r.红");
        scanf("%s", str_to_get_char);
        temp_hito.health_code = str_to_get_char[0];
        if (temp_hito.health_code != 'g' && temp_hito.health_code != 'y' && temp_hito.health_code != 'r') return;

        int temp_input_num;
        SetPosition(POS_X2, pos_y += 2);
        printf("输入 是否经过疫区 0. 无 1. 有");
        scanf("%d", &temp_input_num);
        if (temp_input_num) temp_hito.is_area = 1;
        else temp_hito.is_area = 0;

        SetPosition(POS_X2, pos_y += 2);
        printf("输入 是否有症状 0. 无 1. 有");
        scanf("%d", &temp_input_num);
        if (temp_input_num) temp_hito.is_symptom = 1;
        else temp_hito.is_symptom = 0;

        // format of time 年-月-日 时:分:秒
        SetPosition(POS_X2, pos_y += 2);
        printf("输入 申请入校时间 申请出校时间 实际入校时间 实际出校时间 format of time 年-月-日 时:分:秒");
        scanf("%d-%d-%d %d:%d:%d", &temp_hito.in_time_app.year, &temp_hito.in_time_app.mon,
              &temp_hito.in_time_app.day, &temp_hito.in_time_app.hour, &temp_hito.in_time_app.min,
              &temp_hito.in_time_app.sec);
        scanf("%d-%d-%d %d:%d:%d", &temp_hito.out_time_app.year, &temp_hito.out_time_app.mon,
              &temp_hito.out_time_app.day, &temp_hito.out_time_app.hour, &temp_hito.out_time_app.min,
              &temp_hito.out_time_app.sec);
        scanf("%d-%d-%d %d:%d:%d", &temp_hito.in_time_act.year, &temp_hito.in_time_act.mon,
              &temp_hito.in_time_act.day, &temp_hito.in_time_act.hour, &temp_hito.in_time_act.min,
              &temp_hito.in_time_act.sec);
        scanf("%d-%d-%d %d:%d:%d", &temp_hito.out_time_act.year, &temp_hito.out_time_act.mon,
              &temp_hito.out_time_act.day, &temp_hito.out_time_act.hour, &temp_hito.out_time_act.min,
              &temp_hito.out_time_act.sec);

        SetPosition(POS_X2, pos_y += 2);
        printf("输入 申请理由");
        gets(temp_hito.particular);

        hito[count_record] = temp_hito;
        count_record++;
        SetPosition(POS_X2, pos_y += 2);
        printf("录入完成");
    } else if (how_to_input_ch == 2) {    // 从文件录入
        char file_name[20] = INPUT_FILE_NAME;
        FILE *fp;
        int num_line;

//        SetPosition(POS_X2, pos_y += 2);
//        printf("输入文件名");
//        scanf("%s", file_name);

        SetPosition(POS_X2, pos_y += 2);
        if (!(fp = fopen(file_name, "r"))) {
            printf("打开文件错误");
            return;
        }

        num_line = TxtLine(file_name);
        for (int current_line = 1; current_line <= num_line; current_line++) {
            // 姓名 身份证号 手机号码 公司 车牌号 担保人姓名 担保人电话号码 健康码颜色 是否经过疫区 是否有症状 申请入校时间 申请出校时间 实际入校时间 实际出校时间 申请理由
            fscanf(fp, "%s %s %s %s %s %s %s %c %d %d", temp_hito.name, temp_hito.id, temp_hito.tel, temp_hito.company,
                   temp_hito.car_num, temp_hito.guarantee_name, temp_hito.guarantee_tel, &temp_hito.health_code,
                   &temp_hito.is_area, &temp_hito.is_symptom);
            fscanf(fp, "%d-%d-%d %d:%d:%d", &temp_hito.in_time_app.year, &temp_hito.in_time_app.mon,
                   &temp_hito.in_time_app.day, &temp_hito.in_time_app.hour, &temp_hito.in_time_app.min,
                   &temp_hito.in_time_app.sec);
            fscanf(fp, "%d-%d-%d %d:%d:%d", &temp_hito.out_time_app.year, &temp_hito.out_time_app.mon,
                   &temp_hito.out_time_app.day, &temp_hito.out_time_app.hour, &temp_hito.out_time_app.min,
                   &temp_hito.out_time_app.sec);
            fscanf(fp, "%d-%d-%d %d:%d:%d", &temp_hito.in_time_act.year, &temp_hito.in_time_act.mon,
                   &temp_hito.in_time_act.day, &temp_hito.in_time_act.hour, &temp_hito.in_time_act.min,
                   &temp_hito.in_time_act.sec);
            fscanf(fp, "%d-%d-%d %d:%d:%d", &temp_hito.out_time_act.year, &temp_hito.out_time_act.mon,
                   &temp_hito.out_time_act.day, &temp_hito.out_time_act.hour, &temp_hito.out_time_act.min,
                   &temp_hito.out_time_act.sec);
            fgets(temp_hito.particular, 140, fp);

            hito[count_record] = temp_hito;
            count_record++;
        }
        fclose(fp);
        printf("录入完成");
        Hide();        //隐藏光标
        char ch = _getch();
    }
}

void DeleteRecord() {
    int pos_y = 6;
    int y_n = 0;
    SetPosition(POS_X2, pos_y);
    printf("是否选择删除最近一次存入的数据？ 0. 否 1. 是");
    scanf("%d", &y_n);
    if (y_n == 1 && count_record > 0) {
        count_record--;
        SetPosition(POS_X2, pos_y += 2);
        printf("删除完成");
        Hide();        //隐藏光标
        char ch = _getch();
    }
}

void SearchName() {
    int i;
    int k = 1;  // 已找到的数量 默认为 1 打印时 - 1 操作即可  或者当前的标号 直接使用即可
    int mode;
    printf("1.精准查找  2.模糊查找\n");
    printf("请输入你要查找的模式：");
    scanf("%d", &mode);
    if (mode == 1) {
        char name2seek[NAME_LEN];
        printf("\n");
        printf("请输入你要查找的人的姓名：");
        scanf("%s", name2seek);
        for (i = 0; i < count_record; i++) {
            if (strcmp(hito[i].name, name2seek) == 0)   //按姓名查找，输出相应记录的姓名、身份证号、电话、申请出入时间和实际出入时间
            {
                printf("%d. ", k);
                printf("姓名：%s, 身份证号：%s, 电话：%s\n", hito[i].name, hito[i].id, hito[i].tel);
                printf("申请进入时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].in_time_app.year, hito[i].in_time_app.mon,
                       hito[i].in_time_app.day, hito[i].in_time_app.hour, hito[i].in_time_app.min,
                       hito[i].in_time_app.sec);
                printf("申请离开时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].out_time_app.year, hito[i].out_time_app.mon,
                       hito[i].out_time_app.day, hito[i].out_time_app.hour, hito[i].out_time_app.min,
                       hito[i].out_time_app.sec);
                printf("实际进入时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].in_time_act.year, hito[i].in_time_act.mon,
                       hito[i].in_time_act.day, hito[i].in_time_act.hour, hito[i].in_time_act.min,
                       hito[i].in_time_act.sec);
                printf("实际离开时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].out_time_act.year, hito[i].out_time_act.mon,
                       hito[i].out_time_act.day, hito[i].out_time_act.hour, hito[i].out_time_act.min,
                       hito[i].out_time_act.sec);
                k++;
                printf("\n");
            }
        }
        if (k == 1) printf("未找到这个姓名对应的记录\n");
        else printf("一共找到%d条记录\n", k - 1);
    } else if (mode == 2) {
        char dimname2seek[NAME_LEN];
        printf("请输入你要模糊查找的人的姓名：");
        scanf("%s", dimname2seek);
        for (i = 0; i < count_record; i++) {
            if (strstr(hito[i].name, dimname2seek) != NULL) {
                printf("%d. ", k);
                printf("姓名：%s, 身份证号：%s, 电话：%s\n", hito[i].name, hito[i].id, hito[i].tel);
                printf("申请进入时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].in_time_app.year, hito[i].in_time_app.mon,
                       hito[i].in_time_app.day, hito[i].in_time_app.hour, hito[i].in_time_app.min,
                       hito[i].in_time_app.sec);
                printf("申请离开时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].out_time_app.year, hito[i].out_time_app.mon,
                       hito[i].out_time_app.day, hito[i].out_time_app.hour, hito[i].out_time_app.min,
                       hito[i].out_time_app.sec);
                printf("实际进入时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].in_time_act.year, hito[i].in_time_act.mon,
                       hito[i].in_time_act.day, hito[i].in_time_act.hour, hito[i].in_time_act.min,
                       hito[i].in_time_act.sec);
                printf("实际离开时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].out_time_act.year, hito[i].out_time_act.mon,
                       hito[i].out_time_act.day, hito[i].out_time_act.hour, hito[i].out_time_act.min,
                       hito[i].out_time_act.sec);
                k++;
                printf("\n");
            }
        }
        if (k == 1) printf("未找到这个姓名对应的记录\n");
        else printf("一共找到%d条记录\n", k - 1);
    } else printf("模式输入错误\n");
    Hide();        //隐藏光标
    char ch = _getch();
}

void SearchTel() {
    int i;
    int k = 1;
    int mode;
    printf("1.精准查找  2.模糊查找\n");
    printf("请输入你要查找的模式：");
    scanf("%d", &mode);
    if (mode == 1) {
        char tel2seek[12];      // 11 + 1
        printf("请输入你要查找的人的电话：");
        scanf("%s", tel2seek);
        for (i = 0; i < count_record; i++) {
            if (strcmp(hito[i].tel, tel2seek) == 0) {
                printf("%d. ", k);
                printf("姓名：%s, 身份证号：%s, 电话：%s\n", hito[i].name, hito[i].id, hito[i].tel);
                printf("申请进入时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].in_time_app.year, hito[i].in_time_app.mon,
                       hito[i].in_time_app.day, hito[i].in_time_app.hour, hito[i].in_time_app.min,
                       hito[i].in_time_app.sec);
                printf("申请离开时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].out_time_app.year, hito[i].out_time_app.mon,
                       hito[i].out_time_app.day, hito[i].out_time_app.hour, hito[i].out_time_app.min,
                       hito[i].out_time_app.sec);
                printf("实际进入时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].in_time_act.year, hito[i].in_time_act.mon,
                       hito[i].in_time_act.day, hito[i].in_time_act.hour, hito[i].in_time_act.min,
                       hito[i].in_time_act.sec);
                printf("实际离开时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].out_time_act.year, hito[i].out_time_act.mon,
                       hito[i].out_time_act.day, hito[i].out_time_act.hour, hito[i].out_time_act.min,
                       hito[i].out_time_act.sec);
                k++;
                printf("\n");
            }
        }
        if (k == 1) printf("未找到这个电话对应的记录\n");
        else printf("一共找到%d条记录\n", k - 1);
    } else if (mode == 2) {
        char dimtel2seek[12];
        printf("请输入你要模糊查找的人的电话：");
        scanf("%s", dimtel2seek);
        for (i = 0; i < count_record; i++) {
            if (strstr(hito[i].tel, dimtel2seek) != NULL) {
                printf("%d. ", k);
                printf("姓名：%s, 身份证号：%s, 电话：%s\n", hito[i].name, hito[i].id, hito[i].tel);
                printf("申请进入时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].in_time_app.year, hito[i].in_time_app.mon,
                       hito[i].in_time_app.day, hito[i].in_time_app.hour, hito[i].in_time_app.min,
                       hito[i].in_time_app.sec);
                printf("申请离开时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].out_time_app.year, hito[i].out_time_app.mon,
                       hito[i].out_time_app.day, hito[i].out_time_app.hour, hito[i].out_time_app.min,
                       hito[i].out_time_app.sec);
                printf("实际进入时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].in_time_act.year, hito[i].in_time_act.mon,
                       hito[i].in_time_act.day, hito[i].in_time_act.hour, hito[i].in_time_act.min,
                       hito[i].in_time_act.sec);
                printf("实际离开时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].out_time_act.year, hito[i].out_time_act.mon,
                       hito[i].out_time_act.day, hito[i].out_time_act.hour, hito[i].out_time_act.min,
                       hito[i].out_time_act.sec);
                k++;
                printf("\n");
            }
        }
        if (k == 1) printf("未找到这个电话对应的记录\n");
        else printf("一共找到%d条记录\n", k - 1);
    } else printf("模式输入错误\n");
    Hide();        //隐藏光标
    char ch = _getch();
}

void SearchID() {
    int i;
    int k = 1;
    int mode;
    printf("1.精准查找  2.模糊查找\n");
    printf("请输入你要查找的模式：");
    scanf("%d", &mode);
    if (mode == 1) {
        char id2seek[19];       // 18 + 1
        printf("请输入你要查找的人的身份证号：");
        scanf("%s", id2seek);
        for (i = 0; i < count_record; i++) {
            if (strcmp(hito[i].id, id2seek) == 0) {
                printf("%d. ", k);
                printf("姓名：%s, 身份证号：%s, 电话：%s\n", hito[i].name, hito[i].id, hito[i].tel);
                printf("申请进入时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].in_time_app.year, hito[i].in_time_app.mon,
                       hito[i].in_time_app.day, hito[i].in_time_app.hour, hito[i].in_time_app.min,
                       hito[i].in_time_app.sec);
                printf("申请离开时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].out_time_app.year, hito[i].out_time_app.mon,
                       hito[i].out_time_app.day, hito[i].out_time_app.hour, hito[i].out_time_app.min,
                       hito[i].out_time_app.sec);
                printf("实际进入时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].in_time_act.year, hito[i].in_time_act.mon,
                       hito[i].in_time_act.day, hito[i].in_time_act.hour, hito[i].in_time_act.min,
                       hito[i].in_time_act.sec);
                printf("实际离开时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].out_time_act.year, hito[i].out_time_act.mon,
                       hito[i].out_time_act.day, hito[i].out_time_act.hour, hito[i].out_time_act.min,
                       hito[i].out_time_act.sec);
                k++;
                printf("\n");
            }
        }
        if (k == 1) printf("未找到这个身份证号对应的记录\n");
        else printf("一共找到%d条记录\n", k - 1);
    } else if (mode == 2) {
        char dimid2seek[19];
        printf("%d. ");
        scanf("%s", dimid2seek);
        for (i = 0; i < count_record; i++) {
            if (strstr(hito[i].id, dimid2seek) != NULL) {
                printf("%d. ", k);
                printf("姓名：%s, 身份证号：%s, 电话：%s\n", hito[i].name, hito[i].id, hito[i].tel);
                printf("申请进入时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].in_time_app.year, hito[i].in_time_app.mon,
                       hito[i].in_time_app.day, hito[i].in_time_app.hour, hito[i].in_time_app.min,
                       hito[i].in_time_app.sec);
                printf("申请离开时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].out_time_app.year, hito[i].out_time_app.mon,
                       hito[i].out_time_app.day, hito[i].out_time_app.hour, hito[i].out_time_app.min,
                       hito[i].out_time_app.sec);
                printf("实际进入时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].in_time_act.year, hito[i].in_time_act.mon,
                       hito[i].in_time_act.day, hito[i].in_time_act.hour, hito[i].in_time_act.min,
                       hito[i].in_time_act.sec);
                printf("实际离开时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].out_time_act.year, hito[i].out_time_act.mon,
                       hito[i].out_time_act.day, hito[i].out_time_act.hour, hito[i].out_time_act.min,
                       hito[i].out_time_act.sec);
                k++;
                printf("\n");
            }
        }
        if (k == 1) printf("未找到这个身份证号对应的记录\n");
        else printf("一共找到%d条记录\n", k - 1);
    } else printf("模式输入错误\n");
    Hide();        //隐藏光标
    char ch = _getch();
}

void SearchCarNum() {
    int i;
    int k = 1;
    int mode;
    printf("1.精准查找  2.模糊查找\n");
    printf("请输入你要查找的模式：");
    scanf("%d", &mode);
    if (mode == 1) {
        char car_num2seek[8];
        printf("请输入你要查找的人的车牌号：");
        scanf("%s", car_num2seek);
        for (i = 0; i < count_record; i++) {
            if (strcmp(hito[i].car_num, car_num2seek) == 0) {
                printf("%d. ", k);
                printf("姓名：%s, 身份证号：%s, 电话：%s\n", hito[i].name, hito[i].id, hito[i].tel);
                printf("申请进入时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].in_time_app.year, hito[i].in_time_app.mon,
                       hito[i].in_time_app.day, hito[i].in_time_app.hour, hito[i].in_time_app.min,
                       hito[i].in_time_app.sec);
                printf("申请离开时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].out_time_app.year, hito[i].out_time_app.mon,
                       hito[i].out_time_app.day, hito[i].out_time_app.hour, hito[i].out_time_app.min,
                       hito[i].out_time_app.sec);
                printf("实际进入时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].in_time_act.year, hito[i].in_time_act.mon,
                       hito[i].in_time_act.day, hito[i].in_time_act.hour, hito[i].in_time_act.min,
                       hito[i].in_time_act.sec);
                printf("实际离开时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].out_time_act.year, hito[i].out_time_act.mon,
                       hito[i].out_time_act.day, hito[i].out_time_act.hour, hito[i].out_time_act.min,
                       hito[i].out_time_act.sec);
                k++;
                printf("\n");
            }
        }
        if (k == 1) printf("未找到这个车牌号对应的记录\n");
        else printf("一共找到%d条记录\n", k - 1);
    } else if (mode == 2) {
        char dimcar_num2seek[8];
        printf("请输入你要模糊查找的人的车牌号：");
        scanf("%s", dimcar_num2seek);
        for (i = 0; i < count_record; i++) {
            if (strstr(hito[i].car_num, dimcar_num2seek) != NULL) {
                printf("%d. ", k);
                printf("姓名：%s, 身份证号：%s, 电话：%s\n", hito[i].name, hito[i].id, hito[i].tel);
                printf("申请进入时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].in_time_app.year, hito[i].in_time_app.mon,
                       hito[i].in_time_app.day, hito[i].in_time_app.hour, hito[i].in_time_app.min,
                       hito[i].in_time_app.sec);
                printf("申请离开时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].out_time_app.year, hito[i].out_time_app.mon,
                       hito[i].out_time_app.day, hito[i].out_time_app.hour, hito[i].out_time_app.min,
                       hito[i].out_time_app.sec);
                printf("实际进入时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].in_time_act.year, hito[i].in_time_act.mon,
                       hito[i].in_time_act.day, hito[i].in_time_act.hour, hito[i].in_time_act.min,
                       hito[i].in_time_act.sec);
                printf("实际离开时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].out_time_act.year, hito[i].out_time_act.mon,
                       hito[i].out_time_act.day, hito[i].out_time_act.hour, hito[i].out_time_act.min,
                       hito[i].out_time_act.sec);
                k++;
                printf("\n");
            }
        }
        if (k == 1) printf("未找到这个车牌号对应的记录\n");
        else printf("一共找到%d条记录\n", k - 1);
    } else printf("模式输入错误\n");
    Hide();        //隐藏光标
    char ch = _getch();
}

void SearchDay() {
    int i;
    int k = 1;
    int year2seek, mon2seek, day2seek;
    printf("请输入你要查找的年月日：\n");
    printf("年份：");
    scanf("%d", &year2seek);
    printf("月份：");
    scanf("%d", &mon2seek);
    printf("日期：");
    scanf("%d", &day2seek);
    for (i = 0; i < count_record; i++) {
        if (hito[i].in_time_act.year == year2seek && hito[i].in_time_act.mon == mon2seek &&
            hito[i].in_time_act.day == day2seek) {
            printf("%d. ", k);
            printf("姓名：%s, 身份证号：%s, 电话：%s\n", hito[i].name, hito[i].id, hito[i].tel);
            printf("申请进入时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].in_time_app.year, hito[i].in_time_app.mon,
                   hito[i].in_time_app.day, hito[i].in_time_app.hour, hito[i].in_time_app.min, hito[i].in_time_app.sec);
            printf("申请离开时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].out_time_app.year, hito[i].out_time_app.mon,
                   hito[i].out_time_app.day, hito[i].out_time_app.hour, hito[i].out_time_app.min,
                   hito[i].out_time_app.sec);
            printf("实际进入时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].in_time_act.year, hito[i].in_time_act.mon,
                   hito[i].in_time_act.day, hito[i].in_time_act.hour, hito[i].in_time_act.min, hito[i].in_time_act.sec);
            printf("实际离开时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].out_time_act.year, hito[i].out_time_act.mon,
                   hito[i].out_time_act.day, hito[i].out_time_act.hour, hito[i].out_time_act.min,
                   hito[i].out_time_act.sec);
            printf("已入校\n");
            k++;
            printf("\n");
        }
        if (hito[i].out_time_act.year == year2seek && hito[i].out_time_act.mon == mon2seek &&
            hito[i].out_time_act.day == day2seek) {
            printf("%d. ", k);
            printf("姓名：%s, 身份证号：%s, 电话：%s\n", hito[i].name, hito[i].id, hito[i].tel);
            printf("申请进入时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].in_time_app.year, hito[i].in_time_app.mon,
                   hito[i].in_time_app.day, hito[i].in_time_app.hour, hito[i].in_time_app.min, hito[i].in_time_app.sec);
            printf("申请离开时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].out_time_app.year, hito[i].out_time_app.mon,
                   hito[i].out_time_app.day, hito[i].out_time_app.hour, hito[i].out_time_app.min,
                   hito[i].out_time_app.sec);
            printf("实际进入时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].in_time_act.year, hito[i].in_time_act.mon,
                   hito[i].in_time_act.day, hito[i].in_time_act.hour, hito[i].in_time_act.min, hito[i].in_time_act.sec);
            printf("实际离开时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].out_time_act.year, hito[i].out_time_act.mon,
                   hito[i].out_time_act.day, hito[i].out_time_act.hour, hito[i].out_time_act.min,
                   hito[i].out_time_act.sec);
            printf("已离校\n");
            k++;
            printf("\n");
        }
    }
    if (k == 1) printf("未找到该日期对应的记录\n");
    else printf("一共找到%d条记录\n", k - 1);
    Hide();        //隐藏光标
    char ch = _getch();
}

void SearchPeriod() {
    int i;
    int k = 1;
    int mode;
    printf("1.精确到天  2.精确到小时  3.精确到分\n");
    printf("请输入你要查找的模式：");
    scanf("%d", &mode);
    if (mode == 1) {
        int start_year, start_mon, start_day, end_year, end_mon, end_day;
        printf("请输入起始时间：\n");
        printf("年份：");
        scanf("%d", &start_year);
        printf("月份：");
        scanf("%d", &start_mon);
        printf("日期：");
        scanf("%d", &start_day);
        printf("请输入终止时间：\n");
        printf("年份：");
        scanf("%d", &end_year);
        printf("月份：");
        scanf("%d", &end_mon);
        printf("日期：");
        scanf("%d", &end_day);
        int start_time = start_year * 10000 + start_mon * 100 + start_day;
        int end_time = end_year * 10000 + end_mon * 100 + end_day;
        for (i = 0; i < count_record; i++) {
            int in_time = hito[i].in_time_act.year * 10000 + hito[i].in_time_act.mon * 100 + hito[i].in_time_act.day;
            int out_time =
                    hito[i].out_time_act.year * 10000 + hito[i].out_time_act.mon * 100 + hito[i].out_time_act.day;
            if (in_time >= start_time && in_time <= end_time) {
                printf("%d. ", k);
                printf("姓名：%s, 身份证号：%s, 电话：%s\n", hito[i].name, hito[i].id, hito[i].tel);
                printf("申请进入时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].in_time_app.year, hito[i].in_time_app.mon,
                       hito[i].in_time_app.day, hito[i].in_time_app.hour, hito[i].in_time_app.min,
                       hito[i].in_time_app.sec);
                printf("申请离开时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].out_time_app.year, hito[i].out_time_app.mon,
                       hito[i].out_time_app.day, hito[i].out_time_app.hour, hito[i].out_time_app.min,
                       hito[i].out_time_app.sec);
                printf("实际进入时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].in_time_act.year, hito[i].in_time_act.mon,
                       hito[i].in_time_act.day, hito[i].in_time_act.hour, hito[i].in_time_act.min,
                       hito[i].in_time_act.sec);
                printf("实际离开时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].out_time_act.year, hito[i].out_time_act.mon,
                       hito[i].out_time_act.day, hito[i].out_time_act.hour, hito[i].out_time_act.min,
                       hito[i].out_time_act.sec);
                printf("已入校\n");
                k++;
                printf("\n");
            }
            if (out_time >= start_time && out_time <= end_time) {
                printf("%d. ", k);
                printf("姓名：%s, 身份证号：%s, 电话：%s\n", hito[i].name, hito[i].id, hito[i].tel);
                printf("申请进入时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].in_time_app.year, hito[i].in_time_app.mon,
                       hito[i].in_time_app.day, hito[i].in_time_app.hour, hito[i].in_time_app.min,
                       hito[i].in_time_app.sec);
                printf("申请离开时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].out_time_app.year, hito[i].out_time_app.mon,
                       hito[i].out_time_app.day, hito[i].out_time_app.hour, hito[i].out_time_app.min,
                       hito[i].out_time_app.sec);
                printf("实际进入时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].in_time_act.year, hito[i].in_time_act.mon,
                       hito[i].in_time_act.day, hito[i].in_time_act.hour, hito[i].in_time_act.min,
                       hito[i].in_time_act.sec);
                printf("实际离开时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].out_time_act.year, hito[i].out_time_act.mon,
                       hito[i].out_time_act.day, hito[i].out_time_act.hour, hito[i].out_time_act.min,
                       hito[i].out_time_act.sec);
                printf("已离校\n");
                k++;
                printf("\n");
            }
        }
        if (k == 1)printf("未找到该时间段对应的记录\n");
        else printf("一共找到%d条记录\n", k - 1);
    } else if (mode == 2) {
        int year2seek, mon2seek, day2seek, start_hour, end_hour;
        printf("请输入你要查找的年、月、日：\n");
        printf("年份：");
        scanf("%d", &year2seek);
        printf("月份：");
        scanf("%d", &mon2seek);
        printf("日期：");
        scanf("%d", &day2seek);
        printf("请输入起始时间：\n");
        printf("小时：");
        scanf("%d", &start_hour);
        printf("请输入终止时间：\n");
        printf("小时：");
        scanf("%d", &end_hour);
        for (i = 0; i < count_record; i++) {
            if (hito[i].in_time_act.year == year2seek && hito[i].in_time_act.mon == mon2seek &&
                hito[i].in_time_act.day == day2seek &&
                hito[i].in_time_act.hour >= start_hour && hito[i].in_time_act.hour <= end_hour) {
                printf("%d. ", k);
                printf("姓名：%s, 身份证号：%s, 电话：%s\n", hito[i].name, hito[i].id, hito[i].tel);
                printf("申请进入时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].in_time_app.year, hito[i].in_time_app.mon,
                       hito[i].in_time_app.day, hito[i].in_time_app.hour, hito[i].in_time_app.min,
                       hito[i].in_time_app.sec);
                printf("申请离开时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].out_time_app.year, hito[i].out_time_app.mon,
                       hito[i].out_time_app.day, hito[i].out_time_app.hour, hito[i].out_time_app.min,
                       hito[i].out_time_app.sec);
                printf("实际进入时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].in_time_act.year, hito[i].in_time_act.mon,
                       hito[i].in_time_act.day, hito[i].in_time_act.hour, hito[i].in_time_act.min,
                       hito[i].in_time_act.sec);
                printf("实际离开时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].out_time_act.year, hito[i].out_time_act.mon,
                       hito[i].out_time_act.day, hito[i].out_time_act.hour, hito[i].out_time_act.min,
                       hito[i].out_time_act.sec);
                printf("已入校\n");
                k++;
                printf("\n");
            }
            if (hito[i].out_time_act.year == year2seek && hito[i].out_time_act.mon == mon2seek &&
                hito[i].out_time_act.day == day2seek &&
                hito[i].out_time_act.hour >= start_hour && hito[i].out_time_act.hour <= end_hour) {
                printf("%d. ", k);
                printf("姓名：%s, 身份证号：%s, 电话：%s\n", hito[i].name, hito[i].id, hito[i].tel);
                printf("申请进入时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].in_time_app.year, hito[i].in_time_app.mon,
                       hito[i].in_time_app.day, hito[i].in_time_app.hour, hito[i].in_time_app.min,
                       hito[i].in_time_app.sec);
                printf("申请离开时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].out_time_app.year, hito[i].out_time_app.mon,
                       hito[i].out_time_app.day, hito[i].out_time_app.hour, hito[i].out_time_app.min,
                       hito[i].out_time_app.sec);
                printf("实际进入时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].in_time_act.year, hito[i].in_time_act.mon,
                       hito[i].in_time_act.day, hito[i].in_time_act.hour, hito[i].in_time_act.min,
                       hito[i].in_time_act.sec);
                printf("实际离开时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].out_time_act.year, hito[i].out_time_act.mon,
                       hito[i].out_time_act.day, hito[i].out_time_act.hour, hito[i].out_time_act.min,
                       hito[i].out_time_act.sec);
                printf("已离校\n");
                k++;
                printf("\n");
            }
        }
        if (k == 1)printf("未找到该时间段对应的记录\n");
        else printf("一共找到%d条记录\n", k - 1);
    } else if (mode == 3) {
        int year2seek, mon2seek, day2seek, start_hour, end_hour, start_min, end_min;
        printf("请输入你要查找的年、月、日：\n");
        printf("年份：");
        scanf("%d", &year2seek);
        printf("月份：");
        scanf("%d", &mon2seek);
        printf("日期：");
        scanf("%d", &day2seek);
        printf("请输入起始时间：\n");
        printf("小时：");
        scanf("%d", &start_hour);
        printf("分：");
        scanf("%d", &start_min);
        printf("请输入终止时间：\n");
        printf("小时：");
        scanf("%d", &end_hour);
        printf("分：");
        scanf("%d", &end_min);
        for (i = 0; i < count_record; i++) {
            if (hito[i].in_time_act.year == year2seek && hito[i].in_time_act.mon == mon2seek &&
                hito[i].in_time_act.day == day2seek &&
                hito[i].in_time_act.hour >= start_hour && hito[i].in_time_act.hour <= end_hour &&
                hito[i].in_time_act.min >= start_min && hito[i].in_time_act.min <= end_min) {
                printf("%d. ", k);
                printf("姓名：%s, 身份证号：%s, 电话：%s\n", hito[i].name, hito[i].id, hito[i].tel);
                printf("申请进入时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].in_time_app.year, hito[i].in_time_app.mon,
                       hito[i].in_time_app.day, hito[i].in_time_app.hour, hito[i].in_time_app.min,
                       hito[i].in_time_app.sec);
                printf("申请离开时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].out_time_app.year, hito[i].out_time_app.mon,
                       hito[i].out_time_app.day, hito[i].out_time_app.hour, hito[i].out_time_app.min,
                       hito[i].out_time_app.sec);
                printf("实际进入时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].in_time_act.year, hito[i].in_time_act.mon,
                       hito[i].in_time_act.day, hito[i].in_time_act.hour, hito[i].in_time_act.min,
                       hito[i].in_time_act.sec);
                printf("实际离开时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].out_time_act.year, hito[i].out_time_act.mon,
                       hito[i].out_time_act.day, hito[i].out_time_act.hour, hito[i].out_time_act.min,
                       hito[i].out_time_act.sec);
                printf("已入校\n");
                k++;
                printf("\n");
            }
            if (hito[i].out_time_act.year == year2seek && hito[i].out_time_act.mon == mon2seek &&
                hito[i].out_time_act.day == day2seek &&
                hito[i].out_time_act.hour >= start_hour && hito[i].out_time_act.hour <= end_hour &&
                hito[i].out_time_act.min >= start_min && hito[i].out_time_act.min <= end_min) {
                printf("%d. ", k);
                printf("姓名：%s, 身份证号：%s, 电话：%s\n", hito[i].name, hito[i].id, hito[i].tel);
                printf("申请进入时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].in_time_app.year, hito[i].in_time_app.mon,
                       hito[i].in_time_app.day, hito[i].in_time_app.hour, hito[i].in_time_app.min,
                       hito[i].in_time_app.sec);
                printf("申请离开时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].out_time_app.year, hito[i].out_time_app.mon,
                       hito[i].out_time_app.day, hito[i].out_time_app.hour, hito[i].out_time_app.min,
                       hito[i].out_time_app.sec);
                printf("实际进入时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].in_time_act.year, hito[i].in_time_act.mon,
                       hito[i].in_time_act.day, hito[i].in_time_act.hour, hito[i].in_time_act.min,
                       hito[i].in_time_act.sec);
                printf("实际离开时间：%04d年%02d月%02d日%02d时%02d分%02d秒\n", hito[i].out_time_act.year, hito[i].out_time_act.mon,
                       hito[i].out_time_act.day, hito[i].out_time_act.hour, hito[i].out_time_act.min,
                       hito[i].out_time_act.sec);
                printf("已离校\n");
                k++;
                printf("\n");
            }
        }
        if (k == 1)printf("未找到该时间段对应的记录\n");
        else printf("一共找到%d条记录\n", k - 1);
    } else printf("模式输入错误\n");
    Hide();        //隐藏光标
    char ch = _getch();
}

void StoreRecord() {
    char file_name[20] = OUTPUT_FILE_NAME;
    FILE *fp;
    int num_line;
    int pos_y = 6;

//    SetPosition(POS_X2, pos_y);
//    printf("输入文件名");
//    scanf("%s", file_name);

    SetPosition(POS_X2, pos_y += 2);
    if (!(fp = fopen(file_name, "w"))) {
        printf("打开文件错误");
        return;
    }
    for (int i = 0; i < count_record; ++i) {
        // 姓名 身份证号 手机号码 公司 车牌号 担保人姓名 担保人电话号码 健康码颜色 是否经过疫区 是否有症状 申请入校时间 申请出校时间 实际入校时间 实际出校时间 申请理由
        fprintf(fp, "%s %s %s %s %s %s %s %c %d %d", hito[i].name, hito[i].id, hito[i].tel, hito[i].company,
                hito[i].car_num, hito[i].guarantee_name, hito[i].guarantee_tel, hito[i].health_code, hito[i].is_area,
                hito[i].is_symptom);
        fprintf(fp, " %d-%d-%d %d:%d:%d", hito[i].in_time_app.year, hito[i].in_time_app.mon,
                hito[i].in_time_app.day, hito[i].in_time_app.hour, hito[i].in_time_app.min, hito[i].in_time_app.sec);
        fprintf(fp, " %d-%d-%d %d:%d:%d", hito[i].out_time_app.year, hito[i].out_time_app.mon,
                hito[i].out_time_app.day, hito[i].out_time_app.hour, hito[i].out_time_app.min,
                hito[i].out_time_app.sec);
        fprintf(fp, " %d-%d-%d %d:%d:%d", hito[i].in_time_act.year, hito[i].in_time_act.mon,
                hito[i].in_time_act.day, hito[i].in_time_act.hour, hito[i].in_time_act.min, hito[i].in_time_act.sec);
        fprintf(fp, " %d-%d-%d %d:%d:%d", hito[i].out_time_act.year, hito[i].out_time_act.mon,
                hito[i].out_time_act.day, hito[i].out_time_act.hour, hito[i].out_time_act.min,
                hito[i].out_time_act.sec);
        fprintf(fp, " %s\n", hito[i].particular);
    }
    fclose(fp);
    printf("保存完成");
    Hide();        //隐藏光标
    char ch = _getch();
}

// 不是系统模块函数
void Hide() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cor_info = {1, 0};
    SetConsoleCursorInfo(hOut, &cor_info);
}

void SetPosition(int x, int y) {
    HANDLE hOut;    // typedef void *HANDLE;
    COORD pos;      // struct _COORD {SHORT X; SHORT Y;};

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hOut, pos);
}

void InitHitoArray(int length) {
    // 处理标记 完成 or 未完成 不实现这个功能就是单纯的空函数

}

int TxtLine(char *fname) {
    FILE *fp;
    int count = 0;
    if ((fp = fopen(fname, "r"))) {
        while (!feof(fp)) {
            if ('\n' == fgetc(fp)) count++;
        }
        fclose(fp);
    }
    return count;
}
