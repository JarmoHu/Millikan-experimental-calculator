/* miligen2.1.cpp */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Pi 3.1415926	//定义圆周率的取值
#define DENSITY 981		//油滴的密度
#define b (6.17e-6)		//粘滞系数修正常数
#define g 9.795			//重力加速度
#define d 5e-3			//极板间距离
#define l (1.5e-3)		//油滴匀速上升或下降的距离
#define p 76			//大气压强
#define e 1.6021765e-19 //元电荷
#define ETA (1.83e-5)   //粘滞系数

int main(void)
{
	printf("本程序系百度华中科技大学吧“Kevin170113664”用户所发布的程序改编而来，若有任何疑问请联系QQ：609953934\n版本V2.1\n---------------------------------------------------\n");
	float U, tg, a, q1, tgh, nj, nz;
	double jj, qj, qz, ej, h1, h2, x1, x2;
	int i, n1, j, n2;

	printf("请输入你需要计算的数据组数和每组数据个数,并以空格分隔：\n");
	scanf("%d%d", &n1, &n2);
	puts("---------------------------------------------------\n");

	float q[20], t[20];
	int n[20];

	printf("请依次输入U和t的测量数值，并以空格隔开，并且不需要输入时间数值的小数点，可按顺序一次输入全部数据\n");
	qj = 0;
	nj = 0;
	qz = 0;
	nz = 0;
	h1 = 0;
	h2 = 0;
	jj = 0;

	for (i = 0; i < n1; i++)
	{
		printf("请输入电压值U和时间tg：\n");
		scanf("%f", &U);
		tg = 0;
		tgh = 0;
		for (j = 1; j <= n2; j++)
		{
			scanf("%f", &t[j]);
			tgh = tgh + t[j];
		}
		tg = tgh / n2;
		tg *= 0.1;
		a = sqrt((9 * ETA * l) / (2 * DENSITY * g * tg));
		q[i] = ((18 * Pi * d) / (U * sqrt(2 * DENSITY * g))) * pow((ETA * l) / (tg * (1 + (b / (p * a)))), 1.5);
		q1 = q[i] / e;
		n[i] = (int)q1;
		if (q1 - n[i] > 0.49)
			n[i]++;
		q1 = q[i] / n[i];
		x1 = fabs(((q1 - e) / e));
		printf("第%d组\n平均时间：%4.2f\n平均速度：%e\n总电荷值：%e\n电子数：%d\n电子平均电荷值：%e\n与元电荷的误差：%3.2f%%\n\n", i + 1, tg, l / tg, q[i], n[i], q1, 100 * x1);
		qz = qz + q[i];
		nz = nz + n[i];
		h1 = h1 + q[i] * n[i];
		h2 = h2 + n[i] * n[i];
	}

	qj = qz / n1;
	nj = nz / n1;
	ej = (h1 - n1 * qj * nj) / (h2 - n1 * nj * nj);
	jj = qj - ej * nj;
	x2 = fabs((ej - e) / e);

	printf("最终结果\ne的计算结果：%e\n回归方程：q=%e *n + %e \n相对误差：%3.2f%%\n\n", ej, ej, jj, 100 * x2);
	printf("计算结束，按任意键退出\n");
	system("pause");
	return 0;
}
