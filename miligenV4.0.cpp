#include <iostream>
#include <iomanip>
#include <vector>
#include <conio.h>
#include <cmath>

#define keyboard_enter 13            //定义Enter键值
#define Pi 3.14159265358979323846    //定义圆周率的取值
#define E_MAX 20                     //最大测量电子数，若不够可以修改
#define T_MAX 10                     //最大测量时间数，若不够可以修改
#define experiment_e (1.6021765e-19) //元电荷

using namespace std;

class miligen; //声明结构体

void Print_instructions(void); //打印声明数据
void Print_menu(void);         //打印菜单，包括表格标签和数据
void Print_tab(void);          //打印表格标签
void Data_revise(void);        //修改数据
void Data_delete(void);        //删除数据
void Data_insert(void);        //插入数据
void Data_calculate(void);     //根据已输入数据进行回归计算
void Paramenter_revise(void);  //参数矫正

int number_t = 0;                  //每组油滴下降时间测量次数
double experiment_b = (6.17e-6);   //粘滞系数修正常数
double experiment_g = 9.795;       //重力加速度
double experiment_d = 5e-3;        //正负极板间距离
double experiment_l = (1.5e-3);    //油滴匀速上升或下降的距离
double experiment_p = 76;          //大气压强
double experiment_DENSITY = 981;   //油滴的密度
double experiment_ETA = (1.83e-5); //粘滞系数

vector<miligen> miligen_vec; //创建油滴向量容器空间

int main(void)
{
    //system("chcp 65001");
    Print_instructions(); //打印说明
    while (getch() != keyboard_enter)
        ;
    Paramenter_revise(); //矫正参数

again0:
    cout << "\n每个油滴下降时间测量次数 n = "; //输入每组油滴测量次数
    cin >> number_t;

again1:
    system("cls");
    Print_menu(); //打印菜单
    cout << "\n---------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\b输入数字进入指定功能" << endl
         << "1:增加数据      2:修改数据      3:删除数据" << endl
         << "4:插入数据      5:修改常数      6:回归计算" << endl
         << "7:修改每组油滴测量次数(会清除数据)" << endl;
    cout << "---------------------------------------------------------------------------------------------------------------" << endl;
    switch (getch()) //读取功能
    {
    case '1':
        miligen_vec.emplace_back(miligen_vec.size() + 1);
        break;
    case '2':
        Data_revise();
        break;
    case '3':
        Data_delete();
        break;
    case '4':
        Data_insert();
        break;
    case '5':
        Paramenter_revise();
        break;
    case '6':
        Data_calculate();
        break;
    case '7':
        miligen_vec.clear();
        goto again0;
        break;
    }
    goto again1;

    return 0;
}

class miligen
{
  private:
    /* data */
  public:
    miligen(int num_e);       //输入数据
    void Data_analysis(void); //数据分析
    void Print_text(void);    //打印数据

    /*
        U:电压
        tg:平均时间
        v:平均速度
        Q:总电荷
        q_e:该油滴元电荷数量
        deviation:计算误差
        num:该油滴元电荷数量
        t:下降时间，以向量表示
    */

    double U, tg = 0, v, Q, q_e, deviation;

    int num;
    vector<double> t;
};

miligen::miligen(int num_e) //输入数据
{
    int i = 0;
    double temp;
    cout << "当前为第" << num_e << "组:" << endl;
    cout << "请输入平衡电压(单位V) U = ";
    cin >> U;

    for (i = 0; i < number_t; i++)
    {
        cout << "第" << (i + 1) << "次测量下降时间(单位s) t" << (i + 1) << " = ";
        cin >> temp;
        t.push_back(temp);
        tg += temp;
    }

    tg = tg / number_t;

    Data_analysis();
}

