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
#include "TestPatient.h"

namespace seneca {

	/// <summary>
	/// Global var for next ticket
	/// </summary>
	int nextTestTicket = 1;

	TestPatient::TestPatient()
		: Patient(nextTestTicket) 
	{
		++nextTestTicket;
	}

	char TestPatient::type() const
	{
		return 'C';
	}

	std::ostream& TestPatient::write(std::ostream& ostr) const
	{
		if (&ostr == &std::cout)
		{
			ostr << "Contagion TEST\n";
		}
		Patient::write(ostr);
		return ostr;
	}

	std::istream& TestPatient::read(std::istream& istr)
	{
		Patient::read(istr);
		if (&istr != &std::cin)
		{
			nextTestTicket = this->number() + 1;
		}
		return istr;
	}
}