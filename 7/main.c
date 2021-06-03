// utf-8 编码
#include "snake.h"

//全局变量定义
Snake snake;    //定义蛇结构体变量
Food food, food_sp;        //定义食物结构体变量
Barrier barrier[5];
char now_Dir = RIGHT;    //当前蛇头方向
char direction = RIGHT; //预期蛇头方向
int mode = 2;

int main() {
    srand((unsigned int) time(0));             //生成随机数种子
    int end = 1, result;
    while (end) {
        result = Menu();             //显示主菜单，并根据用户选择菜单选项决定游戏的执行
        switch (result) {
            case 1:                     //选择1表示，开始贪吃蛇游戏
                ChooseMode();
                if (mode == 1 || mode == 2) {
                    InitMap();              //初始化地图、蛇和食物
                    while (MoveSnake());    //如果返回0，则蛇停止移动；返回1，继续移动
                } else if (mode == 3) {
                    InitMapBarrierAru();
                    while (MoveSnakeBarrierAru());
                    // with
                    // void PrintFoodBarrierAru();
                    // void PrintFoodSPBarrierAru();
                    // int IsCorrectBarrierAru();
                }
                StoreScore();
                break;
            case 2:                      //选择2表示，显示帮助信息
                Help();
                break;
            case 3:                      //选择3表示，显示关于信息
                About();
                break;
            case 4:
                ShowRank();
                break;
            case 0:                      //选择0表示，表示结束程序
                end = 0;
                break;
            case -1:
                break;
        }
    }
    return 0;
}

//主菜单实现
int Menu() {
    GotoXY(40, 12);                 //定位光标位置
    printf("S  N  A  K  E");
    GotoXY(43, 14);
    printf("1.GAME START");
    GotoXY(43, 16);
    printf("2.HELP");
    GotoXY(43, 18);
    printf("3.ABOUT");
    GotoXY(43, 20);
    printf("4.RANK");
    GotoXY(43, 22);
    printf("0.QUIT");
    Hide();                           //隐藏光标
    char ch;
    int result = 0;
    ch = _getch();          //接收用户输入的菜单选项
    switch (ch) {           //根据选项设置返回结果值
        case '1':
            result = 1;
            break;
        case '2':
            result = 2;
            break;
        case '3':
            result = 3;
            break;
        case '4':
            result = 4;
            break;
        case '0':
            result = 0;
            break;
        default:
            result = -1;
            break;
    }
    system("cls");                //调用系统命令cls完成清屏操作
    return result;
}

//光标定位函数，将光标定位到(x,y)坐标位置
void GotoXY(int x, int y) {
    HANDLE hout;
    COORD cor;
    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    cor.X = x;
    cor.Y = y;
    SetConsoleCursorPosition(hout, cor);
}

//隐藏光标
void Hide() {
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cor_info = {1, 0};
    SetConsoleCursorInfo(hout, &cor_info);
}


//关于菜单实现
void About() {
    GotoXY(30, 12);
    printf("PROGRAM PRACTICE IN HDU");
    GotoXY(30, 14);
    printf("SNAKE GAME");
    GotoXY(30, 16);
    printf("GITHUB : OCTAY");
    GotoXY(45, 18);
    printf("PRESS ANY KEY TO RETURN");
    Hide();        //隐藏光标
    char ch = _getch();
    system("cls");
}

//帮助菜单实现
void Help() {
    GotoXY(40, 12);
    printf("W UP   S DOWN   A LEFT   D RIGHT");
    GotoXY(40, 14);
    printf("PAST A COPYCAT OF ORIGINAL");
    GotoXY(40, 16);
    printf("PRESENT WITH SUPER FOOD");
    GotoXY(40, 18);
    printf("FUTURE WITH SUPER FOOD AND BARRIERS");
    GotoXY(40, 20);
    printf("GAME ENDS WHEN SNAKE HITS ITSELF OR WALL OR BARRIERS");
    GotoXY(40, 22);
    printf("3 MODES PAST PRESENT FUTURE");
    GotoXY(45, 24);
    printf("PRESS ANY KEY TO RETURN");
    Hide();        //隐藏光标
    char ch = _getch();
    system("cls");
}

