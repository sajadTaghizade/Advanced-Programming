#ifndef UTACCOUNT_HPP
#define UTACCOUNT_HPP

#include "globalStuff.hpp"

class UTaccount
{
public:
    UTaccount();
    string get_id() { return id; }
    string get_password() { return password; }
    vector<Posts> get_posts() { return posts; }
    string get_name() { return UT_ACCOUNT_PASSWORD_REQUEST; }

    void add_post(Posts p);
    void delete_post(string id);
    vector<string> conected_student_id;
    vector<string> conected_professor_id;
    int get_previous() { return previous; }
    int get_previous_course_offer() { return previous_course_offer; }

    void increase_previous() { previous++; }
    vector<string> notifications;
    void increase_previous_course_offer() { previous_course_offer++; }
    void add_profile(string address);


private:
    string id;
    string password;
    vector<Posts> posts;
    int previous ;
    int previous_course_offer ;
        vector<string> profile_photo_address;

};

#endif