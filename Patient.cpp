/* Citation and Sources...
Final Project Milestone MS3
Module: Patient
Filename: Patient.cpp
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
#include "Patient.h"
namespace seneca {
	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="TicketNo">Unique ticket number</param>
	Patient::Patient(int ticketNo) {

	}

	/// <summary>
	/// Copy constructor
	/// </summary>
	/// <param name="that">object to be copied</param>
	Patient::Patient(const Patient& that) {

	}

	/// <summary>
	/// Copy Assignment
	/// </summary>
	/// <param name="that">Object to be assigned</param>
	/// <returns>Assigned object</returns>
	Patient& Patient::operator= (const Patient& that) {

	}

	/// <summary>
	/// Destructor handling with m_patientName
	/// </summary>
	Patient::~Patient() {

	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="that"></param>
	/// <returns></returns>
	bool Patient::operator==(const char type) const {

	}

	/// <summary>
	/// Compares whether two Patient objects are the same
	/// </summary>
	/// <param name="that">rhs comparison</param>
	/// <returns>True if same, false otherwise</returns>
	bool Patient::operator==(const Patient& that) const {

	}

	/// <summary>
	/// Sets the time of the patient's ticket
	/// </summary>
	void Patient::setArrivalTime() {

	}

	/// <summary>
	/// Retrieves the time of the patient's ticket
	/// </summary>
	/// <returns>Time object of patient ticket</returns>
	Time& Patient::time() const {

	}

	/// <summary>
	/// Retrieves number of patient's ticket
	/// </summary>
	/// <returns>an int representing patient ticket number</returns>
	int Patient::number() const{

	}

	/// <summary>
	/// Checks if patient is in a valid state
	/// </summary>
	/// <returns>true if valid, false otherwise</returns>
	Patient::operator bool(){

	}

	/// <summary>
	/// returns the address of the patient name
	/// </summary>
	Patient::operator const char* (){

	}

	/// <summary>
	/// Inserts patient info into seperate ostreams
	/// </summary>
	/// <param name="out">ostream to write to</param>
	/// <returns></returns>
	std::ostream& Patient::write(std::ostream& out) const {

	}

	/// <summary>
	/// Reads info inputted by user into patient object
	/// </summary>
	/// <param name="in">input stream</param>
	/// <returns></returns>
	std::istream& Patient::read(std::istream& in) {

	}
}