#include<stdio.h>
#include<time.h>

int main(void)
{
    // 変数群
    time_t t1, t2;
    struct tm *pt1, *pt2;

    // time構造体作成
    time(&t1);
    pt1 = localtime(&t1);

    // time構造体の内部確認
    while(1)
    {
        // 更新テスト
        time(&t2);
        pt2 = localtime(&t2);

        // config
        printf("\rpt1 -> tm_sec :: %d  ", pt1 -> tm_sec);
        printf("pt2 -> tm_sec :: %d    ",   pt2 -> tm_sec);
    }
}