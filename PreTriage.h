#ifndef SENECA_PRETRIAGE_H
#define SENECA_PRETRIAGE_H
#include "Time.h"
#include "Patient.h"
namespace seneca {
	const int MAX_NUM_PATIENTS = 100;

	class PreTriage {
		/// <summary>
		/// Stores average wait time for contagion test patient
		/// </summary>
		Time m_avgWaitTestPatient;

		/// <summary>
		/// Stores average wait time for triage patient
		/// </summary>
		Time m_avgWaitTriagePatient;

		/// <summary>
		/// An array of all patients in the waitlist { accumalative(test + triage) max = 100 }
		/// </summary>
		Patient* m_patients[MAX_NUM_PATIENTS];

		/// <summary>
		/// An array that stores the file address of patients
		/// </summary>
		char* m_dataFile;

		/// <summary>
		/// Stores the actual number of patient records on file
		/// </summary>
		int m_patientCnt;

		/// <summary>
		/// A PreTriage class is instantiated using the data file name. 
		/// This data file name is stored in the data filename attribute for load and save purposes. 
		/// The constructor also initializes the two Time attributes, Contagion test and Triage, to 15 and 5 respectively.
		/// </summary>
		PreTriage();

		/// <summary>
		/// - Saves the data.
		/// - Iterates through the patient lineup and deletes the elements one by one.
		///	- If there are any other dynamically allocated memory, it will delete them as well.
		/// </summary>
		~PreTriage();

		/// <summary>
		///  and returns the  as follows:
		/// </summary>
		/// <param name="patient">Receives a constant Patient Reference</param>
		/// <returns>Total estimated wait time for that type of Patient (contagion or Triage)</returns>
		Time& getWaitTime(const Patient& patient) const;

		/// <summary>
		/// Adjusts the average wait time of that type of patient based on the admittance time of the patient.
		/// </summary>
		/// <param name="patient">Reference of the admitting patient</param>
		void setAverageWaitTime(Patient& patient);

		/// <summary>
		/// Finds the index of the first patient in line that matches a specified type.
		/// </summary>
		/// <param name="patientType">Receives a character representing the type of patient (C for Contaigen, T for Triage)</param>
		/// <returns>Index of the first patient in line for that type</returns>
		int indexOfFirstInLine(char patientType) const;

		/// <summary>
		/// Loads the average wait times and the patient records from the data file and stores 
		/// them in the lineup array of pointers.
		/// </summary>
		void load(const char* filename);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="filename"></param>
		void save(const char* filename);

		/// <summary>
		/// Calls a sub-menu object to create/insert a patient (Triage or Contagion)
		/// </summary>
		void registerPatient();

		/// <summary>
		/// Calls a sub-menu to call the next patient in line to be admitted
		/// </summary>
		void admit();

		/// <summary>
		/// Prints a report on patients currently in the lineup
		/// </summary>
		void lineup() const;
	public:
		/// <summary>
		/// Runs the PreTriage main application
		/// </summary>
		void run();
	};
}
#endif // ! SENECA_PRETRIAGEPATIENT_H