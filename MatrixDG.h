#ifndef MATRIXDG_H
#define MATRIXDG_H
#include "Complex.h"
#include "Edge.h"
#include "Vexs.h"
#define MAX 100
class MatrixDG
{
    Vexs vexs[MAX];
    int NumVexs;
    int NumEdge;
    int NumUs;
    double Omega;
    Edge Matrix[MAX][MAX];           //定义邻接矩阵
    Complex SourceVoltage[MAX][MAX];  //定义电压源矩阵
    Complex SourceCurrent[MAX][MAX];  //定义电流源矩阵
public:
     MatrixDG(int numV=0, int numE=0, Complex cur=Complex(0,0),Complex res=Complex(DBL_MAX,0) ,Complex v=Complex(0,0)){
        NumVexs=numV;
        NumEdge=numE;
        NumUs=0;
        for(int i=0;i<MAX;i++)
        {
            for(int j=0;j<MAX;j++)
            {
                SourceVoltage[i][j]=Complex(0,0);
                SourceCurrent[i][j]=Complex(0,0);
            }
        }
     };                    //初始化矩阵
     void insertVexs(Complex v=Complex(0,0)){
        NumVexs++;
        vexs[NumVexs-1].setvalue(v);
        vexs[NumVexs-1].settrue();
     };                            //插入一个新顶点
     int getNumV(){
        return NumVexs;
     };
     void iniGauss();                //初始化高斯矩阵
     void iniOmega(double x=0);
     void insertEdge(int a, int b, Complex cur=Complex(0,0), Complex res=Complex(DBL_MAX,0));      //插入ab之间的弧
     void insertC(int a,int b,double C);               //插入一个电容
     void insertL(int a, int b, double L);             //插入一个电感
     void insertUs(int a,int b,Complex Us);            //插入一个从a指向b的电压源
     void insertIs(int a,int b,Complex Is);            //插入一个从a指向b的电流源
     void deleteUs(int a,int b,Complex Us);            //删除从a指向b的电压源
     void deleteIs(int a,int b,Complex Is);            //删除从a指向b的电流源
     void deleteVexs(int a);                           //删除一个顶点
     void deleteEdge(int a, int b);                           //删除从a到b的弧
     void print();                //打印出矩阵
     Complex getcur(int a, int b);    //获得从a到b的电流值
     Complex getres(int a, int b);    //获得从a到b的电阻值
     Complex getV(int a);    //获得节点a的电压
     void solGauss();               //高斯消元法求解方程
     void printgauss();           //打印出高斯消元矩阵
     void Display();              //展示所有节点及电流
};
#endif