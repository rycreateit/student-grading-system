#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <conio.h> //review later
#include <cctype>

int main()
{
    std::FILE *fp, *ft;

    char another, choice;

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

    std::string student_id;

    long int recsize;
    bool found = false;

    fp = std::fopen("GRADE_DB.DAT", "rb+");

    if ( fp == nullptr)
    {
        fp = std::fopen("GRADE_DB.DAT", "wb+");

        if (fp == nullptr)
        {
            std::cout << "Cannot open file" << std::endl;
            return 1;
        }
    }

    while(true)
    {
        std::system("CLS");

        std::system("COLOR F0");
        
        std::cout << std::setprecision(2) << std::fixed;
        
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

        switch (choice)
        {
            case '1':
                fseek (fp, 0, SEEK_END);
                another = 'Y';
                while (another == 'Y')
                {
                    system("CLS");
                }
        }
    }


}