//初始化地图函数
void InitMap() {
    Hide();                    //隐藏光标
    //设置蛇头位置在地图中心
    snake.snakeNode[0].x = MAP_WIDTH / 2 - 1;
    snake.snakeNode[0].y = MAP_HEIGHT / 2 - 1;
    GotoXY(snake.snakeNode[0].x, snake.snakeNode[0].y);      //将光标移动到蛇头位置
    printf("@");                //打印蛇头
    snake.length = 3;        //设置蛇长初始值为3节
    if (mode == 1) snake.speed = 250;        //设置蛇初始移动速度
    else if (mode == 2)snake.speed = 200;
    else if (mode == 3) snake.speed = 150;
    now_Dir = RIGHT;            //当前蛇头方向
    //显示蛇身
    for (int i = 1; i < snake.length; i++) {
        //设置蛇身的纵坐标位置和蛇头位置相同
        snake.snakeNode[i].y = snake.snakeNode[i - 1].y;
        //设置蛇身的横坐标位置，蛇身在蛇头的左边,所以横坐标依次减1
        snake.snakeNode[i].x = snake.snakeNode[i - 1].x - 1;
        GotoXY(snake.snakeNode[i].x, snake.snakeNode[i].y);    //移动光标到蛇身位置
        printf("o");        //打印蛇身
    }
    //生成地图上下边界
    for (int i = 0; i < MAP_WIDTH; i++) {
        GotoXY(i, 0);
        printf("-");
        GotoXY(i, MAP_HEIGHT - 1);
        printf("-");
    }
    //生成地图左右边界
    for (int i = 1; i < MAP_HEIGHT - 1; i++) {
        GotoXY(0, i);
        printf("|");
        GotoXY(MAP_WIDTH - 1, i);
        printf("|");
    }
    //生成食物
    PrintFood();
    if (mode == 2) PrintFoodSP();
    //得分说明
    GotoXY(50, 5);
    printf("SCORE 0");
}

void InitMapBarrierAru() {
    Hide();                    //隐藏光标
    //设置蛇头位置在地图中心
    snake.snakeNode[0].x = MAP_WIDTH / 2 - 1;
    snake.snakeNode[0].y = MAP_HEIGHT / 2 - 1;
    GotoXY(snake.snakeNode[0].x, snake.snakeNode[0].y);      //将光标移动到蛇头位置
    printf("@");                //打印蛇头
    snake.length = 3;        //设置蛇长初始值为3节
    if (mode == 1) snake.speed = 250;        //设置蛇初始移动速度
    else if (mode == 2)snake.speed = 200;
    else if (mode == 3) snake.speed = 150;
    now_Dir = RIGHT;            //当前蛇头方向
    //显示蛇身
    for (int i = 1; i < snake.length; i++) {
        //设置蛇身的纵坐标位置和蛇头位置相同
        snake.snakeNode[i].y = snake.snakeNode[i - 1].y;
        //设置蛇身的横坐标位置，蛇身在蛇头的左边,所以横坐标依次减1
        snake.snakeNode[i].x = snake.snakeNode[i - 1].x - 1;
        GotoXY(snake.snakeNode[i].x, snake.snakeNode[i].y);    //移动光标到蛇身位置
        printf("o");        //打印蛇身
    }
    //生成地图上下边界
    for (int i = 0; i < MAP_WIDTH; i++) {
        GotoXY(i, 0);
        printf("-");
        GotoXY(i, MAP_HEIGHT - 1);
        printf("-");
    }
    //生成地图左右边界
    for (int i = 1; i < MAP_HEIGHT - 1; i++) {
        GotoXY(0, i);
        printf("|");
        GotoXY(MAP_WIDTH - 1, i);
        printf("|");
    }
    // barrier
    for (int i = 0;i < 5;i++)
    {
        int flag = 1;
        while (flag)
        {
            flag = 0;
            barrier[i].x = rand() % (MAP_WIDTH - 2) + 1;
            barrier[i].y = rand() % (MAP_HEIGHT - 2) + 1;
            for (int k = 0;k < snake.length - 1;k++)
            {
                if (snake.snakeNode[k].x == barrier[i].x && snake.snakeNode[k].y == barrier[i].y)
                {
                    flag = 1;
                    break;
                }
            }
            for (int j = 0;j < i;j++)
            {
                if (barrier[j].x == barrier[i].x && barrier[j].y == barrier[i].y)
                {
                    flag = 1;
                    break;
                }
            }
        }
        GotoXY(barrier[i].x, barrier[i].y);
        printf("#");
    }
    //生成食物
    PrintFoodBarrierAru();
    PrintFoodSPBarrierAru();
    //得分说明
    GotoXY(50, 5);
    printf("SCORE 0");
}

