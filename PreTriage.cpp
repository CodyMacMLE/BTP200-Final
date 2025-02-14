/* Citation and Sources...
Final Project Milestone MS5
Module: PreTriage
Filename: PreTriage.cpp
Version 1.0
Author   Cody MacDonald
Revision History
-----------------------------------------------------------
Date      Reason
2024/04/03  Preliminary release
-----------------------------------------------------------
1.	Clearing buffer using max stream buffer size template + limits module (cin.clear & .ignore)
	https://gist.github.com/leimao/418395bf920eb70b2b11fe89d7c1f738
----------------------------------------------------------- */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>
#include <cstring>
#include <memory>
#include "PreTriage.h"
#include "Utils.h"
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
			delete m_patients[i];
		}
		delete[] m_dataFile;
	}

	Time PreTriage::getWaitTime(const Patient& patient) const
	{
		Time waitTime;
		int patientsOfType = 0;
		for (int i = 0; i < m_patientCnt; ++i)
		{
			if (patient.type() == m_patients[i]->type())
				++patientsOfType;
		}

		if (patient.type() == 'C')
			waitTime = m_avgWaitTestPatient * patientsOfType;
		else if (patient.type() == 'T')
			waitTime = m_avgWaitTriagePatient * patientsOfType;

		return waitTime;
	}

	void PreTriage::setAverageWaitTime(Patient& patient)
	{
		Time CT = U.getTime();
		Time PT = patient.time();
		int PTN = patient.number();
		if (patient.type() == 'C')
		{
			m_avgWaitTestPatient = ((CT - PT) + (m_avgWaitTestPatient * (PTN - 1))) / PTN;
		}
		else if (patient.type() == 'T')
		{
			m_avgWaitTriagePatient = ((CT - PT) + (m_avgWaitTriagePatient * (PTN - 1))) / PTN;
		}
	}

	int PreTriage::indexOfFirstInLine(char patientType) const
	{
		int patientIndex = -1;
		for (int i = 0; i < m_patientCnt; ++i)
		{
			if (m_patients[i]->type() == patientType) {
				patientIndex = i;
				break;
			}
		}
		return patientIndex;
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
			Patient* tmpPatient = nullptr;													// Cause of memory leak?
			for (int i = 0; i < MAX_NUM_PATIENTS && file; ++i)
			{
				char category = file.get();
				file.ignore(std::numeric_limits<std::streamsize>::max(), ',');

				if (category == 'C')
				{
					//TestPatient* tmpPatient = dynamic_cast<TestPatient*>(tmpPatient);
					tmpPatient = new TestPatient();											// Cause of memory leak?
				}
				else if (category == 'T')
				{
					//TriagePatient* tmpPatient = dynamic_cast<TriagePatient*>(tmpPatient);
					tmpPatient = new TriagePatient();										// Cause of memory leak?
				}

				if (tmpPatient != nullptr)
				{
					tmpPatient->read(file);
					file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

					m_patients[i] = tmpPatient;
					++m_patientCnt;
				}

				if (file.peek() == EOF)
					file.get();	
				
			}

			// Displaying # loaded
			if (!file.eof())
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

	void PreTriage::registerPatient()
	{
		Menu registerMenu = Menu("Select Type of Registration:\n1- Contagion Test\n2- Triage", 1);
		int registerSelection;

		if (m_patientCnt == MAX_NUM_PATIENTS)
		{
			std::cout << "Line up full!\n";
		}
		else
		{
			registerMenu.display();
			std::cin >> registerSelection;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			Patient* tmpPatient = nullptr;
			int index = m_patientCnt;
			switch (registerSelection)
			{
			case 0: // Exit
				break;
			case 1:
				 tmpPatient = new TestPatient();
				
				std::cout << "Please enter patient information: \n";
				std::cin >> *tmpPatient;
				tmpPatient->setArrivalTime();
				m_patients[index] = tmpPatient;
				std::cout
					<< "\n******************************************\n"
					<< *m_patients[index]
					<< "Estimated Wait Time: " << getWaitTime(*m_patients[index])
					<< "\n******************************************\n\n";
				m_patientCnt++;
				break;
			case 2: // Triage
				tmpPatient = new TriagePatient();
				std::cout << "Please enter patient information: \n";
				std::cin >> *tmpPatient;
				tmpPatient->setArrivalTime();
				m_patients[index] = tmpPatient;
				std::cout
					<< "\n******************************************\n"
					<< *m_patients[index]
					<< "Estimated Wait Time: " << getWaitTime(*m_patients[index])
					<< "\n******************************************\n\n";
				m_patientCnt++;
				break;
			default: // Wrong input
				break;
			}
		}
	}

	void PreTriage::admit()
	{
		Menu admitMenu = Menu("Select Type of Admittance:\n1- Contagion Test\n2- Triage", 1);
		int admitSelection;

		admitMenu.display();
		std::cin >> admitSelection;

		int index;
		Time currentTime;
		switch (admitSelection)
		{
		case 0: // Exit
			break;
		case 1: // Contagion Test
			index = indexOfFirstInLine('C');
			if (index == -1)
			{
				std::cout << "Lineup is empty!\n";
			}
			else if (index >= 0 && index < m_patientCnt)
			{
				currentTime.reset();
				std::cout << std::endl 
					<< "******************************************\n" 
					<< "Call time: [" << currentTime << "]\n"
					<< "Calling at for "
					<< *m_patients[index]
					<< "******************************************\n\n";
				setAverageWaitTime(*m_patients[index]);
				U.removeDynamicElement(m_patients, index, m_patientCnt);
			}
			break;
		case 2: // Triage
			index = indexOfFirstInLine('T');
			if (index == -1)
			{
				std::cout << "Lineup is empty!\n";
			}
			else if (index >= 0 && index < m_patientCnt)
			{
				currentTime.reset();
				std::cout << std::endl
					<< "******************************************\n"
					<< "Call time: [" << currentTime << "]\n"
					<< "Calling at for "
					<< *m_patients[index]
					<< "******************************************\n\n";
				setAverageWaitTime(*m_patients[index]);
				U.removeDynamicElement(m_patients, index, m_patientCnt);
			}
			break;
		default: // Wrong input
			break;
		}
	}

	void PreTriage::lineup() const
	{
		Menu lineupMenu = Menu("Select The Lineup:\n1- Contagion Test\n2- Triage", 1);
		int lineupSelection;

		lineupMenu.display();
		std::cin >> lineupSelection;


		switch (lineupSelection)
		{
		case 0: // Exits
			break;
		case 1: // Contagion Test
			std::cout << "Row - Patient name                                          OHIP     Tk #  Time\n";
			std::cout << "-------------------------------------------------------------------------------\n";
			{
				int rowCnt = 1; // counter for rows
				bool patientExists = false;
				for (int j = 0; j < m_patientCnt; ++j)
				{
					if (m_patients[j]->type() == 'C')
					{
						std::clog.width(3);
						std::clog.setf(std::ios::left);
						std::clog << rowCnt << " - ";
						m_patients[j]->write(std::clog);
						std::clog << "\n";
						std::clog.unsetf(std::ios::left);
						patientExists = true;
						++rowCnt;
					}
				}
				
				if (patientExists)
				{
					std::clog.flush();
				}
				else
				{
					std::clog << "Line up is empty!\n" << std::endl;
				}
			}
			std::cout << "-------------------------------------------------------------------------------" << std::endl;
			break;
		case 2: // Triage
			std::cout << "Row - Patient name                                          OHIP     Tk #  Time\n";
			std::cout << "-------------------------------------------------------------------------------\n";
			{
				int rowCnt = 1; // counter for rows
				bool patientExists = false;
				for (int j = 0; j < m_patientCnt; ++j)
				{
					if (m_patients[j]->type() == 'T')
					{
						std::clog.width(3);
						std::clog.setf(std::ios::left);
						std::clog << rowCnt << " - ";
						m_patients[j]->write(std::clog);
						std::clog << "\n";
						std::clog.unsetf(std::ios::left);
						patientExists = true;
						++rowCnt;
					}
				}
				if (patientExists)
				{
					std::clog.flush();
				}
				else
				{
					std::clog << "Line up is empty!\n" << std::endl;
				}
			}
			std::cout << "-------------------------------------------------------------------------------" << std::endl;
			break;
		default: // Exits
			break;
		}
	}

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