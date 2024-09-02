#include <bits/stdc++.h>
#include "Admin.h"
#include "Teacher.h"
#include "Student.h"
using namespace std;

void adminMenu(Admin &admin);
void teacherMenu(Teacher &teacher);
void studentMenu(Student &student);

int main()
{
    ifstream inFile("Welcome_design.txt");
    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }
    inFile.close();

    Admin admin;
    Teacher teacher;
    Student student;
    while (true)
    {
        cout << "\n------------------------------------";
        cout << "\n|            Home Menu             |";
        cout << "\n------------------------------------\n";
        cout << "| Option 1  | Admin registration   |\n";
        cout << "| Option 2  | Teacher registration |\n";
        cout << "| Option 3  | Student registration |\n";
        cout << "| Option 4  | Admin Login          |\n";
        cout << "| Option 5  | Teacher Login        |\n";
        cout << "| Option 6  | Student Login        |\n";
        cout << "| Option 7  | Exit                 |\n";
        cout << "------------------------------------\n";
        cout << "Enter choice: ";
        int choice;
        cin >> choice;
        cin.ignore();

        string FName, SName, username, password, dept;
        switch (choice)
        {
        case 1:
        {
            cout << "Enter Admin First Name: ";
            getline(cin, FName);
            cout << "Enter Admin Surname: ";
            getline(cin, SName);
            cout << "Enter Admin Username: ";
            getline(cin, username);
            cout << "Enter Admin Password: ";
            getline(cin, password);
            ofstream outFile("AdminLoginInfo.txt", ios::app);
            outFile << FName << ',' << SName << ',' << username << ',' << password << endl;
            outFile.close();
            cout << "\n**************************************************************************************************\n";
            cout << "*                                Admin Registered Successfully                                   *";
            cout << "\n**************************************************************************************************\n";
            cin.ignore();
            break;
        }
        case 2:
        {
            cout << "Enter Teacher First Name: ";
            getline(cin, FName);
            cout << "Enter Teacher Surname: ";
            getline(cin, SName);
            cout << "Enter Teacher Department: ";
            getline(cin, dept);
            cout << "Enter Teacher Username: ";
            getline(cin, username);
            cout << "Enter Teacher Password: ";
            getline(cin, password);
            ofstream outFile("TeacherLoginInfo.txt", ios::app);
            outFile << FName << ',' << SName << ',' << username << ',' << password << ',' << dept << endl;
            outFile.close();
            cout << "\n**************************************************************************************************\n";
            cout << "*                               Teacher Registered Successfully                                  *";
            cout << "\n**************************************************************************************************\n";
            cin.ignore();
            break;
        }
        case 3:
        {
            cout << "Enter Student First Name: ";
            getline(cin, FName);
            cout << "Enter Student Surname: ";
            getline(cin, SName);
            cout << "Enter Student Username: ";
            getline(cin, username);
            cout << "Enter Student Password: ";
            getline(cin, password);
            ofstream outFile("StudentLoginInfo.txt", ios::app);
            outFile << FName << "," << SName << "," << username << "," << password << endl;
            outFile.close();
            cout << "\n**************************************************************************************************\n";
            cout << "*                               Student Registered Successfully                                  *";
            cout << "\n**************************************************************************************************\n";
            cin.ignore();
            break;
        }
        case 4:
        {
            cout << "Enter Admin Username: ";
            getline(cin, username);
            cout << "Enter Admin Password: ";
            getline(cin, password);

            if (admin.loginUser(username, password))
            {
                adminMenu(admin);
            }
            else
            {
                cout << "\n**************************************************************************************************\n";
                cout << "*                                         Login Failed!                                           *";
                cout << "\n**************************************************************************************************\n";
                cin.ignore();
            }
            break;
        }
        case 5:
        {
            cout << "Enter Teacher Username: ";
            getline(cin, username);
            cout << "Enter Teacher Password: ";
            getline(cin, password);

            if (teacher.loginUser(username, password))
            {
                teacherMenu(teacher);
            }
            else
            {
                cout << "\n**************************************************************************************************\n";
                cout << "*                                         Login Failed!                                          *";
                cout << "\n**************************************************************************************************\n";
                cin.ignore();
            }
            break;
        }
        case 6:
        {
            cout << "Enter Student Username: ";
            getline(cin, username);
            cout << "Enter Student Password: ";
            getline(cin, password);

            if (student.loginUser(username, password))
            {
                studentMenu(student);
            }
            else
            {
                cout << "\n**************************************************************************************************\n";
                cout << "*                                         Login Failed!                                          *";
                cout << "\n**************************************************************************************************\n";
                cin.ignore();
            }
            break;
        }
        case 7:
            return 0;
        default:
        {
            cout << "\n**************************************************************************************************\n";
            cout << "*                                         Invalid choice                                           *";
            cout << "\n**************************************************************************************************\n";
            cin.ignore();
        }
        }
    }
}

