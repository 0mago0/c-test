//骰子 102必背
#include <stdio.h>  // 使用 scanf、printf

typedef struct{     // 定義骰子結構
    int u,d,l,r,f,b; // 上 下 左 右 前 後
}Dice;

void F(Dice *x){    // 向前滾一次
    int u=x->u,d=x->d,l=x->l,r=x->r,f=x->f,b=x->b; // 先存原本六面
    x->u=b;         // 後 -> 上
    x->d=f;         // 前 -> 下
    x->f=u;         // 上 -> 前
    x->b=d;         // 下 -> 後
    x->l=l;         // 左不變
    x->r=r;         // 右不變
}

void B(Dice *x){    // 向後滾一次
    int u=x->u,d=x->d,l=x->l,r=x->r,f=x->f,b=x->b; // 先存原本六面
    x->u=f;         // 前 -> 上
    x->d=b;         // 後 -> 下
    x->f=d;         // 下 -> 前
    x->b=u;         // 上 -> 後
    x->l=l;         // 左不變
    x->r=r;         // 右不變
}

void R(Dice *x){    // 向右滾一次
    int u=x->u,d=x->d,l=x->l,r=x->r,f=x->f,b=x->b; // 先存原本六面
    x->u=l;         // 左 -> 上
    x->d=r;         // 右 -> 下
    x->l=d;         // 下 -> 左
    x->r=u;         // 上 -> 右
    x->f=f;         // 前不變
    x->b=b;         // 後不變
}

void L(Dice *x){    // 向左滾一次
    int u=x->u,d=x->d,l=x->l,r=x->r,f=x->f,b=x->b; // 先存原本六面
    x->u=r;         // 右 -> 上
    x->d=l;         // 左 -> 下
    x->l=u;         // 上 -> 左
    x->r=d;         // 下 -> 右
    x->f=f;         // 前不變
    x->b=b;         // 後不變
}

void move(Dice *x,char c,int n){ // 套用一個移動指令
    n%=4;                     // 同方向轉4次會回原狀，所以只做 n%4 次
    for(int i=0;i<n;i++){     // 重複做 n 次單步翻轉
        if(c=='F') F(x);      // 若是 F，向前滾
        else if(c=='B') B(x); // 若是 B，向後滾
        else if(c=='R') R(x); // 若是 R，向右滾
        else if(c=='L') L(x); // 若是 L，向左滾
    }
}

int score(int a,int b,int c){ // 計算三顆骰子朝上點數的分數
    if(a==b && b==c) return a*2; // 三顆都相同，該點數*2
    if(a==b) return c;           // 前兩顆相同，取不同的那顆
    if(a==c) return b;           // 第1和第3顆相同，取不同的那顆
    if(b==c) return a;           // 第2和第3顆相同，取不同的那顆
    return 0;                    // 三顆都不同，得0分
}

int main(){
    Dice A[3],B2[3];   // A、B 各三顆骰子
    int n;             // 每顆骰子的指令數

    for(int i=0;i<3;i++){ // 讀入三顆初始骰子
        scanf("%d%d%d%d%d%d",&A[i].u,&A[i].d,&A[i].l,&A[i].r,&A[i].f,&A[i].b); // 上下左右前後
        B2[i]=A[i];       // 題目範例中 B 初始和 A 相同，所以直接複製
    }

    scanf("%d",&n);       // 讀入每顆骰子要做幾個指令

    for(int i=0;i<3;i++)          // 處理 A 的三顆骰子
        for(int j=0;j<n;j++){     // 每顆有 n 個指令
            char c; int k;        // c=方向, k=距離
            scanf(" %c%d",&c,&k); // 讀入像 F1、R3
            move(&A[i],c,k);      // 套用到 A 的第 i 顆骰子
        }

    for(int i=0;i<3;i++)          // 處理 B 的三顆骰子
        for(int j=0;j<n;j++){     // 每顆有 n 個指令
            char c; int k;        // c=方向, k=距離
            scanf(" %c%d",&c,&k); // 讀入指令
            move(&B2[i],c,k);     // 套用到 B 的第 i 顆骰子
        }

    int sa=score(A[0].u,A[1].u,A[2].u);      // A 三顆骰子朝上的點數計分
    int sb=score(B2[0].u,B2[1].u,B2[2].u);   // B 三顆骰子朝上的點數計分

    if(sa>sb) printf("A win\n"); // 若 A 分數較大
    else if(sb>sa) printf("B win\n"); // 若 B 分數較大
    else printf("Tie\n");        // 若同分則平手

    printf("%d %d\n",sa,sb);     // 印出 A、B 分數

    return 0;                    // 程式結束
}