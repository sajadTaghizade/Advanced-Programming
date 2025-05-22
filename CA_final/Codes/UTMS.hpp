#ifndef UTMS_HPP
#define UTMS_HPP

#include "globalStuff.hpp"
#include "Student.hpp"
#include "Course.hpp"
#include "Major.hpp"
#include "Professor.hpp"
#include "UTaccount.hpp"

class UTMS
{
public:
    UTMS(vector<string> pathes);
    void read_CSV(string path_of_file);
    vector<Student *> get_student() { return students; }
    vector<Professors *> get_professor() { return professors; }
    UTaccount *get_utaccount() { return utaccount; }
    vector<Course *> get_course() { return courses; }
    vector<Major *> get_major() { return majors; }
    bool is_logined = false;
    bool is_ut_account_logined = false;
    bool is_student_logined = false;
    bool is_professor_logined = false;
    Professors *professor_logined;
    Student *student_logined;
    UTaccount *ut_account_logined;
    string professor_id_loged;
    string student_id_loged;
    string ut_account_id_loged;
    string id_loged;

private:
    vector<Student *> students;
    vector<Professors *> professors;
    vector<Major *> majors;
    vector<Course *> courses;
    UTaccount *utaccount;
};

#endif