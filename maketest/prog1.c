#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double kansuu1(int, int);
double kansuu2(int);
double kansuu3(int);

int main(void)
{
    int a=3, b=4;
    double c, d, e;

    c = kansuu1(a, b);
    d = kansuu2(a);
    e = kansuu3(b);

    printf("c=%f\n", c);
    printf("d=%f\n", d);
    printf("e=%f\n", e);
}