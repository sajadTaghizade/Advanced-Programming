#ifndef STUDENT_HPP
#define STUDENT_HPP

#include "Major.hpp"
#include "globalStuff.hpp"

class Student
{
public:
    Student(string _sid, string _name, string _major_id, string _semester, string _password);
    string get_sid() { return sid; }
    string get_name() { return name; }
    string get_password() { return password; }
    string get_semester() { return semester; }
    vector<Posts> get_posts() { return posts; }
    vector<string> get_connected_id() { return conected_id; }
    vector<course_offer> get_my_courses() { return my_coursrs; }
    void add_post(Posts p);
    void delete_my_course(string id);
    void delete_post(string id);
    int get_previous() { return previous; }
    void increase_previous() { previous++; }
    string get_major_id() { return major_id; }
    bool check_time(Time t);
    void add_connection(string id);
    void add_my_courses(course_offer co);
    void recieve_notif(string notif);
    void view_notif();
    void add_profile(string address);

private:
    string sid, name, major_id, semester, password;
    Major *major;
    int previous;
    vector<Time> time;
    vector<string> conected_id;
    vector<course_offer> my_coursrs;
    vector<string> notifications;
    vector<string> profile_photo_address;
    vector<Posts> posts;
};

#endif // STUDENT_HPP