#pragma ident "$Id$"

/**
 * @file BLQDataReader.cpp
 * File stream for ocean tides harmonics data in BLQ file format.
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
//  Dagoberto Salazar - gAGE ( http://www.gage.es ). 2007, 2009
//
//============================================================================

#include "BLQDataReader.hpp"
#include "FFStreamError.hpp"

using namespace std;

#define debug 0

namespace gpstk
{

      // Method to store load ocean tide harmonics data in this class'
      // data map
   void BLQDataReader::loadData(void)
      noexcept(false)
   {

         // Counter of valid data lines
      int row(0);

         // We will store here the station name
      std::string nameString("");

         // Declare structure to store tide harmonics data
      BLQDataReader::tideData data;

         // Do this until end-of-file reached or something else happens
      while(1)
      {

         try
         {

            if(row>6)
            {
                  // If row>6, all station harmonics are already read,
                  // so let's store tide data in data map
               setData(nameString, data);

                  // Clear harmonics data
               data.harmonics.resize(6,11,0.0);

                  // Reset counter to get data from an additional station
               row = 0;
            }

            std::string line;

//          formattedGetLine(line, true);
            getline(blqStream, line);
            if(blqStream.eof())
            {
                EndOfFile err("EOF encountered!");
                GPSTK_THROW(err);
            }


               // If line is too long, we throw an exception
            if (line.size()>255)
            {
               FFStreamError e("Line too long");
               GPSTK_THROW(e);
            }

               // Let's find and strip comments, wherever they are
            if( StringUtils::firstWord(line)[0] == '$' )
            {
//             formattedGetLine(line, true);
               getline(blqStream, line);
               if(blqStream.eof())
               {
                   EndOfFile err("EOF encountered!");
                   GPSTK_THROW(err);
               }
            }

            std::string::size_type idx = line.find('$');
            if( !(idx == std::string::npos) )
            {
               line = line.substr(0, idx);
            }

               // Remove trailing and leading blanks
            line = StringUtils::strip(line);

            if(debug)
            {
                cout << line << endl;
            }

               // Skip blank lines
            if (line.size()==0)
            {
               continue;
            }

               // Let's start to get data out of file
               // If this is the first valid line, it contains station name
            if (row==0)
            {

               nameString =
                  StringUtils::upperCase(StringUtils::stripFirstWord(line));

               ++row;

               continue;

            }
            else
            {

                  // 2nd to 7th valid lines contains tide harmonics
               if ( (row>0) && (row<=6) )
               {
                  for(int col=0; col<11; col++)
                  {
                     std::string value(StringUtils::stripFirstWord(line));
                     data.harmonics((row-1),col) = StringUtils::asDouble(value);
                  }
                  ++row;
                  continue;
               }
            }

         }  // End of try block
         catch (EndOfFile& e)
         {

               // We should close this data stream before returning
            blqStream.close();
            return;
         }
         catch (...)
         {

               // We should close this data stream before returning
            blqStream.close();
            return;
         }

      }  // End of 'while(1)...'

   }  // End of method 'BLQDataReader::loadData()'



      // Method to open AND load ocean tide harmonics data file. It doesn't
      // clear data previously loaded.
   void BLQDataReader::open(const char* fn)
   {

         // We need to be sure current data stream is closed
      blqStream.close();

         // Open data stream
      blqStream.open(fn, std::ios::in);
      if(!blqStream.is_open())
      {
          cerr << "can't open blq file:" <<  fn << endl;
          exit(-1);
      }

      loadData();

      return;
   }  // End of method 'BLQDataReader::open()'



      // Method to open AND load ocean tide harmonics data file. It doesn't
      // clear data previously loaded.
   void BLQDataReader::open(const std::string& fn)
   {

         // We need to be sure current data stream is closed
      blqStream.close();

         // Open data stream
      blqStream.open(fn, std::ios::in);
      if(!blqStream.is_open())
      {
          cerr << "can't open blq file:" <<  fn << endl;
          exit(-1);
      }
      loadData();

      return;
   }  // End of method 'BLQDataReader::open()'


      /** Method to check whether current station is computed in the data.
       *
       * @param station   Station name (case is NOT relevant).
       *
       * @return bool whether this station can be found in the data 
       */
   bool BLQDataReader::isValid(const std::string& station)
   {
         // First, look if such station exist in data map
      tideDataIt iter( OceanTidesData.find( StringUtils::upperCase(station) ) );
      if ( iter != OceanTidesData.end() )
      {
            // if found, return true;
         return true ;
      }
      else
      {
         return false;
      };
   }
         

      /* Method to get the ocean tide harmonics corresponding to a
       * given station.
       *
       * @param station   Station name (case is NOT relevant).
       *
       * @return A Matrix<double> of siw rows and eleven columns
       * containing tide harmonics M2, S2, N2, K2, K1, O1, P1, Q1, MF,
       * MM and SSA for amplitudes (radial, west, south, in meters) and
       * phases (radial, west, south, in degrees). If station is
       * not found, this method will return a matrix full of zeros.
       */
   Matrix<double> BLQDataReader::getTideHarmonics(const std::string& station)
      noexcept(false)
   {

         // First, look if such station exist in data map
      tideDataIt iter( OceanTidesData.find( StringUtils::upperCase(station) ) );
      if ( iter != OceanTidesData.end() )
      {
            // if found, return corresponding harmonics matrix
         return (*iter).second.harmonics;
      }
      else
      {
         
         InvalidRequest e("BLQDataReader::can't find this station in current data table!");
         GPSTK_THROW(e);
      };

   }  // End of method 'BLQDataReader::getTideHarmonics()'



}  // End of namespace gpstk

