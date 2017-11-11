/* Include file for the Fast Tensor classes (FTensor).  Everything is
   in namespace FTensor. */

#pragma once

#include <cmath>
#include <complex>
#ifdef FTENSOR_DEBUG
#include <iostream>
#include <stdexcept>
#include <sstream>
#endif
#include "FTensor/Layout.hpp"
namespace FTensor
{
  template <class T> class Tensor0;

  template <class T, int Dim> class Tensor1;
  template<class A, class T, int Dim, char i> class Tensor1_Expr;

  template <class T, int Dim1, int Dim2, Layout layout=column_major>
  class Tensor2;
  template<class A, class T, int Dim1, int Dim2, char i, char j>
  class Tensor2_Expr;
  template<class A, class T, int N>
  class Tensor2_number_rhs_0;
  template<class A, class T, int N>
  class Tensor2_number_rhs_1;

  template <class T, int Dim> class Tensor2_symmetric;
  template<class A, class T, int Dim, char i, char j>
  class Tensor2_symmetric_Expr;

  template <class T, int Dim> class Tensor2_antisymmetric;
  template<class A, class T, int Dim, char i, char j>
  class Tensor2_antisymmetric_Expr;


  template <class T, int Dim0, int Dim1, int Dim2> class Tensor3;
  template <class A, class T, int Dim0, int Dim1, int Dim2,
    char i, char j, char k> class Tensor3_Expr;
  template<class A, class T, int N> class Tensor3_number_rhs_0;
  template<class A, class T, int N> class Tensor3_number_rhs_2;
  template<class A, class T, int N> class Tensor3_number_rhs_2;
  template<class A, class T, int N1, int N2> class Tensor3_number_rhs_01;
  template<class A, class T, int N1, int N2> class Tensor3_number_rhs_02;
  template<class A, class T, int N1, int N2> class Tensor3_number_rhs_12;

  template <class T, int Dim01, int Dim2> class Tensor3_dg;
  template <class A, class T, int Dim01, int Dim2, char i, char j, char k>
  class Tensor3_dg_Expr;
  template<class A, class T, int N> class Tensor3_dg_number_rhs_0;
  template<class A, class T, int N> class Tensor3_dg_number_rhs_2;
  template<class A, class T, int N1, int N2> class Tensor3_dg_number_rhs_01;
  template<class A, class T, int N1, int N2> class Tensor3_dg_number_rhs_12;

  template <class T, int Dim0, int Dim12> class Tensor3_christof;
  template <class A, class T, int Dim0, int Dim12, char i, char j, char k>
  class Tensor3_christof_Expr;

  template <class T, int Dim0, int Dim12> class Tensor3_antisymmetric;
  template <class A, class T, int Dim0, int Dim12, char i, char j, char k>
  class Tensor3_antisymmetric_Expr;

  template<class T,int Dim0,int Dim1,int Dim2,int Dim3> class Tensor4;
  template <class A, class T, int Dim0, int Dim1, int Dim2, int Dim3,
    char i, char j, char k, char l>
  class Tensor4_Expr;

  template <class T, int Dim> class Tensor4_Riemann;
  template <class A, class T, int Dim, char i, char j, char k, char l>
  class Tensor4_Riemann_Expr;

  template <class T, int Dim01, int Dim23> class Tensor4_ddg;
  template <class A, class T, int Dim01, int Dim23,
    char i, char j, char k, char l> class Tensor4_ddg_Expr;
  template<class A, class T, int N0, int N1>
  class Tensor4_ddg_number_rhs_01;
  template<class A, class T, int N0>
  class Tensor4_ddg_number_rhs_0;
}
#if __cplusplus < 201103L
#include "FTensor/enable_if.hpp"
#else
#include <type_traits>
#endif

#include "FTensor/Index.hpp"
#include "FTensor/Number.hpp"
#include "FTensor/promote.hpp"
#include "FTensor/Tensor0.hpp"
#include "FTensor/Tensor1.hpp"
#include "FTensor/Tensor2.hpp"
#include "FTensor/Tensor2_symmetric.hpp"
#include "FTensor/Tensor2_antisymmetric.hpp"
#include "FTensor/Tensor3/Tensor3_contracted.hpp"
#include "FTensor/Tensor3.hpp"
#include "FTensor/Tensor3_dg.hpp"
#include "FTensor/Tensor3_christof.hpp"
#include "FTensor/Tensor3_antisymmetric.hpp"
#include "FTensor/Tensor4/Tensor4_contracted.hpp"
#include "FTensor/Tensor4.hpp"
#include "FTensor/Tensor4_ddg.hpp"
#include "FTensor/Tensor4_Riemann.hpp"