//生成食物函数
void PrintFood() {
    int flag = 1;
    while (flag) {
        flag = 0;
        //设置随机的食物坐标位置
        food.x = rand() % (MAP_WIDTH - 2) + 1;
        food.y = rand() % (MAP_HEIGHT - 2) + 1;
        //循环判断食物位置是否和蛇的位置重叠，如果重叠则需要重新设置食物位置
        if (food_sp.x == food.x && food_sp.y == food.y) {
            flag = 1;
            continue;
        }
        for (int k = 0; k <= snake.length - 1; k++) {
            if (snake.snakeNode[k].x == food.x && snake.snakeNode[k].y == food.y) {
                flag = 1;                //位置有重叠，需要继续循环
                break;
            }
        }
    }
    GotoXY(food.x, food.y);
    printf("$");
}

void PrintFoodSP() {
    int flag = 1;
    while (flag) {
        flag = 0;
        //设置随机的食物坐标位置
        food_sp.x = rand() % (MAP_WIDTH - 2) + 1;
        food_sp.y = rand() % (MAP_HEIGHT - 2) + 1;
        //循环判断食物位置是否和蛇的位置重叠，如果重叠则需要重新设置食物位置
        if (food_sp.x == food.x && food_sp.y == food.y) {
            flag = 1;
            continue;
        }
        for (int k = 0; k <= snake.length - 1; k++) {
            if (snake.snakeNode[k].x == food_sp.x && snake.snakeNode[k].y == food_sp.y) {
                flag = 1;                //位置有重叠，需要继续循环
                break;
            }
        }
    }
    GotoXY(food_sp.x, food_sp.y);
    printf("&");
}

void PrintFoodBarrierAru() {
    int flag = 1;
    while (flag) {
        flag = 0;
        //设置随机的食物坐标位置
        food.x = rand() % (MAP_WIDTH - 2) + 1;
        food.y = rand() % (MAP_HEIGHT - 2) + 1;
        //循环判断食物位置是否和蛇的位置重叠，如果重叠则需要重新设置食物位置
        if (food_sp.x == food.x && food_sp.y == food.y) {
            flag = 1;
            continue;
        }
        for (int i = 0; i < 5; i++) {
            if (barrier[i].x == food.x && barrier[i].y == food.y) {
                flag = 1;
                break;
            }
        }
        for (int k = 0; k <= snake.length - 1; k++) {
            if (snake.snakeNode[k].x == food.x && snake.snakeNode[k].y == food.y) {
                flag = 1;                //位置有重叠，需要继续循环
                break;
            }
        }
    }
    GotoXY(food.x, food.y);
    printf("$");
}

