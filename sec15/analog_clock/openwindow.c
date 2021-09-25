#include<GL/glut.h>
#include<stdio.h>
#include<time.h>
#include<math.h>


void Display(void);
void Reshape(int, int);
void Timer(int);


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Analog Clock");
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutInitDisplayMode(GLUT_RGBA);
    glutTimerFunc(500, Timer, 0);
    glClearColor(0.0, 0.101, 0.263, 1.0); // #001A43 ... 紺色
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

    //時間の定義
    char l_hour[12][3] = {"3", "2", "1", "12", "11", "10", "9", "8", "7", "6", "5", "4"};

    // 日付格納枠
    char s_curt[26] = {"\0"};

    // 現在時刻の更新
    time(&curt);
    p_curt = localtime(&curt);
    /* ここまで */

    glClear(GL_COLOR_BUFFER_BIT);

    // 時計の描画
    // 中心点計算
    int xc = glutGet(GLUT_WINDOW_WIDTH) / 2;
    int yc = glutGet(GLUT_WINDOW_HEIGHT) / 2;

    // 時計のフレーム作成
    // フレーム半径
    double fr;
    if (xc < yc)
        fr = (double)xc * 0.85;
    else
        fr = (double)yc * 0.85;

    // 外側デザイン
    glPointSize(5.0);
    glBegin(GL_POINTS);
    for (int i=0; i<24; i++)
    {
        glColor3ub(224, 134, 26);    // #E0861A ... 金茶
        double rad = M_PI * (double)i / 12.0;
        for (double gx=0; gx<1; gx += 0.01)
        {
            double gy = 1.618 * (gx-1.0) * (gx - 1.0) * (-gx);
            double x1, x2, y1, y2;
            x1 = 0.75 * fr * (gx * cos(rad) - gy * sin(rad)) + 0.25 * fr * cos(rad);
            x2 = 0.75 * fr * (gx * cos(rad) + gy * sin(rad)) + 0.25 * fr * cos(rad);
            y1 = 0.75 * fr * (gx * sin(rad) + gy * cos(rad)) + 0.25 * fr * sin(rad);
            y2 = 0.75 * fr * (gx * sin(rad) - gy * cos(rad)) + 0.25 * fr * sin(rad);
            glVertex2i(xc + x1, yc + y1);
            glVertex2i(xc + x2, yc + y2);
        }
    }
    glEnd();

    // 時計のフレーム
    glBegin(GL_TRIANGLE_FAN);
        glColor3ub(230, 180, 34); // #e6b422 ... 黄金
        glVertex2i(xc, yc);
        for (double deg=0; deg<360.0; deg+=0.1)
        {
            double rad = M_PI * deg / 180.0;
            int x = (int)(cos(rad) * fr * 0.35) + xc;
            int y = (int)(sin(rad) * fr * 0.35) + yc;
            glVertex2i(x, y);
        }
    glEnd();

    // 時計の背景色
    glBegin(GL_TRIANGLE_FAN);
        glColor3ub(0, 0, 0);
        glVertex2i(xc, yc);
        for (double deg=0; deg<360.0; deg+=0.1)
        {
            double rad = M_PI * deg / 180.0;
            int x = (int)(cos(rad) * fr * 0.33) + xc;
            int y = (int)(sin(rad) * fr * 0.33) + yc;
            glVertex2i(x, y);
        }
    glEnd();

    // 長針描画
    double lr = fr * 0.35;
    double blr = fr * 0.05;
    glLineWidth(2.0);
    glBegin(GL_LINES);
        glColor3ub(209, 171, 5); // #c1ab05 ... アンティークゴールド
        double rad = M_PI * (double)(p_curt -> tm_sec) / 30.0;

        double xe = xc + sin(rad) * lr;
        double ye = yc - cos(rad) * lr;
        double xs = xc - sin(rad) * blr;
        double ys = yc + cos(rad) * blr;

        glVertex2i(xs, ys);
        glVertex2i(xe, ye);
    glEnd();

    // 中針描画
    lr = fr * 0.25;
    glLineWidth(3.0);
    glBegin(GL_LINES);
        glColor3ub(209, 171, 5); // #c1ab05 ... アンティークゴールド

        rad /= 60.0;
        rad += M_PI * (double)(p_curt -> tm_min) / 30.0;
        xe = xc + sin(rad) * lr;
        ye = yc - cos(rad) * lr;

        xs = xc - sin(rad) * blr;
        ys = yc + cos(rad) * blr;

        glVertex2i(xs, ys);
        glVertex2i(xe, ye);
    glEnd();

    // 短針描画
    lr = fr * 0.2;
    glLineWidth(5.0);
    glBegin(GL_LINES);
        glColor3ub(209, 171, 5); // #c1ab05 ... アンティークゴールド

        rad /= 12.0;
        rad += M_PI * (double)(p_curt -> tm_hour) / 6.0;
        xe = xc + sin(rad) * lr;
        ye = yc - cos(rad) * lr;

        xs = xc - sin(rad) * blr;
        ys = yc + cos(rad) * blr;

        glVertex2i(xs, ys);
        glVertex2i(xe, ye);
    glEnd();

    // 中心円
    glBegin(GL_TRIANGLE_FAN);
        glColor3ub(209, 171, 5); // #c1ab05 ... アンティークゴールド
        glVertex2i(xc, yc);
        for (double deg=0; deg<360.0; deg+=0.1)
        {
            double rad = M_PI * deg / 180.0;
            int x = (int)(cos(rad) * 5.0) + xc;
            int y = (int)(sin(rad) * 5.0) + yc;
            glVertex2i(x, y);
        }
    glEnd();
    // 留め具
    glBegin(GL_TRIANGLE_FAN);
        glColor3ub(0, 0, 0);
        glVertex2i(xc, yc);
        for (double deg=0; deg<360.0; deg+=0.1)
        {
            double rad = M_PI * deg / 180.0;
            int x = (int)(cos(rad) * 3.0) + xc;
            int y = (int)(sin(rad) * 3.0) + yc;
            glVertex2i(x, y);
        }
    glEnd();

    //文字盤を描画
    glColor3ub(255, 255, 255);
    for (int i=0; i<12; i++)
    {
        double rad = M_PI * (double)i / 6.0;
        double dx = (fr * 0.33 - 15.0) * cos(rad);
        double dy = (fr * 0.33 - 15.0) * sin(rad);
        if (i == 3 || i == 4 || i == 5)
            glRasterPos2i(xc + dx - 9, yc - dy + 7);
        else
            glRasterPos2i(xc + dx - 4, yc - dy + 7);
        for(int j=0; j<3; j++)
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, l_hour[i][j]);
    }

    // 日時の表示
    sprintf(s_curt, "%4d/%02d/%02d (%3s) %02d:%02d:%02d",
        p_curt->tm_year + 1900,
        p_curt->tm_mon + 1,
        p_curt->tm_mday,
        l_week[p_curt->tm_wday],
        p_curt->tm_hour,
        p_curt->tm_min,
        p_curt->tm_sec);
        
    glColor3ub(255, 255, 255);
    glRasterPos2i(glutGet(GLUT_WINDOW_WIDTH) - 26*9 - 20, glutGet(GLUT_WINDOW_HEIGHT) - 20);
    for(int j=0; j<26; j++)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, s_curt[j]);

    glFlush();
    glutReshapeWindow(640, 480);
}


//
// ウインドウのリサイズが発生した時に座標系を再設定する関数
//
void Reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glScaled(1, -1, 1);
    glTranslated(0, -h, 0);
}

void Timer(int value)
{
    glutPostRedisplay();
    glutTimerFunc(100, Timer, 0);
}