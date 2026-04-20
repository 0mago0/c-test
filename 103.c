//大浮點數運算 放棄
#include <stdio.h>      // scanf、printf
#include <string.h>     // strlen、strcpy、strcat、strcmp、strchr

#define MAX 300         // 陣列大小，開大一點避免不夠用

// 反轉字串
void rev(char *s)
{
    int n = strlen(s);                          // 取得字串長度
    for (int i = 0; i < n / 2; i++)            // 前後交換
    {
        char t = s[i];                         // 暫存前面的字元
        s[i] = s[n - 1 - i];                  // 後面的放到前面
        s[n - 1 - i] = t;                     // 前面的放到後面
    }
}

// 去前導0，至少保留一個字元
void delFront0(char *s)
{
    int i = 0;                                 // 從頭開始找
    while (s[i] == '0' && s[i + 1] != '\0')    // 只要是0且後面還有字元
        i++;                                   // 就往後跳
    if (i > 0)                                 // 如果真的有前導0
        memmove(s, s + i, strlen(s) - i + 1);  // 整段往前搬
}

// 去小數尾端0
void delBack0(char *s)
{
    int n = strlen(s);                         // 字串長度
    while (n > 0 && s[n - 1] == '0')          // 從後面一直刪0
    {
        s[n - 1] = '\0';                      // 改成字串結束
        n--;                                   // 長度減1
    }
}

// 比較兩個非負整數字串大小
// a>b 回1，a<b 回-1，相等回0
int cmp(char *a, char *b)
{
    delFront0(a);                              // 先去前導0
    delFront0(b);                              // 先去前導0

    int la = strlen(a), lb = strlen(b);        // 取長度
    if (la > lb) return 1;                     // 位數多比較大
    if (la < lb) return -1;                    // 位數少比較小

    int t = strcmp(a, b);                      // 位數相同就逐字比
    if (t > 0) return 1;                       // a比較大
    if (t < 0) return -1;                      // b比較大
    return 0;                                  // 一樣大
}

// 大數加法
void addInt(char *a, char *b, char *res)
{
    int i = strlen(a) - 1;                     // a最後一位
    int j = strlen(b) - 1;                     // b最後一位
    int k = 0, carry = 0;                      // k給temp用，carry是進位
    char temp[MAX];                            // 暫存反向結果

    while (i >= 0 || j >= 0 || carry)          // 只要還有位數或進位
    {
        int sum = carry;                       // 先放進位
        if (i >= 0) sum += a[i--] - '0';       // 加a目前位數
        if (j >= 0) sum += b[j--] - '0';       // 加b目前位數
        temp[k++] = sum % 10 + '0';            // 個位先存
        carry = sum / 10;                      // 十位變進位
    }

    temp[k] = '\0';                            // 字串結尾
    rev(temp);                                 // 反轉回正常順序
    strcpy(res, temp);                         // 複製到res
}

// 大數減法，假設 a>=b
void subInt(char *a, char *b, char *res)
{
    int i = strlen(a) - 1;                     // a最後一位
    int j = strlen(b) - 1;                     // b最後一位
    int k = 0, borrow = 0;                     // borrow是借位
    char temp[MAX];                            // 暫存反向結果

    while (i >= 0)                             // a還有位數就繼續
    {
        int x = a[i] - '0' - borrow;           // 先減借位
        int y = (j >= 0) ? b[j] - '0' : 0;     // 如果b還有位數就取，沒有就0
        int d = x - y;                         // 做減法

        if (d < 0)                             // 如果不夠減
        {
            d += 10;                           // 借1，等於加10
            borrow = 1;                        // 記借位
        }
        else
            borrow = 0;                        // 不用借位

        temp[k++] = d + '0';                   // 存這一位答案
        i--;                                   // a往前
        j--;                                   // b往前
    }

    while (k > 1 && temp[k - 1] == '0')        // 去掉多餘0
        k--;

    temp[k] = '\0';                            // 字串結尾
    rev(temp);                                 // 反轉
    strcpy(res, temp);                         // 複製到res
}

