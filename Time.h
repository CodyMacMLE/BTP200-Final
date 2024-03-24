/* Citation and Sources...
Final Project Milestone MS1
Module: Time
Filename: Time.h
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
#ifndef SENECA_TIME_H
#define SENECA_TIME_H
#include <iostream>

namespace seneca
{
	class Time
	{
		int m_minutes;
	public:
		/// <summary>
		/// Default constructor
		/// </summary>
		/// <param name="min">time in minutes to intialize object</param>
		Time(unsigned int min = 0u);

		/// <summary>
		/// resets m_minutes to current system time
		/// </summary>
		/// <returns>The original object</returns>
		Time& reset();

		/// <summary>
		/// This method writes the time into ostream in the HH:MM format. 
		/// </summary>
		/// <param name="out">Where the object is to be displayed</param>
		/// <returns>an object of ostream</returns>
		std::ostream& write(std::ostream& out = std::cout) const;

		/// <summary>
		/// This method reads the time from istream in the H:M format. 
		/// It ensures that the two integers (hours and minutes) are separated 
		/// by a colon (:). If they are not, it sets the istream object to a failure state.
		/// </summary>
		/// <param name="in"></param>
		/// <returns></returns>
		std::istream& read(std::istream& in);

		/// <summary>
		/// Converts m_minutes to hour and minutes 
		/// </summary>
		/// <param name="hours">A reference to hours variable</param>
		/// <param name="minutes">A reference to minutes variable</param>
		void convertTimeHours(int& hours, int& minutes) const;

		/// <summary>
		/// If a Time object is cast to an unsigned integer, it will return the number 
		/// of minutes held in the object.
		/// </summary>
		operator unsigned int() const;

		/// <summary>
		/// It multiplies the number of minutes held in the Time object by val
		/// </summary>
		/// <param name="val">value to multiply by</param>
		/// <returns>a reference to the current object</returns>
		Time& operator*= (int val);

		/// <summary>
		/// It calculates the time difference between the current Time object and the 
		/// Time object 'that' passed as an argument. 
		/// </summary>
		/// <param name="that">second object for time difference</param>
		/// <returns>a reference to the original object</returns>
		Time& operator-= (const Time& that);

		/// <summary>
		/// It calculates the time difference between the current Time object and the 
		/// Time object 'that' passed as an argument.
		/// </summary>
		/// <param name="that">second object for time difference</param>
		/// <returns>a new object with the time difference</returns>
		Time operator- (const Time& that) const;

		friend std::ostream& operator<< (std::ostream& out, const Time time);

		friend std::istream& operator>> (std::istream& in, Time& time);
	};
}
#endif // !SENECA_TIME_H