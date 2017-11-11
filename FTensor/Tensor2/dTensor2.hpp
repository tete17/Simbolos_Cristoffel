/* Takes the derivative of a Tensor2 with respect to a Tensor3
 * and returns a Tensor3 */

#pragma once

namespace FTensor
{
    template<class A,class B,class T,class U,int Dim0,
            int Dim1,int Dim2,char i,char j,char k>
    class dTensor2
    {
        const Tensor2_Expr<A,T,Dim0,Dim1,i,j> Num;
        const Tensor1_Expr<B,U,Dim2,k> Den;
    public:
        dTensor2(const Tensor2_Expr<A,T,Dim0,Dim1,i,j> &m_Num,
                 const Tensor1_Expr<B,U,Dim2,k> &m_Den)
                : Num(m_Num), Den(m_Den) {}
        T operator()(const int N1, const int N2,
                     const int N3) const
        {
            return df(Num(N1,N2),Den(N3));
        }
    };

    template<class A,class B,class T,class U,int Dim0,int Dim1,int Dim2,
            char i,char j,char k>
    inline const Tensor3_Expr<const dTensor2<A,B,T,U,Dim0,Dim1,Dim2,i,j,k>,
            typename promote<T,U>::V,Dim0,Dim1,Dim2,i,j,k>
    d(const Tensor2_Expr<A,T,Dim0,Dim1,i,j> &a,
            const Tensor1_Expr<B,U,Dim2,k> &b)
    {
        typedef const dTensor2<A,B,T,U,Dim0,Dim1,Dim2,i,j,k> TensorExpr;
        return Tensor3_Expr<TensorExpr,typename promote<T,U>::V,Dim0,Dim1,Dim2,i,j,k>
                (TensorExpr(a,b));
    };

/*#ifdef SYMBOLIC_CPLUSPLUS
    template<class A,class B,int Dim0,int Dim1,
            int Dim2,char i,char j,char k>
    Symbolic dTensor2<A,B,Symbolic,Symbolic,Dim0,Dim1,Dim2,i,j,k>::
    operator()(const int N1, const int N2, const int N3)
    {
        return df(Num(N1,N2),Den(N3));
    };
#endif*/

}