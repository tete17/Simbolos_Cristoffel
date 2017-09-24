/* Subtracts a Tensor3_dg from a Tensor3_dg, yielding a
   Tensor3_antisymmetric. */

#pragma once

namespace FTensor
{
  /* A(i,j,k)-B(i,k,j)->Tensor3_antisymmetric */

  template<class A, class B, class T, class U, int Dim, char i, char j, char k>
  class Tensor3_dg_and_Tensor3_dg_12
  {
    const Tensor3_dg_Expr<A,T,Dim,Dim,i,j,k> iterA;
    const Tensor3_dg_Expr<B,U,Dim,Dim,i,k,j> iterB;
  public:
    typename promote<T,U>::V  operator()(const int N1, const int N2, const int N3) const
    {
      return iterA(N1,N2,N3)-iterB(N1,N3,N2);
    }

    Tensor3_dg_and_Tensor3_dg_12(const Tensor3_dg_Expr<A,T,Dim,Dim,i,j,k> &a,
                                 const Tensor3_dg_Expr<B,U,Dim,Dim,i,k,j> &b):
      iterA(a), iterB(b) {}
  };

  template<class A, class B, class T, class U, int Dim, char i, char j, char k>
  inline const Tensor3_antisymmetric_Expr
  <const Tensor3_dg_and_Tensor3_dg_12<A,B,T,U,Dim,i,j,k>,
   typename promote<T,U>::V,Dim,Dim,i,j,k>
  operator&&(const Tensor3_dg_Expr<A,T,Dim,Dim,i,j,k> &a,
             const Tensor3_dg_Expr<B,U,Dim,Dim,i,k,j> &b)
  {
    typedef const Tensor3_dg_and_Tensor3_dg_12<A,B,T,U,Dim,i,j,k> TensorExpr;
    return Tensor3_antisymmetric_Expr<TensorExpr,typename promote<T,U>::V,Dim,Dim,i,j,k>
      (TensorExpr(a,b));
  }

  /* A(i,j,k)-B(k,j,i)->Tensor3_antisymmetric */
  /* We have to do a little index gymnastics here because a
     Tensor3_antisymmetric is antisymmetric on the last two indices, not
     the first and last index. */

  template<class A, class B, class T, class U, int Dim, char i, char j, char k>
  class Tensor3_dg_and_Tensor3_dg_02
  {
    const Tensor3_dg_Expr<A,T,Dim,Dim,i,j,k> iterA;
    const Tensor3_dg_Expr<B,U,Dim,Dim,k,j,i> iterB;
  public:
    typename promote<T,U>::V  operator()(const int N1, const int N2, const int N3) const
    {
      return iterA(N2,N1,N3)-iterB(N3,N1,N2);
    }

    Tensor3_dg_and_Tensor3_dg_02(const Tensor3_dg_Expr<A,T,Dim,Dim,i,j,k> &a,
                                 const Tensor3_dg_Expr<B,U,Dim,Dim,k,j,i> &b):
      iterA(a), iterB(b) {}
  };

  template<class A, class B, class T, class U, int Dim, char i, char j, char k>
  inline const Tensor3_antisymmetric_Expr
  <const Tensor3_dg_and_Tensor3_dg_02<A,B,T,U,Dim,i,j,k>,
   typename promote<T,U>::V,Dim,Dim,j,i,k>
  operator&&(const Tensor3_dg_Expr<A,T,Dim,Dim,i,j,k> &a,
             const Tensor3_dg_Expr<B,U,Dim,Dim,k,j,i> &b)
  {
    typedef const Tensor3_dg_and_Tensor3_dg_02<A,B,T,U,Dim,i,j,k> TensorExpr;
    return Tensor3_antisymmetric_Expr<TensorExpr,typename promote<T,U>::V,Dim,Dim,j,i,k>
      (TensorExpr(a,b));
  }
}
