/* Takes the derivative of a Tensor3 with respect to a Tensor1
 * and returns a Tensor4 */

#pragma once

namespace FTensor
{
  template<class A,class B,class T,class U,int Dim0,int Dim1,int Dim2,int Dim3,
          char i,char j,char k,char l>
  class dTensor3
  {
    const Tensor3_Expr<A,T,Dim0,Dim1,Dim2,i,j,k> iterA;
    const Tensor1_Expr<B,U,Dim3,l> iterB;
  public:
    dTensor3(const Tensor3_Expr<A,T,Dim0,Dim1,Dim2,i,j,k> &a,
             const Tensor1_Expr<B,U,Dim3,l> &b)
            : iterA(a), iterB(b) {}
    T operator()(const int N1, const int N2,
                 const int N3, const int N4) const
    {
      return df(iterA(N1,N2,N3),iterB(N4));
    }
  };

  template<class A,class B,class T,class U,int Dim0,int Dim1,int Dim2,int Dim3,
          char i,char j,char k,char l>
  inline const Tensor4_Expr<const dTensor3<A,B,T,U,Dim0,Dim1,Dim2,Dim3,i,j,k,l>,
          typename promote<T,U>::V,Dim0,Dim1,Dim2,Dim3,i,j,k,l>
  d(const Tensor3_Expr<A,T,Dim0,Dim1,Dim2,i,j,k> &a,
    const Tensor1_Expr<B,U,Dim3,l> &b)
  {
    typedef const dTensor3<A,B,T,U,Dim0,Dim1,Dim2,Dim3,i,j,k,l>
            TensorExpr;
    return Tensor4_Expr<TensorExpr,typename promote<T,U>::V,Dim0,Dim1,Dim2,Dim3,i,j,k,l>
            (TensorExpr(a,b));
  };
}