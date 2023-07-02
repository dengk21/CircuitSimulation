#include "Complex.h"
#include "MatrixDG.h"
#include "Vexs.h"
#include "Edge.h"
extern Complex gauss[MAX][MAX];
Complex calculateDeterminant(Complex **mat,int size){
    Complex detVel =Complex(0,0);
    if(size==1)
    return mat[0][0];
    if(size==2)
    return (mat[0][0] * mat[1][1]) - (mat[0][1] * mat[1][0]);
    Complex **tempdet=new Complex *[size-1];
    for(int i=0;i<size-1;i++)
	  tempdet[i] = new Complex[size-1];
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size-1;j++)
        {
            for(int k=0;k<size-1;k++)
            {
                if(k<i)
                tempdet[j][k]=mat[j+1][k];
                else
                tempdet[j][k]=mat[j+1][k+1];
            }
        }
        detVel=detVel+mat[0][i]*(i%2 ==0 ? Complex(1,0):Complex(-1,0))*calculateDeterminant(tempdet,size-1);
    }
    for(int i=0;i<size-1;i++)
	  delete[] tempdet[i];
    delete[] tempdet;
    return detVel;
};
void MatrixDG::iniOmega(double x){
    Omega=x;
};
void MatrixDG::insertEdge(int a, int b,Complex cur, Complex res){
    if(Matrix[a-1][b-1].showres().Norm()<1.0e7)
    {
    Complex temp=(res*Matrix[a-1][b-1].showres())/(res+Matrix[a-1][b-1].showres());
    Matrix[a-1][b-1].setvalue(cur,temp);
    Matrix[a-1][b-1].addcount();
    Matrix[b-1][a-1].setvalue(Complex(0,0)-cur,temp);
    Matrix[b-1][a-1].addcount();
    }
    else
    {
    Matrix[a-1][b-1].setvalue(cur,res);
    Matrix[a-1][b-1].addcount();
    Matrix[b-1][a-1].setvalue(Complex(0,0)-cur,res);
    Matrix[b-1][a-1].addcount();
    }
}                          // 插入ab之间的弧
void MatrixDG::insertC(int a, int b, double C){
    return MatrixDG::insertEdge(a,b,Complex(0,0), Complex(0,-1/(Omega*C)));
}
void MatrixDG::insertL(int a, int b, double L){
    return MatrixDG::insertEdge(a,b,Complex(0,0), Complex(0,Omega*L));
};
void MatrixDG::deleteVexs(int a){
        for(int x=0;x<NumVexs;x++)
        {
            Matrix[a-1][x].setvalue(Complex(0,0),Complex(DBL_MAX,0));
        }
        for(int x=0;x<NumVexs;x++)
        {
            Matrix[x][a-1].setvalue(Complex(0,0),Complex(DBL_MAX,0));
        }
        vexs[a-1].setfalse();
     };                           //删除一个顶点
void MatrixDG::deleteEdge(int a, int b){
        Matrix[a-1][b-1].setvalue(Complex(0,0),Complex(DBL_MAX,0));
        Matrix[a-1][b-1].subcount();
     };                           //删除从a到b的弧
 void MatrixDG::print(){
        for(int x=0;x<NumVexs;x++)
        {
            if(vexs[x].Judge())     //已经删除的节点则跳过（但编号不改）
            {
            for(int y=0;y<NumVexs;y++)
            {
                if(vexs[y].Judge())   //已经删除的节点则跳过（但编号不改）
                {
                    /*if(Matrix[x][y].showcount()+Matrix[y][x].showcount()>2)
                    {
                        cout<<"弧数量非法，第"<<x+1<<"个顶点与第"<<y+1<<"个顶点之间的弧数量大于2"<<endl;
                        return;
                    }                  //显然在电路图中两个顶点之间只有两条有向弧，超过2条则判定为非法输入，中止程序*/
                    cout<<Matrix[x][y].showres().Show()<<' ';
                }
            }
            cout<<endl;
            }
        }                         //打印出矩阵
     };
