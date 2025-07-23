#ifndef COURSE_HPP
#define COURSE_HPP

#include "globalStuff.hpp"

class Course
{
public:
    Course(string _cid, string _name, string _credit, string _prerequisite, string _majors_id);
    string get_cid() { return cid; }
    string get_major_id() { return majors_id; }
    string get_name() { return name; }
    string get_credit() { return credit; }
    string get_prerequisite() { return prerequisite; }

private:
    string cid, name, credit, prerequisite, majors_id;
};

#endif // COURSE_HPP