// 大數乘法
void mulInt(char *a, char *b, char *res)
{
    int la = strlen(a), lb = strlen(b);        // a、b長度
    int t[MAX] = {0};                          // 存每一位的乘法結果

    for (int i = la - 1; i >= 0; i--)         // a從後往前
    {
        for (int j = lb - 1; j >= 0; j--)     // b從後往前
        {
            int m = (a[i] - '0') * (b[j] - '0'); // 兩位相乘
            int p1 = i + j;                    // 十位位置
            int p2 = i + j + 1;                // 個位位置

            int sum = m + t[p2];               // 加上原本位置的值
            t[p2] = sum % 10;                  // 個位留在p2
            t[p1] += sum / 10;                 // 進位加到p1
        }
    }

    int start = 0, k = 0;                      // start找第一個非0
    while (start < la + lb && t[start] == 0)   // 跳過前面0
        start++;

    if (start == la + lb)                      // 如果全部都是0
    {
        strcpy(res, "0");                      // 結果就是0
        return;                                // 直接結束
    }

    for (int i = start; i < la + lb; i++)      // 把數字陣列轉成字串
        res[k++] = t[i] + '0';

    res[k] = '\0';                             // 字串結尾
}

// 解析數字：拆成符號、整數部分、小數部分
void parse(char *s, int *sign, char *in, char *fr)
{
    int st = 0;                                // 真正數字開始位置

    if (s[0] == '-')                           // 如果是負數
    {
        *sign = -1;                            // 記成負
        st = 1;                                // 從下一格開始讀
    }
    else
        *sign = 1;                             // 否則是正數

    char *dot = strchr(s + st, '.');           // 找小數點

    if (dot)                                   // 如果有小數點
    {
        int len = dot - (s + st);              // 整數部分長度
        strncpy(in, s + st, len);              // 複製整數部分
        in[len] = '\0';                        // 補字串結尾
        strcpy(fr, dot + 1);                   // 複製小數部分
    }
    else                                       // 沒有小數點
    {
        strcpy(in, s + st);                    // 整串都是整數部分
        fr[0] = '\0';                          // 小數部分設空
    }

    delFront0(in);                             // 去整數前導0
    if (strlen(in) == 0) strcpy(in, "0");      // 空的就補成0
}

// 合併整數與小數為整數字串
// 例如 123 和 45 變成 12345
void mergeNum(char *in, char *fr, char *res)
{
    strcpy(res, in);                           // 先放整數部分
    strcat(res, fr);                           // 再接小數部分
    delFront0(res);                            // 去前導0
    if (strlen(res) == 0) strcpy(res, "0");    // 空的就補0
}

// 把整數字串插回小數點
void putDot(char *num, int flen, char *res)
{
    char t[MAX], in[MAX], fr[MAX];             // 暫存字串
    strcpy(t, num);                            // 先複製
    delFront0(t);                              // 去前導0

    if (strcmp(t, "0") == 0)                   // 如果結果是0
    {
        strcpy(res, "0");                      // 直接輸出0
        return;
    }

    int len = strlen(t);                       // 取長度

    if (flen == 0)                             // 沒有小數位
    {
        strcpy(res, t);                        // 直接就是整數
        return;
    }

    if (len <= flen)                           // 如果位數不夠放小數點
    {
        int z = flen - len;                    // 前面要補幾個0
        fr[0] = '\0';                          // 小數部分先清空
        for (int i = 0; i < z; i++)           // 先補0
            strcat(fr, "0");
        strcat(fr, t);                         // 再接原本數字
        delBack0(fr);                          // 去尾端0

        if (strlen(fr) == 0)                   // 如果小數部分全沒了
            strcpy(res, "0");                  // 就是0
        else
            sprintf(res, "0.%s", fr);          // 組成0.xxx
    }
    else                                       // 位數夠放小數點
    {
        strncpy(in, t, len - flen);            // 前面是整數部分
        in[len - flen] = '\0';                 // 補結尾
        strcpy(fr, t + len - flen);            // 後面是小數部分
        delBack0(fr);                          // 小數尾端0刪掉

        if (strlen(fr) == 0)                   // 小數全為0
            strcpy(res, in);                   // 只留整數
        else
            sprintf(res, "%s.%s", in, fr);     // 組成整數.小數
    }
}

// 判斷結果是不是0
int isZero(char *s)
{
    for (int i = 0; s[i]; i++)                 // 每個字元都檢查
        if (s[i] != '0' && s[i] != '.')        // 只要有不是0或.
            return 0;                          // 就不是0
    return 1;                                  // 否則就是0
}

