#ifndef SENECA_TRIAGEPATIENT_H
#define SENECA_TRIAGEPATIENT_H
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
-----------------------------------------------------------
1.	Clearing buffer using max stream buffer size template + limits module (cin.clear & .ignore)
	https://gist.github.com/leimao/418395bf920eb70b2b11fe89d7c1f738
----------------------------------------------------------- */
#include <iostream>
#include "Patient.h"

namespace seneca {
	class TriagePatient :
		public Patient
	{
		/// <summary>
		/// Dynamic array of symptoms of triage patient on arrival { max_size = 512 + 1 }
		/// </summary>
		char* m_symptoms;
	public:
		/// <summary>
		/// Passes nextTriageTicket into the default constructor to build a patient, increases global var by 1
		/// </summary>
		TriagePatient();

		/// <summary>
		/// Handles dallocate of m_symptoms
		/// </summary>
		~TriagePatient();

		/// <summary>
		/// returns type 'T';
		/// </summary>
		char type() const;

		/// <summary>
		/// overrides write function of ioAble
		/// </summary>
		/// <param name="ostr">ostream type</param>
		/// <returns>out stream</returns>
		std::ostream& write(std::ostream& ostr) const;

		/// <summary>
		/// reads from std::cin or csv format, increases nextTestPatient
		/// </summary>
		/// <param name="istr">istream type</param>
		/// <returns>in stream</returns>
		std::istream& read(std::istream& istr);
	};
}
#endif // !SENECA_TRIAGEPATIENT_H
