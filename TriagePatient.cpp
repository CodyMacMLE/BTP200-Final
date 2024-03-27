/* Citation and Sources...
Final Project Milestone MS4
Module: TriagePatient
Filename: TriagePatient.cpp
Version 1.0
Author   Cody MacDonald
Revision History
-----------------------------------------------------------
Date      Reason
2024/03/27  Preliminary release
-----------------------------------------------------------
1.	Clearing buffer using max stream buffer size template + limits module (cin.clear & .ignore)
	https://gist.github.com/leimao/418395bf920eb70b2b11fe89d7c1f738
----------------------------------------------------------- */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <limits>
#include <cstring>
#include "TriagePatient.h"

namespace seneca {

	int nextTriageTicket = 1;
	/// <summary>
	/// Passes nextTriageTicket into the default constructor to build a patient, increases global var by 1
	/// </summary>
	TriagePatient::TriagePatient() :
		Patient (nextTriageTicket)
	{
		m_symptoms = nullptr;
		++nextTriageTicket;
	}

	/// <summary>
	/// Handles dallocate of m_symptoms
	/// </summary>
	TriagePatient::~TriagePatient()
	{
		delete[] m_symptoms;
	}

	/// <summary>
	/// returns type 'T';
	/// </summary>
	char TriagePatient::type() const
	{
		return 'T';
	}

	/// <summary>
	/// overrides write function of ioAble
	/// </summary>
	/// <param name="ostr">ostream type</param>
	/// <returns>out stream</returns>
	std::ostream& TriagePatient::write(std::ostream& ostr) const
	{
		if (&ostr == &std::cout)
		{
			ostr << "TRIAGE\n";
		}
		Patient::write(ostr);
		if (&ostr == &std::cout)
		{
			ostr << "Symptoms: " << m_symptoms << "\n";
		}
		else if (&ostr != &std::clog)
		{
			ostr << "," << m_symptoms;
		}
		return ostr;
	}

	/// <summary>
	/// reads from std::cin or csv format, increases nextTestPatient
	/// </summary>
	/// <param name="istr">istream type</param>
	/// <returns>in stream</returns>
	std::istream& TriagePatient::read(std::istream& istr)
	{
		delete[] m_symptoms;
		Patient::read(istr);

		if (&istr != &std::cin)
		{
			// Copy Triage Patient symptoms from csv
			char symptoms[511 + 1];
			istr.ignore(std::numeric_limits<std::streamsize>::max(), ',');
			istr.get(symptoms, 511, '\n');
			m_symptoms = new char[strlen(symptoms) + 1];
			strcpy(m_symptoms, symptoms);

			// Update next ticket num
			nextTriageTicket = this->number() + 1;
		}
		else
		{
			char symptoms[511 + 1];
			std::cout << "Symptoms: ";
			istr.get(symptoms, 511);
			istr.clear();
			istr.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			m_symptoms = new char[strlen(symptoms) + 1];
			strcpy(m_symptoms, symptoms);
		}

		if (istr.fail())
		{
			delete[] m_symptoms;
			m_symptoms = nullptr;
		}
		return istr;
	}
}