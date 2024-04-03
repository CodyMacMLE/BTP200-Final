/* Citation and Sources...
Final Project Milestone MS4
Module: Ticket
Filename: Ticket.cpp
Version 1.0
Author   Cody MacDonald
Revision History
-----------------------------------------------------------
Date      Reason
2024/03/27  Preliminary release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
----------------------------------------------------------- */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Ticket.h"
#include "Time.h"

namespace seneca {

    Ticket::Ticket(int number)
    {
        if (number > 0)
            m_number = number;
        else
            m_number = 0;
    }

    Time Ticket::time() const
    {
        return m_time;
    }

    int Ticket::number() const
    {
        return m_number;
    }

    void Ticket::resetTime()
    {
        m_time.reset();
    }

    std::ostream& Ticket::write(std::ostream& ostr) const
    {
        if (&ostr == &std::cout)
        {
            ostr << "Ticket No: " << this->m_number << ", Issued at: " << this->m_time;
        }
        else
        {
            ostr << m_number << "," << m_time;
        }
        return ostr;
    }

    std::istream& Ticket::read(std::istream& istr)
    {
        char number[3 + 1];
        istr.get(number, 4, ',');
        istr.ignore(10000000, ',');
        m_number = std::atoi(number);
        this->m_time.read(istr);
        return istr;
    }

}