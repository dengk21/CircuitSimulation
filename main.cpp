#include <iostream>
#include <float.h>
#include <cmath>
#include "Complex.h"
#include "Vexs.h"
#include "Edge.h"
#include "MatrixDG.h"
#define RES_MIN 0.000001
using namespace std;
Complex gauss[MAX][MAX]={Complex(0,0)};
int main(){
    MatrixDG matrix_1;
    matrix_1.insertVexs();
    matrix_1.insertVexs();
    matrix_1.insertVexs();
    matrix_1.insertVexs();
    matrix_1.insertVexs();
    matrix_1.insertUs(1,2,Complex(180,0));
    matrix_1.insertUs(5,1,Complex(240,0));
    matrix_1.insertEdge(2,3,Complex(0,0),Complex(20000,0));
    matrix_1.insertEdge(1,3,Complex(0,0),Complex(40000,0));
    matrix_1.insertEdge(3,4,Complex(0,0),Complex(10000,0));
    matrix_1.insertEdge(1,4,Complex(0,0),Complex(20000,0));
    matrix_1.insertEdge(4,5,Complex(0,0),Complex(40000,0));
    matrix_1.iniGauss();
    //matrix_1.printgauss();
    matrix_1.solGauss();
    matrix_1.Display();
    return 0;
};