/*
 * based on gbk 
 * program practice final assignment in hdu
 * management system for in and out
 * authors' github : @hphuimen @octay @yeshuimuhua
 * ver0.1
 */

#include "ms4io.h"

struct hito_info hito[HITO_NUM];    // ���е����ݶ������� ���� ɾ�� ���� ���� ...
int count_record = 0;       // ��¼����

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
                system("cls");
                SortPrintTime();
                break;
            case 4:
                system("cls");
                SortPrintOrder();
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
                system("cls");
                SearchCarNum();
                break;
            case 9:
                system("cls");
                SearchDay();
                break;
            case 10:
                system("cls");
                SearchPeriod();
                break;
            case 11:
                system("cls");
                StoreRecord();
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
    printf("������Ա�������\n");

    for (int i = 0; i < 2; i++) {   // '-' * 55
        SetPosition(POS_X1, ++pos_y);
        for (int j = 0; j < 55; j++) {
            printf("-");
        }   // for ... j
    }       // for ... i
    // dept
    /*
     1. ��Ϣ¼��
         1.1 �ӿ���̨¼��
         1.2 ���ļ�¼��
     2. ��Ϣɾ��
     3. ʱ��˳������
         3.1 ѡ��ʱ�䷶Χ
         3.2 focus on ������
         3.3 focus on ���޾�������
         3.4 focus on ����֢״
         3.5 ������
     4. ¼��˳������
         4.1 focus on ������
         4.2 focus on ���޾�������
         4.3 focus on ����֢״
         4.4 ������
     5. �����ֲ���
         5.1 ��׼����
         5.2 ģ������
     6. ���ֻ��Ų���
         6.1 ��׼����
         6.2 ģ������
     7. �����֤�Ų���
         7.1 ��׼����
         7.2 ģ������
     8. �����ƺŲ���
         8.1 ��׼����
     */
    /*
     2�ڹ���
     9. �����ڲ���
     10. ��ʱ��β���
     11. ��Ϣ����
     */
    SetPosition(POS_X1, ++pos_y);
    printf("1. ��Ϣ¼��");
    SetPosition(POS_X4, pos_y);
    printf("2. ��Ϣɾ��");
    SetPosition(POS_X1, pos_y += 2);
    printf("3. ʱ��˳������");
    SetPosition(POS_X4, pos_y);
    printf("4. ¼��˳������");
    SetPosition(POS_X1, pos_y += 2);
    printf("5. �����ֲ���");
    SetPosition(POS_X4, pos_y);
    printf("6. ���ֻ��Ų���");
    SetPosition(POS_X1, pos_y += 2);
    printf("7. �����֤�Ų���");
    SetPosition(POS_X4, pos_y);
    printf("8. �����ƺŲ���");
    SetPosition(POS_X1, pos_y += 2);
    printf("9. �����ڲ���");
    SetPosition(POS_X4, pos_y);
    printf("10. ��ʱ��β���");
    SetPosition(POS_X1, pos_y += 2);
    printf("11. ��Ϣ����");
    SetPosition(POS_X1, pos_y += 2);
    printf("0. �˳�");
    for (int i = 0; i < 2; i++) {   // '-' * 55
        SetPosition(POS_X1, ++pos_y);
        for (int j = 0; j < 55; j++) {
            printf("-");
        }   // for ... j
    }       // for ... i
    SetPosition(POS_X1, ++pos_y);
    printf("��ѡ�� [  ]\b\b\b");
    scanf("%d", &dept_ch);
    return dept_ch;
}

