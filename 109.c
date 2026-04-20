#include <stdio.h>      // 輸入輸出
#include <stdlib.h>     // qsort
//df-expression解析 69必背
// 存座標
typedef struct {
    int x, y;          // x=列, y=行
} P;

char s[105];           // DF-expression
int idx = 0;           // 目前讀到字串位置

P ans[1000];           // 存黑色格子
int cnt = 0;           // 黑格數量

// 把一整塊黑色區域加入答案
void add(int r, int c, int sz) {
    for (int i = r; i < r + sz; i++)          // 每一列
        for (int j = c; j < c + sz; j++) {    // 每一行
            ans[cnt].x = i;                  // 記錄 x
            ans[cnt].y = j;                  // 記錄 y
            cnt++;                           // 數量++
        }
}

// 遞迴解析
void dfs(int r, int c, int sz) {
    char ch = s[idx++];          // 讀當前區塊類型

    if (ch == '0') return;       // 全白，直接結束

    if (ch == '1') {             // 全黑
        add(r, c, sz);           // 加入整塊座標
        return;
    }

    int h = sz / 2;              // 切成四塊

    dfs(r, c, h);                // 左上
    dfs(r, c + h, h);            // 右上
    dfs(r + h, c, h);            // 左下
    dfs(r + h, c + h, h);        // 右下
}

// 排序：先 x 再 y
int cmp(const void *a, const void *b) {
    P *p = (P *)a, *q = (P *)b;  // 轉型
    if (p->x != q->x) return p->x - q->x;  // 比 x
    return p->y - q->y;                   // 再比 y
}

int main() {
    int N;                          // 方陣大小

    scanf("%s%d", s, &N);           // 讀字串 + N

    dfs(0, 0, N);                   // 從整張圖開始

    if (cnt == 0) {                 // 沒黑格
        printf("all white\n");
        return 0;
    }

    qsort(ans, cnt, sizeof(P), cmp); // 排序

    for (int i = 0; i < cnt; i++)   // 輸出
        printf("%d,%d\n", ans[i].x, ans[i].y);

    return 0;
}