void miligen::Data_analysis(void) //数据分析
{
    double a;
    v = experiment_l / tg;
    a = sqrt((9 * experiment_ETA * experiment_l) / (2 * experiment_DENSITY * experiment_g * tg));
    Q = ((18 * Pi * experiment_d) / (U * sqrt(2 * experiment_DENSITY * experiment_g))) * pow((experiment_ETA * experiment_l) / (tg * (1 + (experiment_b / (experiment_p * a)))), 1.5);
    num = round(Q / experiment_e);

    q_e = Q / num;
    deviation = fabs(((q_e - experiment_e) / experiment_e));
}

void miligen::Print_text(void) //打印数据
{
    int i;
    cout << setiosflags(ios::left) << setiosflags(ios::fixed) << setprecision(1) << setw(7) << U;
    for (i = 0; i < number_t; i++)
    {
        cout << setprecision(1) << setw(6) << t[i];
    }
    cout << setprecision(1) << setw(9) << tg << resetiosflags(ios::fixed);
    cout << setiosflags(ios::scientific) << setprecision(4) << setw(13) << v;
    cout << setprecision(4) << setw(13) << Q << resetiosflags(ios::scientific);
    cout << setw(11) << num;
    cout << setiosflags(ios::scientific) << setprecision(4) << setw(14) << q_e << resetiosflags(ios::scientific) << resetiosflags(ios::left);
    cout << setiosflags(ios::right) << setiosflags(ios::fixed) << setprecision(2) << setw(5) << deviation * 100 << resetiosflags(ios::right) << "%" << resetiosflags(ios::fixed);
}

void Print_menu(void) //打印菜单，包括表格标签和数据
{
    int i;
    cout << "当前已输入" << miligen_vec.size() << "组数据,每组油滴测量" << number_t << "次" << endl;
    cout << "---------------------------------------------------------------------------------------------------------------" << endl;
    Print_tab();
    for (i = 0; i < int(miligen_vec.size()); i++)
    {
        cout << "\n第" << setfill('0') << setw(2) << (i + 1) << "组: " << setfill(' ');
        miligen_vec[i].Print_text();
    }
}

void Print_tab(void) //打印表格标签
{
    int i;
    cout << "        U      ";
    for (i = 0; i < number_t; i++)
    {
        cout << "t" << (i + 1) << "    ";
    }
    cout << "t(平均)  v(平均)      Q(总电荷)    n(电子数)  q(平均电荷)     误差";
}

void Print_instructions(void) //打印声明数据
{
    cout << "版本 V4.0 ,github地址:https://github.com/hustarbor/Millikan-experimental-calculator" << endl;
    cout << "---------------------------------------------------------------------------------------------------------------" << endl;
    cout << "使用说明：" << endl;
    cout << "   1.本软件主要适用于华中科技大学大学物理实验密里根油滴实验；" << endl;
    cout << "   2.本实验采用平衡电压+自由落体时间测量,其中平衡电压仅测量1次,部分学校采用上升时间测量的不在本软件适用范围;" << endl;
    cout << "   3.V4.0版本支持常用常数修改，可兼容更多高校的实验;" << endl;
    cout << "   4.本软件采用表格设计,若出现换行问题请增大窗口大小，若出现排版不正常请换用等距字体并采用偶数字号,推荐等距更纱黑体" << endl;
    cout << "     下载地址(建议下载sarasa-gothic-ttc):https://github.com/be5invis/Sarasa-Gothic/releases" << endl;
    cout << "     解压后安装到系统,win32窗口更换字体方法自行百度;" << endl;
    cout << "   5.如果实在不想使用表格排版可以使用老版本 V2.1;" << endl;
    cout << "---------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\nEnter键继续";
}

void Data_revise(void)
{
    int number_revise = 0;

    cout << "你想修改第几组数据 n = ";
    fflush(stdin);
    cin >> number_revise;
    if (number_revise > int(miligen_vec.size()))
        return;
    miligen_vec.erase(miligen_vec.begin() + number_revise - 1);
    miligen_vec.emplace(miligen_vec.begin() + number_revise - 1, number_revise);
}

