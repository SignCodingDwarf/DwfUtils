/*!
 * @file main.cpp
 * @brief Test of fileSplitter.h
 * @author Sign Coding Dwarf
 * @version 1.0
 * @date 15 May 2016
 *
 * Test program and use cases of fileSplitter.h methods 
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

#include <iostream>

#include "common_defines.h"
#include "fileSplitter.h"
#include "Version.h"

using namespace std;

/*!
* @brief Program Entry point
* @return EXIT_SUCCESS
*
*/
int main()
{
	cout << "Test file_Split" << endl;
	dwf_utils::fileSplitter fS("logs/testFile", ".txt", 10);
	
	for(unsigned int i = 0; i < 20; ++i)
	{
		//cout << i << endl;
		if(fS.getStatus())
		{
			fS << i << endl;
		}
		else
		{
			cout << "Error" << endl;
		}
	}

	return EXIT_SUCCESS;
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
