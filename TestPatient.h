#ifndef SENECA_TESTPATIENT_H
#define SENECA_TESTPATIENT_H
/* Citation and Sources...
Final Project Milestone MS4
Module: TestPatient
Filename: TestPatient.cpp
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

	class TestPatient :
		public Patient
	{
	public:
		/// <summary>
		/// Passes nextTestTicket into the default constructor to build a patient, increases var by 1
		/// </summary>
		TestPatient();

		/// <summary>
		/// returns type 'C';
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
#endif // !SENECA_TESTPATIENT_H
