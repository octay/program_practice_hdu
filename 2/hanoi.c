#include<stdio.h>
void hanoi(int n, char x, char y, char z);

int count = 0;
int main(int argc, char const *argv[]) {
    int n;
    scanf("%d", &n);
    hanoi(n, 'A', 'B', 'C');
    system("pause");
    return 0;
}

// 信任:该如何做是好
// 将n个件中最大件以上的n-1个件移到缓冲位,再将最大件移到目标位.再将n-1个件移到目标位.
// void hanoi(int n, char x, char y, char z) 分别表示初始位 缓冲位 目标位
// 缓冲位理解成目标位与初始位之外的位也可以
void hanoi(int n, char x, char y, char z){
    if(n == 1) printf("%c -> %c   %d\n", x, z, ++count);
    else{
        hanoi(n - 1, x, z, y);
        printf("%c -> %c   %d\n", x, z, ++count);
        // ↑这一步也可以写成 hanoi(1, x, y, z);
        hanoi(n - 1, y, x, z);
    }
}
