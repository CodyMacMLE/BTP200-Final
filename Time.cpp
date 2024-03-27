/* Citation and Sources...
Final Project Milestone MS4
Module: Time
Filename: Time.cpp
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
#include <iomanip>
#include "Time.h"
#include "Utils.h"

namespace seneca 
{
	Time::Time(unsigned int min)
	{
		if (min >= 0)
			this->m_minutes = min;
		else
			this->m_minutes = 0u;
	}

	Time& Time::reset()
	{
		this->m_minutes = U.getTime();
		return *this;
	}

	std::ostream& Time::write(std::ostream& out) const
	{
		int hours, minutes;
		this->convertTimeHours(hours, minutes);

		std::ios init(NULL);
		init.copyfmt(out); // Copies default 'out' formatting

		out << std::setw(2) << std::setfill('0') << std::right;
		out << hours << ":";
		out << std::setw(2) << std::setfill('0') << std::right;
		out << minutes;

		out.copyfmt(init); // Restores out formatting to copied format 'init'

		return out;
	}

	std::istream& Time::read(std::istream& in)
	{
		char colon;
		int hours, minutes;
		in >> hours;
		if (in.peek() != ':')
			in.setstate(in.failbit);
		in >> colon;
		in >> minutes;
		if (in.good())
			this->m_minutes = minutes + (hours * 60);

		return in;
	}

	void Time::convertTimeHours(int& hours, int& minutes) const
	{
		hours = int(this->m_minutes) / 60;
		minutes = int(this->m_minutes) % 60;
	}

	Time::operator unsigned int() const
	{
		return this->m_minutes;
	}

	Time& Time::operator*= (int val)
	{
		this->m_minutes *= val;
		return *this;
	}

	Time& Time::operator-= (const Time& that)
	{
		this->m_minutes -= that.m_minutes;
		if (this->m_minutes < 0)
			this->m_minutes += 1440;
		return *this;
	}

	Time Time::operator-(const Time& that) const
	{
		int timeDif = this->m_minutes - that.m_minutes;
		if (timeDif < 0)
			timeDif += 1440;
		Time tmp(timeDif);
		return tmp;

	}

	std::ostream& operator<< (std::ostream& out, const Time time)
	{
		time.write(out);
		return out;
	}

	std::istream& operator>> (std::istream& in, Time& time)
	{
		time.read(in);
		return in;
	}
}