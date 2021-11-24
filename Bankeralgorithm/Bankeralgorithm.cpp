//Author:绫雪 时间:2021/11/20 邮箱:2239301685@qq.com/yaolin6666@gmail.com 
//操作系统实验作业:资源分配算法
//银行家算法 安全性算法实现
#include <iostream>
#include<cstring>
#include<algorithm>
#include<windows.h>
class Resources {
public:char name[5];
      int A;
      int B;
      int C;
      int D;
      int E;
      bool flag1;
      bool flag2;
      Resources(void);
      Resources(char n[5], int a, int b, int c);
      Resources(char n[5], int a, int b, int c, int d);
      Resources(char n[5], int a, int b, int c, int d, int e);
      Resources operator+(const Resources& b)
      {
          Resources temp;
          strcpy_s(temp.name, this->name);
          temp.A = this->A + b.A;
          temp.B = this->B + b.B;
          temp.C = this->C + b.C;
          temp.D = this->D + b.D;
          temp.E = this->E + b.E;
          return temp;
      };
      Resources operator-(const Resources& b)
      {
          Resources temp;
          strcpy_s(temp.name, this->name);
          temp.A = this->A - b.A;
          temp.B = this->B - b.B;
          temp.C = this->C - b.C;
          temp.D = this->D - b.D;
          temp.E = this->E - b.E;
          return temp;
      };
      bool operator<(const Resources& b)                                                    
      {
          if (this->A != b.A)
              return this->A < b.A;
          else if (this->B != b.B)
              return this->B < b.B;
          else
              return this->C < b.C;
      };                                           
                                                                                            //'<'有需求时进行重载(此处重载用于sort函数)
};                                                                                          //对于资源使用类 而非数组表示 同时重载各类所需运算符
Resources::Resources(void)
{
    strcpy_s(name, "NULL");
    A = 0, B = 0, C = 0,D=0,E=0;
    flag1 = false, flag2 = false;
}

Resources::Resources(char n[5], int a, int b, int c)
{
    strcpy_s(name, n);
    A = a, B = b, C = c;
    D = 0, E = 0;
    flag1 = false, flag2 = false;
}

Resources::Resources(char n[5], int a, int b, int c,int d)
{
    strcpy_s(name, n);
    A = a, B = b, C = c,D=d;
    E = 0;
    flag1 = false, flag2 = false;
}

Resources::Resources(char n[5], int a, int b, int c,int d,int e)
{
    strcpy_s(name, n);
    A = a, B = b, C = c,D=d,E=e;
    flag1 = false, flag2 = false;
}
using namespace std;
int main()
{
    int MenuN=0;
    while (true)
    {
        cout << "1:judge the system security" << endl << "2:judge the request security" << endl << "3:exit" << endl;
        cin >> MenuN;
        if (MenuN == 1)
        {
            //do sth
        }
        else if (MenuN == 2)
        {
            //do sth;
        }
        else if (MenuN == 3)
        {
            break;
        }
        else
            cout << "input error" << endl;
    }
    cout << "Hello World!\n";
}