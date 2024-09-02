#ifndef STUDENT_H
#define STUDENT_H
#include "User.h"
#include <bits/stdc++.h>
using namespace std;

class Student : public User
{
    string department;

public:
    string fname, sname, uname, pass;
    void registerUser()
    {
    }

    bool loginUser(const string &username, const string &password)
    {
        // Implement login logic
        ifstream inFile("StudentLoginInfo.txt");
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
                getline(ss, pass))
                if (uname == username && pass == password)
                {
                    inFile.close();
                    return true;
                }
        }
        inFile.close();
        return false;
    }

    void viewCGPA()
    {
        // Implement viewing CGPA logic
        string studentReg;
        cout << "Enter Your Registration Number: ";
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
        // Implement creating email logic
        string email = uname + ".students@diu.ac";
        cout << "Student Email: " << email << endl;
        cin.ignore();
    }

    void viewCourseOutline()
    {
        // Implement viewing course outline logic
        string line;
        ifstream inFile1("courseFile.txt");
        while (getline(inFile1, line))
        {
            cout << line << endl;
        }
        inFile1.close();
        cin.ignore();
    }

    void viewSemesterRoutine(int semester)
    {
        // Implement viewing semester routine logic
        string line;
        ifstream inFile;
        switch (semester)
        {
        case 1:
            inFile.open("SemesterRoutine1.txt");
            break;
        case 2:
            inFile.open("SemesterRoutine2.txt");
            break;
        case 3:
            inFile.open("SemesterRoutine3.txt");
            break;
        case 4:
            inFile.open("SemesterRoutine4.txt");
            break;
        case 5:
            inFile.open("SemesterRoutine5.txt");
            break;
        case 6:
            inFile.open("SemesterRoutine6.txt");
            break;
        case 7:
            inFile.open("SemesterRoutine7.txt");
            break;
        case 8:
            inFile.open("SemesterRoutine8.txt");
            break;
        case 9:
            inFile.open("SemesterRoutine9.txt");
            break;
        case 10:
            inFile.open("SemesterRoutine10.txt");
            break;
        case 11:
            inFile.open("SemesterRoutine11.txt");
            break;
        case 12:
            inFile.open("SemesterRoutine12.txt");
            break;
        default:
            inFile.open("SemesterRoutineInvalid.txt");
            break;
        }
        while (getline(inFile, line))
        {
            cout << line << endl;
        }
        inFile.close();
        cin.ignore();
    }

    void giveFeedback()
    {
        // Implement giving feedback logic
        string teacherName, feedback, teacherReg;
        cout << "Enter Teacher Name: ";
        getline(cin, teacherName);
        cout << "Enter Teacher registration Number: ";
        getline(cin, teacherReg);
        cout << "Enter Feedback: ";
        getline(cin, feedback);
        ofstream outFile("Teacherfeedback.txt", ios::app);
        outFile << teacherName << " " << teacherReg << " " << feedback << endl;
        outFile.close();
        cout << "\n**************************************************************************************************\n";
        cout << "*                                     Feedback Given Successfully                                 *";
        cout << "\n**************************************************************************************************\n";
        cin.ignore();
    }

    void downloadAdmitCard()
    {
        // Implement downloading admit card logic
        string studentReg;
        cout << "Enter Your Registration Number: ";
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
            cin.ignore();
            return;
        }

        // Extract and show current semester and department
        stringstream ss(studentLine);
        string name, roll, regNumber, sem, dept, dob, address, nid, bld, batch;
        getline(ss, name, ',');
        getline(ss, roll, ',');
        getline(ss, regNumber, ',');
        getline(ss, sem, ',');
        getline(ss, dept, ',');
        getline(ss, dob, ',');
        getline(ss, address, ',');
        getline(ss, nid, ',');
        getline(ss, bld, ',');
        getline(ss, batch, ',');

        // Admit Card Top Design
        ifstream inFile("AdmitCardTopDesign.txt");
        string line;
        while (getline(inFile, line))
        {
            cout << line << endl;
        }
        inFile.close();
        //
        cout << "                                                                                          Admit Card Number: " << rand() << endl;
        cout << "    Name of the Examinee            : " << name << endl;
        cout << "    Class Roll                      : " << roll << endl;
        cout << "    Registation Number              : " << regNumber << endl;
        cout << "    Current Semester                : " << sem << endl;
        cout << "    Batch                           : " << batch << endl;
        cout << "    Department                      : " << dept << endl;
        cout << "    Date of Birth                   : " << dob << endl;
        cout << "    Permanent Address               : " << address << endl;
        cout << "    National Identity Card Num      : " << nid << endl;
        cout << "    Blood Group                     : " << bld << endl;
        cout << "    Email                           : " << uname + ".students@diu.ac" << endl;
        cout << "    Exam Room Number                : " << 506 << endl;
        cout << "    Center                          : Dhaka International University," << endl;
        cout << "                                      Permanent Campus: Satarkul, Badda, Dhaka." << endl
             << endl
             << endl;
        cout << "                                                 List of Course's" << endl
             << endl;
        ifstream courseFile("courseFile.txt");
        string courseFile_line;
        int line_number = 0;
        int start_line = 0;
        int end_line = 0;
        if (sem == "1")
        {
            start_line = 23;
            end_line = 32;
        }
        else if (sem == "2")
        {
            start_line = 36;
            end_line = 47;
        }
        else if (sem == "3")
        {
            start_line = 51;
            end_line = 62;
        }
        else if (sem == "4")
        {
            start_line = 66;
            end_line = 76;
        }
        else if (sem == "5")
        {
            start_line = 80;
            end_line = 90;
        }
        else if (sem == "6")
        {
            start_line = 94;
            end_line = 104;
        }
        else if (sem == "7")
        {
            start_line = 108;
            end_line = 119;
        }
        else if (sem == "8")
        {
            start_line = 123;
            end_line = 135;
        }
        else if (sem == "9")
        {
            start_line = 149;
            end_line = 150;
        }
        else if (sem == "10")
        {
            start_line = 154;
            end_line = 165;
        }
        else if (sem == "11")
        {
            start_line = 169;
            end_line = 179;
        }
        else if (sem == "12")
        {
            start_line = 183;
            end_line = 191;
        }
        while (getline(courseFile, courseFile_line))
        {
            line_number++;
            if (line_number >= start_line && line_number <= end_line)
            {
                cout << courseFile_line << endl;
            }
            if (line_number > end_line)
            {
                break; // Stop reading once we've reached the end line
            }
        }
        courseFile.close();
        cin.ignore();
    }
};

#endif // STUDENT_H
