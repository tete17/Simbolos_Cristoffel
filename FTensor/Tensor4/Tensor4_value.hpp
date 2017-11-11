/* A general version, not for pointers. */

#include <ostream>

#ifdef FTENSOR_DEBUG
#include <sstream>
#include <stdexcept>
#endif

#pragma once

namespace FTensor
{
  template<class T,int Tensor_Dim0,int Tensor_Dim1,int Tensor_Dim2,int Tensor_Dim3>
  class Tensor4
  {
    T data[Tensor_Dim0][Tensor_Dim1][Tensor_Dim2][Tensor_Dim3];
  public:
    /* There are two operator(int,int,int,int)'s, one for non-consts
       that lets you change the value, and one for consts that
       doesn't. */
    T & operator()(const int N1,const int N2,const int N3,const int N4)
    {
#ifdef FTENSOR_DEBUG
      if(N1>=Tensor_Dim01 || N1<0 || N2>=Tensor_Dim01 || N2<0
         || N3>=Tensor_Dim23 || N3<0 || N4>=Tensor_Dim23 || N4<0)
        {
          std::stringstream s;
          s << "Bad index in Tensor4<T,"
            << Tensor_Dim01 << "," << Tensor_Dim23
            << ">.operator("
            << N1 << "," << N2 << "," << N3 << "," << N4
            << ") const"
            << std::endl;
          throw std::runtime_error(s.str());
        }
#endif
      return data[N1][N2][N3][N4];
    }

    T operator()(const int N1,const int N2,const int N3,const int N4)
            const
    {
#ifdef FTENSOR_DEBUG
      if(N1>=Tensor_Dim01 || N1<0 || N2>=Tensor_Dim01 || N2<0
         || N3>=Tensor_Dim23 || N3<0 || N4>=Tensor_Dim23 || N4<0)
        {
          std::stringstream s;
          s << "Bad index in Tensor4<T,"
            << Tensor_Dim01 << "," << Tensor_Dim23
            << ">.operator("
            << N1 << "," << N2 << "," << N3 << "," << N4 << ")"
            << std::endl;
          throw std::runtime_error(s.str());
        }
#endif
      return data[N1][N2][N3][N4];
    }

    /* These operator()'s are the first part in constructing template
       expressions.  They can be used to slice off lower dimensional
       parts. */

    template<char i,char j,char k,char l,int Dim0,int Dim1,int Dim2,int Dim3>
    typename std::enable_if<(Tensor_Dim0 >= Dim0 && Tensor_Dim1 >= Dim1 && Tensor_Dim2 >= Dim2 && Tensor_Dim3 >= Dim3),
            Tensor4_Expr<Tensor4<T,Tensor_Dim0,Tensor_Dim1,Tensor_Dim2,Tensor_Dim3>,
                   T,Dim0,Dim1,Dim2,Dim3,i,j,k,l> >::type
    operator()(const Index<i,Dim0> , const Index<j,Dim1> ,
               const Index<k,Dim2> , const Index<l,Dim3>)
    {
      return Tensor4_Expr<Tensor4<T,Tensor_Dim0,Tensor_Dim1,Tensor_Dim2,Tensor_Dim3>,
                          T,Dim0,Dim1,Dim2,Dim3,i,j,k,l> (*this);
    };

    template<char i,char j,char k,char l,int Dim0,int Dim1,int Dim2,int Dim3>
    typename std::enable_if<(Tensor_Dim0 >= Dim0 && Tensor_Dim1 >= Dim1 && Tensor_Dim2 >= Dim2 && Tensor_Dim3 >= Dim3),
            Tensor4_Expr<const Tensor4<T,Tensor_Dim0,Tensor_Dim1,Tensor_Dim2,Tensor_Dim3>,
            T,Dim0,Dim1,Dim2,Dim3,i,j,k,l> >::type
    operator()(const Index<i,Dim0> , const Index<j,Dim1> ,
               const Index<k,Dim2> , const Index<l,Dim3>) const
    {
      return Tensor4_Expr<const Tensor4<T,Tensor_Dim0,Tensor_Dim1,Tensor_Dim2,Tensor_Dim3>,
                          T,Dim0,Dim1,Dim2,Dim3,i,j,k,l> (*this);
    };

