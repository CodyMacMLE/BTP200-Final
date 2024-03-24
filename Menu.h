/* Citation and Sources...
Final Project Milestone MS1
Module: Menu
Filename: Menu.h
Version 1.0
Author   Cody MacDonald
Revision History
-----------------------------------------------------------
Date      Reason
2024/03/17  Preliminary release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
----------------------------------------------------------- */
#ifndef SENECA_MENU_H
#define SENECA_MENU_H
#include <iostream>

namespace seneca {
	class Menu {
		char* m_menuContent;
		int m_optionsCnt;
		int m_tabCnt;
	public:
		/// <summary>
		/// This constructor is designed to initialize a Menu object.
		/// </summary>
		/// <param name="menuContent">a pointer to a character string 
		/// menuContent</param>
		/// <param name="numberOfTabs">an optional integer numberOfTabs with a 
		/// default value of 0.</param>
		Menu(const char* menuContent, int numberOfTabs = 0);

		/// <summary>
		/// Handles the dynamic array of content in the menu { m_menuCOntent }.
		/// </summary>
		~Menu();

		/// <summary>
		/// Copy Constructor
		/// </summary>
		/// <param name="that">the object to be copied</param>
		Menu(const Menu& that);

		/// <summary>
		/// Copy Assignment Operator for Menu Object
		/// </summary>
		/// <param name="that">the object to be assigned</param>
		/// <returns></returns>
		Menu& operator= (const Menu& that);


		/// <summary>
		/// displays the menu to std::cout
		/// </summary>
		/// <param name="menu"></param>
		std::ostream& display(std::ostream& out = std::cout) const;

		/// <summary>
		/// Adds a tab {3 spaces}
		/// </summary>
		void addTab(std::ostream& out) const; 
		// Used so there is no code redundancy
		// Not necessarly needed in this object, may move to utils later.

		/// <summary>
		/// 
		/// </summary>
		int& operator>>(int& Selection);
	};
}
#endif // !SENECA_MENU_H