// 做加減法
void calcAddSub(char *A, char *B, char op, char *ans)
{
    int sa, sb;                                // A、B符號
    char ia[MAX], ib[MAX];                     // 整數部分
    char fa[MAX], fb[MAX];                     // 小數部分
    char na[MAX], nb[MAX];                     // 合併後整數字串
    char temp[MAX], out[MAX];                  // 暫存結果

    parse(A, &sa, ia, fa);                     // 解析A
    parse(B, &sb, ib, fb);                     // 解析B

    if (op == '-') sb *= -1;                   // 減法變成 A + (-B)

    int la = strlen(fa), lb = strlen(fb);      // 小數長度
    int mx = (la > lb) ? la : lb;              // 取最大小數長度

    while (strlen(fa) < mx) strcat(fa, "0");   // A小數補0
    while (strlen(fb) < mx) strcat(fb, "0");   // B小數補0

    mergeNum(ia, fa, na);                      // 合併A
    mergeNum(ib, fb, nb);                      // 合併B

    int sign = 1;                              // 結果符號先假設正

    if (sa == sb)                              // 同號直接加
    {
        addInt(na, nb, temp);                  // 做加法
        sign = sa;                             // 符號跟原本一樣
    }
    else                                       // 異號要相減
    {
        char ca[MAX], cb[MAX];                 // 給cmp用的副本
        strcpy(ca, na);                        // 複製A
        strcpy(cb, nb);                        // 複製B
        int c = cmp(ca, cb);                   // 比較絕對值大小

        if (c == 0)                            // 一樣大
        {
            strcpy(ans, "0");                  // 直接是0
            return;                            // 結束
        }
        else if (c > 0)                        // A比較大
        {
            subInt(na, nb, temp);              // A-B
            sign = sa;                         // 符號跟A一樣
        }
        else                                   // B比較大
        {
            subInt(nb, na, temp);              // B-A
            sign = sb;                         // 符號跟B一樣
        }
    }

    putDot(temp, mx, out);                     // 插回小數點

    if (isZero(out))                           // 如果是0
        strcpy(ans, "0");                      // 直接輸出0
    else if (sign < 0)                         // 如果結果為負
        sprintf(ans, "-%s", out);              // 前面補負號
    else
        strcpy(ans, out);                      // 正數直接複製
}

// 做乘法
void calcMul(char *A, char *B, char *ans)
{
    int sa, sb;                                // A、B符號
    char ia[MAX], ib[MAX];                     // 整數部分
    char fa[MAX], fb[MAX];                     // 小數部分
    char na[MAX], nb[MAX];                     // 合併後整數字串
    char temp[MAX], out[MAX];                  // 暫存結果

    parse(A, &sa, ia, fa);                     // 解析A
    parse(B, &sb, ib, fb);                     // 解析B

    int flen = strlen(fa) + strlen(fb);        // 乘法後總小數位數

    mergeNum(ia, fa, na);                      // 合併A
    mergeNum(ib, fb, nb);                      // 合併B

    mulInt(na, nb, temp);                      // 做大數乘法
    putDot(temp, flen, out);                   // 插回小數點

    if (isZero(out))                           // 如果結果是0
        strcpy(ans, "0");                      // 直接輸出0
    else if (sa * sb < 0)                      // 一正一負為負
        sprintf(ans, "-%s", out);              // 補負號
    else
        strcpy(ans, out);                      // 正數直接複製
}

int main()
{
    char A[MAX], B[MAX];                       // 兩個輸入數字
    char addAns[MAX], subAns[MAX], mulAns[MAX * 2]; // 三個答案

    scanf("%s", A);                            // 讀入第一個數
    scanf("%s", B);                            // 讀入第二個數

    calcAddSub(A, B, '+', addAns);             // 算加法
    calcAddSub(A, B, '-', subAns);             // 算減法
    calcMul(A, B, mulAns);                     // 算乘法

    printf("%s\n", addAns);                    // 輸出加法答案
    printf("%s\n", subAns);                    // 輸出減法答案
    printf("%s\n", mulAns);                    // 輸出乘法答案

    return 0;                                  // 程式結束
}