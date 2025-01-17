//==============================================================================
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
//  This software was developed by Applied Research Laboratories at the
//  University of Texas at Austin.
//  Copyright 2004-2020, The Board of Regents of The University of Texas System
//
//==============================================================================

//==============================================================================
//
//  This software was developed by Applied Research Laboratories at the
//  University of Texas at Austin, under contract to an agency or agencies
//  within the U.S. Department of Defense. The U.S. Government retains all
//  rights to use, duplicate, distribute, disclose, or release this software.
//
//  Pursuant to DoD Directive 523024 
//
//  DISTRIBUTION STATEMENT A: This software has been approved for public 
//                            release, distribution is unlimited.
//
//==============================================================================

/// @file YDSTime.cpp

#include <cmath>
#include "YDSTime.hpp"
#include "TimeConverters.hpp"

namespace gpstk
{
// YDSTime constant corresponding to CommonTime::BEGINNING_OF_TIME


   const YDSTime YDSTime::BEGIN_TIME(CommonTime::BEGINNING_OF_TIME);

   YDSTime& YDSTime::operator=( const YDSTime& right )
   {
      year = right.year;
      doy  = right.doy;
      sod  = right.sod;
      timeSystem = right.timeSystem;
      return *this;
   }

   CommonTime YDSTime::convertToCommonTime() const
   {
      try
      {
         long jday = convertCalendarToJD( year, 1, 1 ) + doy - 1;
         CommonTime ct;
         return ct.set( jday, sod, timeSystem );
      }
      catch ( InvalidParameter& ip )
      {
         InvalidRequest ir(ip);
         GPSTK_THROW(ir);
      }
   }

   void YDSTime::convertFromCommonTime( const CommonTime& ct )
   {
      long jday = 0, secDay = 0;
      double fsecDay = 0.0;
      ct.get( jday, secDay, fsecDay, timeSystem );
      sod = static_cast<double>( secDay ) + fsecDay;

      int month = 0, day = 0;
      convertJDtoCalendar( jday, year, month, day );
      doy = jday - convertCalendarToJD( year, 1, 1 ) + 1;
   }

   std::string YDSTime::printf( const std::string& fmt ) const
   {
      try
      {
         using gpstk::StringUtils::formattedPrint;
         std::string rv = fmt;

         rv = formattedPrint( rv, getFormatPrefixInt() + "Y",
                              "Yd", year );
         rv = formattedPrint( rv, getFormatPrefixInt() + "y",
                              "yd", static_cast<short>(year % 100) );
         rv = formattedPrint( rv, getFormatPrefixInt() + "j",
                              "ju", doy );
         rv = formattedPrint( rv, getFormatPrefixFloat() + "s",
                              "sf", sod );
         rv = formattedPrint( rv, getFormatPrefixInt() + "P",
                              "Ps", StringUtils::asString(timeSystem).c_str() );
         return rv;
      }
      catch( gpstk::StringUtils::StringException& exc)
      {
         GPSTK_RETHROW( exc );
      }
   }

   std::string YDSTime::printError( const std::string& fmt ) const
   {
      try
      {
         using gpstk::StringUtils::formattedPrint;
         std::string rv = fmt;

         rv = formattedPrint( rv, getFormatPrefixInt() + "Y",
                              "Ys", getError().c_str() );
         rv = formattedPrint( rv, getFormatPrefixInt() + "y",
                              "ys", getError().c_str() );
         rv = formattedPrint( rv, getFormatPrefixInt() + "j",
                              "js", getError().c_str() );
         rv = formattedPrint( rv, getFormatPrefixFloat() + "s",
                              "ss", getError().c_str() );
         rv = formattedPrint( rv, getFormatPrefixInt() + "P",
                              "Ps", getError().c_str() );
         return rv;
      }
      catch( gpstk::StringUtils::StringException& exc)
      {
         GPSTK_RETHROW( exc );
      }
   }

   bool YDSTime::setFromInfo( const IdToValue& info )
   {
      using namespace gpstk::StringUtils;

      for( IdToValue::const_iterator i = info.begin();
           i != info.end(); i++ )
      {
         switch( i->first )
         {
            case 'Y':
               year = asInt( i->second );
               break;

            case 'y':
                  // match the POSIX strptime() function:
                  /* Year within century. When a century is not
                   * otherwise specified, values in the range 69-99
                   * refer to years in the twentieth century (1969 to
                   * 1999 inclusive); values in the range 00-68 refer
                   * to years in the twenty-first century (2000 to
                   * 2068 inclusive). */
               if( i->second.length() > 2)
                  return false;
               year = asInt( i->second );
               if (year >= 69)
                  year += 1900;
               else
                  year += 2000;
               break;

            case 'j':
               doy = asInt( i->second );
               break;

            case 's':
               sod = asDouble( i->second );
               break;

            case 'P':
               timeSystem = gpstk::StringUtils::asTimeSystem(i->second);
               break;

            default:
                  // do nothing
               break;
         };
      }

      return true;
   }

   bool YDSTime::isValid() const
   {
      YDSTime temp;
      temp.convertFromCommonTime( convertToCommonTime() );
      if( *this == temp )
      {
         return true;
      }
      return false;
   }

   void YDSTime::reset()
   {
      year = doy = 0;
      sod = 0.0;
      timeSystem = TimeSystem::Unknown;
   }

   bool YDSTime::operator==( const YDSTime& right ) const
   {
     /// Any (wildcard) type exception allowed, otherwise must be same time systems
      if ((timeSystem != TimeSystem::Any &&
           right.timeSystem != TimeSystem::Any) &&
          timeSystem != right.timeSystem)
         return false;

      if( year == right.year &&
          doy  == right.doy  &&
          fabs(sod - right.sod) < CommonTime::eps )
      {
         return true;
      }
      return false;
   }

   bool YDSTime::operator!=( const YDSTime& right ) const
   {
      return ( !operator==( right ) );
   }

   bool YDSTime::operator<( const YDSTime& right ) const
   {
     /// Any (wildcard) type exception allowed, otherwise must be same time systems
      if ((timeSystem != TimeSystem::Any &&
           right.timeSystem != TimeSystem::Any) &&
          timeSystem != right.timeSystem)
      {
         gpstk::InvalidRequest ir("CommonTime objects not in same time system, cannot be compared");
	 GPSTK_THROW(ir);
      }

      if( year < right.year )
      {
         return true;
      }
      if( year > right.year )
      {
         return false;
      }
      if( doy < right.doy )
      {
         return true;
      }
      if( doy > right.doy )
      {
         return false;
      }
      if( sod < right.sod )
      {
         return true;
      }
      return false;
   }

   bool YDSTime::operator>( const YDSTime& right ) const
   {
      return ( !operator<=( right ) );
   }

   bool YDSTime::operator<=( const YDSTime& right ) const
   {
      return ( operator<( right ) || operator==( right ) );
   }

   bool YDSTime::operator>=( const YDSTime& right ) const
   {
      return ( !operator<( right ) );
   }

   std::ostream& operator<<(std::ostream& s,
	   const gpstk::YDSTime& yt)
   {
	   s << yt.printf("%04Y/%03j %s %P");
	   return s;
   }

} // namespace
