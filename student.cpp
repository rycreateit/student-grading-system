#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <conio.h> //review later
#include <cctype>

struct Student
{
    std::string student_id;

    std::string first_name;
    std::string middle_name;
    std::string last_name;

    std::string course;
    std::string subject;

    double prelim, midterm, endterm, final_grade;
};

std::string inputText(const std::string& prompt)
{
    std::string value;

    std::cout << prompt;
    std::getline(std::cin, value);

    return value;
}

double inputGrade(const std::string& prompt)
{
    double grade;

    while(true)
    {
        std::cout << prompt;

        if (std::cin >> grade && grade && grade >= 0 && grade <= 100)
        {
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n'
            );
            return grade;
        }

        std::cout << "Invalid grade. Enter a value from 0 to 100.\n";

        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamlsize>::max(), '\n'
        );
    }
}

double calculateFinalGrade(const Student& student)
{
    return (student.prelim * 0.30) +
           (student.midterm * 0.30) +
           (student.endterm * 0.40);
}

void insertStudent()
{
    Student student;

    std::cout <<"\n\n\t===INSERT NEW STUDENT RECORD===\n\n";

    student.student_id = inputText("\tEnter Student ID Number: ");

    student.first_name = inputText("\tEnter First Name: ");

    student.middle_name = inputText("\tEnter Middle Name (optional): ");

    student.last_name = inputText("\tEnter Last Name: ");

    student.course = inputText("\tEnter Course: ");

    student.subject = inputText("\tEnter Subject: ");

    student.prelim = inputText("\tEnter Prelim Grade: ");

    student.midterm = inputText("\tEnter Midterm Grade: ");

    student.endterm = inputTExt("\tEnter Endterm Grade: ");

    student.final_grade = calculateFinalGrade(student);

    std:cout <<"\n\tFinal Grade: "
             << std::fixed << std::setprecision(2)
             << student.final_grade << '\n';

    std::cout << "\n\tStudent information successfully entered.\n";
}

int main() 
{
    char choice;
    char another;

    std::cout << std::fixed << std::setprecision(2);

    while(true)
    {
        std::system("CLS");
        std::system("COLOR F0");
        
        std::cout <<"\n\n\t========================================";
        std::cout <<"\n\tSTUDENT GRADING SYSTEM";
        std::cout <<"\n\t========================================";

        std::cout <<"\n\n\t[1]INSERT STUDENT RECORD";
        std::cout <<"\n\t[2]DISPLAY STUDENT RECORD";
        std::cout <<"\n\t[3]SEARCH STUDENT RECORD";
        std::cout <<"\n\t[4]EDIT STUDENT RECORD";
        std::cout <<"\n\t[5]DELETE STUDENT RECORD";
        std::cout <<"\n\t[6]EXIT";

        std::cout <<"\n\n\tEnter your choice: ";
        std::cin >> choice;

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n'
        )

        switch (choice)
        {
            case '1':

                another = 'Y';

                while (another == 'Y' || another == 'y')
                {
                    system("CLS");

                    insertStudent();

                    std::cout << "\n\tAdd another student record? (Y/N): ";
                    std::cin >> another;

                    std::cin.ignore(
                        std::numeric_limits<std::streamsize>::max(), '\n'
                    );
                }

                break;

            case '2':
            



}