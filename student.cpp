#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include <cctype>

struct Student
{
    std::string student_id;
    std::string first_name;
    std::string middle_name;
    std::string last_name;
    std::string program;
    std::string year_level;
};

struct Grade
{
    std::string student_id;
    std::string course;

    double prelim, midterm, endterm, final_grade;
};

std::vector<Student> students;
std::vector<Grade> grades;

std::string toLower(std::string text)
{
    std::transform(
        text.begin(), text.end(), text.begin(),
        [](unsigned char c)
        {
            return static_cast<char>(std::tolower(c));
        }
    );

    return text;
}

std::string inputRequiredText(const std::string& prompt)
{
    std::string value;

    while(true)
    {
        std::cout << prompt;
        std::getline(std::cin, value);

        bool isEmpty = std::all_of(
            value.begin(), value.end(),
            [](unsigned char c)
            {
                return std::isspace(c);
            }
        );

        if (!isEmpty)
        {
            return value;
        }

        std::cout <<"\tThis field is required. Please enter a value.\n";
    }
}

std::string inputOptionalText(const std::string& prompt)
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

        if (std::cin >> grade && grade >= 0 && grade <= 100)
        {
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n'
            );

            return grade;
        }

        std::cout << "Invalid grade. Enter a value from 0 to 100.\n";

        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n'
        );
    }
}

double calculateFinalGrade(const Grade& grade)
{
    return (grade.prelim * 0.30) +
           (grade.midterm * 0.30) +
           (grade.endterm * 0.40);
}

void pauseScreen()
{
    std::cout <<"\n\tPress Enter to continue...";
    std::cin.get();
}

void registerStudent()
{
    Student student;

    std::cout << "\n\n\t===REGISTER NEW STUDENT===\n\n";

    student.student_id = inputRequiredText(
        "\tEnter Student ID: "
    );

    for (const Student& existing : students)
    {
        if (existing.student_id == student.student_id)
        {
            std::cout << "\n\tStudent ID already exist!";
            return;
        }
    }

    student.first_name = inputRequiredText(
        "\tEnter First Name: "
    );

    student.middle_name = inputOptionalText(
        "\tEnter Middle Name (optional): "
    );

    student.last_name = inputRequiredText(
        "\tEnter Last Name: "
    );

    student.program = inputRequiredText(
        "\tEnter Program: "
    );

    student.year_level = inputRequiredText(
        "\tEnter Year Level: "
    );

    students.push_back(student);

    std::cout << "\n\tStudent successfully registered!\n";
}

std::vector<std::string> getPrograms()
{
    std::vector<std::string> programs;

    for (const Student& student : students)
    {
        bool exists = false;

        for (const std::string& program : programs)
        {
            if (program == student.program)
            {
                exists = true;
                break;
            }
        }

        if (!exists)
        {
            programs.push_back(student.program);
        }
    }

    return programs;
}

std::string selectProgram()
{
    std::vector<std::string> programs = getPrograms();

    if (programs.empty())
    {
        std::cout << "\n\tNo registered students found.\n";
        return "";
    }

    std::cout <<"\n\t=== SELECT PROGRAM ===\n\n";

    for (std::size_t i = 0; i < programs.size(); i++)
    {
        std::cout << "\t[" << i + 1 << "] "
                  << programs[i] << '\n';
    }

    std::size_t choice;

    while(true)
    {
        std::cout << "\n\tSelect Program: ";

        if (std::cin >> choice &&
            choice >= 1 &&
            choice <= programs.size())
        {

            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n'
            );

            return programs[choice - 1];
        }

        std::cout << "\tInvalid selection. Try again.\n";

        std::cin.clear();

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n'
        );
    }
}

int selectStudent(const std::string& program)
{
    std::string search;

    std::cout << "\n\t=== FIND STUDENT ===\n";

    search = inputRequiredText(
        "\n\tSearch Student ID or Name: "
    );

    std::vector<std::size_t> matches;

    std::string searchLower = toLower(search);

    for (std::size_t i = 0; i < students.size(); i++)
    {
        const Student& student = students[i];

        if (student.program != program)
        {
            continue;
        }

        std::string fullName = 
            student.first_name + " " +
            student.middle_name + " " +
            student.last_name;

        if (toLower(student.student_id).find(searchLower) != std::string::npos ||
            toLower(fullName).find(searchLower) != std::string::npos)
        {
            matches.push_back(i);
        }
    }

    if (matches.empty())
    {
        std::cout << "\n\tNo matching student found in this program.\n";
        return -1;
    }

    std::cout << "\n\t=== SEARCH RESULTS ===\n\n";

    for (std::size_t i = 0; i < matches.size(); i++)
    {
        const Student& student = students[matches[i]];

        std::string fullName =
            student.first_name + " " +
            student.middle_name + " " +
            student.last_name;

        std::cout << "\t[" << i + 1 << "] "
                  << student.student_id << " - "
                  << fullName << '\n';
    }

    std::size_t choice;

    while(true)
    {
        std::cout << "\n\tSelect Student: ";

        if (std::cin >> choice &&
            choice >= 1 &&
            choice <= matches.size())
        {
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n'
            );
            
            return static_cast<int>(matches[choice - 1]);
        }

        std::cout << "\tInvalid selection. Try again.\n";

        std::cin.clear();

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n'
        );
    }
}

void displayStudentInformation(const Student& student)
{
    std::cout << "\n\t=== STUDENT INFORMATION ===\n";

    std::cout << "\n\tStudent ID: "
              << student.student_id;

    std::cout << "\n\tFirst Name: "
              << student.first_name;

    std::cout << "\n\tMiddle Name: "
              << (student.middle_name.empty()
                  ? "N/A" : student.middle_name);

    std::cout << "\n\tLast Name: "
              << student.last_name;

    std::cout << "\n\tProgram: "
             << student.program;

    std::cout << "\n\tYear Level: "
              << student.year_level;

    std::cout << '\n';
}

void insertStudentGrades()
{
    std::cout << "\n\n\t=== INSERT STUDENT GRADES ===\n";

    std::string program = selectProgram();

    if (program.empty())
    {
        return;
    }

    std::string course = inputRequiredText(
        "\n\tEnter Course: "
    );

    int studentIndex = selectStudent(program);

    if (studentIndex == -1)
    {
        return;
    }

    const Student& student = students[studentIndex];

    displayStudentInformation(student);

    std::cout << "\n\tSelected Course: " << course << '\n';

    for (const Grade& existing : grades)
    {
        if (existing.student_id == student.student_id &&
            toLower(existing.course) == toLower(course))
        {
            std::cout << "\n\tGrades for this student and course "
                      << "already exists!\\n";
            return;
        }
    }

    Grade grade;

    grade.student_id = student.student_id;
    grade.course = course;

    std::cout << "\n\n\t=== ENTER GRADES ===\n\n";

    grade.prelim = inputGrade("\tEnter Prelim Grade: ");

    grade.midterm = inputGrade("\tEnter Midterm Grade: ");

    grade.endterm = inputGrade("\tEnter Endterm Grade: ");

    grade.final_grade = calculateFinalGrade(grade);

    std::cout << "\n\tFinal Grades: "
              << std::fixed << std::setprecision(2)
              << grade.final_grade << '\n';

    grade.push_back(grade);

    std::cout << "\n\tGrade record successfully added!\n";
}