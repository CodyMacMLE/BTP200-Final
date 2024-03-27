/* Citation and Sources...
Final Project Milestone MS4
Module: Patient
Filename: Patient.cpp
Version 1.0
Author   Cody MacDonald
Revision History
-----------------------------------------------------------
Date      Reason
2024/03/27  Preliminary release
2024/03/27  Added clear buffer from github tutorial to Patient::read()
-----------------------------------------------------------
1.	Clearing buffer using max stream buffer size template + limits module (cin.clear & .ignore)
	https://gist.github.com/leimao/418395bf920eb70b2b11fe89d7c1f738
----------------------------------------------------------- */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <limits>
#include <cstring>
#include <iomanip>
#include "Patient.h"
namespace seneca {

	Patient::Patient(int ticketNo) : m_ticket(ticketNo)
	{
		m_patientName = nullptr;
		m_ohipNo = 0;
	}

	Patient::Patient(const Patient& that) : m_ticket(that.number()){
		m_patientName = nullptr;
		*this = that;
	}

	Patient& Patient::operator= (const Patient& that) {
		// 1. Check self-assignment
		if (this != &that)
		{
			// 2. Clean-up 
			delete[] m_patientName;

			// 3. Shallow copy
			this->m_ohipNo = that.m_ohipNo;
			this->m_ticket = that.m_ticket;

			// 4. Deep copy
			if (that.m_patientName != nullptr)
			{
				this->m_patientName = new char[strlen(that.m_patientName) + 1];
				strcpy(this->m_patientName, that.m_patientName);
			}
			else
			{
				this->m_patientName = nullptr;
			}
		}
		return *this;
	}

	Patient::~Patient() {
		delete[] m_patientName;
	}

	bool Patient::operator==(const char type) const {
		return this->type() == type;
	}

	bool Patient::operator==(const Patient& that) const {
		return (this->type() == that.type()) ? true : false;
	}

	void Patient::setArrivalTime() {
		this->m_ticket.resetTime();
	}

	Time Patient::time() const {
		return this->m_ticket.time();
	}

	int Patient::number() const{
		return this->m_ticket.number();
	}

	Patient::operator bool() const{
		return (m_ohipNo == 0) ? false : true;
	}

	Patient::operator const char*() const{
		return m_patientName;
	}

	std::ostream& Patient::write(std::ostream& ostr) const {
		if (&ostr == &std::clog)
		{
			if ((bool)*this)
			{
				std::ios init(NULL);
				init.copyfmt(ostr); // Copies default 'out' formatting

				ostr.width(53);
				ostr.fill('.');
				ostr << std::left << m_patientName << m_ohipNo;
				ostr.width(5);
				ostr.fill(' ');
				ostr << std::right << this->number() << " " << this->time();

				ostr.copyfmt(init); // Restores out formatting to copied format 'init'
			}
			else
			{
				ostr << "Invalid Patient Record\n";
			}
		}
		else if (&ostr == &std::cout)
		{
			if ((bool)*this)
			{
				ostr << m_ticket << "\n" << m_patientName << ", OHIP: " << m_ohipNo << "\n";
			}
			else
			{
				ostr << "Invalid Patient Record\n";
			}
		}
		else // csv format
		{
			ostr << this->type() << "," << m_patientName << "," << m_ohipNo << ",";
			m_ticket.write(ostr);
		}
		return ostr;
	}

	std::istream& Patient::read(std::istream& istr) {
		if (&istr == &std::cin)
		{
			// Get Name
			std::cout << "Name: ";
			char name[50 + 1];
			istr.get(name, 51);
			istr.clear();
			istr.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			delete[] m_patientName;
			m_patientName = new char[strlen(name) + 1];
			strcpy(m_patientName, name);

			// Get OHIP
			std::cout << "OHIP: ";
			char ohip[15 + 1];
			bool hasWhitespace = false;
			bool hasChar = false;
			bool exitFlag = false;
			do {
				istr.get(ohip, 16);
				istr.clear();
				istr.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				

				for (int i = 0; ohip[i] != '\0'; ++i)
				{
					if (ohip[i] == ' ')
					{
						hasWhitespace = true;
						for (int j = 0; j <= i; ++j)
							ohip[j] = '\0';
					}
					else if (!isdigit(ohip[i]) && ohip[i] != '-')
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

				m_ohipNo = std::atoi(ohip);
				if (m_ohipNo < 100000000 || m_ohipNo > 999999999)
				{
					std::cout << "Invalid value enterd, retry[100000000 <= value <= 999999999]: ";
				}
				else
				{
					exitFlag = true;
				}
			} while (!exitFlag);
		}
		else // CSV format
		{
			// Name
			char name[50 + 1];
			istr.get(name, 51, ',');
			delete[] m_patientName;
			m_patientName = new char[strlen(name) + 1];
			strcpy(m_patientName, name);

			// OHIP
			istr.ignore(10000000, ',');
			istr >> m_ohipNo;
			istr.ignore(10000000, ',');
			// Ticket
			m_ticket.read(istr);
		}
		return istr;
	}
}