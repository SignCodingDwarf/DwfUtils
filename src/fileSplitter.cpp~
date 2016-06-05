/*!
 * @file fileSplitter.cpp
 * @brief Class used to manage storing of big data in several files
 * @author Sign Coding Dwarf
 * @version 1.0
 * @date 15 May 2016
 *
 * Implementation of the class used to store a big set of data in multiple subfiles to get smaller files and avoid too much data loss due to file corruption or bugs.
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

#include "fileSplitter.h"

namespace dwf_utils
{
	fileSplitter::fileSplitter(std::string baseName, std::string extension, unsigned long fileSize) : m_baseName(baseName), m_fileSize(fileSize), m_fileNb(0), m_status(true), m_written(0), m_extension(extension)
	{
		addDot();
		std::string fileName = m_baseName + "_0" + m_extension;
		m_file.open(fileName);
		if(!m_file)
		{
			m_status = false;
		}
	}  

	fileSplitter::~fileSplitter()
	{
		if(m_file)
		{
			m_file.close();
		}	
	}

	int fileSplitter::changeFile()
	{
		if(m_file)
		{
			m_file.close();
		}
		++ m_fileNb;
		m_written = 0;
		std::string fileName = m_baseName + "_" + toString(m_fileNb) + m_extension;
		m_file.open(fileName.c_str());
		if(!m_file)
		{
			m_status = false;
			return EXEC_FAILURE;
		}
		
		return EXEC_SUCCESS;
	}

	bool fileSplitter::getStatus() const
	{
		return m_status;
	}

	void fileSplitter::addDot()
	{
		if(m_extension[0] != '.') // Extension should start by a dot
		{
			m_extension.insert(m_extension.begin(), '.'); // Insert dot at the beginning of string
		}
	}
}

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
