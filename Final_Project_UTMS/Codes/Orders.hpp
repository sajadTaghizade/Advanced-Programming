#ifndef ORDERS_HPP
#define ORDERS_HPP

#include "globalStuff.hpp"
#include "UTMS.hpp"

class Orders
{
public:
    Orders(UTMS *_utms);
    void input();

    void handeling_Post(vector<string> command, string line);
    void handeling_Delete(vector<string> command);
    void handeling_Get(vector<string> command, string line);
    void handeling_Put(vector<string> command);

    void Post_login(UTMS *utms, string username,string password);
    void Post_logout(UTMS *utms);

    bool send_notification_to_student(UTMS *utms, string notif);
    bool send_notification_to_professor(UTMS *utms, string notif);
    void Post_post(string title, string message, string image, vector<string> command, UTMS *utms);

    bool connected_search(string id, UTMS *utms);
    bool is_connected(string id, UTMS *utms);
    void Post_connect(string id, UTMS *utms);

    bool is_conflict_professor(Time t, Professors *professor);
    bool is_conflict_student(Time t, Student *student);
    bool have_major(string id, UTMS *utms, Professors *professor);
    bool have_course(string course_id, UTMS *utms);
    void Post_course_offer(vector<string> command, UTMS *utms);

    void Post_profile_photo(vector<string> command, UTMS *utms);
    void add_post_to_course_offer(Posts p, string id);

    void Post_course_post(vector<string> command, UTMS *utms, string line);
    void Post_ta_form(vector<string> command, UTMS *utms, string line);
    void Post_close_ta_form(vector<string> command, UTMS *utms, string line);
    void Post_ta_request(vector<string> command, UTMS *utms, string line);

    void Delete_post(vector<string> command);
    void Delete_my_course(string id);

    course_offer find_course_offer_by_id(string id);
    void Get_courses(string id, UTMS *utms);
    void Get_all_courses(UTMS *utms);
    void Get_notification(vector<string> command, UTMS *utms);
    bool is_student(string id);
    bool is_professor(string id);
    bool is_ut_account(string id);
    void Get_personal_page(string id, UTMS *utms);
    bool have_course_offer(string id);
    bool have_my_courses(string id, Student *s);

    void Get_my_courses(UTMS *utms);

    void Get_course_channel(string id, UTMS *utms);
    void Get_course_post(string id, string post_id, UTMS *utms);

    course_offer find_course_offer_by_pro_id(string id);

    Major *find_major_by_id(string id);
    void Get_post(string id, string post_id, UTMS *utms);

    Course *find_course_by_id(string id);
    Student *find_student_by_id(string id);
    Professors *find_professor_by_id(string id);
    Student *find_student_by_id_(string id);
    Professors *find_professor_by_id_(string id);
    bool is_not_professor(string id, UTMS *utms);
    vector<course_offer> find_course_offer_by_pro_id_(string id);

    void Put_my_courses(string id, UTMS *utms);
    void increase_post_course_offer_id() { post_course_offer_id++; }
    UTMS* get_info(){return utms;}

private:
    UTMS *utms;
    vector<course_offer> course_offers;
    bool is_offer = false;
    int post_course_offer_id;
    // vector<TA_request>TA_requests;
};

#endif