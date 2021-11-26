//Author:绫雪 时间:2021/11/26 邮箱:2239301685@qq.com/yaolin6666@gmail.com 
//操作系统实验作业:资源分配算法(五进程3资源)
//银行家算法 安全性算法实现
#include <iostream>
#include<cstring>
#include<algorithm>
#include<windows.h>
class Resources {
public:char name[20];
      int A;
      int B;
      int C;
      bool flag1;                                                                           //操作标志位
      bool flag2;                                                                           //安全型算法标志位
      Resources(void);
      Resources(char n[20]);
      Resources(char n[5], int a, int b, int c);
      void set(int a, int b, int c);
      Resources operator+(const Resources& b)
      {
          Resources temp;
          strcpy_s(temp.name, this->name);
          temp.A = this->A + b.A;
          temp.B = this->B + b.B;
          temp.C = this->C + b.C;
          return temp;
      };
      Resources operator-(const Resources& b)
      {
          Resources temp;
          strcpy_s(temp.name, this->name);
          temp.A = this->A - b.A;
          temp.B = this->B - b.B;
          temp.C = this->C - b.C;
          return temp;
      };
      bool operator<(const Resources& b)                                                    
      {
          if (this->A < b.A && this->B < b.B && this->C < b.C)
              return true;
          else
              return false;
      };                                           
                                                                                            //'<'有需求时进行重载(有需求使用)
};                                                                                          //对于资源使用类 而非数组表示 同时重载各类所需运算符
Resources::Resources(void)
{
    strcpy_s(name, "NULL");
    A = 0, B = 0, C = 0;
    flag1 = false, flag2 = false;
}
Resources::Resources(char n[20])
{
    strcpy_s(name, n);
    A = 0, B = 0, C = 0;
    flag1 = false, flag2 = false;
}
Resources::Resources(char n[20], int a, int b, int c)
{
    strcpy_s(name, n);
    A = a, B = b, C = c;
    flag1 = false, flag2 = false;
}
/*构造函数*/
void Resources::set(int a, int b, int c)
{
    A = a, B = b, C = c;
}
using namespace std;

void securityCheck(Resources avi, Resources PT[5], Resources A[5],Resources N[5],Resources Req)           
{
    int flag=0,Temp[5] = {0,0,0,0,0},count=0,j=1;
    Resources workCout[6];
    Resources work;
    work = avi;
    workCout[0] = work;
    while (true)
    {
        count = 0;
        //cout << count << endl;
        for (int i = 0; i < 5; (i++)%5)                         //安全型算法执行
        {
            
            //cout << count << endl;
            if (N[i].A <= work.A && N[i].B <= work.B && N[i].C <= work.C && N[i].flag2 == false)
            {
                work = work + A[i];
                workCout[j] = work;
                j++;
                PT[i].flag2 = true,N[i].flag2=true;
                Temp[flag] = i;
                flag++;
                break;
            }
            count++;                                        //计数在未发现符合条件且为满足安全条件时退出
            
            if (count > 10)
            {
                cout << count << endl;
                break;
            }
            if (flag == 5)
                break;
        }
        cout << count+1 << endl;
        if (count > 10)
        {
            cout <<"System Insecurity"<<endl << Req.name << " can't get resources immediately" << endl;
            break;
        }
        if (flag == 5)
            break;
    }
}

int main()
{
    int size = 5,cursor=-1;                                                                           //用于完善程序通用性
    int MenuN=0;
    bool flag = false;
    char AviName[20] = "availabe";
    Resources availabe(AviName, 3, 3, 2);
    char Np[5][20] = { "p0", "p1", "p2", "p3", "p4" };
    Resources P[5],Allocation[5],Need[5];
    Resources Reqtest(Np[4], 3, 3, 0);
    for (int i = 0; i < size; i++)
    {
        Resources Temp(Np[i]);
        P[i] = Temp;
        Allocation[i] = Temp;
        Need[i] = Temp;
    }
    {
        P[0].set(7, 5, 3), P[1].set(3, 2, 2), P[2].set(9, 0, 2), P[3].set(2, 2, 2), P[4].set(4, 3, 3);
        Allocation[0].set(0, 1, 0), Allocation[1].set(2, 0, 0), Allocation[2].set(3, 0, 2), Allocation[3].set(2, 1, 1), Allocation[4].set(0, 0, 2);
        for (int i = 0; i < size; i++)
        {
            Need[i] = P[i] - Allocation[i];
        }

        for (int i = 0; i < 5; i++)
        {
            if (strcmp(P[i].name, Reqtest.name) == 0)
            {
                cursor = i;
                flag = true;
                break;
            }
        }
        if (flag)
        {
            if (availabe.A < Reqtest.A && availabe.B < Reqtest.B && availabe.C < Reqtest.C)
                cout << "资源总量不足" << endl;
            else if (Need[cursor].A < Reqtest.A && Need[cursor].B < Reqtest.B && Need[cursor].C < Reqtest.C)
                cout << "请求总量大于剩余所需" << endl;
            else
            {
                availabe = availabe - Reqtest, Need[cursor] = Need[cursor] - Reqtest, Allocation[cursor] = Allocation[cursor] + Reqtest;
            }
        }
        else
        {
            cout << "Progress " << Reqtest.name << " Not found" << endl;
            exit(0); 
        }
    }                                                                                      //资源初始化
    /*for (int i = 0; i < 5; i++)
        cout << Need[i].A << Need[i].B << Need[i].C << endl;*/
    securityCheck(availabe, P, Allocation, Need, Reqtest);
                                                                                       
    /*while (true)
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
    }*/
    cout << "Hello World!\n";
}