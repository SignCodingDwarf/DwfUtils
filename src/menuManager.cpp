/*!
 * @file menuManager.h
 * @brief Class used to generate console menus to test applications more easily
 * @author Sign Coding Dwarf
 * @version 1.0
 * @date 05 June 2016
 *
 * Implementation of the class used to generate a console menu to ease the testing of applications and presentation of the different use cases in properly split functions. <br>
 * To test if it is available with your library version use <br>
 * \a \#if \a DWFUTILS_VERSION_NUMERIC>=111552336
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


#include "menuManager.h"

namespace dwf_utils
{
	menuManager::menuManager(std::string menuStart, std::string quitId) : m_menuStart(menuStart), m_quitId(quitId)
	{
	}

	menuManager::~menuManager()
	{
		m_menuActions.clear();
	}

	int menuManager::addAction(std::string actionId, void (*callback)(void), std::string description)
	{
		if(m_menuActions.insert(std::pair<std::string, std::pair<void (*)(void), std::string> >(actionId, std::pair<void (*)(void), std::string>(callback, description))).second)
		{
			return EXEC_SUCCESS;
		}
		else
		{
			return EXEC_FAILURE;
		}
	}

	void menuManager::enterMenu()
	{
		bool error = false;
		std::string action = "";
		m_quit = false;
		do // Enter menu loop
		{
			std::cout << "\033[2J\033[1;1H"; // clear terminal screen
			
			std::cout << m_menuStart << std::endl;
			std::cout << "************************************************" << std::endl;
			if(error) // Display error message if previous action was invalid
			{
				std::cout << "   The action " << action << " is invalid" << std::endl;
				error = false;
			}
#if USE_AUTO_LOOPS
			for(auto const &actionId : m_menuActions) // Nice and simple :)
			{
				std::cout << "   " << actionId.first << " - " << actionId.second.second << std::endl;
			}
#else
			std::map<std::string, std::pair<void (*)(void), std::string> >::const_iterator actionId;
			for(actionId = m_menuActions.begin(); actionId != m_menuActions.end(); ++actionId)
			{
				std::cout << "   " << actionId->first << " - " << actionId->second.second << std::endl;
			}
#endif
			std::cout << "   " << m_quitId << " - Quit Menu" << std::endl;
			std::cout << "Select the desired action : " << std::endl;
			std::cin >> action; 

			std::map<std::string, std::pair<void (*)(void), std::string> >::iterator actionS = m_menuActions.find(action);
			if(actionS != m_menuActions.end())
			{
				std::cout << "\033[2J\033[1;1H"; // clear terminal screen before display of function
				actionS->second.first(); // Run the called action

				std::cout << "Press any touch to come back to menu or " << m_quitId << " to quit" << std::endl;
				std::cin >> action;
			}
			else
			{
				error = true;
			}

			if(action == m_quitId)
			{
				quit();
			}	
			
		}while(!m_quit);
	}

	void menuManager::quit()
	{
		m_quit = true;
		std::cout << "************************************************" << std::endl; // You cannot really terminate a menu
		std::cout << "*                                              *" << std::endl;
		std::cout << "*                 I\'ll be back                 *" << std::endl;
		std::cout << "*                                              *" << std::endl;
		std::cout << "************************************************" << std::endl;
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
