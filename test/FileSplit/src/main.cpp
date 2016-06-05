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
* @brief Program Entry point
* @return EXIT_SUCCESS
*
*/
int main()
{
	cout << "Test file_Split" << endl;
	dwf_utils::fileSplitter fS("logs/testFile", ".txt", 20);
	coordinates c;

	for(unsigned int i = 0; i < 20; ++i)
	{
		//cout << i << endl;
		if(fS.getStatus())
		{
			fS << i << " " << c << endl;
		}
		else
		{
			cout << "Error" << endl;
		}
		c.changeCoord(0.5, -0.2, 0.1);
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
