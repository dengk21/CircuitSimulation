#ifndef EDGE_H
#define EDGE_H
#include "Complex.h"
class Edge
{
    Complex Current;
    Complex Resis;
    int count;
public:
     Edge(Complex x=Complex(DBL_MAX,DBL_MAX), Complex y=Complex(0,0)){
     Current=y;
     Resis=x;
     count=0;
};;
     ~Edge(){};
     void setvalue(Complex cur=Complex(0,0),Complex res=(DBL_MAX,DBL_MAX)){
        Current=cur;
        Resis=res;
     };
     Complex showres(){
        return Resis;
     };
     void addcount(){
        count++;
     };
     void subcount(){
        count--;
     };
     int showcount(){
        return count;
     };
     Complex showcur(){
        return Current;
     };
     void changeCur(Complex cur){
        Current=cur;
     };
};
#endif