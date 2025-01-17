#pragma ident "$Id$"

/**
 * @file ARBase.hpp
 * 
 */

#ifndef GPSTK_ARBASE_HPP
#define GPSTK_ARBASE_HPP

//============================================================================
//
//  This file is part of GPSTk, the GPS Toolkit.
//
//  The GPSTk is free software; you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published
//  by the Free Software Foundation; either version 2.1 of the License, or
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
//
//============================================================================

#include "Exception.hpp"
#include "Matrix.hpp"

namespace gpstk
{
      /// New exception for Ambiguity Resolution
   NEW_EXCEPTION_CLASS(ARException, Exception);


      /** This class ...
       *
       */
   class ARBase   
   {
   public:
      
         /// Default constructor
      ARBase(){}      

      
         /// Integer Ambiguity Resolution method
      virtual ARBase& resolve( const Vector<double>& ambFloat, 
                               const Matrix<double>& ambCov ) =0;
      
         /// Destractor
      virtual ~ARBase(){}
      
         
   };   // End of class 'ARBase'
   
}   // End of namespace gpstk


#endif  //GPSTK_ARBASE_HPP

