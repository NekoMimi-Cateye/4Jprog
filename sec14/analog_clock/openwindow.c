#include<GL/glut.h>


void Display(void);


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(320, 240);
    glutCreateWindow("サンプルその１");
    glutDisplayFunc(Display);
    glutMainLoop();

    return(0);
}



//
// ウインドウの表示内容を更新する関数
//
void Display(void)
{
    // とりあえず何もしない
}