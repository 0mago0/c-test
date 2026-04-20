//圖案輸出 47必背
#include <stdio.h>          // 基本輸入輸出
int main() {
    int N, M;              // 宣告 N (圖案), M (高度)
    if (scanf("%d%d", &N, &M) != 2) { // 若輸入不是兩個整數
        printf("error");   // 印 error
        return 0;          // 結束
    }
    if (N < 1 || N > 2 || M < 2 || M > 9) { // 檢查範圍
        printf("error");   // 不合法
        return 0;
    }
    if (N == 1) {          // ===== 圖案1 =====
        for (int i = 1; i <= M; i++) {   // 控制行數
            for (int j = 1; j <= M - i; j++) // 左邊 #
                printf("#");

            if (i == 1) {  // 第1行
                printf("*");
            } else {
                char ch = 'A' + (i - 2) % 3; // A B C 循環
                for (int j = 1; j <= i; j++) { // 中間 *字母*
                    printf("*");
                    if (j != i) printf("%c", ch); // 最後一個*不加字母
                }
            }
            for (int j = 1; j <= M - i; j++) // 右邊 #
                printf("#");

            printf("\n"); // 換行
        }
    }
    else {                // ===== 圖案2 =====
        for (int i = 1; i <= M; i++) {   // 控制行數
            for (int j = i; j >= 1; j--) // 左邊 i→1
                printf("%d", j);
            for (int j = 1; j <= (M - i + 1) * 2; j++) // 中間 *
                printf("*");
            for (int j = 1; j <= i; j++) // 右邊 1→i
                printf("%d", j);

            printf("\n"); // 換行
        }
    }

    return 0;             // 結束
}