#pragma ident "$Id$"

/**
 * @file XYZ2NED.cpp
 * This is a class to change the reference base from ECEF XYZ to topocentric
 * North-East-Down (NED).
 */

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
//  Dagoberto Salazar - gAGE ( http://www.gage.es ). 2007, 2008, 2011
//
//============================================================================


#include "XYZ2NED.hpp"


namespace gpstk
{

      // Returns a string identifying this object.
   std::string XYZ2NED::getClassName() const
   { return "XYZ2NED"; }



      /* Common constructor taking reference point Position object
       *
       * @param refPos    Reference point Position object.
       */
   XYZ2NED::XYZ2NED(const Position& refPos)
   {

      setLatLon( refPos.getGeodeticLatitude(),
                 refPos.getLongitude() );

   }  // End of 'XYZ2NED::XYZ2NED()'



      /* Method to set the latitude of the reference point, in degrees.
       *
       * @param lat      Latitude of the reference point, in degrees.
       *
       * @warning If parameter 'lat' is outside the +90/-90 degrees range,
       * then latitude will be set to 0 degrees.
       */
   XYZ2NED& XYZ2NED::setLat(const double& lat)
   {

         // Don't allow latitudes out of the -90/+90 interval
      if ( (lat > 90.0) ||
           (lat < -90.0)  )
      {
         refLat = 0.0;
      }
      else
      {
         refLat = (lat*DEG_TO_RAD);
      }

      init();

      return (*this);

   }  // End of method 'XYZ2NED::setLat()'



      /* Method to set the longitude of the reference point, in degrees.
       *
       * @param lon       Longitude of the reference point, in degrees.
       */
   XYZ2NED& XYZ2NED::setLon(const double& lon)
   {

      refLon = (lon*DEG_TO_RAD);

      init();

      return (*this);

   }  // End of method 'XYZ2NED::setLon()'



      /* Method to simultaneously set the latitude and longitude of
       * the reference point, in degrees.
       *
       * @param lat        Latitude of the reference point, in degrees.
       * @param lon        Longitude of the reference point, in degrees.
       *
       * @warning If parameter 'lat' is outside the +90/-90 degrees range,
       * then latitude will be set to 0 degrees.
       */
   XYZ2NED& XYZ2NED::setLatLon( const double& lat,
                                const double& lon )
   {

         // Don't allow latitudes out of the -90/+90 interval
      if ( (lat > 90.0) ||
           (lat < -90.0)  )
      {
         refLat = 0.0;
      }
      else
      {
         refLat = (lat*DEG_TO_RAD);
      }

      refLon = (lon*DEG_TO_RAD);

      init();

      return (*this);

   }  // End of method 'XYZ2NED::setLatLon()'



      // Returns a reference to a satTypeValueMap object after converting
      // from a geocentric reference system to a topocentric reference system.
      //
      // @param gData     Data object holding the data.
      //
   satTypeValueMap& XYZ2NED::Process(satTypeValueMap& gData)
      noexcept(false)
   {

      try
      {

         Matrix<double> neuMatrix;

            // Get the corresponding geometry/design matrix data
         Matrix<double> dMatrix(gData.getMatrixOfTypes(inputSet));

            // Compute the base change. For convenience, we use the property:
            // Y = A*B => Y^T = (A*B)^T => Y^T = B^T * A^T
         neuMatrix = dMatrix*neuRotationMatrix;

         gData.insertMatrix(outputSet, neuMatrix);

         return gData;

      }
      catch(Exception& u)
      {
            // Throw an exception if something unexpected happens
         ProcessingException e( getClassName() + ":"
                                + u.what() );

         GPSTK_THROW(e);

      }

   }  // End of method 'XYZ2NED::Process()'



      // This method builds the rotation matrix according to 'refLat' and
      // 'refLon' values.
   void XYZ2NED::init()
   {

         // First, let's resize rotation matrix and assign the proper values
      neuRotationMatrix.resize(3,3);

         // The clasical rotation matrix is transposed here for convenience
      neuRotationMatrix(0,0) = -std::sin(refLat)*std::cos(refLon);
      neuRotationMatrix(1,0) = -std::sin(refLat)*std::sin(refLon);
      neuRotationMatrix(2,0) = std::cos(refLat);
      neuRotationMatrix(0,1) = -std::sin(refLon);
      neuRotationMatrix(1,1) = std::cos(refLon);
      neuRotationMatrix(2,1) = 0.0;
      neuRotationMatrix(0,2) = -std::cos(refLat)*std::cos(refLon);
      neuRotationMatrix(1,2) = -std::cos(refLat)*std::sin(refLon);
      neuRotationMatrix(2,2) = -std::sin(refLat);

         // Then, fill the sets with the proper types
      inputSet.clear();
      inputSet.insert(TypeID::dX);
      inputSet.insert(TypeID::dY);
      inputSet.insert(TypeID::dZ);

      outputSet.clear();
      outputSet.insert(TypeID::dLat);
      outputSet.insert(TypeID::dLon);
      outputSet.insert(TypeID::dH);

   }  // End of method 'XYZ2NED::init()'


}  // End of namespace gpstk
