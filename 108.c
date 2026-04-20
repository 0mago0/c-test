#include <stdio.h>      // 輸入輸出
#include <string.h>     // 字串處理
#include <stdlib.h>     // llabs()
//分數運算 96必背
// 最大公因數（約分用）
long long gcd(long long a, long long b){
    return b==0 ? llabs(a) : gcd(b,a%b); // 輾轉相除法
}

// 解析分數字串 → 轉成假分數
void parse(char *s,long long *n,long long *d){
    long long a=0,b=0,c=0; // a整數 b分子 c分母
    int neg=0;             // 是否負數

    if(s[0]=='-'){neg=1; s++;} // 若負數，記錄並跳過 '-'

    if(strchr(s,'(')){ // 帶分數
        sscanf(s,"%lld(%lld/%lld)",&a,&b,&c);
        *n=a*c+b;      // 整數轉假分數
        *d=c;
    }else{             // a/b
        sscanf(s,"%lld/%lld",&b,&c);
        *n=b; *d=c;
    }

    if(neg) *n=-*n;    // 補負號
}

// 輸出（最簡＋帶分數）
void print(long long n,long long d){
    if(d==0){printf("error\n"); return;} // 分母0

    if(n==0){printf("0\n"); return;}     // 結果0

    int neg=0;
    if(n<0){neg=1; n=-n;}                // 處理負號

    long long g=gcd(n,d);                // 約分
    n/=g; d/=g;

    long long a=n/d;                     // 整數部分
    long long b=n%d;                     // 餘數

    if(neg) printf("-");                 // 先印負號

    if(b==0) printf("%lld\n",a);         // 整數
    else if(a==0) printf("%lld/%lld\n",b,d); // 真分數
    else printf("%lld(%lld/%lld)\n",a,b,d);  // 帶分數
}

int main(){
    char s1[50],s2[50],op,cont; // 兩分數+運算+是否繼續

    while(1){
        scanf("%s",s1);        // 第一個分數
        scanf(" %c",&op);      // 運算符
        scanf("%s",s2);        // 第二個分數

        long long a,b,c,d;     // a/b , c/d
        parse(s1,&a,&b);       // 解析
        parse(s2,&c,&d);

        if(b==0||d==0){        // 分母0
            printf("error\n");
        }else{
            long long n,dn;    // 結果

            if(op=='+'){       // 加法
                n=a*d+b*c;
                dn=b*d;
            }
            else if(op=='-'){  // 減法
                n=a*d-b*c;
                dn=b*d;
            }
            else if(op=='*'){  // 乘法
                n=a*c;
                dn=b*d;
            }
            else if(op=='/'){  // 除法
                if(c==0){      // 除數為0
                    printf("error\n");
                    goto next; // 跳過
                }
                n=a*d;
                dn=b*c;
            }

            print(n,dn);       // 輸出
        }

        next:
        scanf(" %c",&cont);    // 是否繼續
        if(cont=='n') break;   // n結束
    }
}