void PrintFoodSPBarrierAru() {
    int flag = 1;
    while (flag) {
        flag = 0;
        //设置随机的食物坐标位置
        food_sp.x = rand() % (MAP_WIDTH - 2) + 1;
        food_sp.y = rand() % (MAP_HEIGHT - 2) + 1;
        //循环判断食物位置是否和蛇的位置重叠，如果重叠则需要重新设置食物位置
        if (food_sp.x == food.x && food_sp.y == food.y) {
            flag = 1;
            continue;
        }
        for (int i = 0; i < 5; i++) {
            if (barrier[i].x == food_sp.x && barrier[i].y == food_sp.y) {
                flag = 1;
                break;
            }
        }
        for (int k = 0; k <= snake.length - 1; k++) {
            if (snake.snakeNode[k].x == food_sp.x && snake.snakeNode[k].y == food_sp.y) {
                flag = 1;                //位置有重叠，需要继续循环
                break;
            }
        }
    }
    GotoXY(food_sp.x, food_sp.y);
    printf("&");
}

//蛇移动函数实现,返回值为1表示继续移动，为0表示停止移动
int MoveSnake() {
    Snakenode temp;
    int flag = 0;
    temp = snake.snakeNode[snake.length - 1];            //记录蛇尾
    for (int i = snake.length - 1; i >= 1; i--)
        snake.snakeNode[i] = snake.snakeNode[i - 1];    //将所有蛇身向前移动一个位置
    GotoXY(snake.snakeNode[1].x, snake.snakeNode[1].y);
    printf("o");            //前进方向打印一节蛇身，其他蛇身不需要打印
    //响应键盘修改
    if (_kbhit()) {            //键盘输入返回1，非键盘输入返回0
        direction = _getch();
        switch (direction) {
            case UP:  //按下w键
                if (now_Dir != DOWN)        //如果蛇头向下，按向上移动的键w时不起作用
                    now_Dir = direction;
                break;
            case DOWN:  //按下s键
                if (now_Dir != UP)            //如果蛇头向上，按向下移动的键s时不起作用
                    now_Dir = direction;
                break;
            case LEFT:  //按下a键
                if (now_Dir != RIGHT)        //如果蛇头向右，按向左移动的键a时不起作用
                    now_Dir = direction;
                break;
            case RIGHT:  //按下d键
                if (now_Dir != LEFT)        //如果蛇头向左，按向右移动的键d时不起作用
                    now_Dir = direction;
                break;
        }
    }
    switch (now_Dir) {                    //根据现在的方向修改蛇头的位置
        case UP:
            snake.snakeNode[0].y--;
            break;        //向上移动
        case DOWN:
            snake.snakeNode[0].y++;
            break;        //向下移动
        case LEFT:
            snake.snakeNode[0].x--;
            break;        //向左移动
        case RIGHT:
            snake.snakeNode[0].x++;
            break;    //向右移动
    }
    //打印蛇头
    GotoXY(snake.snakeNode[0].x, snake.snakeNode[0].y);
    printf("@");
    //判断是否吃到食物，如果蛇头的位置和食物的位置相同表示吃到食物
    if (snake.snakeNode[0].x == food.x && snake.snakeNode[0].y == food.y) {
        snake.length++;        //吃到食物，蛇长加1
        flag = 1;                //flag为1表示吃到食物，为0表示没有吃到食物
        snake.snakeNode[snake.length - 1] = temp;    //吃到食物，蛇尾加一节
        PrintFood();                //吃到食物，则需要在地图上重新更新一个食物
        GotoXY(50, 5);
        printf("SCORE %d", snake.length - 3);    //打印得分，得分为蛇长减原始长度3
    } else if (mode == 2 && snake.snakeNode[0].x == food_sp.x && snake.snakeNode[0].y == food_sp.y) {
        snake.length++;        //吃到食物，蛇长加1
        flag = 1;                //flag为1表示吃到食物，为0表示没有吃到食物
        snake.snakeNode[snake.length - 1] = temp;    //吃到食物，蛇尾加一节
        snake.length++;
        if (snake.snakeNode[snake.length - 3].x == temp.x && snake.snakeNode[snake.length - 3].y - 1 == temp.y)
            snake.snakeNode[snake.length - 1].x = temp.x, snake.snakeNode[snake.length - 1].y = temp.y - 1;
        if (snake.snakeNode[snake.length - 3].x == temp.x && snake.snakeNode[snake.length - 3].y + 1 == temp.y)
            snake.snakeNode[snake.length - 1].x = temp.x, snake.snakeNode[snake.length - 1].y = temp.y + 1;
        if (snake.snakeNode[snake.length - 3].x - 1 == temp.x && snake.snakeNode[snake.length - 3].y == temp.y)
            snake.snakeNode[snake.length - 1].x = temp.x - 1, snake.snakeNode[snake.length - 1].y = temp.y;
        if (snake.snakeNode[snake.length - 3].x + 1 == temp.x && snake.snakeNode[snake.length - 3].y == temp.y)
            snake.snakeNode[snake.length - 1].x = temp.x + 1, snake.snakeNode[snake.length - 1].y = temp.y;
        if (!IsCorrect()) {
            system("cls");
            GotoXY(45, 14);
            printf("FINAL SCORE %d", snake.length - 3);
            GotoXY(45, 16);
            printf("GAME OVER");
            GotoXY(45, 18);
            printf("PRESS ANY KEY TO RETURN");
            char c = _getch();
            system("cls");
            return 0;
        }
        GotoXY(snake.snakeNode[snake.length - 1].x, snake.snakeNode[snake.length - 1].y);
        printf("o");
        PrintFoodSP();
        GotoXY(50, 5);
        printf("SCORE %d", snake.length - 3);    //打印得分，得分为蛇长减原始长度3
    }
    //输出蛇此时状态
    //没吃到食物时，在原来的蛇尾打印一个空格，去掉原来的蛇尾
    if (!flag) {
        GotoXY(temp.x, temp.y);
        printf(" ");
    }
    //判断是否死亡
    if (!IsCorrect()) {        //如果自撞或撞墙，则清楚屏幕，打印最终得分，游戏结束
        system("cls");
        GotoXY(45, 14);
        printf("FINAL SCORE %d", snake.length - 3);
        GotoXY(45, 16);
        printf("GAME OVER");
        GotoXY(45, 18);
        printf("PRESS ANY KEY TO RETURN");
        char c = _getch();
        system("cls");
        return 0;
    }
    //调整速度
    SpeedControl();
    Sleep(snake.speed);        //把进程挂起一段时间，用于控制蛇移动的速度
    return 1;
}