void adminMenu(Admin &admin)
{
    while (true)
    {
        cout << "\n----------------------------------------------------------\n";
        cout << "|                       Admin Menu                       |";
        cout << "\n----------------------------------------------------------\n";
        cout << "| Option 1 | Add Student                                 |\n";
        cout << "| Option 2 | Add Teacher                                 |\n";
        cout << "| Option 3 | Show Students by Semester and Department    |\n";
        cout << "| Option 4 | Show Teachers by Department                 |\n";
        cout << "| Option 5 | Delete Student                              |\n";
        cout << "| Option 6 | Delete Teacher                              |\n";
        cout << "| Option 7 | View Teacher Feedback                       |\n";
        cout << "| Option 8 | Back                                        |\n";
        cout << "| Option 9 | Home                                        |\n";
        cout << "----------------------------------------------------------\n";
        cout << "Enter choice: ";
        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            admin.addStudent();
            break;
        case 2:
            admin.addTeacher();
            break;
        case 3:
        {
            int semester;
            string department;
            cout << "Enter Semester: ";
            cin >> semester;
            cin.ignore();
            cout << "Enter Department: ";
            getline(cin, department);
            admin.displayStudentInfoBySemesterAndDepartment(semester, department);
            break;
        }
        case 4:
        {
            string department;
            cout << "Enter Department: ";
            getline(cin, department);
            admin.displayTeacherInfoByDepartment(department);
            break;
        }
        case 5:
        {
            string regNumber;
            cout << "Enter Registration Number: ";
            getline(cin, regNumber);
            admin.deleteStudent(regNumber);
            break;
        }
        case 6:
        {
            string regNumber;
            cout << "Enter Registration Number: ";
            getline(cin, regNumber);
            admin.deleteTeacher(regNumber);
            break;
        }
        case 7:
        {
            string regNumber;
            cout << "Enter Registration Number: ";
            getline(cin, regNumber);
            admin.viewTeacherFeedback(regNumber);
            break;
        }
        case 8:
            return;
        case 9:
            main();
        default:
        {
            cout << "\n**************************************************************************************************\n";
            cout << "*                                         Invalid choice                                           *";
            cout << "\n**************************************************************************************************\n";
            cin.ignore();
        }
        }
    }
}

void teacherMenu(Teacher &teacher)
{
    while (true)
    {
        cout << "\n---------------------------------------\n";
        cout << "|               Teacher Mune          |";
        cout << "\n---------------------------------------\n";
        cout << "| Option 1 | Provide Result           |\n";
        cout << "| Option 2 | View Result              |\n";
        cout << "| Option 3 | Create Email             |\n";
        cout << "| Option 4 | Back                     |\n";
        cout << "| Option 5 | Home                     |\n";
        cout << "---------------------------------------\n";
        cout << "Enter choice: ";
        int choice;
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
            teacher.provideResult();
            break;
        case 2:
            teacher.viewResult();
            break;
        case 3:
            teacher.createEmail();
            break;
        case 4:
            return;
        case 5:
            main();
        default:
        {
            cout << "\n**************************************************************************************************\n";
            cout << "*                                         Invalid choice                                           *";
            cout << "\n**************************************************************************************************\n";
            cin.ignore();
        }
        }
    }
}

void studentMenu(Student &student)
{
    while (true)
    {
        cout << "\n----------------------------------------\n";
        cout << "|              Student Mune            |";
        cout << "\n----------------------------------------\n";
        cout << "| Option 1 | Academic Result           |\n";
        cout << "| Option 2 | Create Email              |\n";
        cout << "| Option 3 | View Course Outline       |\n";
        cout << "| Option 4 | View Semester Routine     |\n";
        cout << "| Option 5 | Give Teacher Feedback     |\n";
        cout << "| Option 6 | View Admit Card           |\n";
        cout << "| Option 7 | Back                      |\n";
        cout << "| Option 8 | Home                      |\n";
        cout << "----------------------------------------\n";
        cout << "Enter choice: ";
        int choice;
        cin >> choice;
        cin.ignore();
        char x;
        switch (choice)
        {
        case 1:
            student.viewCGPA();
            break;
        case 2:
            student.createEmail();
            break;
        case 3:
            student.viewCourseOutline();
            break;
        case 4:
        {
            int semester;
            cout << "Enter Semester: ";
            cin >> semester;
            student.viewSemesterRoutine(semester);
            break;
        }
        case 5:
            student.giveFeedback();
            break;
        case 6:
            student.downloadAdmitCard();
            break;
        case 7:
            return;
        case 8:
            main();
        default:
            cout << "\n**************************************************************************************************\n";
            cout << "*                                         Invalid choice                                           *";
            cout << "\n**************************************************************************************************\n";
            cin.ignore();
        }
    }
}