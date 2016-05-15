/*!
 * @file fileSplitter.h
 * @brief Class used to manage storing of big data in several files
 * @author Sign Coding Dwarf
 * @version 1.0
 * @date 15 May 2016
 *
 * Definition of the class used to store a big set of data in multiple subfiles to get smaller files and avoid too much data loss due to file corruption or program bugs.
 * The amount of data to store is determined by the number of call to operator<<. User may also manually trigger a file change.
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


#ifndef FILESPLITTER
#define FILESPLITTER

#include <iostream>
#include <fstream>
#include <string>

#include "common_defines.h"
#include "convUtils.h"

/*! 
* @namespace dwf_utils
* @brief A namespace used to regroup all utilitary functions or classes spanning through multiple applications
*/
namespace dwf_utils
{
	class fileSplitter
	{
	public:
		fileSplitter(std::string baseName, std::string extension, unsigned long fileSize);  

		virtual ~fileSplitter();

		virtual int changeFile();

		bool getStatus() const;

		template <class T>
		fileSplitter& operator<<(T const& data)
		{
			if(m_status)
			{
		    		m_file << data;
				++m_written;
				if(m_written >= m_fileSize)
				{
					changeFile() == EXEC_FAILURE && (m_status = false); 
				}
			}
			return *this;
		}

		fileSplitter& operator<<(std::ostream& (*pf)(std::ostream&))
		{
			if(m_status)
			{
		    		pf(m_file);
				++m_written;
				if(m_written >= m_fileSize)
				{
					changeFile() == EXEC_FAILURE && (m_status = false); 
				}
			}
			return *this;
		}


	protected:
		std::ofstream m_file; /*!< Flux to file */
		std::string m_baseName; /*!< Base name of files */
		std::string m_extension; /*!< Extension of files */
		unsigned long m_fileSize; /*!< Maximal number of operator<< calls */
		unsigned long m_written; /*!< Current number of operator<< calls */
		unsigned long m_fileNb; /*!< Number of files already complete */
		bool m_status; /*!< Indicates status of class */
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