int MoveSnakeBarrierAru() {
    Snakenode temp;
    int flag = 0;
    temp = snake.snakeNode[snake.length - 1];            //记录蛇尾
    for (int i = snake.length - 1; i >= 1; i--)
        snake.snakeNode[i] = snake.snakeNode[i - 1];    //将所有蛇身向前移动一个位置
    GotoXY(snake.snakeNode[1].x, snake.snakeNode[1].y);
    printf("o");            //前进方向打印一节蛇身，其他蛇身不需要打印
    //响应键盘修改
    if (_kbhit()) {            //键盘输入返回1，非键盘输入返回0
        direction = _getch();
        switch (direction) {
            case UP:  //按下w键
                if (now_Dir != DOWN)        //如果蛇头向下，按向上移动的键w时不起作用
                    now_Dir = direction;
                break;
            case DOWN:  //按下s键
                if (now_Dir != UP)            //如果蛇头向上，按向下移动的键s时不起作用
                    now_Dir = direction;
                break;
            case LEFT:  //按下a键
                if (now_Dir != RIGHT)        //如果蛇头向右，按向左移动的键a时不起作用
                    now_Dir = direction;
                break;
            case RIGHT:  //按下d键
                if (now_Dir != LEFT)        //如果蛇头向左，按向右移动的键d时不起作用
                    now_Dir = direction;
                break;
        }
    }
    switch (now_Dir) {                    //根据现在的方向修改蛇头的位置
        case UP:
            snake.snakeNode[0].y--;
            break;        //向上移动
        case DOWN:
            snake.snakeNode[0].y++;
            break;        //向下移动
        case LEFT:
            snake.snakeNode[0].x--;
            break;        //向左移动
        case RIGHT:
            snake.snakeNode[0].x++;
            break;    //向右移动
    }
    //打印蛇头
    GotoXY(snake.snakeNode[0].x, snake.snakeNode[0].y);
    printf("@");
    //判断是否吃到食物，如果蛇头的位置和食物的位置相同表示吃到食物
    if (snake.snakeNode[0].x == food.x && snake.snakeNode[0].y == food.y) {
        snake.length++;        //吃到食物，蛇长加1
        flag = 1;                //flag为1表示吃到食物，为0表示没有吃到食物
        snake.snakeNode[snake.length - 1] = temp;    //吃到食物，蛇尾加一节
        PrintFoodBarrierAru();                //吃到食物，则需要在地图上重新更新一个食物
        GotoXY(50, 5);
        printf("SCORE %d", snake.length - 3);    //打印得分，得分为蛇长减原始长度3
    } else if (snake.snakeNode[0].x == food_sp.x && snake.snakeNode[0].y == food_sp.y) {
        snake.length++;        //吃到食物，蛇长加1
        flag = 1;                //flag为1表示吃到食物，为0表示没有吃到食物
        snake.snakeNode[snake.length - 1] = temp;    //吃到食物，蛇尾加一节
        snake.length++;
        if (snake.snakeNode[snake.length - 3].x == temp.x && snake.snakeNode[snake.length - 3].y - 1 == temp.y)
            snake.snakeNode[snake.length - 1].x = temp.x, snake.snakeNode[snake.length - 1].y = temp.y - 1;
        if (snake.snakeNode[snake.length - 3].x == temp.x && snake.snakeNode[snake.length - 3].y + 1 == temp.y)
            snake.snakeNode[snake.length - 1].x = temp.x, snake.snakeNode[snake.length - 1].y = temp.y + 1;
        if (snake.snakeNode[snake.length - 3].x - 1 == temp.x && snake.snakeNode[snake.length - 3].y == temp.y)
            snake.snakeNode[snake.length - 1].x = temp.x - 1, snake.snakeNode[snake.length - 1].y = temp.y;
        if (snake.snakeNode[snake.length - 3].x + 1 == temp.x && snake.snakeNode[snake.length - 3].y == temp.y)
            snake.snakeNode[snake.length - 1].x = temp.x + 1, snake.snakeNode[snake.length - 1].y = temp.y;
        if (!IsCorrectBarrierAru()) {
            system("cls");
            GotoXY(45, 14);
            printf("FINAL SCORE %d", snake.length - 3);
            GotoXY(45, 16);
            printf("GAME OVER");
            GotoXY(45, 18);
            printf("PRESS ANY KEY TO RETURN");
            char c = _getch();
            system("cls");
            return 0;
        }
        GotoXY(snake.snakeNode[snake.length - 1].x, snake.snakeNode[snake.length - 1].y);
        printf("o");
        PrintFoodSPBarrierAru();
        GotoXY(50, 5);
        printf("SCORE %d", snake.length - 3);    //打印得分，得分为蛇长减原始长度3
    }
    //输出蛇此时状态
    //没吃到食物时，在原来的蛇尾打印一个空格，去掉原来的蛇尾
    if (!flag) {
        GotoXY(temp.x, temp.y);
        printf(" ");
    }
    //判断是否死亡
    if (!IsCorrectBarrierAru()) {        //如果自撞或撞墙，则清楚屏幕，打印最终得分，游戏结束
        system("cls");
        GotoXY(45, 14);
        printf("FINAL SCORE %d", snake.length - 3);
        GotoXY(45, 16);
        printf("GAME OVER");
        GotoXY(45, 18);
        printf("PRESS ANY KEY TO RETURN");
        char c = _getch();
        system("cls");
        return 0;
    }
    //调整速度
    SpeedControl();
    Sleep(snake.speed);        //把进程挂起一段时间，用于控制蛇移动的速度
    return 1;
}

