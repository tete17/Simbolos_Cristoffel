#pragma once

/* A general version, not for pointers. */

#include <ostream>
#ifdef FTENSOR_DEBUG
#include <sstream>
#include <stdexcept>
#endif

namespace FTensor
{
  template <class T, int Tensor_Dim>
  class Tensor2_symmetric
  {
    T data[(Tensor_Dim*(Tensor_Dim+1))/2];
  public:
    Tensor2_symmetric() {}

    /* Tensor_Dim=1 */
    Tensor2_symmetric(T d00)
    {
      Tensor2_symmetric_constructor<T,Tensor_Dim>(data,d00);
    }

    /* Tensor_Dim=2 */
    Tensor2_symmetric(T d00, T d01, T d11)
    {
      Tensor2_symmetric_constructor<T,Tensor_Dim>(data,d00,d01,d11);
    }

    /* Tensor_Dim=3 */
    Tensor2_symmetric(T d00, T d01, T d02, T d11, T d12, T d22)
    {
      Tensor2_symmetric_constructor<T,Tensor_Dim>(data,d00,d01,d02,d11,d12,d22);
    }

    /* Tensor_Dim=4 */
    Tensor2_symmetric(T d00, T d01, T d02, T d03, T d11, T d12, T d13, T d22,
                      T d23, T d33)
    {
      Tensor2_symmetric_constructor<T,Tensor_Dim>
        (data,d00,d01,d02,d03,d11,d12,d13,d22,d23,d33);
    }

    /* There are two operator(int,int)'s, one for non-consts that lets you
       change the value, and one for consts that doesn't. */

    T & operator()(const int N1, const int N2)
    {
#ifdef FTENSOR_DEBUG
      if(N1>=Tensor_Dim || N1<0 || N2>=Tensor_Dim || N2<0)
        {
          std::stringstream s;
          s << "Bad index in Tensor2_symmetric<T," << Tensor_Dim
            << ">.operator(" << N1 << "," << N2 << ")"
            << std::endl;
          throw std::runtime_error(s.str());
        }
#endif
      return N1>N2 ? data[N1+(N2*(2*Tensor_Dim-N2-1))/2]
        : data[N2+(N1*(2*Tensor_Dim-N1-1))/2];
    }

    T operator()(const int N1, const int N2) const
    {
#ifdef FTENSOR_DEBUG
      if(N1>=Tensor_Dim || N1<0 || N2>=Tensor_Dim || N2<0)
        {
          std::stringstream s;
          s << "Bad index in Tensor2_symmetric<T," << Tensor_Dim
            << ">.operator(" << N1 << "," << N2 << ") const"
            << std::endl;
          throw std::runtime_error(s.str());
        }
#endif
      return N1>N2 ? data[N1+(N2*(2*Tensor_Dim-N2-1))/2]
        : data[N2+(N1*(2*Tensor_Dim-N1-1))/2];
    }

    /* These operator()'s are the first part in constructing template
       expressions.  They can be used to slice off lower dimensional
       parts. They are not entirely safe, since you can accidently use a
       higher dimension than what is really allowed (like Dim=5). */

    /* This returns a Tensor2_Expr, since the indices are not really
       symmetric anymore since they cover different dimensions. */

    template<char i, char j, int Dim0, int Dim1>
    Tensor2_Expr<Tensor2_symmetric<T,Tensor_Dim>,T,Dim0,Dim1,i,j>
    operator()(const Index<i,Dim0> , const Index<j,Dim1> )
    {
      return Tensor2_Expr<Tensor2_symmetric<T,Tensor_Dim>,T,Dim0,Dim1,i,j>
        (*this);
    }

    template<char i, char j, int Dim0, int Dim1>
    Tensor2_Expr<const Tensor2_symmetric<T,Tensor_Dim>,T,Dim0,Dim1,i,j>
    operator()(const Index<i,Dim0> , const Index<j,Dim1> ) const
    {
      return Tensor2_Expr<const Tensor2_symmetric<T,Tensor_Dim>,T,Dim0,Dim1,i,j>
        (*this);
    }

    /* This returns a Tensor2_symmetric_Expr, since the indices are still
       symmetric on the lower dimensions. */

    template<char i, char j, int Dim>
    Tensor2_symmetric_Expr<Tensor2_symmetric<T,Tensor_Dim>,T,Dim,i,j>
    operator()(const Index<i,Dim> , const Index<j,Dim> )
    {
      return Tensor2_symmetric_Expr<Tensor2_symmetric<T,Tensor_Dim>,T,Dim,i,j>
        (*this);
    }

    template<char i, char j, int Dim>
    Tensor2_symmetric_Expr<const Tensor2_symmetric<T,Tensor_Dim>,T,Dim,i,j>
    operator()(const Index<i,Dim> , const Index<j,Dim> ) const
    {
      return Tensor2_symmetric_Expr<const Tensor2_symmetric<T,Tensor_Dim>,
                                    T,Dim,i,j>(*this);
    }

    /* This is for expressions where a number is used for one slot, and
       an index for another, yielding a Tensor1_Expr.  The non-const
       versions don't actually create a Tensor2_number_rhs_[01] object.
       They create a Tensor1_Expr directly, which provides the
       appropriate indexing operators.  The const versions do create a
       Tensor2_number_[01]. */

    template<char i, int N, int Dim>
    Tensor1_Expr<Tensor2_number_rhs_1<Tensor2_symmetric<T,Tensor_Dim>,T,N>,
                 T,Dim,i>
    operator()(const Index<i,Dim> , const Number<N> &)
    {
      typedef Tensor2_number_rhs_1<Tensor2_symmetric<T,Tensor_Dim>,T,N>
        TensorExpr;
      return Tensor1_Expr<TensorExpr,T,Dim,i>(*this);
    }

