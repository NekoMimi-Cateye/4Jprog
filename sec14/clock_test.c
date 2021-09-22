#include<stdio.h>
#include<time.h>

int main(void)
{
    // 変数群
    time_t t1;
    time_t t2;
    struct tm *pt1;
    struct tm *pt2;

    // 開始時刻を t1,pt1 として格納
    time(&t1);
    pt1 = localtime(&t1);

    // time構造体の内部確認
    while(1)
    {
        // 現在時刻を t2,pt2 として格納
        time(&t2);
        pt2 = localtime(&t2);

        // なぜか勝手に t1 も更新されている件の確認
        printf("\rpt1 -> tm_sec :: %d  ", pt1 -> tm_sec);
        printf("pt2 -> tm_sec :: %d    ", pt2 -> tm_sec);
    }
}