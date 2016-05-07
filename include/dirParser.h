/*!
 * @file dirParser.h
 * @brief Class used to parse working directory and program location.
 * @author Sign Coding Dwarf
 * @version 1.0
 * @date 06 May 2016
 *
 * Definition of the class used to parse working directory and programm location. Adapted to work both on Windows and Linux.
 * Can be inherited according to application needs to add other directories.
 * Based on http://stackoverflow.com/questions/143174/how-do-i-get-the-directory-that-a-program-is-running-from
 *
 */

/* 
Copyright 2016 SignCodingDwarf

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/


#ifndef DIRPARSER
#define DIRPARSER

#include <iostream>
#include <string>

#ifdef _WIN32
	#include <direct.h>
	#include <windows.h>
#elif __linux__
	#include <unistd.h>
	#include <limits.h>
 #endif

/*! 
* @namespace dwf_utils
* @brief A namespace used to regroup all utilitary functions or classes spanning through multiple applications
*/
namespace dwf_utils
{
	/*! \class dirParser
	* \brief Class for working directory and program location parsing
	*
	* Class used to parse working directory and program location. Can be inherited according to application needs to define applicative folders.
	* 
	*/
	class dirParser
	{
	public:
		/*!
		* @brief Constructor of the dirParser class
		* @param maxPathLength : maximal size of the paths. Default is system maximal size PATH_MAX. 
		*
		* Constructor of the dirParser class allowing to initialize the working directory and program location. 
		*
		*/
		dirParser(unsigned int maxPathLength = PATH_MAX);

		/*!
		* @brief Destructor of the dirParser class
		*
		* Destructor of the dirParser class. Currently does nothing.
		* Virtual function.
		*
		*/
		virtual ~dirParser(void);

		/*!
		* @brief Know if directories could be loaded
		* @return TRUE if directories could be loaded and FALSE otherwise
		*
		* Know if directories loading process went fine.
		* Constant function.
		*
		*/
		bool getDirLoaded() const;

		/*!
		* @brief Get program location
		* @return Program location as a string terminated by the / or \\ character or an empty string if could not be loaded.
		*
		* Get program locationr (i.e. directory in which the executable is located).
		* Constant function.
		*
		*/
		std::string getExeLoc() const;

		/*!
		* @brief Get working directory
		* @return Working directory as a string terminated by the / or \\ character or an empty string if could not be loaded.
		*
		* Get working directory (i.e. directory from which the executable is run).
		* Constant function.
		*
		*/
		std::string getWDir() const;

		/*!
		* @brief Get maximal length of path names
		* @return Maximal length of path names as an unsigned int
		*
		* Get maximal length of path names.
		* Constant function.
		*
		*/
		unsigned int getMaxPathLength() const;

		/*!
		* @brief Set maximal length of path names
		* @param maxPathLength : maximal size of the paths. Default is system maximal size PATH_MAX. 
		*
		* Set maximal length of path names.
		*
		*/
		void setMaxPathLength(unsigned int maxPathLength = PATH_MAX);

		/*!
		* @brief Function used to update the working directory and program location.
		* @return TRUE if values could be updated, false otherwise
		*
		* Function allowing to update the working directory and program location during execution.
		* Its output can also be obtained through a getDirLoaded call.
		* Virtual function.
		*
		*/
		virtual bool update();

	protected:
		/*!
		* @brief Function used to set the working directory and program location.
		*
		* Function allowing to set the working directory and program location.
		* Done during initialization but may be done especially if initial run failed.
		* Protected function. May be called again through update function.
		*
		*/
		void setDir();

		std::string m_exeLoc; /*!< Program Location folder as a string */
		std::string m_WDir; /*!< Working Directory as a string */
		bool m_dirLoaded; /*!< Were directories loaded ? */
		unsigned int m_maxPathLength; /*!< Max size of path names */
	};
}

#endif

//  ______________________________
// |                              |
// |    ______________________    |       
// |   |                      |   |
// |   |         sign         |   |
// |   |        coding        |   |
// |   |        dw@rf         |   |
// |   |         1.0          |   |
// |   |______________________|   |
// |                              |
// |______________________________|
//               |  |           
//               |  |             
//               |  |
//               |  |
//               |  |
//               |  |
//               |  |
//               |  |
//               |  |
//               |  |
//               |  |
//               |__|
