/*!
 * @file main.cpp
 * @brief Test of fileSplitter.h
 * @author Sign Coding Dwarf
 * @version 1.0
 * @date 05 June 2016
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
#include "menuManager.h"

using namespace std;

/*! \class coordinates
* \brief Example class containing coordinates
*
* Example class that allows to store and display 3D coordinates with an operator<< to be stored in file.
* 
*/
class coordinates
{
public:
	coordinates(float x=1.0, float y=2.1, float z=0.0) : m_x(x), m_y(y),m_z(z)
	{
	}

	void display(ostream& flux) const
	{
		flux << m_x << " " << m_y << " " << m_z;
	}

	void changeCoord(float dx, float dy, float dz)
	{
		m_x += dx;
		m_y += dy;
		m_z += dz;
	}

protected:
	float m_x;
	float m_y;
	float m_z;
};

ostream& operator<<( ostream &flux, coordinates const& coord )
{
	coord.display(flux);
	return flux;
}

/*!
* @brief Example of write file splitting
*
* Test of file splitter class with size condition on the number of operator< calls.
*
*/
void testWrite()
{
	cout << "Example of write file splitting" << endl << endl;

	cout << "Go in the log folder. You should see 5 files : " << endl;
	cout << "   - testWriteSplit_0 contains coordinates 0 to 4" << endl;
	cout << "   - testWriteSplit_1 contains coordinates 5 to 9" << endl;
	cout << "   - testWriteSplit_2 contains coordinates 10 to 14" << endl;
	cout << "   - testWriteSplit_3 contains coordinates 15 to 19" << endl;
	cout << "   - testWriteSplit_4 is empty" << endl;

	dwf_utils::fileSplitter fS("logs/testWriteSplit", ".txt", 20); // Create file
	coordinates c;

	for(unsigned int i = 0; i < 20; ++i)
	{
		if(fS.getStatus()) // Check if file could be opened and is ready for writing
		{
			fS << i << " : " << c << endl; // 4 operator<< calls by loop means 5 points are stored in each file
		}
		else
		{
			cout << "Error, cannot write in file" << endl;
		}
		c.changeCoord(0.5, -0.2, 0.1); // Move point
	}
}

/*!
* @brief Program Entry point
* @return EXIT_SUCCESS
*
*/
int main()
{
	string menuHead = "************************************************\n";
	      menuHead += "*                                              *\n";   
	      menuHead += "*          Test of fileSplitter class          *\n";   
	      menuHead += "*                                              *\n";
	      menuHead += "************************************************";      	

	dwf_utils::menuManager menu(menuHead);

	menu.addAction("1", &testWrite, "Example of write file splitting");

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