int IsCorrect() {
    if (snake.snakeNode[0].x == 0 || snake.snakeNode[0].y == 0 || snake.snakeNode[0].x == MAP_WIDTH - 1 ||
        snake.snakeNode[0].y == MAP_HEIGHT - 1) //判断蛇头是否撞墙
        return 0;
    for (int i = 1; i < snake.length; i++) {   //判断蛇头是否和蛇身重叠，重叠表示自撞
        if (snake.snakeNode[0].x == snake.snakeNode[i].x && snake.snakeNode[0].y == snake.snakeNode[i].y)
            return 0;
    }
    return 1;
}

int IsCorrectBarrierAru() {
    if (snake.snakeNode[0].x == 0 || snake.snakeNode[0].y == 0 || snake.snakeNode[0].x == MAP_WIDTH - 1 ||
        snake.snakeNode[0].y == MAP_HEIGHT - 1) //判断蛇头是否撞墙
        return 0;
    for (int i = 1; i < snake.length; i++) {   //判断蛇头是否和蛇身重叠，重叠表示自撞
        if (snake.snakeNode[0].x == snake.snakeNode[i].x && snake.snakeNode[0].y == snake.snakeNode[i].y)
            return 0;
    }
    for (int i = 0;i < 5;i++)
    {
        if (barrier[i].x == snake.snakeNode[0].x && barrier[i].y == snake.snakeNode[0].y)
            return 0;
    }
    return 1;
}

