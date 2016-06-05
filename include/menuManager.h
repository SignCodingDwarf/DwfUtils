/*!
 * @file menuManager.h
 * @brief Class used to generate console menus to test applications more easily
 * @author Sign Coding Dwarf
 * @version 1.0
 * @date 05 June 2016
 *
 * Definition of the class used to generate a console menu to ease the testing of applications and presentation of the different use cases in properly split functions. <br>
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


#ifndef MENUMANAGER
#define MENUMANAGER

#include <iostream>
#include <string>
#include <map>

#include "common_defines.h"

/*! 
* @namespace dwf_utils
* @brief A namespace used to regroup all utilitary functions or classes spanning through multiple applications
*/
namespace dwf_utils
{
	/*! \class menuManager
	* \brief Class allowing to manage your application menu
	*
	* Class used to manage a console menu to call more easily to test functions with void *func(void) signature.
	* 
	*/
	class menuManager
	{
	public:
		/*!
		* @brief Constructor of the menuManager class
		* @param menuStart : Welcome text of the menu. Default text proposes to kill you
		* @param quitId : Id of the quit action as a string. Default is q.
		*
		* Constructor of the menuManager class allowing to initialize our class. 
		*
		*/
		menuManager(std::string menuStart = "The Dwarves shall kill you \nFor you didn\'t find a better menu introduction", std::string quitId = "q");

		/*!
		* @brief Destructor of the menuManager class
		*
		* Destructor of the menuManager class. Empties actions map.
		* Virtual function.
		*
		*/
		virtual ~menuManager();

		/*!
		* @brief Add menu action
		* @param actionId : Id of the action to perform as a string
		* @param callback : Function pointer on the action to perform. The function must have no return and no parameters.
		* @param description : Description of the action as a string
		* @return EXEC_SUCCESS if action could be added and EXEC_FAILURE otherwise
		*
		* Add an action with its Id and its description. The action is only added if its Id is not taken by another action.
		*
		*/
		int addAction(std::string actionId, void (*callback)(void), std::string description);

		/*!
		* @brief Run menu loop and wait user input for actions
		*
		* Displays the menu and enter the action loop. Stays in this function until the user asks for the quit action.
		*
		*/
		void enterMenu();

	protected:
		/*!
		* @brief Quit action
		*
		* Function called for the quit action. Also displays goodbye message.
		* Virtual function.
		*
		*/
		virtual void quit();

		std::string m_menuStart; /*!< Welcome message of menu */
		std::map<std::string, std::pair<void (*)(void), std::string> > m_menuActions; /*!< Map of actions associated with their description and Id */
		bool m_quit; /*!< Quit menu flag */
		std::string m_quitId; /*!< Id of the quit action */
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
