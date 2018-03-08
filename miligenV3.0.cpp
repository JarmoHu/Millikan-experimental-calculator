
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Pi 3.14159265358979323846 //定义圆周率的取值
#define DENSITY 981               //油滴的密度
#define b (6.17e-6)               //粘滞系数修正常数
#define g 9.795                   //重力加速度
#define d 5e-3                    //极板间距离
#define l (1.5e-3)                //油滴匀速上升或下降的距离
#define p 76                      //大气压强
#define e 1.6021765e-19           //元电荷
#define ETA (1.83e-5)             //粘滞系数
#define E_MAX 20                  //最大测量电子数，若不够可以修改
#define T_MAX 10                  //最大测量时间数，若不够可以修改

void Print_instructions(void); //打印启动说明
void Print_menu(void);         //打印数据菜单
void Print_tab(void);          //打印表格标签
void Print_text(void);         //打印表格数据
void Data_add(int n);          //增加数据
void Data_revise(void);        //修改数据
void Data_calculate(void);     //回归方程计算
void Data_analysis(int n);     //数据分析

int number_e = 0, number_t = 0, number_e_h = 0, num[E_MAX];
double U[E_MAX], t[E_MAX][T_MAX], tg[E_MAX], v[E_MAX], Q[E_MAX], q[E_MAX], deviation[E_MAX], q1[E_MAX];

int main(void)
{
    system("cls");
    Print_instructions();
    while (getch() != 13)
        ;

    system("cls");
    printf("\n实验共测量的油滴数量 n = ");
    scanf("%d", &number_e);
    printf("\n每个油滴下降时间测量次数 n = ");
    scanf("%d", &number_t);
again:
    system("cls");
    Print_menu();
    puts("\n---------------------------------------------------------------------------------------------------------------");
    printf("\n键入a可继续输入，键入b可进行修改，键入c可查看最终计算数据");

    switch (getch())
    {
    case 'a':
        if (number_e_h < number_e)
        {
            Data_add(number_e_h);
            number_e_h++;
        }
        else
        {
            puts("\n数据溢出");
            system("pause");
        }
        break;
    case 'b':
        Data_revise();
        break;
    case 'c':
        Data_calculate();
        break;
    }
    goto again;
}

void Data_calculate(void)
{
    int i;
    double Q_all = 0, h1 = 0, h2 = 0, Q_average, q_average, num_average, deviation_all, jj, num_all = 0;
    for (i = 0; i < number_e_h; i++)
    {
        Q_all = Q_all + Q[i];
        num_all = num_all + num[i];
        h1 = h1 + Q[i] * num[i];
        h2 = h2 + num[i] * num[i];
    }
    Q_average = Q_all / number_e_h;
    num_average = num_all / number_e_h;
    q_average = (h1 - number_e_h * Q_average * num_average) / (h2 - number_e_h * num_average * num_average);
    jj = Q_average - q_average * num_average;
    deviation_all = fabs((q_average - e) / e);
    puts("\n---------------------------------------------------------------------------------------------------------------");
    printf("根据线性回归方程计算\n平均电荷量(斜率)e = %11.4e\n截距 = %11.4e\n相对误差 = %5.2f%%", q_average, jj, 100 * deviation_all);
    system("pause");
}

void Data_analysis(int n)
{
    int i = 0;
    double tgh = 0, a;
    for (i = 0; i < number_t; i++)
    {
        tgh += t[n][i];
    }
    tg[n] = tgh / number_t;
    v[n] = l / tg[n];
    a = sqrt((9 * ETA * l) / (2 * DENSITY * g * tg[n]));
    Q[n] = ((18 * Pi * d) / (U[n] * sqrt(2 * DENSITY * g))) * pow((ETA * l) / (tg[n] * (1 + (b / (p * a)))), 1.5);
    q1[n] = Q[n] / e;
    num[n] = (int)(q1[n]);
    if (q1[n] - num[n] > 0.49)
        num[n]++;
    q1[n] = Q[n] / num[n];
    deviation[n] = fabs(((q1[n] - e) / e));
}

void Data_add(int n)
{
    int i = 0;
    puts("\n---------------------------------------------------------------------------------------------------------------");
    printf("当前为第%02d组:", n + 1);
    printf("\n请输入平衡电压(单位V) U = ");
    scanf("%lf", &U[n]);
    for (i = 0; i < number_t; i++)
    {
        printf("第%d次测量下降时间(单位s) t%d = ", i + 1, i + 1);
        scanf("%lf", &t[n][i]);
    }
    Data_analysis(n);
}

void Data_revise(void)
{
    int number_revise = 0;
    puts("\n---------------------------------------------------------------------------------------------------------------");

    printf("你想修改第几组数据 n = ");
    fflush(stdin);
    scanf("%d", &number_revise);
    if (number_revise > number_e)
        return;
    Data_add(number_revise - 1);
    Data_analysis(number_revise - 1);
}

void Print_menu(void)
{
    printf("共有%d组数据,当前已输入%d组数据\n", number_e, number_e_h);
    puts("---------------------------------------------------------------------------------------------------------------");
    Print_tab();
    // puts("          U     t1    t2    t3    t4    t5   t(平均)    v(平均)      Q(总电荷)   n(电子数)  q(平均电荷)   误差");
    Print_text();
    // puts("\n第 1组: 220.1  20.1  20.2  20.3  20.4  20.5   20.3    6.8182e-005   4.0459e-019      04     1.3486e-019  15.82%");
}

void Print_text(void)
{
    int i = 0, j = 0;
    for (i = 0; i < number_e_h; i++)
    {
        printf("\n第%02d组: %5.1f ", i + 1, U[i]);
        for (j = 0; j < number_t; j++)
        {
            printf(" %4.1f ", t[i][j]);
        }
        printf("  %4.1f    %11.4e   %11.4e    %4d     %11.4e  %5.2f%%", tg[i], v[i], Q[i], num[i], q1[i], 100 * deviation[i]);
    }
}

void Print_tab(void)
{
    int i = 0;
    printf("          U   ");
    for (i = 0; i < number_t; i++)
    {
        printf("  t%d  ", i + 1);
    }
    printf(" t(平均)    v(平均)      Q(总电荷)   n(电子数)  q(平均电荷)   误差\n");
}

void Print_instructions(void)
{
    puts("\n\n\n版本 V3.0 ,github地址:https://github.com/hustarbor/Millikan-experimental-calculator");
    puts("---------------------------------------------------------------------------------------------------------------");
    puts("使用说明：");
    puts("   1.本软件主要适用于华中科技大学大学物理实验密里根油滴实验；");
    puts("   2.本实验采用平衡电压+自由落体时间测量,其中平衡电压仅测量1次,部分学校采用上升时间测量的不在本软件适用范围;");
    puts("   3.本软件所使用常数为华中科技大学密里根油滴实验（2015）所用常数,其中g=9.795，请查看其它常数是否与实验一致;");
    puts("   4.本软件采用表格设计,若出现换行问题请增大窗口大小，若出现排版不正常请换用等距字体并采用偶数字号,推荐等距更纱黑体");
    puts("     下载地址(建议下载sarasa-gothic-ttc):https://github.com/be5invis/Sarasa-Gothic/releases");
    puts("     解压后安装到系统,win32窗口更换字体方法自行百度;");
    puts("   5.如果实在不想使用表格排版可以使用老版本 V2.1;");
    puts("---------------------------------------------------------------------------------------------------------------");
    puts("\n\n\nEnter键继续");
}
