/* Citation and Sources...
Final Project Milestone MS3
Module: Ticket
Filename: Ticket.h
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
#ifndef SENECA_TICKET_H
#define SENECA_TICKET_H
#include <iostream>
#include "Time.h"
#include "IOAble.h"
namespace seneca {
   class Ticket : public IOAble {
      /// <summary>
      /// The time the ticket was issued
      /// </summary>
      Time m_time;

      /// <summary>
      /// The ticket number, a sequential number { starts at 1, unique for each lineup }
      /// </summary>
      int m_number;
   public:

      /// <summary>
      /// Constructs a Ticket by setting the m_number member variable
      /// </summary>
      /// <param name="number">The number of the ticket</param>
      Ticket(int number);

      /// <summary>
      /// A query that returns the time when the ticket was issued.
      /// </summary>
      /// <returns></returns>
      Time time() const;

      /// <summary>
      /// A query returning the number of the ticket
      /// </summary>
      /// <returns></returns>
      int number() const;

      /// <summary>
      /// Sets the Ticket time to the current time.
      /// </summary>
      void resetTime();

      /// <summary>
      /// Inserts a ticket into the ostream to be displayed on the console 
      /// or inserts comma-separated ticket number and time into ostream 
      /// based on the ostream reference being cout or not.
      /// </summary>
      /// <param name="ostr"></param>
      /// <returns></returns>
      std::ostream& write(std::ostream& ostr) const;

      /// <summary>
      /// Extracts the ticket number and time in a comma-separated format from istream.
      /// </summary>
      /// <param name="istr"></param>
      /// <returns></returns>
      std::istream& read(std::istream& istr);
   };
}
#endif // !SENECA_TICKET_H_
