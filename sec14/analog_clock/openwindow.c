#include<GL/glut.h>


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
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}