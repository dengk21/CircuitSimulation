#ifndef COMPLEX_H
#define COMPLEX_H
#include <iostream>
#include <float.h>
#include <cmath>
using namespace std;
#define Pi 3.1415926
class Complex{
    double Real,Image;
public:
    Complex(double x=0,double y=0){
        Real=x;
        Image=y;
    };
    ~Complex(){};
    string Show(){
        return to_string(Real)+'+'+to_string(Image)+"i";
    };
    string ShowArg(){
        return to_string(sqrt(Real*Real+Image*Image))+"∠ "+to_string(atan2(Image,Real)*180/Pi)+"°";
    };
    double real(){
        return Real;
    };
    double image(){
        return Image;
    };
    void Display(){
        cout<<Real<<"+"<<Image<<"i";
    };
    void ChangeValue(double x,double y){
        Real=x;
        Image=y;
    };
    Complex operator +(Complex &x)
    {
        Complex y;
		y.Real=Real+x.Real;
		y.Image=Image+x.Image;
		return y;
    };
    Complex operator +(const Complex &x)
    {
        Complex y;
		y.Real=Real+x.Real;
		y.Image=Image+x.Image;
		return y;
    };
    Complex operator +(double &x)
    {
        Complex y;
		y.Real=Real+x;
		y.Image=Image;
		return y;
    };
    Complex operator +(int &x)
    {
        Complex y;
		y.Real=Real+x;
		y.Image=Image;
		return y;
    };
    Complex operator -(double &x)
    {
        Complex y;
		y.Real=Real-x;
		y.Image=Image;
		return y;
    };
    Complex operator -(int &x)
    {
        Complex y;
		y.Real=Real-x;
		y.Image=Image;
		return y;
    };
    bool operator !=(Complex &x)
    {
        if(Real==x.Real&&Image==x.Image)
        return false;
        else
        return true;
    };
    bool operator !=(const Complex &x)
    {
        if(Real==x.Real&&Image==x.Image)
        return false;
        else
        return true;
    };
    bool operator ==(Complex &x)
    {
        if(Real==x.Real&&Image==x.Image)
        return true;
        else
        return false;
    };
    bool operator ==(const Complex &x)
    {
        if(Real==x.Real&&Image==x.Image)
        return true;
        else
        return false;
    };
    Complex operator -(Complex &x)
    {
        Complex y;
		y.Real=Real-x.Real;
		y.Image=Image-x.Image;
		return y;
    };
    Complex operator -(const Complex &x)
    {
        Complex y;
		y.Real=Real-x.Real;
		y.Image=Image-x.Image;
		return y;
    };
    Complex operator *(Complex &x)
    {
        Complex y;
		y.Real=Real*x.Real-Image*x.Image;
		y.Image=Real*x.Image+Image*x.Real;
		return y;
    };
    Complex operator *(const Complex &x)
    {
        Complex y;
		y.Real=Real*x.Real-Image*x.Image;
		y.Image=Real*x.Image+Image*x.Real;
		return y;
    };
    Complex operator /(Complex &x)
    {
        Complex y;
		y.Real=(Real*x.Real+Image*x.Image)/(x.Real*x.Real+x.Image*x.Image);
		y.Image=(Image*x.Real-Real*x.Image)/(x.Real*x.Real+x.Image*x.Image);
		return y;
    };
    Complex operator /(const Complex &x)
    {
        Complex y;
		y.Real=(Real*x.Real+Image*x.Image)/(x.Real*x.Real+x.Image*x.Image);
		y.Image=(Image*x.Real-Real*x.Image)/(x.Real*x.Real+x.Image*x.Image);
		return y;
    };
    double Norm(){
        return sqrt(Real*Real+Image*Image);
    };
    double Arg(){
        return atan2(Image,Real)*180/Pi;
    };
    void DisplayArg(){
        cout<<sqrt(Real*Real+Image*Image)<<"∠"<<atan2(Image,Real)*180/Pi<<"°";
    };
};
#endif