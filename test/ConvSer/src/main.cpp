/*!
 * @file main.cpp
 * @brief Test of convUtils.h and serialUtils.h
 * @author Sign Coding Dwarf
 * @version 2.0
 * @date 05 June 2016
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
#include "menuManager.h"

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
* @brief Test of conversion functions
*
* Basic examples of conversion functions
*
*/
void testConvUtils()
{
	cout << "Basic Conversion Examples" << endl << endl;

	cout << "Double to string" << endl;
	double c = 2.15;
	string s("Converted string : ");
	s += dwf_utils::toString<double>(c);
	cout << s << endl << endl;	

	cout << "Bool to string, true appears as 1 and false as 0" << endl;
	bool f = true;
	s = "Conversion of true to string : ";
	s += dwf_utils::toString<bool>(f);
	cout << s << endl;
	s = "Conversion of false to string : ";
	s += dwf_utils::toString<bool>(false);
	cout << s << endl << endl;

	cout << "Conversion of int to and back from string" << endl;
	int i = 42;
	s = dwf_utils::toString<int>(i);
	int j = dwf_utils::fromString<int>(s);
	cout << "Int after conversion : " << j << endl << endl;
}

/*!
* @brief Issues of conversion functions
*
* Illustrate the need for converted classes to have operator<<, operator>> and default constructor. Uncomment the appropriate lines to create a compile error.
*
*/
void testConvIssue()
{
	cout << "This test case does nothing. Uncomment the appropriate functions in main.cpp and recompile to generate compile errors because dummyFail class has no operator<<, operator>> and default constructor" << endl;

	// Problematic Case : dummyFail has no operator<<. Compile will fail.
	string s = "Chaine Convertie ";	
	dummyFail o(4);
	//s += dwf_utils::toString<dummyFail>(o); // !!! Uncomment to generate a compile error

	// Problematic Case 2 : dummyFail has no operator>> and default constructor. Compile will fail. 
	//o = dwf_utils::fromString<dummyFail>(s); // !!! Uncomment to generate a compile error
}

/*!
* @brief Serialization example
*
* Illustrates basic serialization calls and use of max size parameter
*
*/
void testSerialization()
{
	cout << "Basic Serialization Examples" << endl << endl;

	string s = "";
	string separator = ";";

	cout << "Adding \"0106\"" << endl;
	if(dwf_utils::strSerialize<string>(s, string("0106"), separator) == EXEC_SUCCESS)
	{
		cout << "Addition done" <<endl;		
	}
	else
	{
		cout << "Addition failed because string length after addition would have exceeded allowed size" <<endl;		
	}
	cout << "Serialized string : " << s << endl << endl;

	cout << "Adding 12.324" << endl;
	// Adds a double, default separator is ';' so we stay consistent
	if(dwf_utils::strSerialize<double>(s, 12.324) == EXEC_SUCCESS)
	{
		cout << "Addition done" <<endl;		
	}
	else
	{
		cout << "Addition failed because string length after addition would have exceeded allowed size" <<endl;		
	}
	cout << "Serialized string : " << s << endl << endl;

	cout << "Adding 14.451 but force maximal string size to 12 characters" << endl;
	// Adds another double and check for maximum size of the assembled string.
	if(dwf_utils::strSerialize<double>(s, 14.451, separator, 12) == EXEC_SUCCESS)
	{
		cout << "Addition done" <<endl;		
	}
	else
	{
		cout << "Addition failed because string length after addition would have exceeded allowed size" <<endl;		
	}
	cout << "Serialized string : " << s << endl << endl;

	// Other serializations
	cout << "Adding -1.54" << endl;
	if(dwf_utils::strSerialize<double>(s, -1.54) == EXEC_SUCCESS)
	{
		cout << "Addition done" <<endl;		
	}
	else
	{
		cout << "Addition failed because string length after addition would have exceeded allowed size" <<endl;		
	}
	cout << "Serialized string : " << s << endl << endl;

	cout << "Adding 0.666" << endl;
	if(dwf_utils::strSerialize<double>(s, 0.666) == EXEC_SUCCESS)
	{
		cout << "Addition done" <<endl;		
	}
	else
	{
		cout << "Addition failed because string length after addition would have exceeded allowed size" <<endl;		
	}
	cout << "Serialized string : " << s << endl << endl;

}

/*!
* @brief Deserialization example
*
* Illustrates basic deserialization calls and especially using position update to deserialize in a loop
*
*/
void testDeserialization()
{
	cout << "Basic Deserialization Examples" << endl << endl;

	unsigned int pos = 0;
	double d = 0.0;
	int n = 0;
	string s  = "0106;12.324;-1.54;0.666";
	cout << "Original String : " << s << endl << endl;

	// Example of deserialization
	dwf_utils::strDeserialize(s, n, pos, ";"); // n and pos are updated after extraction
	cout << "Extracted Integer : " << n << endl;
	
	// Serial extraction of several data of identical type
	bool extractionRunning = true;
	do
	{
		extractionRunning = dwf_utils::strDeserialize(s, d, pos, ";") == EXEC_SUCCESS; // Detect end of extraction
		cout << "Extracted Double : " << d << endl;
	}while(extractionRunning);

	cout << "I'm done extracting" << endl;
}

/*!
* @brief Program Entry point
* @return EXIT_SUCCESS
*
*/
int main()
{
	string menuHead = "**************************************************\n";
	      menuHead += "*                                                *\n";   
	      menuHead += "* Test of conversion and serialization functions *\n";   
	      menuHead += "*                                                *\n";
	      menuHead += "**************************************************";      	

	dwf_utils::menuManager menu(menuHead);

	menu.addAction("1", &testConvUtils, "Basic Conversion Examples");
	menu.addAction("2", &testConvIssue, "Conversion Compile error examples");
	menu.addAction("3", &testSerialization, "Basic Serialization Examples");
	menu.addAction("4", &testDeserialization, "Basic Deserialization Examples");

	menu.enterMenu();	

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
