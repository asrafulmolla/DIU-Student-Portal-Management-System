#ifndef TEACHER_H
#define TEACHER_H
#include <bits/stdc++.h>
using namespace std;
#include "User.h"

class Teacher : public User
{
    string designation;
    string department;

public:
    string fname, sname, uname, pass, dept;
    Teacher() {}
    void registerUser()
    {
    }

    bool loginUser(const string &username, const string &password)
    {
        // Implement login logic
        ifstream inFile("TeacherLoginInfo.txt");
        if (!inFile)
        {
            // Handle file open error, return false
            return false;
        }
        string line;
        while (getline(inFile, line))
        {
            stringstream ss(line);
            if (getline(ss, fname, ',') &&
                getline(ss, sname, ',') &&
                getline(ss, uname, ',') &&
                getline(ss, pass, ',') &&
                getline(ss, dept))
                if (uname == username && pass == password)
                {
                    inFile.close();
                    return true;
                }
        }
        inFile.close();
        return false;
    }

    void provideResult()
    {
        // Implement providing result logic
        string studentReg;
        cout << "Enter Student Registration Number: ";
        getline(cin, studentReg);

        // Check if the student exists
        ifstream studentFile("students.txt");
        string studentLine;
        bool studentFound = false;
        while (getline(studentFile, studentLine))
        {
            if (studentLine.find(studentReg) != string::npos)
            {
                studentFound = true;
                break;
            }
        }
        studentFile.close();

        if (!studentFound)
        {
            cout << "\n**************************************************************************************************\n";
            cout << "*                                         Student Not Found                                      *";
            cout << "\n**************************************************************************************************\n";
            return;
        }

        // Extract and show current semester and department
        stringstream ss(studentLine);
        string name, roll, regNumber, sem, dept;
        getline(ss, name, ',');
        getline(ss, roll, ',');
        getline(ss, regNumber, ',');
        getline(ss, sem, ',');
        getline(ss, dept, ',');

        cout << "\n                    ***********************\n";
        cout << "                     Student Name: " << name << endl;
        cout << "                     Current Semester: " << sem << endl;
        cout << "                     Department: " << dept << endl;
        cout << "                    ***********************\n"
             << endl;

        int currentSemester = stoi(sem);
        vector<tuple<string, string, string, double>> results;

        for (int i = 1; i <= currentSemester; i++)
        {
            int numSubjects;
            cout << "Enter number of subjects for semester " << i << ": ";
            cin >> numSubjects;
            cin.ignore();

            for (int j = 1; j <= numSubjects; j++)
            {
                string subjectCode, subjectName;
                double credit, cgpa;

                cout << "Enter " << j << " Subject Code: ";
                getline(cin, subjectCode);
                cout << "Enter " << j << " Subject Name: ";
                getline(cin, subjectName);
                cout << "Enter Credit: ";
                cin >> credit;
                cout << "Enter CGPA: ";
                cin >> cgpa;
                cin.ignore();

                results.emplace_back(subjectCode, subjectName, to_string(credit), cgpa);
            }

            // Store the results for this semester
            ofstream resultFile("results.txt", ios::app);
            resultFile << studentReg << ",";
            for (const auto &result : results)
            {
                resultFile << get<0>(result) << "," << get<1>(result) << "," << get<2>(result) << "," << get<3>(result) << ",";
            }
            resultFile << endl;
            results.clear(); // Clear results for next semester
            resultFile.close();
        }

        cout << "\n**************************************************************************************************\n";
        cout << "*                                Results Provided Successfully                                   *";
        cout << "\n**************************************************************************************************\n";
        cin.ignore();
    }