//速度调整函数
void SpeedControl() {
    if (mode == 1)
        switch (snake.length) {        //根据蛇长调整蛇的移动速度
            case 8:
                snake.speed = 230;
                break;
            case 16:
                snake.speed = 210;
                break;
            case 24:
                snake.speed = 190;
                break;
            case 32:
                snake.speed = 170;
                break;
            case 40:
                snake.speed = 150;
                break;
            default:
                break;
        }
    else if (mode == 2)
        switch (snake.length) {        //根据蛇长调整蛇的移动速度
            case 8:
                snake.speed = 180;
                break;
            case 16:
                snake.speed = 160;
                break;
            case 24:
                snake.speed = 140;
                break;
            case 32:
                snake.speed = 120;
                break;
            case 40:
                snake.speed = 100;
                break;
            default:
                break;
        }
    else if (mode == 3)
        switch (snake.length) {        //根据蛇长调整蛇的移动速度
            case 8:
                snake.speed = 130;
                break;
            case 16:
                snake.speed = 110;
                break;
            case 24:
                snake.speed = 90;
                break;
            default:
                break;
        }
}

void StoreScore() {
    FILE *fp;
    fp = fopen("score.txt", "a");
    time_t cur_time;
    time(&cur_time);
    fprintf(fp, "%d  %d  %s", snake.length - 3, mode, ctime(&cur_time));
    fclose(fp);
}

void ChooseMode() {
    GotoXY(45, 12);
    printf("1.PAST");
    GotoXY(45, 14);
    printf("2.PRESENT (DEFAULT)");
    GotoXY(45, 16);
    printf("3.FUTURE");
    Hide();        //隐藏光标
    char ch = _getch();
    switch (ch) {
        case '1':
            mode = 1;
            break;
        case '3':
            mode = 3;
            break;
        default:
            mode = 2;
            break;
    }
    system("cls");
}

