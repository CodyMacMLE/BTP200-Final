/* Citation and Sources...
Final Project Milestone MS4
Module: IOAble
Filename: IOAble.cpp
Version 1.0
Author   Cody MacDonald
Revision History
-----------------------------------------------------------
Date      Reason
2024/03/19  Preliminary release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
----------------------------------------------------------- */
#define _CRT_SECURE_NO_WARNINGS
#include "IOAble.h"
namespace seneca {
	IOAble::~IOAble(){}

	std::ostream& operator<<(std::ostream& out, const IOAble& object)
	{
		object.write(out);
		return out;
	}

	std::istream& operator>>(std::istream& in, IOAble& object)
	{
		object.read(in);
		return in;
	}
}