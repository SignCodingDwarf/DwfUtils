# Description :
# Find DwfUtils library content

# Input Variables : 
# DWFUTILS_INCLUDE_DIR : set the path to Xerces include directory if it is not standard
# DWFUTILS_LIBRARY_DIR : set the path to Xerces lib directory if it is not standard

# Once done this will define :
# DWFUTILS_FOUND : set to true if Xerces-C is defined  
# DWFUTILS_INCLUDE : set the path to the Xerces-C include directory
# DWFUTILS_LIBRARY : set the path to the Xerces-C library
# DWFUTILS_VERSION : set the Xerces-C version number
# DWFUTILS_STATIC : set to true if static library is used and to false if dynamic library is used

message(STATUS "Locating DwfUtils library")

### Check if data are already stored in cache ###
if(DEFINED DWFUTILS_INCLUDE AND DEFINED DWFUTILS_LIBRARY)
	set(DWFUTILS_FIND_QUIETLY true)
else()
	set(DWFUTILS_FIND_QUIETLY false)
endif()

#############################################################################

### Choose library compilation type ###
set(DWFUTILS_STATIC false) # true to use .a library, false to use .so
if(NOT DEFINED DWFUTILS_WAS_STATIC OR NOT ${DWFUTILS_WAS_STATIC} STREQUAL ${DWFUTILS_STATIC})
	unset(DWFUTILS_LIBRARY CACHE)
	unset(DWFUTILS_LIBRARY_DEBUG CACHE)
	set(DWFUTILS_FIND_QUIETLY false) # We have to find back xerces with the new library
endif()

set(DWFUTILS_WAS_STATIC ${DWFUTILS_STATIC} CACHE INTERNAL "Set to true to use static library (.a)" ) # Store previous library choice in cache

#############################################################################

### Find include directory path ###
if(NOT DWFUTILS_FIND_QUIETLY) # If it was not already found, search for Xerces include folder
	find_path(DWFUTILS_INCLUDE NAMES Version.h # Find version path
	PATHS
	$ENV{DWFUTILS_INCLUDE_DIR} # Custom search paths as an environment variable
	${DWFUTILS_INCLUDE_DIR} # Custom search paths as a CMake variable
	/usr/local/include # Default search paths
	/usr/local/include/DwfUtils
	/usr/include
	/usr/include/DwfUtils
	)
endif()

#############################################################################

### Find library file ###
if(NOT DWFUTILS_FIND_QUIETLY) # If it was not already found, search for Xerces library file
	if(DWFUTILS_STATIC)
		FIND_LIBRARY(DWFUTILS_LIBRARY NAMES DwfUtils_static
		PATHS
		$ENV{DWFUTILS_LIBRARY_DIR}
		${DWFUTILS_LIBRARY_DIR}
		/usr/lib
		/usr/lib/DwfUtils
		/usr/local/lib
		/usr/local/lib/DwfUtils
		)
	else()
		FIND_LIBRARY(DWFUTILS_LIBRARY NAMES DwfUtils
		PATHS
		$ENV{DWFUTILS_LIBRARY_DIR}
		${DWFUTILS_LIBRARY_DIR}
		/usr/lib
		/usr/lib/DwfUtils
		/usr/local/lib
		/usr/local/lib/DwfUtils
		)
	endif()
endif()

MARK_AS_ADVANCED(DWFUTILS_INCLUDE DWFUTILS_LIBRARY)

#############################################################################

### Set find flag ###
if(DWFUTILS_INCLUDE AND DWFUTILS_LIBRARY)
	set(DWFUTILS_FOUND true)
else()
	set(DWFUTILS_FOUND false)
endif()

#############################################################################

### Identify library version ###
if(DWFUTILS_FOUND)
	FIND_PATH(DWFUTILS_VERHPATH NAMES Version.h # Find Header containing Xerces Version
	PATHS
	${DWFUTILS_INCLUDE}
	PATH_SUFFIXES DWFUTILS)

	if(${DWFUTILS_VERHPATH} STREQUAL DWFUTILS_VERHPATH-NOTFOUND)
		message(WARNING "   Could not find Version.h, please check your DwfUtils installation.")
		set(DWFUTILS_VERSION "0") # Being unable to identify library version is not considered as a critical failure
	else()
		file(READ ${DWFUTILS_VERHPATH}/Version.h VERH) # Read file content

		# Locate version Ids
		string(REGEX MATCHALL "\n *#define DWFUTILS_VERSION_MAJOR +[0-9]+" XVERMAJ ${VERH}) # Find major version Id
		string(REGEX MATCH "\n *#define DWFUTILS_VERSION_MINOR +[0-9]+" XVERMIN ${VERH}) # Find minor version Id
		string(REGEX MATCH "\n *#define DWFUTILS_VERSION_REVISION +[0-9]+" XVERREV ${VERH}) # Find revision Id

		# Insulate Ids numbers
		string(REGEX REPLACE "\n *#define DWFUTILS_VERSION_MAJOR +" "" XVERMAJ ${XVERMAJ})
		string(REGEX REPLACE "\n *#define DWFUTILS_VERSION_MINOR +" "" XVERMIN ${XVERMIN})
		string(REGEX REPLACE "\n *#define DWFUTILS_VERSION_REVISION +" "" XVERREV ${XVERREV})

		# Assemble version number
		set(DWFUTILS_VERSION ${XVERMAJ}.${XVERMIN}.${XVERREV})
	endif()
endif()

#############################################################################

### Display library informations or error messages ###
if(DWFUTILS_FOUND)
	message(STATUS "   Found DwfUtils : ${DWFUTILS_LIBRARY}")
	message(STATUS "   Include Directory : ${DWFUTILS_INCLUDE}")
	message(STATUS "   Version : ${DWFUTILS_VERSION}")
else()
	message(FATAL_ERROR "\n   Could not find DwfUtils library !
   Please visit https://github.com/SignCodingDwarf/DwfUtils
   for further information and install instructions \n")
endif()

#############################################################################

#  ______________________________
# |                              |
# |    ______________________    |       
# |   |                      |   |
# |   |         sign         |   |
# |   |        coding        |   |
# |   |        dw@rf         |   |
# |   |         1.0          |   |
# |   |______________________|   |
# |                              |
# |______________________________|
#               |  |           
#               |  |             
#               |  |
#               |  |
#               |  |
#               |  |
#               |  |
#               |  |
#               |  |
#               |  |
#               |  |
#               |__|
