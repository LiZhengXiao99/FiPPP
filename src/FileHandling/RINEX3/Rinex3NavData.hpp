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

/// @file Rinex3NavData.hpp
/// Encapsulates RINEX ver 3.02 Navigation data

#ifndef GPSTK_RINEXNAVDATA_HPP
#define GPSTK_RINEXNAVDATA_HPP

#include <list>
#include <string>

#include "StringUtils.hpp"
#include "CommonTime.hpp"
#include "FFStream.hpp"
#include "Rinex3NavBase.hpp"
#include "Rinex3NavStream.hpp"
#include "EngEphemeris.hpp"         // GPS only, deprecated
#include "GloEphemeris.hpp"
#include "GPSEphemeris.hpp"
#include "GalEphemeris.hpp"
#include "BDSEphemeris.hpp"
#include "QZSEphemeris.hpp"
#include "RinexSatID.hpp"
#include "RinexNavData.hpp"

namespace gpstk
{
      /// @ingroup FileHandling
      //@{

      /**
       * This class models a RINEX 3 Nav record.
       *
       * \sa FunctionalTests/Rinex3NavText for example.
       * \sa Rinex3NavHeader and Rinex3NavStream classes.
       */

   class Rinex3NavData : public Rinex3NavBase
   {
   public:
         /** Constructor
          * @warning CHECK THE PRNID TO SEE IF THIS DATA IS VALID BEFORE
          *          USING!!!.
          */
      Rinex3NavData(void)
            : time(CommonTime::BEGINNING_OF_TIME), PRNID(-1), fitint(4)
      {}

         /// Initializes the nav data with a GloEphemeris
      Rinex3NavData(const GloEphemeris& gloe);

         /// Create from a RinexNavData (for backward compatibility)
      Rinex3NavData(const RinexNavData& rnd);

         /// Initializes the nav data with an EngEphemeris
         /// EngEphemeris is deprecated; use GPSEphemeris
      Rinex3NavData(const EngEphemeris& ee);

         /// Initializes the nav data with a GPSEphemeris
      Rinex3NavData(const GPSEphemeris& gpseph);

         /// Initializes the nav data with a GalEphemeris
      Rinex3NavData(const GalEphemeris& galeph);

         /// Initializes the nav data with a BDSEphemeris
      Rinex3NavData(const BDSEphemeris& bdseph);

         /// Initializes the nav data with a QZSEphemeris
      Rinex3NavData(const QZSEphemeris& qzseph);

         /// Destructor
      virtual ~Rinex3NavData() {}

         /// Rinex3NavData is "data" so this function always returns true.
      virtual bool isData(void) const {return true;}

         /// Write selected info (system dependent) as a single line
      std::string dumpString(void) const;

         /// A debug output function.
         /// Prints the PRN id and the IODC for this record.
      virtual void dump(std::ostream& s) const;

         /// deprecated; use GPSEphemeris, GPS-only.
         /// Converts Rinex3NavData to an EngEphemeris object.
      operator EngEphemeris() const throw();

         /// Converts Rinex3NavData to a GPSEphemeris object.
      operator GPSEphemeris() const throw();

         /// Converts this Rinex3NavData to a GloEphemeris object.
      operator GloEphemeris() const throw();

         /// Converts Rinex3NavData to a GalEphemeris object.
      operator GalEphemeris() const throw();

         /// Converts Rinex3NavData to a BDSEphemeris object.
      operator BDSEphemeris() const throw();

         /// Converts Rinex3NavData to a QZSEphemeris object.
      operator QZSEphemeris() const throw();

         /// Converts the (non-CommonTime) data to an easy list
         /// for comparison operators.
      std::list<double> toList() const;

         /// Sort on time, then satellite; for use with Rinex3EphemerisStore
      bool operator<(const Rinex3NavData& right) const
      {
         CommonTime t(time),r(right.time);
         t.setTimeSystem(TimeSystem::Any);
         r.setTimeSystem(TimeSystem::Any);
         if(t == r) return (sat < right.sat);
         return (t < r);
      }

      static long fixSF1xmitSOW(unsigned long sow)
      { return sow - (sow % 30); }


         /** @name General Data */
         //@{
      CommonTime time;     ///< Time according to the sat/epoch record (TOC)
      std::string satSys;  ///< Satellite system of Epoch: G,R,E,S,C
      short PRNID;         ///< SV PRN ID
      RinexSatID sat;      ///< RinexSatID (from PRNID & satSys)
      long xmitTime;       ///< Time of subframe 1-3 (sec of week)
      short weeknum;       ///< GPS full week corresponding to HOWtime of SF1
                           ///< (N.B.:in RINEX files, week number corresponds
                           /// >to ToE, not GLO)
      double accuracy;   ///< SV accuracy (m)
      short health;        ///< SV health
         //@}

         /** @name GPS Data */
         //@{
      short   codeflgs;    ///< L2 codes
      short   L2Pdata;     ///< L2 P data flag 
      double  IODC;      ///< Index of data-clock
      double  IODE;      ///< Index of data-eph
         //@}