    template<char i, int N, int Dim>
    Tensor1_Expr<const Tensor2_number_1<const Tensor2_symmetric<T,Tensor_Dim>,
                                        T,N>,T,Dim,i>
    operator()(const Index<i,Dim> , const Number<N> &) const
    {
      typedef const Tensor2_number_1<const Tensor2_symmetric<T,Tensor_Dim>,T,N>
        TensorExpr;
      return Tensor1_Expr<TensorExpr,T,Dim,i>(TensorExpr(*this));
    }

    template<char i, int N, int Dim>
    Tensor1_Expr<Tensor2_number_rhs_0<Tensor2_symmetric<T,Tensor_Dim>,T,N>,
                 T,Dim,i>
    operator()(const Number<N> &, const Index<i,Dim> )
    {
      typedef Tensor2_number_rhs_0<Tensor2_symmetric<T,Tensor_Dim>,T,N>
        TensorExpr;
      return Tensor1_Expr<TensorExpr,T,Dim,i>(*this);
    }

    template<char i, int N, int Dim>
    Tensor1_Expr<const Tensor2_number_0<const Tensor2_symmetric<T,Tensor_Dim>,
                                        T,N>,T,Dim,i>
    operator()(const Number<N> &, const Index<i,Dim> ) const
    {
      typedef const Tensor2_number_0<const Tensor2_symmetric<T,Tensor_Dim>,T,N>
        TensorExpr;
      return Tensor1_Expr<TensorExpr,T,Dim,i>(TensorExpr(*this));
    }

    /* Specializations for using actual numbers instead of Number<> */

    template<char i, int Dim>
    Tensor1_Expr<const Tensor2_numeral_1<const Tensor2_symmetric<T,Tensor_Dim>,
                                         T>,T,Dim,i>
    operator()(const Index<i,Dim> , const int N) const
    {
      typedef const Tensor2_numeral_1<const Tensor2_symmetric<T,Tensor_Dim>,T>
        TensorExpr;
      return Tensor1_Expr<TensorExpr,T,Dim,i>(TensorExpr(*this,N));
    }

    template<char i, int Dim>
    Tensor1_Expr<const Tensor2_numeral_0<const Tensor2_symmetric<T,Tensor_Dim>,
                                         T>,T,Dim,i>
    operator()(const int N, const Index<i,Dim> ) const
    {
      typedef const Tensor2_numeral_0<const Tensor2_symmetric<T,Tensor_Dim>,T>
        TensorExpr;
      return Tensor1_Expr<TensorExpr,T,Dim,i>(TensorExpr(*this,N));
    }
  
    /* These two operator()'s return the Tensor2 with internal
       contractions, yielding a T.  I have to specify one for both
       const and non-const because otherwise the compiler will use the
       operator() which gives a Tensor2_Expr<>. */
  
    template<char i, int Dim>
    T operator()(const Index<i,Dim> , const Index<i,Dim> )
    {
      return internal_contract(Number<Dim>());
    }

    template<char i, int Dim>
    T operator()(const Index<i,Dim> , const Index<i,Dim> ) const
    {
      return internal_contract(Number<Dim>());
    }
  private:
    template<int N>
    T internal_contract(const Number<N> &) const
    {
      return data[N-1+((N-1)*(2*Tensor_Dim-N))/2]
        + internal_contract(Number<N-1>());
    }

    T internal_contract(const Number<1> &) const
    {
      return data[0];
    }
  };
}

/// JSON compatible output.  It only outputs unique elments, so a 3x3
/// symmetric matrix only outputs 6 elements.

namespace FTensor
{
  template <class T, int Tensor_Dim>
  std::ostream &
  Tensor2_symmetric_ostream_row
  (std::ostream &os,
   const FTensor::Tensor2_symmetric<T,Tensor_Dim> &t,
   const int &i)
  {
    os << '[';
    for(int j=i; j+1<Tensor_Dim; ++j)
      { os << t(i,j) << ','; }
    if(Tensor_Dim>0)
      { os << t(i,Tensor_Dim-1); }
    os << ']';
    return os;
  }
}

template <class T, int Tensor_Dim>
std::ostream & operator<<(std::ostream &os,
                          const FTensor::Tensor2_symmetric<T,Tensor_Dim> &t)
{
  os << '[';
  for(int i=0; i+1<Tensor_Dim; ++i)
    {
      FTensor::Tensor2_symmetric_ostream_row(os,t,i);
      os << ',';
    }
  if(Tensor_Dim>0)
    {
      FTensor::Tensor2_symmetric_ostream_row(os,t,Tensor_Dim-1);
    }
  os << ']';
  return os;
}


namespace FTensor
{
  template <class T, int Tensor_Dim>
  std::istream &
  Tensor2_symmetric_istream_row
  (std::istream &is,
   FTensor::Tensor2_symmetric<T,Tensor_Dim> &t,
   const int &i)
  {
    char c;
    is >> c;
    for(int j=i; j+1<Tensor_Dim; ++j)
      { is >> t(i,j) >> c; }
    if(Tensor_Dim>0)
      { is >> t(i,Tensor_Dim-1); }
    is >> c;
    return is;
  }
}

template <class T, int Tensor_Dim>
std::istream & operator>>(std::istream &is,
                          FTensor::Tensor2_symmetric<T,Tensor_Dim> &t)
{
  char c;
  is >> c;
  for(int i=0; i+1<Tensor_Dim; ++i)
    {
      FTensor::Tensor2_symmetric_istream_row(is,t,i);
      is >> c;
    }
  if(Tensor_Dim>0)
    {
      FTensor::Tensor2_symmetric_istream_row(is,t,Tensor_Dim-1);
    }
  is >> c;
  return is;
}