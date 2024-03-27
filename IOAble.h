/* Citation and Sources...
Final Project Milestone MS4
Module: IOAble
Filename: IOAble.h
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
#ifndef SENECA_IOABLE_H
#define SENECA_IOABLE_H
#include <iostream>
namespace seneca {
	class IOAble {
	public:
		virtual std::ostream& write(std::ostream&) const = 0;
		virtual std::istream& read(std::istream&) = 0;
		virtual ~IOAble();
	};
	std::ostream& operator<<(std::ostream&, const IOAble&);
	std::istream& operator>>(std::istream&, IOAble&);
}
#endif // SENECA_IOABLE_H
