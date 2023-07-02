#ifndef VEXS_H
#define VEXS_H
#include "Complex.h"
class Vexs
{
    Complex Voltage;
    bool judge;
public:
    Vexs(double x = 0,double y=0){
    Voltage=Complex(x,y);
};
    ~Vexs(){};
    void setvalue(double x,double y){
        Voltage=Complex(x,y);
    };
    void setvalue(Complex x){
        Voltage=x;
    };
    void settrue(){
        judge=true;
    };
    void setfalse(){
        judge=false;
    };
    bool Judge(){
        return judge;
    };
    Complex showvoltage(){
        return Voltage;
    };
};
#endif