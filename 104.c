#include <stdio.h>   // 載入標準輸入輸出函式庫（scanf、printf）
//迷宮 62必背
int main() {

    int R, C;                      // 列、欄
    scanf("%d %d", &R, &C);        // 輸入大小

    int a[10][10], v[10][10]={0};  // a存矩陣，v記錄走過

    for(int i=0;i<R;i++)           // 讀矩陣
        for(int j=0;j<C;j++)
            scanf("%d",&a[i][j]);

    int r=0,c=0;                  // 起點座標(先設0,0)
    for(int i=0;i<R;i++)          // 找全圖最小值
        for(int j=0;j<C;j++)
            if(a[i][j]<a[r][c]){  // 如果更小
                r=i; c=j;         // 更新起點
            }

    int dr[4]={-1,1,0,0};         // 上下左右 row
    int dc[4]={0,0,-1,1};         // 上下左右 col

    int sum=a[r][c];              // 總和先加起點
    v[r][c]=1;                    // 標記走過
    int step=1;                   // 從移動開始算第1步

    while(1){                     // 一直走

        int nr=-1,nc=-1;          // 下一點
        int f=0;                  // 是否找到

        for(int k=0;k<4;k++){     // 掃四方向

            int tr=r+dr[k];       // 新row
            int tc=c+dc[k];       // 新col

            if(tr>=0&&tr<R&&tc>=0&&tc<C&&!v[tr][tc]){ // 合法

                if(!f){           // 第一個候選
                    nr=tr; nc=tc; // 先存
                    f=1;
                }
                else if(step%2==1 && a[tr][tc]<a[nr][nc]){ // 奇數→最小
                    nr=tr; nc=tc;
                }
                else if(step%2==0 && a[tr][tc]>a[nr][nc]){ // 偶數→最大
                    nr=tr; nc=tc;
                }
            }
        }

        if(!f) break;             // 沒路就停

        r=nr; c=nc;               // 移動
        v[r][c]=1;                // 標記
        sum+=a[r][c];             // 加總
        step++;                   // 步數+1
    }

    printf("%d\n",sum);           // 輸出答案
}