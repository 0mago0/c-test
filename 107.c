//直線方程式 61 必背
#include <stdio.h>      // 輸入輸出
#include <stdlib.h>     // abs 用
// 最大公因數
int gcd(int a,int b){
    return b==0?abs(a):gcd(b,a%b);   // 遞迴求 gcd
}
// 約分 + 分母轉正
void sim(int *n,int *d){
    int g=gcd(*n,*d);   // 找最大公因數
    *n/=g;              // 分子除 gcd
    *d/=g;              // 分母除 gcd
    if(*d<0){           // 若分母為負
        *n*=-1;         // 分子乘 -1
        *d*=-1;         // 分母乘 -1（轉正）
    }
}
// 印分數（或整數）
void pf(int n,int d){
    if(d==1) printf("%d",n);   // 分母=1 → 印整數
    else printf("%d/%d",n,d);  // 否則印分數
}
int main(){
    int n; 
    scanf("%d",&n);   // 測資筆數
    while(n--){
        int x1,y1,x2,y2;
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2); // 讀兩點
        // m = (y1-y2)/(x1-x2)
        int mn=y1-y2, md=x1-x2;
        sim(&mn,&md);  // 約分 m
        // b = (x2*y1 - x1*y2)/(x2-x1)
        int bn=x2*y1-x1*y2, bd=x2-x1;
        sim(&bn,&bd);  // 約分 b

        printf("y = ");   // 固定開頭
        // m = 0 → y = b
        if(mn==0){
            pf(bn,bd);   // 印 b
            printf("\n");
            continue;    // 下一筆
        }
        // 印 m
        if(mn==md) printf("x");         // m = 1
        else if(mn==-md) printf("-x");  // m = -1
        else{
            pf(mn,md);   // 印 m
            printf("x");
        }
        // 印 b
        if(bn>0){
            printf(" + ");
            pf(bn,bd);
        }
        else if(bn<0){
            printf(" - ");
            pf(abs(bn),bd); // 印絕對值
        }
        printf("\n");   // 換行
    }
}