    void viewResult()
    {
        string studentReg;
        cout << "Enter Student Registration Number: ";
        getline(cin, studentReg);

        ifstream resultFile("results.txt");
        string line;
        bool resultFound = false;
        vector<tuple<string, string, double, double>> allResults;
        vector<vector<tuple<string, string, double, double>>> semesterResults;

        // Reading all results from file
        while (getline(resultFile, line))
        {
            if (line.find(studentReg) != string::npos)
            {
                resultFound = true;
                stringstream ss(line);
                string regNumber;
                getline(ss, regNumber, ',');

                vector<tuple<string, string, double, double>> semesterResult;
                while (!ss.eof())
                {
                    string subjectCode, subjectName, creditStr, cgpaStr;
                    getline(ss, subjectCode, ',');
                    getline(ss, subjectName, ',');
                    getline(ss, creditStr, ',');
                    getline(ss, cgpaStr, ',');

                    if (!subjectCode.empty() && !subjectName.empty() && !creditStr.empty() && !cgpaStr.empty())
                    {
                        double credit = stod(creditStr);
                        double cgpa = stod(cgpaStr);
                        allResults.emplace_back(subjectCode, subjectName, credit, cgpa);
                        semesterResult.emplace_back(subjectCode, subjectName, credit, cgpa);
                    }
                }
                semesterResults.push_back(semesterResult);
            }
        }
        resultFile.close();

        if (!resultFound)
        {
            cout << "\n**************************************************************************************************\n";
            cout << "*                                No Results Found for Student                                    *";
            cout << "\n**************************************************************************************************\n";
            cin.ignore();
            return;
        }
        cout << "\n\n-------------------------------------------------------";
        cout << "\n|                      Result Menu                    |";
        cout << "\n-------------------------------------------------------";
        cout << "\n| Option 1 | Specific semester result view            |";
        cout << "\n| Option 2 | Show all semester results and total CGPA |";
        cout << "\n-------------------------------------------------------\n";
        cout << "Enter Your choice: ";
        int op;
        cin >> op;
        if (op == 1)
        {
            // Option 1: Specific semester result view
            int semesterChoice;
            cout << "\nEnter Semester Number to View (1-" << semesterResults.size() << "): ";
            cin >> semesterChoice;

            if (semesterChoice >= 1 && semesterChoice <= semesterResults.size())
            {
                vector<tuple<string, string, double, double>> selectedSemester = semesterResults[semesterChoice - 1];

                double totalCredits = 0, totalGradePoints = 0;
                cout << "\n_______________________________________________________________";
                cout << "\n|        Result for Registration Number " << studentReg << " Semester " << semesterChoice << "      |" << endl;
                cout << "---------------------------------------------------------------" << endl;
                cout << left << "| " << setw(15) << "Subject Code" << setw(30) << "Subject Name" << setw(10) << "Credit" << "CGPA |" << endl;
                cout << "---------------------------------------------------------------" << endl;

                for (const auto &result : selectedSemester)
                {
                    cout << left << "| " << setw(15) << get<0>(result) << setw(30) << get<1>(result) << setw(10) << get<2>(result) << setw(4) << get<3>(result) << " |" << endl;
                    totalCredits += get<2>(result);
                    totalGradePoints += get<2>(result) * get<3>(result);
                }

                double semesterCGPA = totalGradePoints / totalCredits;
                cout << "---------------------------------------------------------------" << endl;
                cout << "                                        Semester " << fixed << setprecision(2) << semesterChoice << " CGPA: " << semesterCGPA << endl;
                cin.ignore();
            }
            else
            {
                cout << "\n********************************************************\n";
                cout << "*         Semester " << semesterChoice << " results not available.            *";
                cout << "\n********************************************************\n";
                cin.ignore();
            }
            cin.ignore();
        }
        else if (op == 2)
        {
            // Option 2: Show all semester results and total CGPA
            double totalCredits = 0, totalGradePoints = 0;
            cout << "\n_______________________________________________________________";
            cout << "\n|      All Semester Results for Registration Number " << studentReg << "     |" << endl;
            cout << "---------------------------------------------------------------" << endl;
            cout << left << "| " << setw(15) << "Subject Code" << setw(30) << "Subject Name" << setw(10) << "Credit" << "CGPA |" << endl;
            cout << "---------------------------------------------------------------" << endl;

            for (const auto &result : allResults)
            {
                cout << left << "| " << setw(15) << get<0>(result) << setw(30) << get<1>(result) << setw(10) << get<2>(result) << setw(4) << get<3>(result) << " |" << endl;
                totalCredits += get<2>(result);
                totalGradePoints += get<2>(result) * get<3>(result);
            }

            double totalCGPA = totalGradePoints / totalCredits;
            cout << "---------------------------------------------------------------" << endl;
            cout << "                                             Total CGPA: " << fixed << setprecision(2) << totalCGPA << endl;
            cin.ignore();
            cin.ignore();
        }
        else
        {
            cout << "\n**************************************************************************************************\n";
            cout << "*                                         Invalid choice                                           *";
            cout << "\n**************************************************************************************************\n";
            cin.ignore();
        }
    }

    void createEmail()
    {
        string email = uname + "." + dept + "@diu.ac";
        cout << "Teacher Email: " << email << endl;
        cin.ignore();
    }
};

#endif // TEACHER_H
