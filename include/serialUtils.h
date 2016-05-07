/*!
 * @file serialUtils.h
 * @brief Definition of serialization or deserialization functions
 * @author Sign Coding Dwarf
 * @version 1.0
 * @date 06 May 2016
 *
 * Definition of functions used to serialize and deserialize a flux of data in a string.
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


#ifndef SERIAL_UTILS
#define SERIAL_UTILS

#include <string>

#include "common_defines.h"
#include "convUtils.h"

/*! 
* @namespace dwf_utils
* @brief A namespace used to regroup all utilitary functions or classes spanning through multiple applications
*/
namespace dwf_utils
{
	/*!
	* @brief To serialize a data into a string
	* @tparam T : type of the data to add to serial
	* @param serial : reference to the string containing the serialized data
	* @param toAdd : data to Add as a const
	* @param separator : const string represensenting the separator used. Default is ;
	* @param maxSize : optional maximal size of the serialized string. Default is 0, which means size is unlimited
	* @return EXEC_SUCCESS if data could be serialized, EXEC_FAILURE otherwise
	*
	* Templated Function to serialize a data of type T into a string and add the separator before the data if serialized string is not empty. Can also allow to check if you respect a maximal size for the serialized string.
	* T must contain operator<<.
	*
	*/
	template<typename T>
	int strSerialize(std::string &serial, const T toAdd, const std::string separator=";", const unsigned int maxSize = 0)
	{
		std::string str_toAdd = toString<T>(toAdd);
		bool maxSizeEmpty = serial.size() == 0 && str_toAdd.size() <= maxSize; // If string is empty, we use no separator so we just check str_toAdd size versus max size.
		bool maxSizeSep = serial.size() != 0 && str_toAdd.size() + serial.size() + separator.size() <= maxSize;
		if(maxSize == 0 || maxSizeEmpty || maxSizeSep)  // If size of the serialized string is unlimited or if the maximal size is not reached after addition, we can serialize the new data
		{
			if(serial.size() == 0) // If first element in string, we only add the data not the separator
			{
				serial = str_toAdd;
			}
			else
			{
				serial += separator + str_toAdd; // The addition paradigm assumes to add the separator first so that last element added is always data
			}
			return EXEC_SUCCESS;
		}
		else
		{
			return EXEC_FAILURE;
		}
	}

	/*!
	* @brief To deserialize a data from a string
	* @tparam T : type of the data to deserialize
	* @param serial : string to deserialize
	* @param extracted : reference to the extracted element
	* @param pos : reference to the position after which to start the extraction. Is updated with the position right after the last detected separator to simplify extraction in big chains
	* @param separator : const string represensenting the separator used. Default is ;
	* @return EXEC_SUCCESS if extraction could be done, EXEC_FAILURE otherwise (i.e. invalid separator for chain or extraction completed)
	*
	* Templated Function to extract a data of type T from a serialized string after a given position. T must contain operator>> and a default constructor.
	*
	*/
	template<typename T>
	int strDeserialize(std::string serial, T& extracted, unsigned int &pos, const std::string separator=";")
	{
		int ind = serial.find(separator, pos);

		// Extraction
		std::string elem = serial.substr(pos, ind-pos);
		pos = ind + 1;
		extracted = fromString<T>(elem);

		// Check extraction status
		if(ind != std::string::npos) 
		{
			return EXEC_SUCCESS;
		}
		else // no more separators were found, either serial string is not valid or deserialization ended
		{
			return EXEC_FAILURE;
		}
	}
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