Complex MatrixDG::getcur(int a, int b){
    return Matrix[a-1][b-1].showcur();
};                                //获取两顶点之间的电流值
Complex MatrixDG::getres(int a, int b){
    return Matrix[a-1][b-1].showres();
};                                //获取两顶点之间的电阻值
Complex MatrixDG::getV(int a){
    return vexs[a-1].showvoltage();//获取a顶点的电压值
};
void MatrixDG::insertUs(int a,int b,Complex Us){
    SourceVoltage[a-1][b-1]=Us;     //插入一个从a指向b的电压源
    NumUs++;
}; 
void MatrixDG::insertIs(int a,int b,Complex Is){
    SourceCurrent[a-1][b-1]=Is;     //插入一个从a指向b的电流源
};
void MatrixDG::deleteIs(int a,int b,Complex Is){
    SourceCurrent[a-1][b-1]=SourceCurrent[a-1][b-1]-Is;     //删除一个从a指向b的电流源
};
void MatrixDG::deleteUs(int a,int b,Complex Us){
    SourceVoltage[a-1][b-1]=SourceVoltage[a-1][b-1]-Us;     //删除一个从a指向b的电压源
    NumUs--;
};
void MatrixDG::iniGauss(){
    
    for(int i=0;i<NumVexs;i++)
    {
        for(int j=0;j<NumVexs;j++)
        {
            if(i==j)
            {
                for(int k=0;k<NumVexs;k++)
                gauss[i][j]=gauss[i][j]+Complex(1,0)/Matrix[i][k].showres();   //自电导
            }
            else
            gauss[i][j]=Complex(-1,0)/Matrix[i][j].showres();                  //互电导
        }
    }
    for(int i=0;i<NumVexs;i++)
    {
        for(int j=0;j<NumVexs;j++)
        {
            if(SourceCurrent[i][j]!=Complex(0,0))
            gauss[i][NumVexs]=gauss[i][NumVexs]-SourceCurrent[i][j];    //流入节点电流之和
            gauss[j][NumVexs]=gauss[j][NumVexs]+SourceCurrent[i][j];
        }
    }
    int k=0;
    for(int i=0;i<NumVexs;i++)
    {
        for(int j=0;j<NumVexs;j++)
        {
            if(SourceVoltage[i][j]!=Complex(0,0))
            {
                k++;
                gauss[i][NumVexs+k]=Complex(1,0);
                gauss[j][NumVexs+k]=Complex(-1,0);
                gauss[NumVexs+k-1][i]=Complex(-1,0);
                gauss[NumVexs+k-1][j]=Complex(1,0);
                gauss[NumVexs+k-1][NumVexs]=SourceVoltage[i][j];
                /*if(i!=0)
                {
                    for(int k=0;k<=NumVexs;k++)
                {
                    gauss[j][k]=gauss[i][k]+gauss[j][k];
                    gauss[i][k]=0;
                }
                    gauss[i][i]=-1;
                    gauss[i][j]=1;
                    gauss[i][NumVexs]=SourceVoltage[i][j];
                }
                if(j!=0)
                {
                for(int k=0;k<=NumVexs;k++)
                {
                    gauss[i][k]=gauss[i][k]+gauss[j][k];
                    gauss[j][k]=0;
                }
                gauss[j][i]=-1;
                gauss[j][j]=1;
                gauss[j][NumVexs]=SourceVoltage[i][j];          //对于电压源的处理
                }*/
            }
        }
    }
        for(int k=0;k<=NumVexs+NumUs;k++)
         {
            gauss[0][k]=Complex(0,0);
        }
    gauss[0][0]=Complex(1,0);
    gauss[0][NumVexs]=Complex(0,0);
};
void MatrixDG::printgauss(){
    for(int x=0;x<NumVexs+NumUs;x++)
    {
      for(int y=0;y<=NumVexs+NumUs;y++)
    {
       cout<<gauss[x][y].Show()<<' ';
    }
    cout<<endl;
    }
};
void MatrixDG::solGauss(){
    Complex **tempmat= new Complex *[NumVexs+NumUs];
    Complex *CurUs= new Complex [NumUs];
    for (int i = 0; i < NumVexs+NumUs; i++) {
        tempmat[i] = new Complex[NumVexs+NumUs];
        for (int j = 0; j < NumVexs+NumUs; j++) {
            if(j<NumVexs)
            tempmat[i][j] = gauss[i][j];
            else
            tempmat[i][j] = gauss[i][j+1];
        }
    }
    Complex base=calculateDeterminant(tempmat,NumVexs+NumUs);
    for(int k=0;k<NumVexs+NumUs;k++)
    {
    for(int i=0;i<NumVexs+NumUs;i++)
    {
        for(int j=0;j<NumVexs+NumUs;j++)
        {
            if(j<NumVexs)
            {
            if(j!=k)
            tempmat[i][j]=gauss[i][j];
            else
            tempmat[i][j]=gauss[i][NumVexs];
            }
            else
            {
            if(j!=k)
            tempmat[i][j]=gauss[i][j+1];
            else
            tempmat[i][j]=gauss[i][NumVexs];
            }
        }
    }
    if(k<NumVexs)
    vexs[k].setvalue(calculateDeterminant(tempmat,NumVexs+NumUs)/base);
    else
    {
    CurUs[k-NumVexs]=calculateDeterminant(tempmat,NumVexs+NumUs)/base;
    }
    }
    for(int i=0;i<NumVexs+NumUs;i++)
	  delete[] tempmat[i];
    delete[] tempmat;
    int k=0;
    for(int i=0;i<NumVexs;i++)
    {
        for(int j=0;j<NumVexs;j++)
        {
            if(i!=j)
            {
                if(SourceVoltage[i][j]!=Complex(0,0))
                {
                    Matrix[i][j].changeCur(CurUs[k]);
                    Matrix[j][i].changeCur(Complex(0,0)-CurUs[k]);
                    k++;
                }
                else
                Matrix[i][j].changeCur((vexs[i].showvoltage()-vexs[j].showvoltage())/Matrix[i][j].showres());
            }
        }
    }
    for(int i=0;i<NumVexs;i++)
    {
        for(int j=0;j<NumVexs;j++)
        {
            if(SourceCurrent[i][j]!=Complex(0,0))                            //电流源特殊处理
            {
                Matrix[i][j].changeCur(SourceCurrent[i][j]);
                Matrix[j][i].changeCur(Complex(0,0)-SourceCurrent[i][j]);
            }
        }
    }
    delete []CurUs;
};
void MatrixDG::Display(){
    if (Omega!=0)
    {
    for(int i=1;i<=getNumV();i++)
    {
        std::cout<<"节点"<<i<<"的电压为"<<getV(i).ShowArg()<<"V"<<endl;
    }
        for(int i=1;i<=getNumV();i++)
    {
        for(int j=1;j<=getNumV();j++)
        {
            if(getcur(i,j).Norm()>=0.000001&&i!=j)
            std::cout<<"节点"<<i<<"与节点"<<j<<"之间的电流为"<<getcur(i,j).ShowArg()<<"A"<<endl;
        }
    }
    }
    else
    {
        for(int i=1;i<=getNumV();i++)
    {
        std::cout<<"节点"<<i<<"的电压为"<<getV(i).real()<<"V"<<endl;
    }
        for(int i=1;i<=getNumV();i++)
    {
        for(int j=1;j<=getNumV();j++)
        {
            if(getcur(i,j).Norm()>=0.000001&&i!=j)
            std::cout<<"节点"<<i<<"与节点"<<j<<"之间的电流为"<<getcur(i,j).real()<<"A"<<endl;
        }
    }
    }
};