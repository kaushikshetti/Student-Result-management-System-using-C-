#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

int main()
{
    // Considering the max length of data entered (name) to be 20.
    char studentData[20];
    int numStudents = 0, choice = 0, countStudents = 0;
    // This is the initial mark allotted to a subject.
    string emptyMark = "00";
    string advisor = "";
    // Name of the file in which DB is stored.
    ifstream inputFile("StudentData.txt");
    string line;

    // The following for loop counts the total number of lines in the file.
    for (int i = 0; std::getline(inputFile, line); ++i) {
        countStudents++;
    }

    while (choice != 6) {
        // This prints out all the available options in the DB
        cout << "\nAvailable operations: \n1. Add New Students\n"
                "2. Student Login\n3. Faculty Login\n4. Advisor Login\n"
                "5. Admin View\n6. Exit\nEnter your choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter the number of students: ";
            cin >> numStudents;

            countStudents = countStudents + numStudents;

            for (int i = 0; i < numStudents; i++) {
                ofstream outputFile;
                outputFile.open("StudentData.txt", ios::app);
                // The entire data of a single student is stored line-by-line.
                cout << "Enter your registration number: ";
                cin >> studentData;
                outputFile << studentData << "\t";

                cout << "Enter your name: ";
                cin >> studentData;
                int len = strlen(studentData);

                while (len < 20) {
                    studentData[len] = ' ';
                    len = len + 1;
                }
                outputFile << studentData << "\t";
                // Inserting empty data initially into the file
                outputFile << emptyMark << "\t";
                outputFile << emptyMark << "\t";

                cout << "Enter your advisor ID: ";
                cin >> advisor;

                outputFile << advisor << endl;
            }
        }

        else if (choice == 2) {
            char regNum[9];
            cout << "Enter your registration number: ";
            cin >> regNum;
            ifstream inputFile;
            int check = 0;
            inputFile.open("StudentData.txt", ios::in);

            // This loop prints out the data according to the registration number specified.
            while (inputFile >> studentData) {
                if (strcmp(studentData, regNum) == 0) {
                    cout << "\nRegistration Number: " << studentData << endl;
                    inputFile >> studentData;
                    cout << "Name: " << studentData << endl;

                    inputFile >> studentData;
                    cout << "Subject1 mark: " << studentData << endl;

                    inputFile >> studentData;
                    cout << "Subject2 mark: " << studentData << endl;

                    inputFile >> studentData;
                    cout << "Advisor ID: " << studentData << endl;

                    inputFile.close();
                    check = 1;
                }
            }

            if (check == 0) {
                cout << "No such registration number found!" << endl;
            }
        }

        // This loop is used to view and add marks to the database of a student.
        else if (choice == 3) {
            char subjectCode[7];
            cout << "Enter your subject code: ";
            cin >> subjectCode;
            string code1 = "CS101", code2 = "CS102", mark = "";
            ifstream inputFile;
            int check = 0;

            cout << "\nAvailable operations: \n1. Add data about marks\n"
                    "2. View data\nEnter your choice: ";
            cin >> choice;

            if (choice == 1) {
                cout << "Warning! You would need to add mark details for all the students!" << endl;
                for (int i = 0; i < countStudents; i++) {
                    fstream file("StudentData.txt");

                    // The seek in file has been done according to the length
                    // of the data being inserted. It needs to be adjusted accordingly for different
                    // lengths of data.

                    if (strcmp(subjectCode, code1.c_str()) == 0) {
                        file.seekp(26 + 41 * i, std::ios_base::beg);
                        cout << "Enter the mark of student #" << (i + 1) << " : ";
                        cin >> mark;
                        file.write(mark.c_str(), 2);
                    }

                    if (strcmp(subjectCode, code2.c_str()) == 0) {
                        file.seekp(29 + 41 * i, std::ios_base::beg);
                        cout << "Enter the mark of student #" << (i + 1) << " : ";
                        cin >> mark;
                        file.write(mark.c_str(), 2);
                    }
                }
            }

            // This loop is used to view marks of a student.
            // The extra inputFile commands have been used to get a specific mark only since the data has
            // been separated by a tabspace.

            else if (choice == 2) {
                inputFile.open("StudentData.txt", ios::in);
                if (strcmp(subjectCode, code1.c_str()) == 0) {
                    cout << "Registration number - Marks\n" << endl;
                    while (inputFile >> studentData) {
                        cout << studentData;
                        inputFile >> studentData;
                        inputFile >> studentData;
                        cout << " - " << studentData << endl;
                        inputFile >> studentData;
                        inputFile >> studentData;
                        check = 1;
                    }
                }

                inputFile.close();
                inputFile.open("StudentData.txt", ios::in);

                if (strcmp(subjectCode, code2.c_str()) == 0) {
                    cout << "Registration number - Marks\n" << endl;
                    while (inputFile >> studentData) {
                        cout << studentData;
                        inputFile >> studentData;
                        inputFile >> studentData;
                        inputFile >> studentData;
                        cout << " - " << studentData << endl;
                        inputFile >> studentData;
                        check = 1;
                    }
                }
            }

            inputFile.close();

            if (check == 0) {
                cout << "No such subject code found!" << endl;
            }
        }

        // This loop displays all the details of students under the same advisor ID.
       else if (choice == 4) {
            char advisorID[7];
            cout << "Enter your advisor ID: ";
            cin >> advisorID;
            int check = 0;
            char temp1[100], temp2[100], temp3[100];
            char temp4[100], id[100];
            ifstream inputFile;
            inputFile.open("StudentData.txt", ios::in);

            while (inputFile >> temp1) {
                inputFile >> temp2;
                inputFile >> temp3;
                inputFile >> temp4;
                inputFile >> id;

                if (strcmp(id, advisorID) == 0) {
                    cout << "\nRegistration Number: " << temp1 << endl;
                    cout << "Name: " << temp2 << endl;
                    cout << "Subject1 Mark: " << temp3 << endl;
                    cout << "Subject2 Mark: " << temp4 << endl;
                    check = 1;
                }
            }

            if (check == 0) {
                cout << "No such advisor ID found!" << endl;
            }
        }

        // This loop acts as an admin view to see all the data in the file.
        else if (choice == 5) {
            char password[25];
            cout << "Enter the admin password: ";
            cin >> password;

            // This variable value can be changed according to your requirement of the administrator password.
            string adminPass = "admin";

            if (strcmp(password, adminPass.c_str()) == 0) {
                cout << "Reg No.\t\tName\t\tSubject1\tSubject2\tAdvisor ID" << endl;
                ifstream inputFile;
                inputFile.open("StudentData.txt", ios::in);
                char studentData[30];

                while (inputFile >> studentData) {
                    cout << studentData << "\t";
                    inputFile >> studentData;
                    cout << studentData << "\t";
                    inputFile >> studentData;
                    cout << studentData << "\t";
                    inputFile >> studentData;
                    cout << studentData << "\t";
                    inputFile >> studentData;
                    cout << studentData << endl;
                }
            }
        }
    }
}
