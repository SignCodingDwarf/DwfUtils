/*!
 * @file main.cpp
 * @brief Test of convUtils.h and serialUtils.h
 * @author Sign Coding Dwarf
 * @version 1.0
 * @date 06 May 2016
 *
 * Test program and use cases of convUtils.h and serialUtils.h methods 
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
#include "serialUtils.h"
#include "Version.h"

using namespace std;

/*! \class dummyFail
* \brief Class to illustrate compile errors in conversion
*
* Class that doesn't contain the appropriate operators for the from or to string conversion. It is used to illustrate compile errors that occur in this situation.
* 
*/
class dummyFail
{
public:
	dummyFail(int i) : m_i(i)
	{
	}

protected:
	int m_i;
};

/*!
* @brief Program Entry point
* @return EXIT_SUCCESS
*
*/
int main()
{
	cout << "Test of convUtils.h" << endl;

	// Conversion of a double to a string
	double c = 2.15;
	string s("Chaine Convertie ");
	s += dwf_utils::toString<double>(c);
	cout << s << endl;

	// Conversion of a double to a string
	s = "Chaine Convertie ";
	bool f = true;
	s += dwf_utils::toString<bool>(f);
	cout << s << endl;

	// Conversion of a double to and the from string
	s = dwf_utils::toString<double>(c);
	c = dwf_utils::fromString<double>(s);
	cout << c << endl;

	// Problematic Case : dummyFail has no operator<<. Compile will fail.
	s = "Chaine Convertie ";	
	dummyFail o(4);
	//s += dwf_utils::toString<dummyFail>(o); // !!! Uncomment to generate a compile error

	// Problematic Case 2 : dummyFail has no operator>> and default constructor. Compile will fail. 
	//o = dwf_utils::fromString<dummyFail>(s); // !!! Uncomment to generate a compile error

	cout << "*********************" << endl;
	cout << "Test of serialUtils.h" << endl;

	s = "";
	string separator = ";";

	// Adds string with separator
	if(dwf_utils::strSerialize<string>(s, string("0106"), separator) == EXEC_SUCCESS)
	{
		cout << s << endl;
	}

	// Adds a double, default separator is ';' so we stay consistent
	if(dwf_utils::strSerialize<double>(s, 12.324) == EXEC_SUCCESS)
	{
		cout << s << endl;
	}

	// Adds another double and check for maximum size of the assembled string.
	if(dwf_utils::strSerialize<double>(s, 14.451, separator, 12) == EXEC_SUCCESS)
	{
		cout << s << endl;
	}
	else // It is over 12 characters so the addition is rejected
	{
		cout << "String too long" <<endl;
	}

	// Other serializations
	if(dwf_utils::strSerialize<double>(s, -1.54) == EXEC_SUCCESS)
	{
		cout << s << endl;
	}

	if(dwf_utils::strSerialize<double>(s, 0.666) == EXEC_SUCCESS)
	{
		cout << s << endl;
	}

	// Deserialization
	unsigned int pos = 0;
	double d = 0.0;
	int n = 0;

	// Example of deserialization
	dwf_utils::strDeserialize(s, n, pos, ";"); // n and pos are updated after extraction
	cout << "Extracted : " << n << endl;
	
	// Serial extraction of several data of identical type
	bool extractionRunning = true;
	do
	{
		extractionRunning = dwf_utils::strDeserialize(s, d, pos, ";") == EXEC_SUCCESS; // Detect end of extraction
		cout << "Extracted : " << d << endl;
	}while(extractionRunning);

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