#include<GL/glut.h>
#include<stdio.h>
#include<time.h>


void Display(void);


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(320, 240);
    glutCreateWindow("サンプルその１");
    glutDisplayFunc(Display);
    glutInitDisplayMode(GLUT_RGBA);
    glClearColor(0.0, 0.0, 1.0, 1.0);

    glutMainLoop();

    return(0);
}



//
// ウインドウの表示内容を更新する関数
//
void Display(void)
{
    /* sec14/clock1.c より移植・改変 */
    // 変数群
    time_t curt;
    struct tm *p_curt;

    // 曜日の定義
    char l_week[7][4] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

    // 現在時刻の更新
    time(&curt);
    p_curt = localtime(&curt);

    // 表示
    printf("\r%d/%02d/%02d %3s %02d:%02d:%02d",
        p_curt -> tm_year + 1900,
        p_curt -> tm_mon + 1,
        p_curt -> tm_mday,
        l_week[p_curt -> tm_wday],
        p_curt -> tm_hour,
        p_curt -> tm_min,
        p_curt -> tm_sec);
    /* ここまで */

    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();

}