#include <iostream>
#include "FTensor.hpp"
#include "Symbolics/symbolicc++.h"

using namespace std;
using namespace FTensor;

template<class T>
Tensor2<T, 4, 4> Transpose(Tensor2<T, 4, 4> &Input){
    Tensor2<T, 4, 4> Output;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            Output(i,j)=Input(j,i);
        }
    }
    return Output;
};

template<class T>
Tensor2<T,4,4> Inverse(const Tensor2<T,4,4> &Input){
    Tensor2<T,4,4> Inverse;
    T det= Input(0,0)*(  Input(1,1)*(Input(2,2)*Input(3,3)-Input(3,2)*Input(2,3))
                            -Input(1,2)*(Input(2,1)*Input(3,3)-Input(3,1)*Input(2,3))
                            +Input(1,3)*(Input(2,1)*Input(3,2)-Input(3,1)*Input(2,2)))

                  - Input(0,1)*(  Input(1,0)*(Input(2,2)*Input(3,3)-Input(3,2)*Input(2,3))
                              -Input(1,2)*(Input(2,0)*Input(3,3)-Input(3,0)*Input(2,3))
                              +Input(1,3)*(Input(2,0)*Input(3,2)-Input(3,0)*Input(2,2)))

                  + Input(0,2)*(  Input(1,0)*(Input(2,1)*Input(3,3)-Input(3,1)*Input(2,3))
                              -Input(1,1)*(Input(2,0)*Input(3,3)-Input(3,0)*Input(2,3))
                              +Input(1,3)*(Input(2,0)*Input(3,1)-Input(3,0)*Input(2,1)))

                  - Input(0,3)*(  Input(1,0)*(Input(2,0)*Input(3,1)-Input(3,0)*Input(2,1))
                              -Input(1,1)*(Input(2,0)*Input(3,2)-Input(3,0)*Input(2,2))
                              +Input(1,2)*(Input(2,0)*Input(3,1)-Input(3,0)*Input(2,1)));

    Inverse(0,0)=( Input(1,1)*(Input(2,2)*Input(3,3)-Input(3,2)*Input(2,3))
                -Input(1,2)*(Input(2,1)*Input(3,3)-Input(3,1)*Input(2,3))
                +Input(1,3)*(Input(2,1)*Input(3,2)-Input(3,1)*Input(2,2)))/det;

    Inverse(1,0)= -(Input(1,0)*(Input(2,2)*Input(3,3)-Input(3,2)*Input(2,3))
                 -Input(1,2)*(Input(2,0)*Input(3,3)-Input(3,0)*Input(2,3))
                 +Input(1,3)*(Input(2,0)*Input(3,2)-Input(3,0)*Input(2,2)))/det;

    Inverse(2,0)=( Input(1,0)*(Input(2,1)*Input(3,3)-Input(3,1)*Input(2,3))
                -Input(1,1)*(Input(2,0)*Input(3,3)-Input(3,0)*Input(2,3))
                +Input(1,3)*(Input(2,0)*Input(3,1)-Input(3,0)*Input(2,1)))/det;

    Inverse(3,0)= -(Input(1,0)*(Input(2,0)*Input(3,1)-Input(3,0)*Input(2,1))
                 -Input(1,1)*(Input(2,0)*Input(3,2)-Input(3,0)*Input(2,2))
                 +Input(1,2)*(Input(2,0)*Input(3,1)-Input(3,0)*Input(2,1)))/det;

    Inverse(0,1)= -(Input(0,1)*(Input(2,2)*Input(3,3)-Input(3,2)*Input(2,3))
                 -Input(0,2)*(Input(2,1)*Input(3,3)-Input(3,1)*Input(2,3))
                 +Input(0,3)*(Input(2,1)*Input(3,2)-Input(3,1)*Input(2,2)))/det;

    Inverse(1,1)=( Input(0,0)*(Input(2,2)*Input(3,3)-Input(3,2)*Input(2,3))
                -Input(0,2)*(Input(2,0)*Input(3,3)-Input(3,0)*Input(2,3))
                +Input(0,3)*(Input(2,0)*Input(3,2)-Input(3,0)*Input(2,2)))/det;

    Inverse(2,1)= -(Input(0,0)*(Input(2,1)*Input(3,3)-Input(3,1)*Input(2,3))
                 -Input(0,1)*(Input(2,0)*Input(3,3)-Input(3,0)*Input(2,3))
                 +Input(0,3)*(Input(2,0)*Input(3,1)-Input(3,0)*Input(2,1)))/det;

    Inverse(3,1)=( Input(0,0)*(Input(2,1)*Input(3,2)-Input(3,1)*Input(2,2))
                -Input(0,1)*(Input(2,0)*Input(3,2)-Input(3,0)*Input(2,2))
                +Input(0,2)*(Input(2,0)*Input(3,1)-Input(3,0)*Input(2,1)))/det;

    Inverse(0,2)=( Input(0,1)*(Input(1,2)*Input(3,3)-Input(3,2)*Input(1,3))
                -Input(0,2)*(Input(1,1)*Input(3,3)-Input(3,1)*Input(1,3))
                +Input(0,3)*(Input(1,1)*Input(3,2)-Input(3,1)*Input(1,2)))/det;

    Inverse(1,2)= -(Input(0,0)*(Input(1,2)*Input(3,3)-Input(3,2)*Input(1,3))
                 -Input(0,2)*(Input(1,0)*Input(3,3)-Input(3,0)*Input(1,3))
                 +Input(0,3)*(Input(1,0)*Input(3,2)-Input(3,0)*Input(1,2)))/det;

    Inverse(2,2)=( Input(0,0)*(Input(1,1)*Input(3,3)-Input(3,1)*Input(1,3))
                -Input(0,1)*(Input(1,0)*Input(3,3)-Input(3,0)*Input(1,3))
                +Input(0,3)*(Input(1,0)*Input(3,1)-Input(3,0)*Input(1,1)))/det;

    Inverse(3,2)= -(Input(0,0)*(Input(1,1)*Input(3,2)-Input(3,1)*Input(1,2))
                 -Input(0,1)*(Input(1,0)*Input(3,2)-Input(3,0)*Input(1,2))
                 +Input(0,2)*(Input(1,0)*Input(3,1)-Input(3,0)*Input(1,1)))/det;

    Inverse(0,3)= -(Input(0,1)*(Input(1,2)*Input(2,3)-Input(2,2)*Input(1,3))
                 -Input(0,2)*(Input(1,1)*Input(2,3)-Input(2,1)*Input(1,3))
                 +Input(0,3)*(Input(1,1)*Input(2,2)-Input(2,1)*Input(1,2)))/det;

    Inverse(1,3)=( Input(0,0)*(Input(1,2)*Input(2,3)-Input(2,2)*Input(1,3))
                -Input(0,2)*(Input(1,0)*Input(2,3)-Input(2,0)*Input(1,3))
                +Input(0,3)*(Input(1,0)*Input(2,2)-Input(2,0)*Input(1,2)))/det;

    Inverse(2,3)= -(Input(0,0)*(Input(1,1)*Input(2,3)-Input(2,1)*Input(1,3))
                 -Input(0,1)*(Input(1,0)*Input(2,3)-Input(2,0)*Input(1,3))
                 +Input(0,3)*(Input(1,0)*Input(2,1)-Input(2,0)*Input(1,1)))/det;

    Inverse(3,3)=( Input(0,0)*(Input(1,1)*Input(2,2)-Input(2,1)*Input(1,2))
                -Input(0,1)*(Input(1,0)*Input(2,2)-Input(2,0)*Input(1,2))
                +Input(0,2)*(Input(1,0)*Input(2,1)-Input(2,0)*Input(1,1)))/det;
    return Inverse;
};

