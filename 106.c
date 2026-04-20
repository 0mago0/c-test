#include <stdio.h>      // 提供 scanf、printf
#include <string.h>     // 提供 strlen、strcmp、memmove
//大數除法 131 有餘力的話
// 比大小：a >= b 回傳1，否則0（簡化版，只夠這題用）
int ge(char a[], char b[]) {
    int la = strlen(a), lb = strlen(b);     // 取得長度
    if (la != lb) return la > lb;           // 長度大的一定比較大
    return strcmp(a, b) >= 0;               // 長度相同用字典比較
}

// 去前導零
void trim(char s[]) {
    int i = 0;                              // 從開頭找
    while (s[i] == '0' && s[i+1]) i++;      // 跳過前導0
    if (i) memmove(s, s+i, strlen(s)-i+1);  // 把有效部分往前搬
}

// 大數減法：a = a - b（已保證 a >= b）
void sub(char a[], char b[]) {
    int la = strlen(a), lb = strlen(b), borrow = 0; // 長度與借位

    for (int i = 0; i < la; i++) {         // 從個位數開始
        int ai = a[la-1-i] - '0';          // 取 a 的數字
        int bi = (i < lb) ? b[lb-1-i]-'0' : 0; // 取 b 或補0

        int v = ai - bi - borrow;          // 做減法
        if (v < 0) { v += 10; borrow = 1; } // 不夠減就借位
        else borrow = 0;                   // 否則不借

        a[la-1-i] = v + '0';               // 存回字元
    }
    trim(a);                               // 去前導零
}

// 大數除法
void divi(char A[], char B[]) {
    char cur[205] = "";                    // 當前被除數片段
    char ans[205] = "";                    // 整數部分
    char dec[105] = "";                    // 小數部分
    int al = strlen(A), ai = 0, di = 0;    // 長度與索引

    // ----- 整數部分 -----
    for (int i = 0; i < al; i++) {         // 每次帶一位
        int l = strlen(cur);               
        cur[l] = A[i];                     // 加一位
        cur[l+1] = '\0';                   // 補結尾

        trim(cur);                         // 去前導零

        int cnt = 0;                       // 這一位商
        while (ge(cur, B)) {               // 如果還能減
            sub(cur, B);                   // 減掉一次
            cnt++;                         // 商+1
        }

        ans[ai++] = cnt + '0';             // 存商
        ans[ai] = '\0';                    // 補結尾
    }

    trim(ans);                             // 去前導零
    if (!strlen(ans)) strcpy(ans, "0");    // 保險變0

    // ----- 小數部分（100位）-----
    for (int i = 0; i < 100; i++) {        // 最多100位
        if (!strcmp(cur, "0")) break;      // 餘數為0就停

        int l = strlen(cur);
        cur[l] = '0';                      // 乘10
        cur[l+1] = '\0';

        trim(cur);                         // 去前導零

        int cnt = 0;
        while (ge(cur, B)) {               // 繼續做除法
            sub(cur, B);
            cnt++;
        }

        dec[di++] = cnt + '0';             // 記錄小數位
        dec[di] = '\0';
    }

    // 去尾0
    while (di > 0 && dec[di-1] == '0') di--;
    dec[di] = '\0';

    // ----- 輸出 -----
    if (!strcmp(ans, "0") && di == 0)      // 如果結果為0
        printf("0");
    else if (di == 0)                     // 沒小數
        printf("%s", ans);
    else                                  // 有小數
        printf("%s.%s", ans, dec);
}

int main() {
    char A[205], B[205];                  // 兩個大數
    int neg = 0;                          // 紀錄負號

    scanf("%s%s", A, B);                  // 輸入

    if (!strcmp(A, "0")) {                // A為0直接輸出
        printf("0");
        return 0;
    }

    // 處理負號
    if (A[0] == '-') {                    // A是負
        neg ^= 1;                         // 記錄負號
        memmove(A, A+1, strlen(A));       // 去掉'-'
    }
    if (B[0] == '-') {                    // B是負
        neg ^= 1;
        memmove(B, B+1, strlen(B));
    }

    trim(A); trim(B);                     // 去前導零

    // 如果相等直接輸出1或-1
    if (!strcmp(A, B)) {
        if (neg) printf("-1");
        else printf("1");
        return 0;
    }

    if (neg) printf("-");                 // 若結果負，先印負號

    divi(A, B);                           // 做除法

    return 0;
}