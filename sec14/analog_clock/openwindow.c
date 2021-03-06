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
    glutInitWindowSize(400, 400);
    glutCreateWindow("Analog Clock");
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutInitDisplayMode(GLUT_RGBA);
    glutTimerFunc(500, Timer, 0);
    glClearColor(0.7, 1.0, 1.0, 1.0);
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
    /* ここまで */

    glClear(GL_COLOR_BUFFER_BIT);

    // 時計の描画
    // 中心点計算
    int xc = glutGet(GLUT_WINDOW_WIDTH) / 2;
    int yc = glutGet(GLUT_WINDOW_HEIGHT) / 2;

    // 時計のフレーム作成
    // 正葉曲線の係数
    double k = 0.7;
    double fr;
    // フレーム半径
    if (xc < yc)
        fr = (double)xc * 0.85;
    else
        fr = (double)yc * 0.85;
    // フレーム描画
    glBegin(GL_TRIANGLE_FAN);
        glColor3ub(0, 0, 0);
        glVertex2i(xc, yc);
        for (double deg=0; deg<360.0; deg+=0.1)
        {
            double rad = M_PI * deg / 180.0;
            int x = (int)(cos(rad) * fr) + xc;
            int y = (int)(sin(rad) * fr) + yc;
            glVertex2i(x, y);
        }
    glEnd();

    // フレーム装飾
    glPointSize(3.0);
    glBegin(GL_POINTS);
        for (double deg=0; deg<1800.0; deg+=0.1)
        {
            double rad = M_PI * deg / 180.0;
            double r = fr * sin(rad * k);

            int x = (int)(cos(rad) * r) + xc;
            int y = (int)(sin(rad) * r) + yc;
            double ddeg = 1800.0 * (double)(p_curt->tm_sec) / 60.0;
            
            double fcc = (double)((int)(deg+ddeg) % 1800);
            int fcr, fcg, fcb;
            if (fcc <= 600)
            {
                fcr = (int)(fcc * 255.0 / 600.0);
                fcg = (int)((600.0 - fcc) * 255.0 / 600.0);
                fcb = 0;
            }
            else if (fcc <= 1200)
            {
                fcr = (int)((1200.0 - fcc) * 255.0 / 600.0);
                fcg = 0;
                fcb = (int)((fcc - 600.0) * 255.0 / 600.0);
            }
            else
            {
                fcr = 0;
                fcg = (int)((fcc - 1200.0) * 255.0 / 600.0);
                fcb = (int)((1800.0 - fcc) * 255.0 / 600.0);
            }
            glColor3ub(fcr, fcg, fcb);
            glVertex2i(x, y);
        }
    glEnd();

    // 中心点描画
    glBegin(GL_TRIANGLE_FAN);
        glColor3ub(255, 255, 255);
        glVertex2i(xc, yc);
        for (double deg=0; deg<360.0; deg+=0.1)
        {
            double rad = M_PI * deg / 180.0;
            int x = (int)(cos(rad) * 10.0) + xc;
            int y = (int)(sin(rad) * 10.0) + yc;
            glVertex2i(x, y);
        }
    glEnd();

    // 長針描画
    double lr;
    if (xc < yc)
        lr = (double)xc * 0.75;
    else
        lr = (double)yc * 0.75;
    glLineWidth(2.0);
    glBegin(GL_LINES);
        glColor3ub(255, 255, 255);

        double rad = M_PI * (double)(p_curt -> tm_sec) / 30.0;
        double xe = xc + sin(rad) * lr;
        double ye = yc - cos(rad) * lr;

        glVertex2i(xc, yc);
        glVertex2i(xe, ye);
    glEnd();

    // 中針描画
    if (xc < yc)
        lr = (double)xc * 0.6;
    else
        lr = (double)yc * 0.6;
    glLineWidth(3.0);
    glBegin(GL_LINES);
        glColor3ub(255, 255, 255);

        rad = M_PI * (double)(p_curt -> tm_min) / 30.0;
        xe = xc + sin(rad) * lr;
        ye = yc - cos(rad) * lr;

        glVertex2i(xc, yc);
        glVertex2i(xe, ye);
    glEnd();

    // 短針描画
    if (xc < yc)
        lr = (double)xc * 0.5;
    else
        lr = (double)yc * 0.5;
    glLineWidth(5.0);
    glBegin(GL_LINES);
        glColor3ub(255, 255, 255);

        rad = M_PI * (double)(p_curt -> tm_hour) / 6.0;
        xe = xc + sin(rad) * lr;
        ye = yc - cos(rad) * lr;

        glVertex2i(xc, yc);
        glVertex2i(xe, ye);
    glEnd();
    glFlush();
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
    glutTimerFunc(500, Timer, 0);
}