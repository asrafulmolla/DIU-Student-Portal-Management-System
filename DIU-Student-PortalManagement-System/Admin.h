#ifndef ADMIN_H
#define ADMIN_H
#include <bits/stdc++.h>
using namespace std;
#include "User.h"
class Admin : public User
{
public:
    Admin() {}
    void registerUser()
    {
    }
    bool loginUser(const string &username, const string &password)
    {
        // Implement login logic
        ifstream inFile("AdminLoginInfo.txt");
        if (!inFile)
        {
            // Handle file open error, return false
            return false;
        }
        string line;
        while (getline(inFile, line))
        {
            stringstream ss(line);
            string fname, sname, uname, pass;
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
    void addStudent()
    {
        // Implement adding a student logic
        string name, dob, address, nid, bloodGroup, department;
        int classRoll;
        string regNumber, batchNumber, semesterNumber;

        cout << "Enter Student Name: ";
        getline(cin, name);
        cout << "Enter Date of Birth: ";
        getline(cin, dob);
        cout << "Enter Permanent Address: ";
        getline(cin, address);
        cout << "Enter NID Number: ";
        getline(cin, nid);
        cout << "Enter Blood Group: ";
        getline(cin, bloodGroup);
        cout << "Enter Department Name: ";
        getline(cin, department);
        cout << "Enter Class Roll: ";
        cin >> classRoll;
        cin.ignore();
        cout << "Enter Registration Number: ";
        getline(cin, regNumber);
        cout << "Enter Batch Number: ";
        getline(cin, batchNumber);
        cout << "Enter Semester Number: ";
        getline(cin, semesterNumber);

        ofstream outFile("students.txt", ios::app);
        outFile << name << "," << classRoll << "," << regNumber << "," << semesterNumber << "," << department << "," << dob << "," << address << "," << nid << "," << bloodGroup << "," << batchNumber << endl;
        outFile.close();
        cout << "\n**************************************************************************************************\n";
        cout << "*                               Student Added Successfully                                        *";
        cout << "\n**************************************************************************************************\n";
        cin.ignore();
    }

    void addTeacher()
    {
        // Implement adding a teacher logic
        string name, nid, address, department;
        string regNumber, deg;

        cout << "Enter Teacher Name: ";
        getline(cin, name);
        cout << "Enter Teacher Dagigration: ";
        getline(cin, deg);
        cout << "Enter NID Number: ";
        getline(cin, nid);
        cout << "Enter Permanent Address: ";
        getline(cin, address);
        cout << "Enter Department Name: ";
        getline(cin, department);
        cout << "Enter Registration Number: ";
        getline(cin, regNumber);

        ofstream outFile("teachers.txt", ios::app);
        outFile << name << "," << deg << "," << nid << "," << address << "," << regNumber << "," << department << endl;
        outFile.close();
        cout << "\n**************************************************************************************************\n";
        cout << "*                               Teacher Added Successfully                                        *";
        cout << "\n**************************************************************************************************\n";
        cin.ignore();
    }

    void displayStudentInfoBySemesterAndDepartment(int semester, const std::string &department)
    {
        // Implement displaying student info by semester and department logic
        cout << "\n               _________________________________________________________________________________________________";
        cout << "\n              |                        Student Information for Department " << department << " and Semester " << semester << "                    |" << endl;
        cout << "-------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "| " << left << setw(20) << "Name" << setw(10) << "Roll" << setw(15) << "Reg Number" << setw(15) << "Semester" << setw(15) << "DOB" << setw(15) << "Address" << setw(15) << "NID Numbre" << setw(15) << "blood Group" << "Batch|" << endl;
        cout << "-------------------------------------------------------------------------------------------------------------------------------" << endl;

        ifstream inFile("students.txt");
        string line;
        while (getline(inFile, line))
        {
            stringstream ss(line);
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

            if (stoi(sem) == semester && dept == department)
            {
                cout << "| " << left << setw(20) << name << setw(10) << roll << setw(15) << regNumber << setw(15) << sem << setw(15) << dob << setw(15) << address << setw(15) << nid << setw(15) << bld << batch << " |" << endl;
            }
        }

        cout << "-------------------------------------------------------------------------------------------------------------------------------\n"
             << endl;
        inFile.close();
        cin.ignore();
    }
    void displayTeacherInfoByDepartment(const string &department)
    {
        // Implement displaying teacher info by department logic
        cout << "                     ___________________________________________________";
        cout << "\n                    |       Teacher Information for Department " << department << "      |" << endl;
        cout << "----------------------------------------------------------------------------------------------\n";
        cout << "| " << left << setw(20) << "Name" << setw(20) << "Degigration" << setw(20) << "NID" << setw(20) << "Address" << "Reg Number |" << endl;
        cout << "----------------------------------------------------------------------------------------------"
             << endl;

        ifstream inFile("teachers.txt");
        string line;
        while (getline(inFile, line))
        {
            stringstream ss(line);
            string name, nid, address, regNumber, dept, deg;
            getline(ss, name, ',');
            getline(ss, deg, ',');
            getline(ss, nid, ',');
            getline(ss, address, ',');
            getline(ss, regNumber, ',');
            getline(ss, dept, ',');

            if (dept == department)
            {
                cout << "| " << left << setw(20) << name << setw(20) << deg << setw(20) << nid << setw(20) << address << regNumber << "        |" << endl;
            }
        }

        cout << "----------------------------------------------------------------------------------------------\n"
             << endl;
        inFile.close();
        cin.ignore();
    }

    void deleteStudent(const string &regNumber)
    {
        // Implement deleting a student logic
        ifstream inFile("students.txt");
        ofstream outFile("temp.txt");
        string line;

        while (getline(inFile, line))
        {
            if (line.find(regNumber) == string::npos)
            {
                outFile << line << endl;
            }
        }
        inFile.close();
        outFile.close();

        remove("students.txt");
        rename("temp.txt", "students.txt");
        cout << "\n**************************************************************************************************\n";
        cout << "*                               Student Deleted Successfully                                      *";
        cout << "\n**************************************************************************************************\n";
        cin.ignore();
    }

    void deleteTeacher(const std::string &regNumber)
    {
        // Implement deleting a teacher logic
        ifstream inFile("teachers.txt");
        ofstream outFile("temp.txt");
        string line;

        while (getline(inFile, line))
        {
            if (line.find(regNumber) == string::npos)
            {
                outFile << line << endl;
            }
        }
        inFile.close();
        outFile.close();

        remove("teachers.txt");
        rename("temp.txt", "teachers.txt");
        cout << "\n**************************************************************************************************\n";
        cout << "*                               Teacher Deleted Successfully                                      *";
        cout << "\n**************************************************************************************************\n";
        cin.ignore();
    }

    void viewTeacherFeedback(const string &regNumber)
    {
        // Implement viewing teacher feedback logic
        cout << "\n               ________________________________";
        cout << "\n              | Student Feedback From Teachers | " << endl;
        cout << "-------------------------------------------------------------\n";
        cout << left << setw(20) << "| Teacher Name" << setw(20) << "Teacher Reg" << setw(20) << "Feedback"<<setw(5)<<"|" << endl;
        cout << "-------------------------------------------------------------\n";
        ifstream inFile("Teacherfeedback.txt");
        string line;
        while (getline(inFile, line))
        {
            stringstream ss(line);
            string teacherName, teacherReg, feedback;
            getline(ss, teacherName, ' ');
            getline(ss, teacherReg, ' ');
            getline(ss, feedback);

            if (teacherReg == regNumber)
            {
                cout << "| " << left << setw(20) << teacherName << setw(20) << teacherReg<<setw(18) << feedback<<setw(10) << "|" << endl;
            }
        }

        cout << "-------------------------------------------------------------\n"
             << endl;
        inFile.close();
        cin.ignore();
        cin.ignore();
    }
};

#endif // ADMIN_H