         /** @name GLO Data */
         //@{
      double  TauN;      ///< SV clock bias (sec)
      double  GammaN;    ///< SV relative frequency bias
      double  MFTraw;      ///< Message frame time (sec of UTC week) <double>
      long    MFtime;      ///< Message frame time (sec of UTC week) <long>
      short   freqNum;     ///< Frequency number (-7..+12)
      double  ageOfInfo; ///< Age of oper. information (days)
         //@}

         /** @name GAL Data */
         //@{
      short   datasources; ///< Data sources
      double  IODnav;    ///< Index of data-eph
         //@}

         /** @name GEO Data */
         //@{
      double  accCode;   ///< Accuracy code (URA, meters)
      double  IODN;      ///< Issue of data navigation, DO229,
                           ///< 8 first bits after Message type if MT9
         //@}

         /** @name Clock Information */
         //@{
      double  Toc;         ///< Time of clock (sec of week)
      double  af0;       ///< SV clock error (sec)
      double  af1;       ///< SV clock drift (sec/sec)
      double  af2;       ///< SV clock drift rate (sec/sec**2)
      double  Tgd;       ///< Group delay diff. (sec) (GPS, BDS:B1/B3 GAL:E5a/E1)
      double  Tgd2;      ///< Group delay differential (sec) (BDS:B2/B3 GAL:E5b/E1)
         //@}

         /** @name Harmonic Perturbations */
         //@{
      double  Cuc;       ///< Cosine latitude (rad)
      double  Cus;       ///< Sine latitude (rad)
      double  Crc;       ///< Cosine radius (m)
      double  Crs;       ///< Sine radius (m)
      double  Cic;       ///< Cosine inclination (rad)
      double  Cis;       ///< Sine inclination (rad)
         //@}

         /** @name Major Ephemeris Parameters */
         //@{
      double  Toe;       ///< Ephemeris epoch (sec of week)
      double  M0;        ///< Mean anomaly (rad)
      double  dn;        ///< Correction to mean motion (rad/sec)
      double  ecc;       ///< Eccentricity
      double  Ahalf;     ///< SQRT of semi-major axis (m**1/2)
      double  OMEGA0;    ///< Rt ascension of ascending node (rad)
      double  i0;        ///< Inclination (rad)
      double  w;         ///< Argument of perigee (rad)
      double  OMEGAdot;  ///< Rate of Rt ascension (rad/sec)
      double  idot;      ///< Rate of inclination angle (rad/sec)
      double  fitint;    ///< Fit interval

         //@}

         /** @name Tabular Ephemeris Parameters */
         //@{
      double px, py, pz; ///< SV position
      double vx, vy, vz; ///< SV velocity
      double ax, ay, az; ///< SV acceleration
         //@}


   private:

         /** Parses string \a currentLine to obtain PRN id and epoch.
          *  @param strm RINEX Nav stream
          * @throw StringUtils::StringException
          * @throw FFStreamError
          */
      void getPRNEpoch(Rinex3NavStream& strm);


         /**  Read and parse the nth record after the epoch record
          *   @param int n record number (1-7), for nth record after
          *     the epoch line
          *   @param Rinex3NavStream strm stream to read from
          * @throw StringUtils::StringException
          * @throw FFStreamError
          */
      void getRecord(const int& n, Rinex3NavStream& strm);

         /** Generates the PRN/epoch line and outputs it to strm
          *  @param strm RINEX Nav stream
          * @throw StringUtils::StringException
          */
      void putPRNEpoch(Rinex3NavStream& strm) const;


         /** Construct and write the nth record after the epoch record
          *  @param int n                 Record number (1-7), for nth record
          *                               after the epoch line.
          *  @param Rinex3NavStream strm  Stream to read from.
          * @throw StringUtils::StringException
          * @throw FFStreamError
          */
      void putRecord(const int& n, Rinex3NavStream& strm) const;

         /** Helper routine for constructors of this from
          * OrbitEph-based Ephemerides */
      void loadFrom(const OrbitEph *oeptr);

         /// Helper routine for casts from this to OrbitEph-based Ephemerides
      void castTo(OrbitEph *oeptr) const;

   protected:

         /** This function retrieves a RINEX 3 NAV record from the given
          *  FFStream.
          *  If an error is encountered in reading from the stream, the stream
          *  is returned to its original position and its fail-bit is set.
          * @throw std::exception
          *  @throw StringException when a StringUtils function fails.
          *  @throw FFStreamError when exceptions(failbit) is set and a read
          *          or formatting error occurs. This also resets the stream
          *          to its pre-read position.
          */
      virtual void reallyGetRecord(FFStream& s);


         /** Outputs the record to the FFStream \a s.
          * @throw std::exception
          * @throw StringUtils::StringException
          * @throw FFStreamError
          */
      virtual void reallyPutRecord(FFStream& s) const;

   }; // End of class 'Rinex3NavData'

      //@}

}  // End of namespace gpstk

#endif   // GPSTK_RINEXNAVDATA_HPP
