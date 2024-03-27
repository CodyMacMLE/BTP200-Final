#define _CRT_SECURE_NO_WARNINGS
/* Citation and Sources...
Final Project Milestone MS1
Module: Menu
Filename: Menu.cpp
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
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Menu.h"

namespace seneca {
	Menu::Menu(const char* menuContent, int numberOfTabs)
	{
		this->m_tabCnt = numberOfTabs;
		this->m_optionsCnt = 0;

		if (menuContent != nullptr)
		{
			int menuContentSize = 1;
			for (int i = 0; menuContent[i] != '\0'; ++i)
				++menuContentSize;
			m_menuContent = new char[menuContentSize];
			strcpy(m_menuContent, menuContent);

			for (int i = 0; i< menuContentSize; ++i)
			{
				if (this->m_menuContent[i] == '\n')
					++this->m_optionsCnt;
			}
		}
		else
		{
			this->m_menuContent = nullptr;
			this->m_optionsCnt = 0;
		}	
	}

	Menu::~Menu()
	{
		delete[] m_menuContent;
	}
	
	Menu::Menu(const Menu& that)
	{
		this->m_menuContent = nullptr;
		*this = that;
	}

	Menu& Menu::operator= (const Menu& that)
	{
		if (this != &that)
		{
			delete[] this->m_menuContent;

			this->m_tabCnt = that.m_tabCnt;
			this->m_optionsCnt = that.m_optionsCnt;

			if (that.m_menuContent != nullptr)
			{
				int menuContentSize = sizeof(that.m_menuContent) / sizeof(char);
				this->m_menuContent = new char[menuContentSize];
				strcpy(this->m_menuContent, that.m_menuContent);
			}
			else
				this->m_menuContent = nullptr;
		}
		return *this;
	}

	std::ostream& Menu::display(std::ostream& out) const
	{
		addTab(out);
		for (int i = 0; m_menuContent[i] != '\0'; ++i)
		{
			out << m_menuContent[i];
			if (m_menuContent[i] == '\n')
				addTab(out);
		}
		out << std::endl;
		addTab(out);
		out << "0- Exit\n";
		addTab(out);
		out	<< "> ";
		return out;
	}

	void Menu::addTab(std::ostream& out) const
	{
		for (int i = 0; i < m_tabCnt; ++i)
			out << "   ";
	}

	int& Menu::operator>>(int& Selection)
	{
		display(std::cout);

		char tmp[10];
		bool hasWhitespace = false;
		bool hasChar = false;
		bool exitFlag = false;
		do {
			std::cin.getline(tmp, 10);

			for (int i = 0; tmp[i] != '\0'; ++i)
			{
				if (tmp[i] == ' ')
				{
					hasWhitespace = true;
					for (int j = 0; j <= i; ++j)
						tmp[j] = '\0';
				}
				else if (!isdigit(tmp[i]) && tmp[i] != '-')
					hasChar = true;
			}
			
			if (hasWhitespace)
			{
				std::cout << "Only enter an integer, try again: ";
				hasWhitespace = false;
				continue;
			} 
			else if (hasChar) 
			{
				std::cout << "Bad integer value, try again: ";
				hasChar = false;
				continue;
			}

			Selection = std::atoi(tmp);
			if (Selection < 0 || Selection > m_optionsCnt)
			{
				std::cout << "Invalid value enterd, retry[0 <= value <= " << m_optionsCnt << "]: ";
			}
			else
			{
				exitFlag = true;
			}
		} while (!exitFlag);

		return Selection;
	}
}

