#include<stdio.h>
#include<time.h>

int main(void)
{
    // 変数群
    time_t curt;
    struct tm *p_curt;

    // 曜日の定義
    char l_week[7][4] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

    // 表示用変数
    int year, mon, day, week, hour, min, sec;

    // 処理部
    while(1)
    {
        // 現在時刻の更新
        time(&curt);
        p_curt = localtime(&curt);

        // 表示用変数に日時を格納
        year = p_curt -> tm_year + 1900;
        mon = p_curt -> tm_mon + 1;
        day = p_curt -> tm_mday;
        week = p_curt -> tm_wday;
        hour = p_curt -> tm_hour;
        min = p_curt -> tm_min;
        sec = p_curt -> tm_sec;

        // 表示
        printf("\r%d/%02d/%02d %3s %02d:%02d:%02d", year, mon, day, l_week[week], hour, min, sec);
    }
}