void ShowRank() {
    GotoXY(35, 12);
    printf("RANK SCORE MODE TIME");

    struct {
        int score;
        int mode;
        char time[25];
    } rank_score[5];
    int temp_score;
    int temp_mode;
    char temp_time[40];
    char temp_time2[40];
    char temp_time3[40];
    char temp_time4[40];
    char temp_time5[40];
    char *str_space = " ";
    FILE *fp1;
    char *fname = "score.txt";
    int num_line;

    for (int i = 0; i < 5; ++i) {
        rank_score[i].mode = 0;
        rank_score[i].score = 0;
    }

    if (!(fp1 = fopen(fname, "r"))) {
        GotoXY(35, 12);
        printf("%s LOAD ERROR OR NO RANK", fname);
        GotoXY(45, 14);
        printf("PRESS ANY KEY TO RETURN");
    } else {
        num_line = TxtLine(fname);

        for (int current_line = 1; current_line <= num_line; current_line++) {
            fscanf(fp1, "%d%d%s%s%s%s%s", &temp_score, &temp_mode, temp_time, temp_time2, temp_time3, temp_time4,
                   temp_time5);

            strcat(temp_time, str_space);
            strcat(temp_time, temp_time2);
            strcat(temp_time, str_space);
            strcat(temp_time, temp_time3);
            strcat(temp_time, str_space);
            strcat(temp_time, temp_time4);
            strcat(temp_time, str_space);
            strcat(temp_time, temp_time5);

            // EOFを書き込み不可能
            //"%d  %d  %s", snake.length - 3, mode, ctime(&cur_time)
            if (temp_score >= rank_score[0].score) {
                for (int i = 4; i >= 1; --i) {
                    rank_score[i].score = rank_score[i - 1].score;
                    rank_score[i].mode = rank_score[i - 1].mode;
                    strcpy(rank_score[i].time, rank_score[i - 1].time);
                }
                rank_score[0].score = temp_score;
                rank_score[0].mode = temp_mode;
                strcpy(rank_score[0].time, temp_time);
            } else if (temp_score >= rank_score[1].score) {
                for (int i = 4; i >= 2; --i) {
                    rank_score[i].score = rank_score[i - 1].score;
                    rank_score[i].mode = rank_score[i - 1].mode;
                    strcpy(rank_score[i].time, rank_score[i - 1].time);
                }
                rank_score[1].score = temp_score;
                rank_score[1].mode = temp_mode;
                strcpy(rank_score[1].time, temp_time);
            } else if (temp_score >= rank_score[2].score) {
                for (int i = 4; i >= 3; --i) {
                    rank_score[i].score = rank_score[i - 1].score;
                    rank_score[i].mode = rank_score[i - 1].mode;
                    strcpy(rank_score[i].time, rank_score[i - 1].time);
                }
                rank_score[2].score = temp_score;
                rank_score[2].mode = temp_mode;
                strcpy(rank_score[2].time, temp_time);
            } else if (temp_score >= rank_score[3].score) {
                rank_score[4].score = rank_score[3].score;
                rank_score[4].mode = rank_score[3].mode;
                strcpy(rank_score[4].time, rank_score[3].time);
                rank_score[3].score = temp_score;
                rank_score[3].mode = temp_mode;
                strcpy(rank_score[3].time, temp_time);
            } else if (temp_score >= rank_score[4].score) {
                rank_score[4].score = temp_score;
                rank_score[4].mode = temp_mode;
                strcpy(rank_score[4].time, temp_time);
            } else continue;
        }
        fclose(fp1);

        GotoXY(20, 14);
        if (rank_score[0].mode == 0) printf("1. BLANK");
        else
            printf("1. %d  %d  %s", rank_score[0].score, rank_score[0].mode, rank_score[0].time);

        GotoXY(20, 16);
        if (rank_score[1].mode == 0) printf("2. BLANK");
        else
            printf("2. %d  %d  %s", rank_score[1].score, rank_score[1].mode, rank_score[1].time);

        GotoXY(20, 18);
        if (rank_score[2].mode == 0) printf("3. BLANK");
        else
            printf("3. %d  %d  %s", rank_score[2].score, rank_score[2].mode, rank_score[2].time);

        GotoXY(20, 20);
        if (rank_score[3].mode == 0) printf("4. BLANK");
        else
            printf("4. %d  %d  %s", rank_score[3].score, rank_score[3].mode, rank_score[3].time);

        GotoXY(20, 22);
        if (rank_score[4].mode == 0) printf("5. BLANK");
        else
            printf("5. %d  %d  %s", rank_score[4].score, rank_score[4].mode, rank_score[4].time);

        GotoXY(45, 24);
        printf("PRESS ANY KEY TO RETURN");
    }
    Hide();        //隐藏光标
    char ch = _getch();
    system("cls");
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
