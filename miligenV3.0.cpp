
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Pi 3.14159265358979323846 //����Բ���ʵ�ȡֵ
#define DENSITY 981               //�͵ε��ܶ�
#define b (6.17e-6)               //ճ��ϵ����������
#define g 9.795                   //�������ٶ�
#define d 5e-3                    //��������
#define l (1.5e-3)                //�͵������������½��ľ���
#define p 76                      //����ѹǿ
#define e 1.6021765e-19           //Ԫ���
#define ETA (1.83e-5)             //ճ��ϵ��
#define E_MAX 20                  //�������������������������޸�
#define T_MAX 10                  //������ʱ�����������������޸�

void Print_instructions(void); //��ӡ����˵��
void Print_menu(void);         //��ӡ���ݲ˵�
void Print_tab(void);          //��ӡ����ǩ
void Print_text(void);         //��ӡ�������
void Data_add(int n);          //��������
void Data_revise(void);        //�޸�����
void Data_calculate(void);     //�ع鷽�̼���
void Data_analysis(int n);     //���ݷ���

int number_e = 0, number_t = 0, number_e_h = 0, num[E_MAX];
double U[E_MAX], t[E_MAX][T_MAX], tg[E_MAX], v[E_MAX], Q[E_MAX], q[E_MAX], deviation[E_MAX], q1[E_MAX];

int main(void)
{
    system("cls");
    Print_instructions();
    while (getch() != 13)
        ;

    system("cls");
    printf("\nʵ�鹲�������͵����� n = ");
    scanf("%d", &number_e);
    printf("\nÿ���͵��½�ʱ��������� n = ");
    scanf("%d", &number_t);
again:
    system("cls");
    Print_menu();
    puts("\n---------------------------------------------------------------------------------------------------------------");
    printf("\n����a�ɼ������룬����b�ɽ����޸ģ�����c�ɲ鿴���ռ�������");

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
            puts("\n�������");
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
    printf("�������Իع鷽�̼���\nƽ�������(б��)e = %11.4e\n�ؾ� = %11.4e\n������ = %5.2f%%", q_average, jj, 100 * deviation_all);
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
    printf("��ǰΪ��%02d��:", n + 1);
    printf("\n������ƽ���ѹ(��λV) U = ");
    scanf("%lf", &U[n]);
    for (i = 0; i < number_t; i++)
    {
        printf("��%d�β����½�ʱ��(��λs) t%d = ", i + 1, i + 1);
        scanf("%lf", &t[n][i]);
    }
    Data_analysis(n);
}

void Data_revise(void)
{
    int number_revise = 0;
    puts("\n---------------------------------------------------------------------------------------------------------------");

    printf("�����޸ĵڼ������� n = ");
    fflush(stdin);
    scanf("%d", &number_revise);
    if (number_revise > number_e)
        return;
    Data_add(number_revise - 1);
    Data_analysis(number_revise - 1);
}

void Print_menu(void)
{
    printf("����%d������,��ǰ������%d������\n", number_e, number_e_h);
    puts("---------------------------------------------------------------------------------------------------------------");
    Print_tab();
    // puts("          U     t1    t2    t3    t4    t5   t(ƽ��)    v(ƽ��)      Q(�ܵ��)   n(������)  q(ƽ�����)   ���");
    Print_text();
    // puts("\n�� 1��: 220.1  20.1  20.2  20.3  20.4  20.5   20.3    6.8182e-005   4.0459e-019      04     1.3486e-019  15.82%");
}

void Print_text(void)
{
    int i = 0, j = 0;
    for (i = 0; i < number_e_h; i++)
    {
        printf("\n��%02d��: %5.1f ", i + 1, U[i]);
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
    printf(" t(ƽ��)    v(ƽ��)      Q(�ܵ��)   n(������)  q(ƽ�����)   ���\n");
}

void Print_instructions(void)
{
    puts("\n\n\n�汾 V3.0 ,github��ַ:https://github.com/hustarbor/Millikan-experimental-calculator");
    puts("---------------------------------------------------------------------------------------------------------------");
    puts("ʹ��˵����");
    puts("   1.�������Ҫ�����ڻ��пƼ���ѧ��ѧ����ʵ��������͵�ʵ�飻");
    puts("   2.��ʵ�����ƽ���ѹ+��������ʱ�����,����ƽ���ѹ������1��,����ѧУ��������ʱ������Ĳ��ڱ�������÷�Χ;");
    puts("   3.�������ʹ�ó���Ϊ���пƼ���ѧ������͵�ʵ�飨2015�����ó���,����g=9.795����鿴���������Ƿ���ʵ��һ��;");
    puts("   4.��������ñ�����,�����ֻ������������󴰿ڴ�С���������Ű治�����뻻�õȾ����岢����ż���ֺ�,�Ƽ��Ⱦ��ɴ����");
    puts("     ���ص�ַ(��������sarasa-gothic-ttc):https://github.com/be5invis/Sarasa-Gothic/releases");
    puts("     ��ѹ��װ��ϵͳ,win32���ڸ������巽�����аٶ�;");
    puts("   5.���ʵ�ڲ���ʹ�ñ���Ű����ʹ���ϰ汾 V2.1;");
    puts("---------------------------------------------------------------------------------------------------------------");
    puts("\n\n\nEnter������");
}