void Data_delete(void)
{
    int number_delete = 0;

    cout << "你想删除第几组数据 n = ";
    fflush(stdin);
    cin >> number_delete;
    if (number_delete > int(miligen_vec.size()))
        return;
    miligen_vec.erase(miligen_vec.begin() + number_delete - 1);
}

void Data_insert(void)
{
    int number_insert = 0;

    cout << "你想删除第几组数据 n = ";
    fflush(stdin);
    cin >> number_insert;
    if (number_insert > int(miligen_vec.size()))
        return;
    miligen_vec.emplace(miligen_vec.begin() + number_insert - 1, number_insert);
}

void Data_calculate(void)
{
    unsigned int i, number_e = miligen_vec.size();
    double Q_all = 0, h1 = 0, h2 = 0, Q_average, q_average, num_average, deviation_all, intercept, num_all = 0;
    for (i = 0; i < number_e; i++)
    {
        Q_all = Q_all + miligen_vec[i].Q;
        num_all = num_all + miligen_vec[i].num;
        h1 = h1 + miligen_vec[i].Q * miligen_vec[i].num;
        h2 = h2 + miligen_vec[i].num * miligen_vec[i].num;
    }
    Q_average = Q_all / number_e;
    num_average = num_all / number_e;
    q_average = (h1 - number_e * Q_average * num_average) / (h2 - number_e * num_average * num_average);
    intercept = Q_average - q_average * num_average;
    deviation_all = fabs((q_average - experiment_e) / experiment_e);
    cout << "根据线性回归方程计算" << endl
         << "平均电荷量(斜率)e =" << setiosflags(ios::scientific) << q_average << endl
         << "截距 =" << intercept << resetiosflags(ios::scientific) << endl
         << "相对误差 = " << 100 * deviation_all << "%" << endl;
    system("pause");
}

void Paramenter_revise(void)
{
again2:
    system("cls");
    cout << setiosflags(ios::left);
    cout << "1.  b          " << setw(10) << experiment_b << "         粘滞系数修正常数" << endl;
    cout << "2.  g          " << setw(10) << experiment_g << "m/(s^2)  重力加速度" << endl;
    cout << "3.  d          " << setw(10) << experiment_d << "m        正负极板间距离" << endl;
    cout << "4.  l          " << setw(10) << experiment_l << "m        油滴匀速上升或下降的距离" << endl;
    cout << "5.  p          " << setw(10) << experiment_p << "cm       大气压强(汞柱高度)" << endl;
    cout << "6.  DENSITY    " << setw(10) << experiment_DENSITY << "Kg/(m^3) 油滴的密度" << endl;
    cout << "7.  ETA        " << setw(10) << experiment_ETA << "         粘滞系数" << endl;
    cout << resetiosflags(ios::left);
    cout << "\n---------------------------------------------------------------------------------------------------------------\n";
    cout << "输入参数标号可修改参数，Enter键确定参数设置,0恢复默认值" << endl;

    fflush(stdin);
    switch (getch())
    {
    case '0':
        experiment_b = (6.17e-6);   //粘滞系数修正常数
        experiment_g = 9.795;       //重力加速度
        experiment_d = 5e-3;        //正负极板间距离
        experiment_l = (1.5e-3);    //油滴匀速上升或下降的距离
        experiment_p = 76;          //大气压强
        experiment_DENSITY = 981;   //油滴的密度
        experiment_ETA = (1.83e-5); //粘滞系数
        break;
    case '1':
        cout << "b = ";
        cin >> experiment_b;
        break;
    case '2':
        cout << "g = ";
        cin >> experiment_g;
        break;
    case '3':
        cout << "d = ";
        cin >> experiment_d;
        break;
    case '4':
        cout << "l = ";
        cin >> experiment_l;
        break;
    case '5':
        cout << "p = ";
        cin >> experiment_p;
        break;
    case '6':
        cout << "DENSITY = ";
        cin >> experiment_DENSITY;
        break;
    case '7':
        cout << "ETA = ";
        cin >> experiment_ETA;
        break;
    case keyboard_enter:
        return;
        break;
    }

    goto again2;
}