int main() {
    //Test Metrica
    Index<'i',4> i; Index<'j',4> j; Index<'k',4> k; Index<'l',4> l; Index<'m',4> m;
    Symbolic t("t"), r("r"), theta("theta"), phi("phi"), K("k");
    Symbolic zero(0);
    Symbolic one(1);

    Tensor1<Symbolic,4> X(t,r,theta,phi);
    Tensor2<Symbolic,4,4> g;
    g(0,0)=-(K^2*r^2+1);    g(0,1)=zero;                g(0,2)=zero; g(0,3)=zero;
    g(1,0)=zero;            g(1,1)= (K^2*r^2+1)^-1;     g(1,2)=zero; g(1,3)=zero;
    g(2,0)=zero;            g(2,1)=zero;                g(2,2)= r^2; g(2,3)=zero;
    g(3,0)=zero;            g(3,1)=zero;                g(3,2)=zero; g(3,3)= (r*sin(theta))^2;

    Tensor2<Symbolic,4,4> gInverse;
    gInverse=Inverse(g);
    cout << "g^-1: "<< gInverse << endl;

    Tensor3<Symbolic,4,4,4> Cristoff;
    Cristoff(i,k,l) = 0.5*gInverse(i,m) *
            (d(g(m,k),X(l)) + d(g(m,l),X(k))-d(g(k,l),X(m)));
    cout << "Cristoff: " << Cristoff << endl << endl;

    Tensor4<Symbolic,4,4,4,4> Riemann;
    Riemann(i,j,k,l) = d(Cristoff(i,l,j),X(k)) - d(Cristoff(i,k,j),X(l)) +
            Cristoff(i,k,m)*Cristoff(m,l,j) - Cristoff(i,l,m)*Cristoff(m,k,j);
    cout << "Riemann: " << Riemann << endl << endl;

    Tensor2<Symbolic,4,4> Ricci;
    Ricci(i,j)=Riemann(m,i,m,j);
    cout << "Ricci: " << Ricci << endl << endl;

    Symbolic R;
    R = Ricci(i,i);
    cout << "R: " << R << endl << endl;

    return zero;
}