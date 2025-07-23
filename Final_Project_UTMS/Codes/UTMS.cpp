#include "UTMS.hpp"

vector<string> divider(string inputVector, char delimiter)
{
    vector<string> outputVector;

    stringstream ss(inputVector);

    string token;
    while (getline(ss, token, delimiter))
    {
        outputVector.push_back(token);
    }

    return outputVector;
}

UTMS::UTMS(vector<string> pathes)
{
    for (int i = 0; i < pathes.size(); i++)
        read_CSV(pathes[i]);

    UTaccount* new_utaccount = new UTaccount();
    utaccount=new_utaccount;
}

void UTMS::read_CSV(string path_of_file)
{
    ifstream file(path_of_file);
    string line;
    getline(file, line);
    vector<string> first_line = divider(line, COMMA_DELIMITER);
    while (getline(file, line))
    {
        vector<string> devided_line = divider(line, COMMA_DELIMITER);
        if (first_line[0] == STUDENT_ID)
        {
            Student *new_student = new Student(devided_line[0], devided_line[1], devided_line[2], devided_line[3], devided_line[4]);
            students.push_back(new_student);
        }
        else if (first_line[0] == PROFESSOR_ID)
        {
            Professors *new_professors = new Professors(devided_line[0], devided_line[1], devided_line[2], devided_line[3], devided_line[4]);
            professors.push_back(new_professors);
        }
        else if (first_line[0] == MAJOR_ID)
        {
            Major *new_major = new Major(devided_line[0], devided_line[1]);
            majors.push_back(new_major);
        }
        else if (first_line[0] == COURSE_ID)
        {
            Course *new_course = new Course(devided_line[0], devided_line[1], devided_line[2], devided_line[3], devided_line[4]);
            courses.push_back(new_course);
        }
    }
    file.close();
}