/* Citation and Sources...
Final Project Milestone MS3
Module: Ticket
Filename: Ticket.cpp
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
#include <string>
#include "Ticket.h"
#include "Time.h"

namespace seneca {
    Ticket::Ticket(int number)
    {
        m_time.reset();
        m_number = number;
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
        // Ticket No: 24, Issued at: 08:00
        ostr << "Ticket No: " << this->m_number << ", Issued at: " << this->m_time;
        return ostr;
    }

    std::istream& Ticket::read(std::istream& istr)
    {
        std::string tmpName;
        std::string tmpOHIP;
        std::string tmpTicketNo;
        std::string tmpTime;
        std::getline(istr, tmpName, ',');
        std::getline(istr, tmpOHIP, ',');
        std::getline(istr, tmpTicketNo, ',');
        std::getline(istr, tmpTime);
        return istr;
    }
}