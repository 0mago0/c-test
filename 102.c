//判斷字串是什麼 145有餘力的話
#include <stdio.h>      // printf、scanf、fgets
#include <string.h>     // strlen、strcpy、strncpy、strcspn
#include <ctype.h>      // isdigit、isalpha、isalnum
#include <stdlib.h>     // llabs

int isInt(char s[]) {                           // 判斷是否為整數
    int len = strlen(s), i = 0;                // len=長度，i=掃描位置
    if (len < 1 || len > 50) return 0;         // 長度不符直接錯
    if (s[0] == '-') i = 1;                    // 若開頭是負號，從下一格開始看
    if (i == len) return 0;                    // 只有 "-" 不算整數
    for (int j = i; j < len; j++)              // 檢查剩下每個字元
        if (!isdigit(s[j])) return 0;          // 只要不是數字就錯
    if (s[i] == '0' && len - i > 1) return 0;  // 不可有前導零，但 0、-0 可
    return 1;                                  // 符合整數規則
}

int isFloat(char s[]) {                        // 判斷是否為浮點數
    int len = strlen(s), i = 0;               // len=長度，i=起始位置
    int dot = 0, pos = -1;                    // dot=小數點數量，pos=小數點位置
    if (len < 3 || len > 50) return 0;        // 浮點數長度限制
    if (s[0] == '-') i = 1;                   // 若有負號，跳過
    if (i == len) return 0;                   // 避免只有 "-"
    for (int j = i; j < len; j++) {           // 掃描整串
        if (s[j] == '.') {                    // 如果是小數點
            dot++;                            // 小數點數量加一
            pos = j;                          // 記住位置
        } else if (!isdigit(s[j])) return 0;  // 不是點也不是數字就錯
    }
    if (dot != 1) return 0;                   // 小數點必須剛好一個
    if (pos == i || pos == len - 1) return 0; // 不可開頭是點，也不可結尾是點
    if (pos - i > 1 && s[i] == '0') return 0; // 整數部分不可有前導零，如 01.5
    return 1;                                 // 符合浮點數規則
}

int isVar(char s[]) {                          // 判斷是否為合法變數
    int len = strlen(s);                      // 取得長度
    if (len < 1 || len > 10) return 0;        // 變數長度限制 1~10
    if (!(isalpha(s[0]) || s[0] == '_'))      // 第一個字元必須是字母或底線
        return 0;
    for (int i = 1; i < len; i++)             // 從第二個字元開始檢查
        if (!(isalnum(s[i]) || s[i] == '_'))  // 只能是字母、數字、底線
            return 0;
    return 1;                                 // 符合變數規則
}

int isFrac(char s[], int *type) {             // 判斷是否為分數，並回傳真/假分數
    int len = strlen(s), slash = -1, cnt = 0; // slash=/位置，cnt=/數量
    char a[60], b[60];                        // a 存分子，b 存分母
    long long x = 0, y = 0;                   // x=分子值，y=分母值
    int sign = 1, p = 0;                      // sign=正負，p=數字起點

    if (len < 1 || len > 10) return 0;        // 分數長度限制
    for (int i = 0; i < len; i++)             // 找 /
        if (s[i] == '/') {
            cnt++;                            // / 數量加一
            slash = i;                        // 記住 / 位置
        }
    if (cnt != 1) return 0;                   // 必須剛好一個 /

    strncpy(a, s, slash);                     // 複製 / 前面到 a
    a[slash] = '\0';                          // 補字串結尾
    strcpy(b, s + slash + 1);                 // 複製 / 後面到 b

    if (!isInt(a) || !isInt(b)) return 0;     // 分子分母都要是合法整數

    if (a[0] == '-') {                        // 若分子有負號
        sign = -1;                            // 記錄負號
        p = 1;                                // 真正數字從 a[1] 開始
    }

    for (int i = 0; b[i]; i++)                // 檢查分母內不能再有負號
        if (b[i] == '-') return 0;

    for (int i = p; a[i]; i++)                // 把分子字串轉成數字
        x = x * 10 + (a[i] - '0');

    for (int i = 0; b[i]; i++)                // 把分母字串轉成數字
        y = y * 10 + (b[i] - '0');

    x *= sign;                                // 如果原本有負號，補回去
    if (x == 0 || y == 0) return 0;           // 分子分母都不能是 0

    if (llabs(x) < llabs(y)) *type = 1;       // |分子| < |分母| → 真分數
    else *type = 2;                           // 否則是假分數

    return 1;                                 // 是合法分數
}

int isMixed(char s[]) {                       // 判斷是否為帶分數
    int len = strlen(s), sp = -1, cnt = 0;   // sp=空白位置，cnt=空白數量
    char a[60], b[60];                        // a=整數部分，b=分數部分
    int type;                                 // 接收分數型態

    if (len < 1 || len > 10) return 0;       // 帶分數長度限制
    for (int i = 0; i < len; i++)            // 找空白
        if (s[i] == ' ') {
            cnt++;                           // 空白數量加一
            sp = i;                          // 記住空白位置
        }
    if (cnt != 1) return 0;                  // 必須剛好一個空白

    strncpy(a, s, sp);                       // 複製空白前面到 a
    a[sp] = '\0';                            // 補字串結尾
    strcpy(b, s + sp + 1);                   // 複製空白後面到 b

    if (!isInt(a)) return 0;                 // 前半段必須是整數
    if (!isFrac(b, &type)) return 0;         // 後半段必須是分數
    if (type != 1) return 0;                 // 帶分數後面一定要是真分數

    for (int i = 0; b[i]; i++)               // 後半段不能再有負號
        if (b[i] == '-') return 0;

    return 1;                                // 符合帶分數規則
}

int main() {
    int n, type;                             // n=輸入行數，type=分數種類
    char s[100];                             // 存每一行輸入

    scanf("%d", &n);                         // 讀入 n
    getchar();                               // 吃掉換行

    while (n--) {                            // 做 n 次
        fgets(s, sizeof(s), stdin);          // 讀一整行
        s[strcspn(s, "\n")] = '\0';          // 去掉結尾換行

        if (isMixed(s))                      // 先判斷帶分數
            printf("mixed fraction\n");
        else if (isFrac(s, &type)) {         // 再判斷分數
            if (type == 1) printf("proper fraction\n");
            else printf("improper fraction\n");
        }
        else if (isFloat(s))                 // 再判斷浮點數
            printf("float\n");
        else if (isInt(s))                   // 再判斷整數
            printf("integer\n");
        else if (isVar(s))                   // 再判斷變數
            printf("variable\n");
        else                                 // 以上都不是
            printf("string\n");
    }

    return 0;                                // 程式結束
}