void AppendRecord() {
    int pos_y = 6;
    struct hito_info temp_hito;
    int how_to_input_ch;
    SetPosition(POS_X2, pos_y);
    printf("1. �ӿ���̨¼�� 2. ���ļ�¼�� [  ]\b\b\b");
    scanf("%d", &how_to_input_ch);
    if (how_to_input_ch == 1) {         // �ӿ���̨¼��
        SetPosition(POS_X2, pos_y += 2);
        printf("���� ����");
        scanf("%s", temp_hito.name);

        SetPosition(POS_X2, pos_y += 2);
        printf("���� ���֤��");
        scanf("%s", temp_hito.id);
        if (strlen(temp_hito.id) != 18) return;     // judge id
        for (int i = 0; i < 17; ++i) if (!isdigit(temp_hito.id[i])) return;
        if (isdigit(temp_hito.id[17] == 0 || temp_hito.id[17] == 'x' || temp_hito.id[17] == 'X')) return;
        temp_hito.sex = (temp_hito.id[16] - '0' % 2 == 0) ? 2 : 1;  // judge sex from id

        SetPosition(POS_X2, pos_y += 2);
        printf("���� �ֻ�����");
        scanf("%s", temp_hito.tel);
        for (int i = 0; temp_hito.tel[i] != '\0'; ++i) if (!isdigit(temp_hito.tel[i])) return;  // judge tel

        SetPosition(POS_X2, pos_y += 2);
        printf("���� ��˾");
        scanf("%s", temp_hito.company);

        SetPosition(POS_X2, pos_y += 2);
        printf("���� ���ƺ�");
        scanf("%s", temp_hito.car_num);

        SetPosition(POS_X2, pos_y += 2);
        printf("���� ����������");
        scanf("%s", temp_hito.guarantee_name);

        SetPosition(POS_X2, pos_y += 2);
        printf("���� �����˵绰����");
        scanf("%s", temp_hito.guarantee_tel);
        for (int i = 0; temp_hito.guarantee_tel[i] != '\0'; ++i) if (!isdigit(temp_hito.guarantee_tel[i])) return;

        SetPosition(POS_X2, pos_y += 2);
        char str_to_get_char[10];
        printf("���� ��������ɫ g.�� y.�� r.��");
        scanf("%s", str_to_get_char);
        temp_hito.health_code = str_to_get_char[0];
        if (temp_hito.health_code != 'g' && temp_hito.health_code != 'y' && temp_hito.health_code != 'r') return;

        int temp_input_num;
        SetPosition(POS_X2, pos_y += 2);
        printf("���� �Ƿ񾭹����� 0. �� 1. ��");
        scanf("%d", &temp_input_num);
        if (temp_input_num) temp_hito.is_area = 1;
        else temp_hito.is_area = 0;

        SetPosition(POS_X2, pos_y += 2);
        printf("���� �Ƿ���֢״ 0. �� 1. ��");
        scanf("%d", &temp_input_num);
        if (temp_input_num) temp_hito.is_symptom = 1;
        else temp_hito.is_symptom = 0;

        // format of time ��-��-�� ʱ:��:��
        SetPosition(POS_X2, pos_y += 2);
        printf("���� ������Уʱ�� �����Уʱ�� ʵ����Уʱ�� ʵ�ʳ�Уʱ�� format of time ��-��-�� ʱ:��:��");
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
        printf("���� ��������");
        gets(temp_hito.particular);

        hito[count_record] = temp_hito;
        count_record++;
        SetPosition(POS_X2, pos_y += 2);
        printf("¼�����");
    } else if (how_to_input_ch == 2) {    // ���ļ�¼��
        char file_name[20] = INPUT_FILE_NAME;
        FILE *fp;
        int num_line;

//        SetPosition(POS_X2, pos_y += 2);
//        printf("�����ļ���");
//        scanf("%s", file_name);

        SetPosition(POS_X2, pos_y += 2);
        if (!(fp = fopen(file_name, "r"))) {
            printf("���ļ�����");
            return;
        }

        num_line = TxtLine(file_name);
        for (int current_line = 1; current_line <= num_line; current_line++) {
            // ���� ���֤�� �ֻ����� ��˾ ���ƺ� ���������� �����˵绰���� ��������ɫ �Ƿ񾭹����� �Ƿ���֢״ ������Уʱ�� �����Уʱ�� ʵ����Уʱ�� ʵ�ʳ�Уʱ�� ��������
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
        printf("¼�����");
        Hide();        //���ع��
        char ch = _getch();
    }
}

void DeleteRecord() {
    int pos_y = 6;
    int y_n = 0;
    SetPosition(POS_X2, pos_y);
    printf("�Ƿ�ѡ��ɾ�����һ�δ�������ݣ� 0. �� 1. ��");
    scanf("%d", &y_n);
    if (y_n == 1 && count_record > 0) {
        count_record--;
        SetPosition(POS_X2, pos_y += 2);
        printf("ɾ�����");
        Hide();        //���ع��
        char ch = _getch();
    }
}

void SearchName() {
    int i;
    int k = 1;  // ���ҵ������� Ĭ��Ϊ 1 ��ӡʱ - 1 ��������  ���ߵ�ǰ�ı�� ֱ��ʹ�ü���
    int mode;
    printf("1.��׼����  2.ģ������\n");
    printf("��������Ҫ���ҵ�ģʽ��");
    scanf("%d", &mode);
    if (mode == 1) {
        char name2seek[NAME_LEN];
        printf("\n");
        printf("��������Ҫ���ҵ��˵�������");
        scanf("%s", name2seek);
        for (i = 0; i < count_record; i++) {
            if (strcmp(hito[i].name, name2seek) == 0)   //���������ң������Ӧ��¼�����������֤�š��绰���������ʱ���ʵ�ʳ���ʱ��
            {
                printf("%d. ", k);
                printf("������%s, ���֤�ţ�%s, �绰��%s\n", hito[i].name, hito[i].id, hito[i].tel);
                printf("������Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].in_time_app.year, hito[i].in_time_app.mon,
                       hito[i].in_time_app.day, hito[i].in_time_app.hour, hito[i].in_time_app.min,
                       hito[i].in_time_app.sec);
                printf("������Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].out_time_app.year, hito[i].out_time_app.mon,
                       hito[i].out_time_app.day, hito[i].out_time_app.hour, hito[i].out_time_app.min,
                       hito[i].out_time_app.sec);
                printf("ʵ����Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].in_time_act.year, hito[i].in_time_act.mon,
                       hito[i].in_time_act.day, hito[i].in_time_act.hour, hito[i].in_time_act.min,
                       hito[i].in_time_act.sec);
                printf("ʵ����Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].out_time_act.year, hito[i].out_time_act.mon,
                       hito[i].out_time_act.day, hito[i].out_time_act.hour, hito[i].out_time_act.min,
                       hito[i].out_time_act.sec);
                k++;
                printf("\n");
            }
        }
        if (k == 1) printf("δ�ҵ����������Ӧ�ļ�¼\n");
        else printf("һ���ҵ�%d����¼\n", k - 1);
    } else if (mode == 2) {
        char dimname2seek[NAME_LEN];
        printf("��������Ҫģ�����ҵ��˵�������");
        scanf("%s", dimname2seek);
        for (i = 0; i < count_record; i++) {
            if (strstr(hito[i].name, dimname2seek) != NULL) {
                printf("%d. ", k);
                printf("������%s, ���֤�ţ�%s, �绰��%s\n", hito[i].name, hito[i].id, hito[i].tel);
                printf("������Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].in_time_app.year, hito[i].in_time_app.mon,
                       hito[i].in_time_app.day, hito[i].in_time_app.hour, hito[i].in_time_app.min,
                       hito[i].in_time_app.sec);
                printf("������Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].out_time_app.year, hito[i].out_time_app.mon,
                       hito[i].out_time_app.day, hito[i].out_time_app.hour, hito[i].out_time_app.min,
                       hito[i].out_time_app.sec);
                printf("ʵ����Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].in_time_act.year, hito[i].in_time_act.mon,
                       hito[i].in_time_act.day, hito[i].in_time_act.hour, hito[i].in_time_act.min,
                       hito[i].in_time_act.sec);
                printf("ʵ����Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].out_time_act.year, hito[i].out_time_act.mon,
                       hito[i].out_time_act.day, hito[i].out_time_act.hour, hito[i].out_time_act.min,
                       hito[i].out_time_act.sec);
                k++;
                printf("\n");
            }
        }
        if (k == 1) printf("δ�ҵ����������Ӧ�ļ�¼\n");
        else printf("һ���ҵ�%d����¼\n", k - 1);
    } else printf("ģʽ�������\n");
    Hide();        //���ع��
    char ch = _getch();
}

void SearchTel() {
    int i;
    int k = 1;
    int mode;
    printf("1.��׼����  2.ģ������\n");
    printf("��������Ҫ���ҵ�ģʽ��");
    scanf("%d", &mode);
    if (mode == 1) {
        char tel2seek[12];      // 11 + 1
        printf("��������Ҫ���ҵ��˵ĵ绰��");
        scanf("%s", tel2seek);
        for (i = 0; i < count_record; i++) {
            if (strcmp(hito[i].tel, tel2seek) == 0) {
                printf("%d. ", k);
                printf("������%s, ���֤�ţ�%s, �绰��%s\n", hito[i].name, hito[i].id, hito[i].tel);
                printf("������Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].in_time_app.year, hito[i].in_time_app.mon,
                       hito[i].in_time_app.day, hito[i].in_time_app.hour, hito[i].in_time_app.min,
                       hito[i].in_time_app.sec);
                printf("������Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].out_time_app.year, hito[i].out_time_app.mon,
                       hito[i].out_time_app.day, hito[i].out_time_app.hour, hito[i].out_time_app.min,
                       hito[i].out_time_app.sec);
                printf("ʵ����Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].in_time_act.year, hito[i].in_time_act.mon,
                       hito[i].in_time_act.day, hito[i].in_time_act.hour, hito[i].in_time_act.min,
                       hito[i].in_time_act.sec);
                printf("ʵ����Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].out_time_act.year, hito[i].out_time_act.mon,
                       hito[i].out_time_act.day, hito[i].out_time_act.hour, hito[i].out_time_act.min,
                       hito[i].out_time_act.sec);
                k++;
                printf("\n");
            }
        }
        if (k == 1) printf("δ�ҵ�����绰��Ӧ�ļ�¼\n");
        else printf("һ���ҵ�%d����¼\n", k - 1);
    } else if (mode == 2) {
        char dimtel2seek[12];
        printf("��������Ҫģ�����ҵ��˵ĵ绰��");
        scanf("%s", dimtel2seek);
        for (i = 0; i < count_record; i++) {
            if (strstr(hito[i].tel, dimtel2seek) != NULL) {
                printf("%d. ", k);
                printf("������%s, ���֤�ţ�%s, �绰��%s\n", hito[i].name, hito[i].id, hito[i].tel);
                printf("������Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].in_time_app.year, hito[i].in_time_app.mon,
                       hito[i].in_time_app.day, hito[i].in_time_app.hour, hito[i].in_time_app.min,
                       hito[i].in_time_app.sec);
                printf("������Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].out_time_app.year, hito[i].out_time_app.mon,
                       hito[i].out_time_app.day, hito[i].out_time_app.hour, hito[i].out_time_app.min,
                       hito[i].out_time_app.sec);
                printf("ʵ����Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].in_time_act.year, hito[i].in_time_act.mon,
                       hito[i].in_time_act.day, hito[i].in_time_act.hour, hito[i].in_time_act.min,
                       hito[i].in_time_act.sec);
                printf("ʵ����Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].out_time_act.year, hito[i].out_time_act.mon,
                       hito[i].out_time_act.day, hito[i].out_time_act.hour, hito[i].out_time_act.min,
                       hito[i].out_time_act.sec);
                k++;
                printf("\n");
            }
        }
        if (k == 1) printf("δ�ҵ�����绰��Ӧ�ļ�¼\n");
        else printf("һ���ҵ�%d����¼\n", k - 1);
    } else printf("ģʽ�������\n");
    Hide();        //���ع��
    char ch = _getch();
}

void SearchID() {
    int i;
    int k = 1;
    int mode;
    printf("1.��׼����  2.ģ������\n");
    printf("��������Ҫ���ҵ�ģʽ��");
    scanf("%d", &mode);
    if (mode == 1) {
        char id2seek[19];       // 18 + 1
        printf("��������Ҫ���ҵ��˵����֤�ţ�");
        scanf("%s", id2seek);
        for (i = 0; i < count_record; i++) {
            if (strcmp(hito[i].id, id2seek) == 0) {
                printf("%d. ", k);
                printf("������%s, ���֤�ţ�%s, �绰��%s\n", hito[i].name, hito[i].id, hito[i].tel);
                printf("������Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].in_time_app.year, hito[i].in_time_app.mon,
                       hito[i].in_time_app.day, hito[i].in_time_app.hour, hito[i].in_time_app.min,
                       hito[i].in_time_app.sec);
                printf("������Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].out_time_app.year, hito[i].out_time_app.mon,
                       hito[i].out_time_app.day, hito[i].out_time_app.hour, hito[i].out_time_app.min,
                       hito[i].out_time_app.sec);
                printf("ʵ����Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].in_time_act.year, hito[i].in_time_act.mon,
                       hito[i].in_time_act.day, hito[i].in_time_act.hour, hito[i].in_time_act.min,
                       hito[i].in_time_act.sec);
                printf("ʵ����Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].out_time_act.year, hito[i].out_time_act.mon,
                       hito[i].out_time_act.day, hito[i].out_time_act.hour, hito[i].out_time_act.min,
                       hito[i].out_time_act.sec);
                k++;
                printf("\n");
            }
        }
        if (k == 1) printf("δ�ҵ�������֤�Ŷ�Ӧ�ļ�¼\n");
        else printf("һ���ҵ�%d����¼\n", k - 1);
    } else if (mode == 2) {
        char dimid2seek[19];
        printf("%d. ");
        scanf("%s", dimid2seek);
        for (i = 0; i < count_record; i++) {
            if (strstr(hito[i].id, dimid2seek) != NULL) {
                printf("%d. ", k);
                printf("������%s, ���֤�ţ�%s, �绰��%s\n", hito[i].name, hito[i].id, hito[i].tel);
                printf("������Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].in_time_app.year, hito[i].in_time_app.mon,
                       hito[i].in_time_app.day, hito[i].in_time_app.hour, hito[i].in_time_app.min,
                       hito[i].in_time_app.sec);
                printf("������Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].out_time_app.year, hito[i].out_time_app.mon,
                       hito[i].out_time_app.day, hito[i].out_time_app.hour, hito[i].out_time_app.min,
                       hito[i].out_time_app.sec);
                printf("ʵ����Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].in_time_act.year, hito[i].in_time_act.mon,
                       hito[i].in_time_act.day, hito[i].in_time_act.hour, hito[i].in_time_act.min,
                       hito[i].in_time_act.sec);
                printf("ʵ����Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].out_time_act.year, hito[i].out_time_act.mon,
                       hito[i].out_time_act.day, hito[i].out_time_act.hour, hito[i].out_time_act.min,
                       hito[i].out_time_act.sec);
                k++;
                printf("\n");
            }
        }
        if (k == 1) printf("δ�ҵ�������֤�Ŷ�Ӧ�ļ�¼\n");
        else printf("һ���ҵ�%d����¼\n", k - 1);
    } else printf("ģʽ�������\n");
    Hide();        //���ع��
    char ch = _getch();
}

void SearchCarNum() {
    int i;
    int k = 1;
    int mode;
    printf("1.��׼����  2.ģ������\n");
    printf("��������Ҫ���ҵ�ģʽ��");
    scanf("%d", &mode);
    if (mode == 1) {
        char car_num2seek[8];
        printf("��������Ҫ���ҵ��˵ĳ��ƺţ�");
        scanf("%s", car_num2seek);
        for (i = 0; i < count_record; i++) {
            if (strcmp(hito[i].car_num, car_num2seek) == 0) {
                printf("%d. ", k);
                printf("������%s, ���֤�ţ�%s, �绰��%s\n", hito[i].name, hito[i].id, hito[i].tel);
                printf("������Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].in_time_app.year, hito[i].in_time_app.mon,
                       hito[i].in_time_app.day, hito[i].in_time_app.hour, hito[i].in_time_app.min,
                       hito[i].in_time_app.sec);
                printf("������Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].out_time_app.year, hito[i].out_time_app.mon,
                       hito[i].out_time_app.day, hito[i].out_time_app.hour, hito[i].out_time_app.min,
                       hito[i].out_time_app.sec);
                printf("ʵ����Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].in_time_act.year, hito[i].in_time_act.mon,
                       hito[i].in_time_act.day, hito[i].in_time_act.hour, hito[i].in_time_act.min,
                       hito[i].in_time_act.sec);
                printf("ʵ����Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].out_time_act.year, hito[i].out_time_act.mon,
                       hito[i].out_time_act.day, hito[i].out_time_act.hour, hito[i].out_time_act.min,
                       hito[i].out_time_act.sec);
                k++;
                printf("\n");
            }
        }
        if (k == 1) printf("δ�ҵ�������ƺŶ�Ӧ�ļ�¼\n");
        else printf("һ���ҵ�%d����¼\n", k - 1);
    } else if (mode == 2) {
        char dimcar_num2seek[8];
        printf("��������Ҫģ�����ҵ��˵ĳ��ƺţ�");
        scanf("%s", dimcar_num2seek);
        for (i = 0; i < count_record; i++) {
            if (strstr(hito[i].car_num, dimcar_num2seek) != NULL) {
                printf("%d. ", k);
                printf("������%s, ���֤�ţ�%s, �绰��%s\n", hito[i].name, hito[i].id, hito[i].tel);
                printf("������Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].in_time_app.year, hito[i].in_time_app.mon,
                       hito[i].in_time_app.day, hito[i].in_time_app.hour, hito[i].in_time_app.min,
                       hito[i].in_time_app.sec);
                printf("������Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].out_time_app.year, hito[i].out_time_app.mon,
                       hito[i].out_time_app.day, hito[i].out_time_app.hour, hito[i].out_time_app.min,
                       hito[i].out_time_app.sec);
                printf("ʵ����Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].in_time_act.year, hito[i].in_time_act.mon,
                       hito[i].in_time_act.day, hito[i].in_time_act.hour, hito[i].in_time_act.min,
                       hito[i].in_time_act.sec);
                printf("ʵ����Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].out_time_act.year, hito[i].out_time_act.mon,
                       hito[i].out_time_act.day, hito[i].out_time_act.hour, hito[i].out_time_act.min,
                       hito[i].out_time_act.sec);
                k++;
                printf("\n");
            }
        }
        if (k == 1) printf("δ�ҵ�������ƺŶ�Ӧ�ļ�¼\n");
        else printf("һ���ҵ�%d����¼\n", k - 1);
    } else printf("ģʽ�������\n");
    Hide();        //���ع��
    char ch = _getch();
}

void SearchDay() {
    int i;
    int k = 1;
    int year2seek, mon2seek, day2seek;
    printf("��������Ҫ���ҵ������գ�\n");
    printf("��ݣ�");
    scanf("%d", &year2seek);
    printf("�·ݣ�");
    scanf("%d", &mon2seek);
    printf("���ڣ�");
    scanf("%d", &day2seek);
    for (i = 0; i < count_record; i++) {
        if (hito[i].in_time_act.year == year2seek && hito[i].in_time_act.mon == mon2seek &&
            hito[i].in_time_act.day == day2seek) {
            printf("%d. ", k);
            printf("������%s, ���֤�ţ�%s, �绰��%s\n", hito[i].name, hito[i].id, hito[i].tel);
            printf("������Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].in_time_app.year, hito[i].in_time_app.mon,
                   hito[i].in_time_app.day, hito[i].in_time_app.hour, hito[i].in_time_app.min, hito[i].in_time_app.sec);
            printf("������Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].out_time_app.year, hito[i].out_time_app.mon,
                   hito[i].out_time_app.day, hito[i].out_time_app.hour, hito[i].out_time_app.min,
                   hito[i].out_time_app.sec);
            printf("ʵ����Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].in_time_act.year, hito[i].in_time_act.mon,
                   hito[i].in_time_act.day, hito[i].in_time_act.hour, hito[i].in_time_act.min, hito[i].in_time_act.sec);
            printf("ʵ����Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].out_time_act.year, hito[i].out_time_act.mon,
                   hito[i].out_time_act.day, hito[i].out_time_act.hour, hito[i].out_time_act.min,
                   hito[i].out_time_act.sec);
            printf("����У\n");
            k++;
            printf("\n");
        }
        if (hito[i].out_time_act.year == year2seek && hito[i].out_time_act.mon == mon2seek &&
            hito[i].out_time_act.day == day2seek) {
            printf("%d. ", k);
            printf("������%s, ���֤�ţ�%s, �绰��%s\n", hito[i].name, hito[i].id, hito[i].tel);
            printf("������Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].in_time_app.year, hito[i].in_time_app.mon,
                   hito[i].in_time_app.day, hito[i].in_time_app.hour, hito[i].in_time_app.min, hito[i].in_time_app.sec);
            printf("������Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].out_time_app.year, hito[i].out_time_app.mon,
                   hito[i].out_time_app.day, hito[i].out_time_app.hour, hito[i].out_time_app.min,
                   hito[i].out_time_app.sec);
            printf("ʵ����Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].in_time_act.year, hito[i].in_time_act.mon,
                   hito[i].in_time_act.day, hito[i].in_time_act.hour, hito[i].in_time_act.min, hito[i].in_time_act.sec);
            printf("ʵ����Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].out_time_act.year, hito[i].out_time_act.mon,
                   hito[i].out_time_act.day, hito[i].out_time_act.hour, hito[i].out_time_act.min,
                   hito[i].out_time_act.sec);
            printf("����У\n");
            k++;
            printf("\n");
        }
    }
    if (k == 1) printf("δ�ҵ������ڶ�Ӧ�ļ�¼\n");
    else printf("һ���ҵ�%d����¼\n", k - 1);
    Hide();        //���ع��
    char ch = _getch();
}

void SearchPeriod() {
    int i;
    int k = 1;
    int mode;
    printf("1.��ȷ����  2.��ȷ��Сʱ  3.��ȷ����\n");
    printf("��������Ҫ���ҵ�ģʽ��");
    scanf("%d", &mode);
    if (mode == 1) {
        int start_year, start_mon, start_day, end_year, end_mon, end_day;
        printf("��������ʼʱ�䣺\n");
        printf("��ݣ�");
        scanf("%d", &start_year);
        printf("�·ݣ�");
        scanf("%d", &start_mon);
        printf("���ڣ�");
        scanf("%d", &start_day);
        printf("��������ֹʱ�䣺\n");
        printf("��ݣ�");
        scanf("%d", &end_year);
        printf("�·ݣ�");
        scanf("%d", &end_mon);
        printf("���ڣ�");
        scanf("%d", &end_day);
        int start_time = start_year * 10000 + start_mon * 100 + start_day;
        int end_time = end_year * 10000 + end_mon * 100 + end_day;
        for (i = 0; i < count_record; i++) {
            int in_time = hito[i].in_time_act.year * 10000 + hito[i].in_time_act.mon * 100 + hito[i].in_time_act.day;
            int out_time =
                    hito[i].out_time_act.year * 10000 + hito[i].out_time_act.mon * 100 + hito[i].out_time_act.day;
            if (in_time >= start_time && in_time <= end_time) {
                printf("%d. ", k);
                printf("������%s, ���֤�ţ�%s, �绰��%s\n", hito[i].name, hito[i].id, hito[i].tel);
                printf("������Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].in_time_app.year, hito[i].in_time_app.mon,
                       hito[i].in_time_app.day, hito[i].in_time_app.hour, hito[i].in_time_app.min,
                       hito[i].in_time_app.sec);
                printf("������Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].out_time_app.year, hito[i].out_time_app.mon,
                       hito[i].out_time_app.day, hito[i].out_time_app.hour, hito[i].out_time_app.min,
                       hito[i].out_time_app.sec);
                printf("ʵ����Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].in_time_act.year, hito[i].in_time_act.mon,
                       hito[i].in_time_act.day, hito[i].in_time_act.hour, hito[i].in_time_act.min,
                       hito[i].in_time_act.sec);
                printf("ʵ����Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].out_time_act.year, hito[i].out_time_act.mon,
                       hito[i].out_time_act.day, hito[i].out_time_act.hour, hito[i].out_time_act.min,
                       hito[i].out_time_act.sec);
                printf("����У\n");
                k++;
                printf("\n");
            }
            if (out_time >= start_time && out_time <= end_time) {
                printf("%d. ", k);
                printf("������%s, ���֤�ţ�%s, �绰��%s\n", hito[i].name, hito[i].id, hito[i].tel);
                printf("������Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].in_time_app.year, hito[i].in_time_app.mon,
                       hito[i].in_time_app.day, hito[i].in_time_app.hour, hito[i].in_time_app.min,
                       hito[i].in_time_app.sec);
                printf("������Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].out_time_app.year, hito[i].out_time_app.mon,
                       hito[i].out_time_app.day, hito[i].out_time_app.hour, hito[i].out_time_app.min,
                       hito[i].out_time_app.sec);
                printf("ʵ����Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].in_time_act.year, hito[i].in_time_act.mon,
                       hito[i].in_time_act.day, hito[i].in_time_act.hour, hito[i].in_time_act.min,
                       hito[i].in_time_act.sec);
                printf("ʵ����Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].out_time_act.year, hito[i].out_time_act.mon,
                       hito[i].out_time_act.day, hito[i].out_time_act.hour, hito[i].out_time_act.min,
                       hito[i].out_time_act.sec);
                printf("����У\n");
                k++;
                printf("\n");
            }
        }
        if (k == 1)printf("δ�ҵ���ʱ��ζ�Ӧ�ļ�¼\n");
        else printf("һ���ҵ�%d����¼\n", k - 1);
    } else if (mode == 2) {
        int year2seek, mon2seek, day2seek, start_hour, end_hour;
        printf("��������Ҫ���ҵ��ꡢ�¡��գ�\n");
        printf("��ݣ�");
        scanf("%d", &year2seek);
        printf("�·ݣ�");
        scanf("%d", &mon2seek);
        printf("���ڣ�");
        scanf("%d", &day2seek);
        printf("��������ʼʱ�䣺\n");
        printf("Сʱ��");
        scanf("%d", &start_hour);
        printf("��������ֹʱ�䣺\n");
        printf("Сʱ��");
        scanf("%d", &end_hour);
        for (i = 0; i < count_record; i++) {
            if (hito[i].in_time_act.year == year2seek && hito[i].in_time_act.mon == mon2seek &&
                hito[i].in_time_act.day == day2seek &&
                hito[i].in_time_act.hour >= start_hour && hito[i].in_time_act.hour <= end_hour) {
                printf("%d. ", k);
                printf("������%s, ���֤�ţ�%s, �绰��%s\n", hito[i].name, hito[i].id, hito[i].tel);
                printf("������Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].in_time_app.year, hito[i].in_time_app.mon,
                       hito[i].in_time_app.day, hito[i].in_time_app.hour, hito[i].in_time_app.min,
                       hito[i].in_time_app.sec);
                printf("������Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].out_time_app.year, hito[i].out_time_app.mon,
                       hito[i].out_time_app.day, hito[i].out_time_app.hour, hito[i].out_time_app.min,
                       hito[i].out_time_app.sec);
                printf("ʵ����Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].in_time_act.year, hito[i].in_time_act.mon,
                       hito[i].in_time_act.day, hito[i].in_time_act.hour, hito[i].in_time_act.min,
                       hito[i].in_time_act.sec);
                printf("ʵ����Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].out_time_act.year, hito[i].out_time_act.mon,
                       hito[i].out_time_act.day, hito[i].out_time_act.hour, hito[i].out_time_act.min,
                       hito[i].out_time_act.sec);
                printf("����У\n");
                k++;
                printf("\n");
            }
            if (hito[i].out_time_act.year == year2seek && hito[i].out_time_act.mon == mon2seek &&
                hito[i].out_time_act.day == day2seek &&
                hito[i].out_time_act.hour >= start_hour && hito[i].out_time_act.hour <= end_hour) {
                printf("%d. ", k);
                printf("������%s, ���֤�ţ�%s, �绰��%s\n", hito[i].name, hito[i].id, hito[i].tel);
                printf("������Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].in_time_app.year, hito[i].in_time_app.mon,
                       hito[i].in_time_app.day, hito[i].in_time_app.hour, hito[i].in_time_app.min,
                       hito[i].in_time_app.sec);
                printf("������Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].out_time_app.year, hito[i].out_time_app.mon,
                       hito[i].out_time_app.day, hito[i].out_time_app.hour, hito[i].out_time_app.min,
                       hito[i].out_time_app.sec);
                printf("ʵ����Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].in_time_act.year, hito[i].in_time_act.mon,
                       hito[i].in_time_act.day, hito[i].in_time_act.hour, hito[i].in_time_act.min,
                       hito[i].in_time_act.sec);
                printf("ʵ����Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].out_time_act.year, hito[i].out_time_act.mon,
                       hito[i].out_time_act.day, hito[i].out_time_act.hour, hito[i].out_time_act.min,
                       hito[i].out_time_act.sec);
                printf("����У\n");
                k++;
                printf("\n");
            }
        }
        if (k == 1)printf("δ�ҵ���ʱ��ζ�Ӧ�ļ�¼\n");
        else printf("һ���ҵ�%d����¼\n", k - 1);
    } else if (mode == 3) {
        int year2seek, mon2seek, day2seek, start_hour, end_hour, start_min, end_min;
        printf("��������Ҫ���ҵ��ꡢ�¡��գ�\n");
        printf("��ݣ�");
        scanf("%d", &year2seek);
        printf("�·ݣ�");
        scanf("%d", &mon2seek);
        printf("���ڣ�");
        scanf("%d", &day2seek);
        printf("��������ʼʱ�䣺\n");
        printf("Сʱ��");
        scanf("%d", &start_hour);
        printf("�֣�");
        scanf("%d", &start_min);
        printf("��������ֹʱ�䣺\n");
        printf("Сʱ��");
        scanf("%d", &end_hour);
        printf("�֣�");
        scanf("%d", &end_min);
        for (i = 0; i < count_record; i++) {
            if (hito[i].in_time_act.year == year2seek && hito[i].in_time_act.mon == mon2seek &&
                hito[i].in_time_act.day == day2seek &&
                hito[i].in_time_act.hour >= start_hour && hito[i].in_time_act.hour <= end_hour &&
                hito[i].in_time_act.min >= start_min && hito[i].in_time_act.min <= end_min) {
                printf("%d. ", k);
                printf("������%s, ���֤�ţ�%s, �绰��%s\n", hito[i].name, hito[i].id, hito[i].tel);
                printf("������Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].in_time_app.year, hito[i].in_time_app.mon,
                       hito[i].in_time_app.day, hito[i].in_time_app.hour, hito[i].in_time_app.min,
                       hito[i].in_time_app.sec);
                printf("������Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].out_time_app.year, hito[i].out_time_app.mon,
                       hito[i].out_time_app.day, hito[i].out_time_app.hour, hito[i].out_time_app.min,
                       hito[i].out_time_app.sec);
                printf("ʵ����Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].in_time_act.year, hito[i].in_time_act.mon,
                       hito[i].in_time_act.day, hito[i].in_time_act.hour, hito[i].in_time_act.min,
                       hito[i].in_time_act.sec);
                printf("ʵ����Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].out_time_act.year, hito[i].out_time_act.mon,
                       hito[i].out_time_act.day, hito[i].out_time_act.hour, hito[i].out_time_act.min,
                       hito[i].out_time_act.sec);
                printf("����У\n");
                k++;
                printf("\n");
            }
            if (hito[i].out_time_act.year == year2seek && hito[i].out_time_act.mon == mon2seek &&
                hito[i].out_time_act.day == day2seek &&
                hito[i].out_time_act.hour >= start_hour && hito[i].out_time_act.hour <= end_hour &&
                hito[i].out_time_act.min >= start_min && hito[i].out_time_act.min <= end_min) {
                printf("%d. ", k);
                printf("������%s, ���֤�ţ�%s, �绰��%s\n", hito[i].name, hito[i].id, hito[i].tel);
                printf("������Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].in_time_app.year, hito[i].in_time_app.mon,
                       hito[i].in_time_app.day, hito[i].in_time_app.hour, hito[i].in_time_app.min,
                       hito[i].in_time_app.sec);
                printf("������Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].out_time_app.year, hito[i].out_time_app.mon,
                       hito[i].out_time_app.day, hito[i].out_time_app.hour, hito[i].out_time_app.min,
                       hito[i].out_time_app.sec);
                printf("ʵ����Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].in_time_act.year, hito[i].in_time_act.mon,
                       hito[i].in_time_act.day, hito[i].in_time_act.hour, hito[i].in_time_act.min,
                       hito[i].in_time_act.sec);
                printf("ʵ����Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].out_time_act.year, hito[i].out_time_act.mon,
                       hito[i].out_time_act.day, hito[i].out_time_act.hour, hito[i].out_time_act.min,
                       hito[i].out_time_act.sec);
                printf("����У\n");
                k++;
                printf("\n");
            }
        }
        if (k == 1)printf("δ�ҵ���ʱ��ζ�Ӧ�ļ�¼\n");
        else printf("һ���ҵ�%d����¼\n", k - 1);
    } else printf("ģʽ�������\n");
    Hide();        //���ع��
    char ch = _getch();
}

void StoreRecord() {
    char file_name[20] = OUTPUT_FILE_NAME;
    FILE *fp;
    int num_line;
    int pos_y = 6;

//    SetPosition(POS_X2, pos_y);
//    printf("�����ļ���");
//    scanf("%s", file_name);

    SetPosition(POS_X2, pos_y += 2);
    if (!(fp = fopen(file_name, "w"))) {
        printf("���ļ�����");
        return;
    }
    for (int i = 0; i < count_record; ++i) {
        // ���� ���֤�� �ֻ����� ��˾ ���ƺ� ���������� �����˵绰���� ��������ɫ �Ƿ񾭹����� �Ƿ���֢״ ������Уʱ�� �����Уʱ�� ʵ����Уʱ�� ʵ�ʳ�Уʱ�� ��������
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
        fprintf(fp, " %s", hito[i].particular);
    }
    fclose(fp);
    printf("�������");
    Hide();        //���ع��
    char ch = _getch();
}

void SortPrintTime() {
    int mode;
    printf("��������Ҫ�� 1 ������Уʱ�� 2 ������Уʱ�� 3 ʵ����Уʱ�� 4 ʵ����Уʱ�� 1 ���� 2 ����\n");
    scanf("%d", &mode);
    switch (mode) {
        case 11:
        case 1:     // Ĭ�ϲ�ȫһЩ���������
            SortByTime(1, 1);
            break;
        case 12:
            SortByTime(1, 2);
            break;
        case 21:
        case 2:
            SortByTime(2, 1);
            break;
        case 22:
            SortByTime(2, 2);
            break;
        case 31:
        case 3:
        default:    // Ĭ�ϵ�����ʽ ʵ����Уʱ�� ����
            SortByTime(3, 1);
            break;
        case 32:
            SortByTime(3, 2);
            break;
        case 41:
        case 4:
            SortByTime(4, 1);
            break;
        case 42:
            SortByTime(4, 2);
            break;
    }
}

void SortByTime(int k, int m) {
    // k 4 different time moments m 1 ascend 2 descend
    int temp;
    int temp_sum;
    struct {
        int index;
        int sec_sum;
    } toy[HITO_NUM];
    for (int i = 0; i < 140; i++) {
        toy[i].index = i;
    }
    switch (k) {
        case 1:
            for (int i = 0; i < count_record; i++) {    //��ʱ�任��������������д�С�Ƚ���ʵ������
                toy[i].sec_sum = (hito[i].in_time_app.year - 2020) * 31622400 + hito[i].in_time_app.mon * 2678400 +
                                 hito[i].in_time_app.day * 86400 + hito[i].in_time_app.hour * 3600 +
                                 hito[i].in_time_app.min * 60 + hito[i].in_time_app.sec;
            }
            break;
        case 2:
            for (int i = 0; i < count_record; i++) {    //��ʱ�任��������������д�С�Ƚ���ʵ������
                toy[i].sec_sum = (hito[i].out_time_app.year - 2020) * 31622400 + hito[i].out_time_app.mon * 2678400 +
                                 hito[i].out_time_app.day * 86400 + hito[i].out_time_app.hour * 3600 +
                                 hito[i].out_time_app.min * 60 + hito[i].out_time_app.sec;
            }
            break;
        case 3:
        default:
            for (int i = 0; i < count_record; i++) {    //��ʱ�任��������������д�С�Ƚ���ʵ������
                toy[i].sec_sum = (hito[i].in_time_act.year - 2020) * 31622400 + hito[i].in_time_act.mon * 2678400 +
                                 hito[i].in_time_act.day * 86400 + hito[i].in_time_act.hour * 3600 +
                                 hito[i].in_time_act.min * 60 + hito[i].in_time_act.sec;
            }
            break;
        case 4:
            for (int i = 0; i < count_record; i++) {    //��ʱ�任��������������д�С�Ƚ���ʵ������
                toy[i].sec_sum = (hito[i].out_time_act.year - 2020) * 31622400 + hito[i].out_time_act.mon * 2678400 +
                                 hito[i].out_time_act.day * 86400 + hito[i].out_time_act.hour * 3600 +
                                 hito[i].out_time_act.min * 60 + hito[i].out_time_act.sec;
            }
            break;
    }

    if (m == 1)
        for (int i = 0; i < count_record; i++) {
            for (int j = 0; j < count_record - 1 - i; j++) {
                if (toy[j].sec_sum > toy[j + 1].sec_sum) {
                    temp_sum = toy[j].sec_sum;
                    toy[j].sec_sum = toy[j + 1].sec_sum;
                    toy[j + 1].sec_sum = temp_sum;
                    temp = toy[j].index;
                    toy[j].index = toy[j + 1].index;
                    toy[j + 1].index = temp;
                }
            }
        }
    else if (m == 2)
        for (int i = 0; i < count_record; i++) {
            for (int j = 0; j < count_record - 1 - i; j++) {
                if (toy[j].sec_sum < toy[j + 1].sec_sum) {
                    temp_sum = toy[j].sec_sum;
                    toy[j].sec_sum = toy[j + 1].sec_sum;
                    toy[j + 1].sec_sum = temp_sum;
                    temp = toy[j].index;
                    toy[j].index = toy[j + 1].index;
                    toy[j + 1].index = temp;
                }
            }
        }
    //��֤ԭ���鲻���˼· �ٶ���һ���յĽṹ�����飬���´��򻻽�ȥ��������֮���¼��˳�������л᷽�㲻�٣������֮���Ǳ��û�й�������
    for (int i = 0; i < count_record; i++) {
        printf("%d. ", i + 1);
        printf("������%s, ���֤�ţ�%s, �绰��%s\n", hito[toy[i].index].name, hito[toy[i].index].id, hito[toy[i].index].tel);
        printf("������Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[toy[i].index].in_time_app.year,
               hito[toy[i].index].in_time_app.mon,
               hito[toy[i].index].in_time_app.day, hito[toy[i].index].in_time_app.hour,
               hito[toy[i].index].in_time_app.min,
               hito[toy[i].index].in_time_app.sec);
        printf("������Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[toy[i].index].out_time_app.year,
               hito[toy[i].index].out_time_app.mon,
               hito[toy[i].index].out_time_app.day, hito[toy[i].index].out_time_app.hour,
               hito[toy[i].index].out_time_app.min,
               hito[toy[i].index].out_time_app.sec);
        printf("ʵ����Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[toy[i].index].in_time_act.year,
               hito[toy[i].index].in_time_act.mon,
               hito[toy[i].index].in_time_act.day, hito[toy[i].index].in_time_act.hour,
               hito[toy[i].index].in_time_act.min,
               hito[toy[i].index].in_time_act.sec);
        printf("ʵ����Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[toy[i].index].out_time_act.year,
               hito[toy[i].index].out_time_act.mon,
               hito[toy[i].index].out_time_act.day, hito[toy[i].index].out_time_act.hour,
               hito[toy[i].index].out_time_act.min,
               hito[toy[i].index].out_time_act.sec);
        printf("\n");
    }
    Hide();        //���ع��
    char ch = _getch();
}

void SortPrintOrder() {
    int mode;
    printf("��������Ҫ�� 1 ���� 2 ����\n");
    scanf("%d", &mode);
    if (mode == 1) {
        for (int i = 0; i < count_record; i++) {
            printf("%d. ", i + 1);
            printf("������%s, ���֤�ţ�%s, �绰��%s\n", hito[i].name, hito[i].id, hito[i].tel);
            printf("������Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].in_time_app.year, hito[i].in_time_app.mon,
                   hito[i].in_time_app.day, hito[i].in_time_app.hour, hito[i].in_time_app.min, hito[i].in_time_app.sec);
            printf("������Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].out_time_app.year, hito[i].out_time_app.mon,
                   hito[i].out_time_app.day, hito[i].out_time_app.hour, hito[i].out_time_app.min,
                   hito[i].out_time_app.sec);
            printf("ʵ����Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].in_time_act.year, hito[i].in_time_act.mon,
                   hito[i].in_time_act.day, hito[i].in_time_act.hour, hito[i].in_time_act.min, hito[i].in_time_act.sec);
            printf("ʵ����Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[i].out_time_act.year, hito[i].out_time_act.mon,
                   hito[i].out_time_act.day, hito[i].out_time_act.hour, hito[i].out_time_act.min,
                   hito[i].out_time_act.sec);
            printf("\n");
        }
    } else if (mode == 2) {
        for (int i = 0; i < count_record; i++) {
            printf("%d. ", i + 1);
            printf("������%s, ���֤�ţ�%s, �绰��%s\n", hito[count_record - i - 1].name, hito[count_record - i - 1].id,
                   hito[count_record - i - 1].tel);
            printf("������Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[count_record - i - 1].in_time_app.year,
                   hito[count_record - i - 1].in_time_app.mon, hito[count_record - i - 1].in_time_app.day,
                   hito[count_record - i - 1].in_time_app.hour, hito[count_record - i - 1].in_time_app.min,
                   hito[count_record - i - 1].in_time_app.sec);
            printf("������Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[count_record - i - 1].out_time_app.year,
                   hito[count_record - i - 1].out_time_app.mon, hito[count_record - i - 1].out_time_app.day,
                   hito[count_record - i - 1].out_time_app.hour, hito[count_record - i - 1].out_time_app.min,
                   hito[count_record - i - 1].out_time_app.sec);
            printf("ʵ����Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[count_record - i - 1].in_time_act.year,
                   hito[count_record - i - 1].in_time_act.mon, hito[count_record - i - 1].in_time_act.day,
                   hito[count_record - i - 1].in_time_act.hour, hito[count_record - i - 1].in_time_act.min,
                   hito[count_record - i - 1].in_time_act.sec);
            printf("ʵ����Уʱ�䣺%04d��%02d��%02d��%02dʱ%02d��%02d��\n", hito[count_record - i - 1].out_time_act.year,
                   hito[count_record - i - 1].out_time_act.mon, hito[count_record - i - 1].out_time_act.day,
                   hito[count_record - i - 1].out_time_act.hour, hito[count_record - i - 1].out_time_act.min,
                   hito[count_record - i - 1].out_time_act.sec);
            printf("\n");
        }
    }
    Hide();        //���ع��
    char ch = _getch();
}

// ����ϵͳģ�麯��
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
    // ������ ��� or δ��� ��ʵ��������ܾ��ǵ����Ŀպ���

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