    /* These operators are for internal contractions, resulting in a Tensor2.
     * For example something like A(k,i,k,j) */


    template<char i,char j,char k,int Dim>
    inline
    typename std::enable_if<(Tensor_Dim0 >= Dim && Tensor_Dim1 >= Dim && Tensor_Dim2 >= Dim && Tensor_Dim3 >= Dim),
            Tensor2_Expr<const Tensor4_contracted_02<Tensor4<T,Tensor_Dim0,Tensor_Dim1,Tensor_Dim2,Tensor_Dim3>,
            T,Dim>,T,Dim,Dim,i,j> >::type
    operator()(const Index<k,Dim> , const Index<i,Dim> ,
               const Index<k,Dim> , const Index<j,Dim>)
    {
      typedef const Tensor4_contracted_02<Tensor4<T,Tensor_Dim0,Tensor_Dim1,Tensor_Dim2,Tensor_Dim3>,T,Dim> TensorExpr;
      return Tensor2_Expr<TensorExpr,T,Dim,Dim,i,j>(TensorExpr(*this));
    };


    /* This is for expressions where a number is used for one slot, and
       an index for another, yielding a Tensor3_Expr.  The non-const
       versions don't actually create a Tensor3_number_rhs_[0123] object.
       They create a Tensor3_Expr directly, which provides the
       appropriate indexing operators.  The const versions do create a
       Tensor3_number_[0123]. */
    // TODO

  };
}

/// JSON compatible output

namespace FTensor
{
  template<class T,int Tensor_Dim0,int Tensor_Dim1,int Tensor_Dim2,int Tensor_Dim3>
  std::ostream & Tensor4_0001(std::ostream &os,
                              const Tensor4<T,Tensor_Dim0,Tensor_Dim1,Tensor_Dim2,Tensor_Dim3> &t,
                              const int &iterator0,
                              const int &iterator1,
                              const int &iterator2)
  {
    os << '[';
    for (int i = 0; i < Tensor_Dim3-1; ++i) {
      os << t(iterator0,iterator1,iterator2,i);
      os << ',';
    }
    os << t(iterator0,iterator1,iterator2,Tensor_Dim3-1);
    os << ']';

    return os;
  }

  template<class T,int Tensor_Dim0,int Tensor_Dim1,int Tensor_Dim2,int Tensor_Dim3>
  std::ostream & Tensor4_0010(std::ostream &os,
                              const Tensor4<T,Tensor_Dim0,Tensor_Dim1,Tensor_Dim2,Tensor_Dim3> &t,
                              const int &iterator0,
                              const int &iterator1)
  {
    os << '[';
    for (int i = 0; i < Tensor_Dim2-1; ++i) {
      FTensor::Tensor4_0001(os, t, iterator0, iterator1, i);
      os << ',';
    }
    FTensor::Tensor4_0001(os, t, iterator0, iterator1, Tensor_Dim2-1);
    os << ']';

    return os;
  }

  template<class T,int Tensor_Dim0,int Tensor_Dim1,int Tensor_Dim2,int Tensor_Dim3>
  std::ostream & Tensor4_0100(std::ostream &os,
                              const Tensor4<T,Tensor_Dim0,Tensor_Dim1,Tensor_Dim2,Tensor_Dim3> &t,
                              const int &iterator0)
  {
    os << '[';
    for (int i = 0; i < Tensor_Dim1-1; ++i) {
      FTensor::Tensor4_0010(os, t, iterator0, i);
      os << ',';
    }
    FTensor::Tensor4_0010(os, t, iterator0, Tensor_Dim1-1);
    os << ']';

    return os;
  }

}

template<class T,int Tensor_Dim0,int Tensor_Dim1,int Tensor_Dim2,int Tensor_Dim3>
std::ostream & operator<<(std::ostream &os,
                          const FTensor::Tensor4<T,Tensor_Dim0,Tensor_Dim1,Tensor_Dim2,Tensor_Dim3> &t)
{
  os << '[';
  for (int i = 0; i < Tensor_Dim0-1; ++i) {
    FTensor::Tensor4_0100(os, t, i);
    os << ',';
  }
  FTensor::Tensor4_0100(os, t, Tensor_Dim0-1);
  os << ']';

  return os;
}
