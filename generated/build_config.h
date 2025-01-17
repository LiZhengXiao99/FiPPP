#ifndef BUILD_CONFIG_H
#define BUILD_CONFIG_H

//------------------------------------------------------------
// Purpose:
//     Define your source root and build root from CMake vars
//     so you can pass paths from CMake into C++
//------------------------------------------------------------
// Notes:
//     If you need these CMake variables for pure C code,
//     then use the #define variables, otherwise, use the
//     get methods defined in the gpstk namespace.
//------------------------------------------------------------

#include <string>

namespace gpstk
{

  //----------------------------------------
  // Purpose: get path separator character, e.g. ":" or ";"
  // Usage:   std::string file_sep = gpstk::getPathSep()
  //----------------------------------------
  inline std::string getPathSep( void )
  {
    #ifdef WIN32
    const std::string path_sep(";");
    #else
    const std::string path_sep(":");
    #endif

    return( path_sep );
  }

  //----------------------------------------
  // Purpose: get file system file separator character, e.g. "/" or "\"
  // Usage:   std::string file_sep = gpstk::getFileSep()
  //----------------------------------------
  inline std::string getFileSep( void )
  {
    #ifdef WIN32
    const std::string file_sep("\\");
    #else
    const std::string file_sep("/");
    #endif
    return( file_sep );
  }

  //----------------------------------------
  // Purpose: get file system path to top level of source tree
  // Usage:   std::string src_path = gpstk::getPathSrc()
  //----------------------------------------
  inline std::string getPathSrc( void )
  {
    return( "D:/FiPPP" );
  }

  //----------------------------------------
  // Purpose: get file system path to the CMake build dir
  // Usage:   std::string build_path = gpstk::getPathBuild()
  //----------------------------------------
  inline std::string getPathBuild( void )
  {
    return( "D:/FiPPP/cmake-build-debug-tdm_gcc103" );
  }

  //----------------------------------------
  // Purpose: get file system path to location of gpstk data files
  // Usage:   std::string data_path = gpstk::getPathData()
  //----------------------------------------
  inline std::string getPathData( void )
  {
    return( "" );
  }

  //----------------------------------------
  // Purpose: get file system path to location to write temp test output
  // Usage:   std::string temp_path = gpstk::getPathTestTemp()
  //----------------------------------------
  inline std::string getPathTestTemp( void )
  {
     return( "" );
  }


}

#endif // BUILD_CONFIG_H

