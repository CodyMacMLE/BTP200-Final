#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <limits>
#include "PreTriage.h"
#include "Time.h"
#include "Menu.h"
#include "Patient.h"
#include "TestPatient.h"
#include "TriagePatient.h"


namespace seneca {
	
	PreTriage::PreTriage(const char* filename)
	{
		m_avgWaitTestPatient = Time(15u);
		m_avgWaitTriagePatient = Time(5u);
		for (int i = 0; i < MAX_NUM_PATIENTS; ++i)
			m_patients[i] = nullptr;
		m_patientCnt = 0;

		if (filename != nullptr)
		{
			m_dataFile = new char[strlen(filename) + 1];
			strcpy(m_dataFile, filename);

			load(m_dataFile); // handles m_patient and m_patientCnt
		}
		else
		{
			m_dataFile = nullptr;
		}
	}

	PreTriage::~PreTriage()
	{
		save(m_dataFile);
		for (int i = 0; i < m_patientCnt; ++i)
		{
			delete[] m_patients[i];
		}
		delete[] m_dataFile;
	}

	Time& PreTriage::getWaitTime(const Patient& patient) const
	{
		return patient.time();
	}

	/// <summary>
	/// Adjusts the average wait time of that type of patient based on the admittance time of the patient.
	/// </summary>
	/// <param name="patient">Reference of the admitting patient</param>
	void PreTriage::setAverageWaitTime(Patient& patient)
	{

	}

	/// <summary>
	/// Finds the index of the first patient in line that matches a specified type.
	/// </summary>
	/// <param name="patientType">Receives a character representing the type of patient (C for Contaigen, T for Triage)</param>
	/// <returns>Index of the first patient in line for that type</returns>
	int PreTriage::indexOfFirstInLine(char patientType) const
	{
		return 0;
	}

	void PreTriage::load(const char* filename)
	{
		std::ifstream file(filename);

		std::cout << "Loading data...\n";
		if (file.is_open())
		{
			// read and store Average Contagion Test Wait Time
			m_avgWaitTestPatient.read(file);
			file.ignore(std::numeric_limits<std::streamsize>::max(), ',');
			// read and store Average Triage Wait Time
			m_avgWaitTriagePatient.read(file);
			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			// Adding Patients to m_patients
			Patient* tmpPatients[MAX_NUM_PATIENTS];
			for (int i = 0; i < MAX_NUM_PATIENTS && file; ++i)
			{
				tmpPatients[i] = nullptr;

				if (file.get() == 'C')
				{
					tmpPatients[i] = new TestPatient();
				}
				else if (file.get() == 'T')
				{
					tmpPatients[i] = new TriagePatient();
				}
				if (tmpPatients[i] != nullptr)
				{
					tmpPatients[i]->read(file);
					m_patients[i] = tmpPatients[i];
					++m_patientCnt;
				}
			}

			// Displaying # loaded
			if (!EOF)
			{
				std::cout << "Warning: number of records exceeded 100\n";
			}

			if (m_patientCnt > 0)
			{
				std::cout << m_patientCnt << " Records imported...\n\n";
			}
			else
			{
				std::cout << "No data or bad data file!\n\n";
			}
		}
		else
		{
			std::cout << "No data or bad data file!\n\n";
		}
		file.close();
	}

	void PreTriage::save(const char* filename)
	{
		std::ofstream file;
		file.open(filename);

		int savedTestPatients = 0;
		int savedTriagePatients = 0;

		std::cout << "Saving lineup...\n";
		file << m_avgWaitTestPatient << ',' << m_avgWaitTriagePatient << '\n';
		for (int i = 0; i < m_patientCnt; ++i)
		{
			if (m_patients[i]->type() == 'C')
				++savedTestPatients;
			else if (m_patients[i]->type() == 'T')
				++savedTriagePatients;

			m_patients[i]->write(file);
			file << '\n';
		}

		std::cout << savedTestPatients << " Contagion Tests and " << savedTriagePatients << " Triage records were saved!\n";
		file.close();
	}

	/// <summary>
	/// Calls a sub-menu object to create/insert a patient (Triage or Contagion)
	/// </summary>
	void PreTriage::registerPatient()
	{

	}

	/// <summary>
	/// Calls a sub-menu to call the next patient in line to be admitted
	/// </summary>
	void PreTriage::admit()
	{

	}

	/// <summary>
	/// Prints a report on patients currently in the lineup
	/// </summary>
	void PreTriage::lineup() const
	{

	}

	/// <summary>
	/// Runs the PreTriage main application
	/// </summary>
	void PreTriage::run()
	{
		Menu preTriageApp = Menu("General Healthcare Facility Pre-Triage Application\n1- Register\n2- Admit\n3- View Lineup");
		
		int selection;
		bool exitFlag = false;
		while (!exitFlag)
		{
			preTriageApp.display();
			std::cin >> selection;

			switch (selection)
			{
			case 0:
				exitFlag = true;
				break;
			case 1:
				registerPatient();
				break;
			case 2:
				admit();
				break;
			case 3:
				lineup();
				break;
			default:
				break;
			}
		}
	}
}