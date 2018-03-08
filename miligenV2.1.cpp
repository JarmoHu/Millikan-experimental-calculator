/* miligen2.1.cpp */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Pi 3.1415926	//����Բ���ʵ�ȡֵ
#define DENSITY 981		//�͵ε��ܶ�
#define b (6.17e-6)		//ճ��ϵ����������
#define g 9.795			//�������ٶ�
#define d 5e-3			//��������
#define l (1.5e-3)		//�͵������������½��ľ���
#define p 76			//����ѹǿ
#define e 1.6021765e-19 //Ԫ���
#define ETA (1.83e-5)   //ճ��ϵ��

int main(void)
{
	printf("������ϵ�ٶȻ��пƼ���ѧ�ɡ�Kevin170113664���û��������ĳ���ı�����������κ���������ϵQQ��609953934\n�汾V2.1\n---------------------------------------------------\n");
	float U, tg, a, q1, tgh, nj, nz;
	double jj, qj, qz, ej, h1, h2, x1, x2;
	int i, n1, j, n2;

	printf("����������Ҫ���������������ÿ�����ݸ���,���Կո�ָ���\n");
	scanf("%d%d", &n1, &n2);
	puts("---------------------------------------------------\n");

	float q[20], t[20];
	int n[20];

	printf("����������U��t�Ĳ�����ֵ�����Կո���������Ҳ���Ҫ����ʱ����ֵ��С���㣬�ɰ�˳��һ������ȫ������\n");
	qj = 0;
	nj = 0;
	qz = 0;
	nz = 0;
	h1 = 0;
	h2 = 0;
	jj = 0;

	for (i = 0; i < n1; i++)
	{
		printf("�������ѹֵU��ʱ��tg��\n");
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
		printf("��%d��\nƽ��ʱ�䣺%4.2f\nƽ���ٶȣ�%e\n�ܵ��ֵ��%e\n��������%d\n����ƽ�����ֵ��%e\n��Ԫ��ɵ���%3.2f%%\n\n", i + 1, tg, l / tg, q[i], n[i], q1, 100 * x1);
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

	printf("���ս��\ne�ļ�������%e\n�ع鷽�̣�q=%e *n + %e \n�����%3.2f%%\n\n", ej, ej, jj, 100 * x2);
	printf("�����������������˳�\n");
	system("pause");
	return 0;
}
