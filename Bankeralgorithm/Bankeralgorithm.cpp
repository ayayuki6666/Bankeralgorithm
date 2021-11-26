//Author:绫雪 时间:2021/11/26 邮箱:2239301685@qq.com/yaolin6666@gmail.com 
//操作系统实验作业:资源分配算法(五进程3资源)
//银行家算法 安全性算法实现
#include <iostream>
#include<cstring>
#include<algorithm>
#include<windows.h>
using namespace std;
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
void securityCheck(Resources avi, Resources PT[5], Resources A[5],Resources N[5],Resources Req)           
{
    int flag=0,Temp[5] = {0,0,0,0,0},count=0,j=1;
    Resources workCout[6];
    Resources work;
    work = avi;
    workCout[0] = work;
    int i = 0;                              //i=0位置影响最终顺序
    while(true)
    {
        count = 0;
        for (;;)                         //安全型算法执行
        {
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
            count++;
            if (flag == 5)
                break;
            if (count > 10)
                break;
            i = (i+1) % 5;
        }
        if (count > 10)
        {
            cout << "SYSTEM INSECURITY" << endl;
            if(strcmp(Req.name,"NULL")!=0)
                cout << Req.name << " CAN'T GET RESOURCES IMMEDIATELY" << endl;
            break;
        }
        if (flag == 5)
        {
                cout << "Name\t\tWork\t\tNeed\t\tAllocation\t\tWork+Allocation\t\tFinish" << endl;
                for(int i=0;i<5;i++)
                {
                    cout << PT[Temp[i]].name << "\t\t" << workCout[i].A << "  " << workCout[i].B << "  " << workCout[i].C << "  ";
                    cout << "\t" << N[Temp[i]].A << "  " << N[Temp[i]].B << "  " << N[Temp[i]].C << "  ";
                    cout << "\t" << A[Temp[i]].A << "  " << A[Temp[i]].B << "  " << A[Temp[i]].C << "  ";
                    cout << "\t\t" << workCout[i+1].A << "  " << workCout[i+1].B << "  " << workCout[i+1].C << "  ";
                    if (PT[Temp[i]].flag2)
                        cout << "\t\tT" << endl;
                    else
                        cout << "\t\tF" << endl;
                    
                }
                cout << "SYSTEM SECURITY!!!!"<<endl;
            break;
        }
    }
}
int main()
{
    int size = 5,cursor=-1;                                                                           //用于完善程序通用性
    int MenuN=0;
    bool flag = false;
    char AviName[20] = "availabe";
    char Te[5] = "NULL";
    char T[20],Tbeta[20];
    int Tn[6];
    Resources P[5],Allocation[5],Need[5],Reqtest,availabe(AviName);
    cout << "Input the amount of resource (maximum,allocated) of each customer" << endl;
    for (int i = 0; i < 5; i++)
    {
        cin >> T >> Tn[0] >> Tn[1] >> Tn[2] >> Tn[3] >> Tn[4] >> Tn[5];
        Resources A(T, Tn[0], Tn[1], Tn[2]);
        Resources B(T, Tn[3], Tn[4], Tn[5]);
        P[i] = A,Allocation[i]=B,Need[i]=A-B;
    }
    cout << "Input the amount of resources(available)" << endl;
    cin >> Tn[0] >> Tn[1] >> Tn[2];
    availabe.set(Tn[0], Tn[1], Tn[2]);
    while (true)
    {
        cout << "1:judge the system security" << endl << "2:judge the request security" << endl << "3:exit" << endl;
        cin >> MenuN;
        if (MenuN == 1)
        {
            Resources Temp(Te);
            Reqtest = Temp;
            securityCheck(availabe, P, Allocation, Need, Reqtest);
            break;
        }
        else if (MenuN == 2)
        {
            cout << "Please input the customer's name and request"<<endl;
            cin >> Tbeta >> Tn[0] >> Tn[1] >> Tn[2];
            Resources Temp(Tbeta);
            Reqtest = Temp;
            Reqtest.set(Tn[0], Tn[1], Tn[2]);
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
                    cout << "INSUFFICIENT AVAILABLE RESOURCES" << endl;
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
            securityCheck(availabe, P, Allocation, Need, Reqtest);
            break;
        }
        else if (MenuN == 3)
        {
            break;
        }
        else
            cout << "input error" << endl;
    }
}