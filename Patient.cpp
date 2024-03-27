#define _CRT_SECURE_NO_WARNINGS
/* Citation and Sources...
Final Project Milestone MS3
Module: Patient
Filename: Patient.cpp
Version 1.0
Author   Cody MacDonald
Revision History
-----------------------------------------------------------
Date      Reason
2024/03/20  Preliminary release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
----------------------------------------------------------- */
#include <iostream>
#include <iomanip>
#include "Patient.h"
namespace seneca {

	Patient::Patient(int ticketNo)
	{
		m_patientName = nullptr;
		m_ohipNo = 0;
		m_ticket.setNumber(ticketNo); // Is not setting ticketNo
	}

	Patient::Patient(const Patient& that) {
		delete[] m_patientName;
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
		return this->m_ohipNo == that.m_ohipNo;
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

	Patient::operator bool(){
		return (m_ohipNo == 0) ? false : true;
	}

	Patient::operator const char*() const{
		return m_patientName;
	}

	std::ostream& Patient::write(std::ostream& out) const {
		if (&out == &std::clog)
		{
			if ((bool)this)
			{
				out << "Invalid Patient Record\n";
			}
			else
			{
				std::ios init(NULL);
				init.copyfmt(out); // Copies default 'out' formatting

				out.width(53);
				out.setf('.');
				out << std::left << m_patientName << m_ohipNo;
				out.width(5);
				out.setf(' ');
				out << std::right << this->number() << " " << this->time();

				out.copyfmt(init); // Restores out formatting to copied format 'init'
			}
		}
		else if (&out == &std::cout)
		{
			if ((bool)this)
			{
				out << "Invalid Patient Record\n";
			}
			else
			{
				out << m_ticket << "\n" << m_patientName << ", OHIP: " << m_ohipNo << "\n"; 
			}
		}
		else // csv format
		{
			out << this->type() << "," << m_patientName << "," << m_ohipNo << ",";
			m_ticket.write(out);
		}
		return out;
	}

	std::istream& Patient::read(std::istream& in) {
		if (&in == &std::cin)
		{
			// Get Name
			std::cout << "Name: ";
			char name[50 + 1];
			in.get(name, 50);
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
				in.ignore(); // clear buffer
				in.get(ohip, 15); 
				

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
			in.get(name, 50);
			delete[] m_patientName;
			m_patientName = new char[strlen(name) + 1];
			strcpy(m_patientName, name);

			// OHIP
			in.ignore(strlen(name) + 1);
			char ohip[9 + 1];
			in.get(ohip, 9);
			m_ohipNo = std::atoi(ohip);

			// Ticket
			m_ticket.read(in);
		}
		return in;
	}
}