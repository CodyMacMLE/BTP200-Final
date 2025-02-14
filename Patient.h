#ifndef SENECA_PATIENT_H
#define SENECA_PATIENT_H
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
#include "IOAble.h"
#include "Ticket.h"
namespace seneca {
	class Patient :
		public IOAble
	{
		/// <summary>
		/// dynamic array that stores the patients name
		/// </summary>
		char* m_patientName;

		/// <summary>
		/// Patient's Ontario Insurance Number
		/// </summary>
		int m_ohipNo;

		/// <summary>
		/// Ticket details for patient
		/// </summary>
		Ticket m_ticket;
	public:
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="TicketNo">Unique ticket number</param>
		Patient(int ticketNo);

		/// <summary>
		/// Copy constructor
		/// </summary>
		/// <param name="that">object to be copied</param>
		Patient(const Patient& that);

		/// <summary>
		/// Copy Assignment
		/// </summary>
		/// <param name="that">Object to be assigned</param>
		/// <returns>Assigned object</returns>
		Patient& operator= (const Patient& that);

		/// <summary>
		/// Destructor handling with m_patientName
		/// </summary>
		~Patient();
		
		/// <summary>
		/// Pure virtual function that identifies patient type
		/// </summary>
		/// <returns>A single char that identifies patient type</returns>
		virtual char type() const = 0;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="that"></param>
		/// <returns></returns>
		bool operator==(const char type) const;

		/// <summary>
		/// Compares whether two Patient objects are the same
		/// </summary>
		/// <param name="that">rhs comparison</param>
		/// <returns>True if same, false otherwise</returns>
		bool operator==(const Patient& that) const;

		/// <summary>
		/// Sets the time of the patient's ticket
		/// </summary>
		void setArrivalTime();

		/// <summary>
		/// Retrieves the time of the patient's ticket
		/// </summary>
		/// <returns>Time object of patient ticket</returns>
		Time time() const;

		/// <summary>
		/// Retrieves number of patient's ticket
		/// </summary>
		/// <returns>an int representing patient ticket number</returns>
		int number() const;

		/// <summary>
		/// Checks if patient is in a valid state
		/// </summary>
		/// <returns>true if valid, false otherwise</returns>
		operator bool() const;

		/// <summary>
		/// returns the address of the patient name
		/// </summary>
		operator const char*() const;

		/// <summary>
		/// Inserts patient info into seperate ostreams
		/// </summary>
		/// <param name="out">ostream to write to</param>
		/// <returns></returns>
		std::ostream& write(std::ostream& ostr) const;

		/// <summary>
		/// Reads info inputted by user into patient object
		/// </summary>
		/// <param name="in">input stream</param>
		/// <returns></returns>
		std::istream& read(std::istream& istr);
	};
}
#endif // !SENECA_PATIENT_H
