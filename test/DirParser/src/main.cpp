/*!
 * @file main.cpp
 * @brief Test of dirParser class
 * @author Sign Coding Dwarf
 * @version 2.0
 * @date 05 June 2016
 *
 * Test program for dirParser class and example of inheritance to define application folders. <br>
 * To see differences between folders do the following (with \a \<location\> path to test/DirParser) <br>
 * \a cd \a \<location\>/test <br>
 * \a DirParser/TestDirParser
 *
 */

#include <iostream>

#include "dirParser.h"
#include "menuManager.h"

using namespace std;

/*! \class applicationDir
* \brief Example of class inheriting from dirParser to define application specific directories
*
* Class inheriting from dirParser to define application specific directories such as log files location, images location or directory containing test files.
* 
*/
class applicationDir : public dwf_utils::dirParser
{
public:
	applicationDir(unsigned int maxPathLength = PATH_MAX) : dirParser(maxPathLength)
	{
		setAddDir();
	}

	string getImgs() const
	{
		return m_images;
	}

	string getLog() const
	{
		return m_log;
	}

	string getTest() const
	{
		return m_testFiles;
	}

	virtual bool update()
	{
		m_dirLoaded = true;
		setDir();
		setAddDir();
		return m_dirLoaded;
	}

protected:
	void setAddDir() // Set inherited class specific directories
	{
		m_images = m_exeLoc + "images/";
		if(m_images.size() > m_maxPathLength) // You may be willing to reject directories names that are superior to desired name length.
		{
			m_images = "";
			m_dirLoaded = false;
		}	
		m_log = m_WDir + "log/";
		if(m_log.size() > m_maxPathLength) // You may be willing to reject directories names that are superior to desired name length.
		{
			m_log = "";
			m_dirLoaded = false;
		}
		m_testFiles = m_exeLoc + "test/";
		if(m_testFiles.size() > m_maxPathLength) // You may be willing to reject directories names that are superior to desired name length.
		{
			m_testFiles = "";
			m_dirLoaded = false;
		}
	}

	string m_images;
	string m_log;
	string m_testFiles;
};

/*!
* @brief Basic parsing test
*
* Basic test with succeding parsing at class creation
*
*/
void testDirParser()
{
	cout << "Basic dirParser test" << endl << endl;

	// Simple example
	dwf_utils::dirParser fP(500);
	if(fP.getDirLoaded())
	{
		cout << "Application Location : " << fP.getExeLoc() << endl; // Should display <location>/test/DirParser/
		cout << "Working Directory : " << fP.getWDir() << endl; // Should display <location>/test/ 
	}
	else
	{
		cout << "Could not find application folders" << endl;
	}
}

/*!
* @brief Reload example
*
* Example of failed load due to insufficient path size allowed and shows how update can be called to reload paths
*
*/
void testReload()
{
	cout << "dirParser size error and reload example" << endl << endl;

	// Example with error and reload
	dwf_utils::dirParser fP2(5); //Insufficient path length
	if(fP2.getDirLoaded())
	{
		cout << "Application Location : " << fP2.getExeLoc() << endl; // Should display <location>/test/DirParser/
		cout << "Working Directory : " << fP2.getWDir() << endl; // Should display <location>/test/ 
	}
	else
	{
		cout << "Could not find application folders" << endl;
		cout << "Reloading" << endl;
		fP2.setMaxPathLength(); // Set path length to default value
		if(fP2.update()) // Do update and check it went fine
		{
			cout << "Application Location : " << fP2.getExeLoc() << endl; // Should display <location>/test/DirParser/
			cout << "Working Directory : " << fP2.getWDir() << endl; // Should display <location>/test/ 
		}
		else
		{
			cout << "Could not find application folders after update" << endl;
		}

	}	
}

/*!
* @brief Inheritance example
*
* Illustrates how diParser class can be inherited to define application specific folders
*
*/
void testInheritance()
{
	cout << "Inheritance example" << endl << endl;

	// Example with inherited class
	applicationDir aD(100);
	if(aD.getDirLoaded())
	{
		cout << "Application Location : " << aD.getExeLoc() << endl; // Should display <location>/test/DirParser/
		cout << "Working Directory : " << aD.getWDir() << endl; // Should display <location>/test/ 
		cout << "Images Directory : " << aD.getImgs() << endl; // Should display <location>/test/DirParser/images/ 
		cout << "Log Directory : " << aD.getLog() << endl; // Should display <location>/test/log/ 
		cout << "Test Files Directory : " << aD.getTest() << endl; // Should display <location>/test/DirParser/test/ 
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
	      menuHead += "*            Test of dirParser class           *\n";   
	      menuHead += "*                                              *\n";
	      menuHead += "************************************************";      	

	dwf_utils::menuManager menu(menuHead);

	menu.addAction("1", &testDirParser, "Basic dirParser test");
	menu.addAction("2", &testReload, "dirParser size error and reload example");
	menu.addAction("3", &testInheritance, "Inheritance example");

	menu.enterMenu();	

	return EXIT_SUCCESS;
}
