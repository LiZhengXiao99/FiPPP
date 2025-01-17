//============================================================================
//
//  This file is part of GPSTk, the GPS Toolkit.
//
//  The GPSTk is free software; you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published
//  by the Free Software Foundation; either version 3.0 of the License, or
//  any later version.
//
//  The GPSTk is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with GPSTk; if not, write to the Free Software Foundation,
//  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
//
//  Copyright 2004, The University of Texas at Austin
//  Dagoberto Salazar - gAGE ( http://www.gage.es ). 2008
//
//============================================================================

//============================================================================
//
//This software developed by Applied Research Laboratories at the University of
//Texas at Austin, under contract to an agency or agencies within the U.S.
//Department of Defense. The U.S. Government retains all rights to use,
//duplicate, distribute, disclose, or release this software.
//
//Pursuant to DoD Directive 523024
//
// DISTRIBUTION STATEMENT A: This software has been approved for public
//                           release, distribution is unlimited.
//
//=============================================================================

/**
 * @file SpecialFunctions.hpp
 * Contains handy special functions: Gamma, erf, erfc, etc.
 */

#ifndef SPECIALFUNCTIONS_HPP
#define SPECIALFUNCTIONS_HPP

#include <cmath>
#include "GNSSconstants.hpp"
#include "Exception.hpp"


namespace gpstk
{

      /** @addtogroup math */
      //@{


      /** Computes the Gamma function using a simple Lanczos approximation.
       *
       * This implementation typically gives 15 correct decimal places, and
       * it is adapted from free Python code found in:
       *
       * http://en.wikipedia.org/wiki/Lanczos_approximation
       *
       * \warning Be aware that Gamma function is not defined for 0, -1, -2,...
       */
   double gamma(const double val);


      /** Computes the natural logarithm of Gamma function
       *  using the Lanczos approximation.
       *
       * \warning This version does not work for values <= 0.0
       */
   double lngamma(double val);


      /// Lower incomplete gamma function.
   double lower_gamma(const double a, const double z);


      /// Upper incomplete gamma function.
   double upper_gamma(const double a, const double z);


      /// Lower incomplete regularized gamma function P(a,z).
   double gammaP(const double a, const double z);


      /// Upper incomplete regularized gamma function Q(a,z).
   double gammaQ(const double a, const double z);


      /** Computes factorial of integer number n.
       *
       * This implementation typically gives 15 correct decimal places, and
       * returns the result as double.
       */
   double factorial(const int n);


      /** Computes factorial of double number n.
       *  d < 360 has been tested
       */
   double factorial(const double d);


      /** Error function.
       *
       * This is a C++ implementation of the free Python code found in:
       *
       *   http://code.activestate.com/recipes/576391/
       *
       * Such code was based in a C code base with OpenBSD license from:
       *
       * ====================================================
       * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
       *
       * Developed at SunPro, a Sun Microsystems, Inc. business.
       * Permission to use, copy, modify, and distribute this
       * software is freely granted, provided that this notice
       * is preserved.
       * ====================================================
       */
   double erf(const double x);


      /// Complementary error function.
   double erfc(const double x);


      /** Inverse of error function.
       *
       * \ warning Value "z" must be in the range (-1, 1)
       */
   double inverf(const double z);


      /** Beta function.
       *
       * \warning This version may not work for values > 130.0
       */
   double beta(const double x, const double y);


      /** Computes the natural logarithm of Beta function
       *
       * \warning This version does not work for values <= 0.0
       */
   double lnbeta(double x, double y);


      /** Computes the regularized incomplete Beta function Ix(a,b).
       *
       * This code is a C++ implementation and adaptation from code found
       * in Cephes Math Library Release 2.8, copyright by Stephen L. Moshier,
       * released under a BSD license.
       */
   double regIncompleteBeta(const double x, const double a, const double b)
      noexcept(false);


      //@}

}  // End of namespace gpstk
#endif   // SPECIALFUNCTIONS_HPP
