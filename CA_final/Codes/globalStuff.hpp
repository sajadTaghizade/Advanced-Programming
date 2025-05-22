#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

const char SEMI_COLON_DELIMITER = ';';
const char COLON_DELIMITER = ':';
const char COMMA_DELIMITER = ',';
const char DOUBLE_QUATATION_DELIMITER = '"';
const char SPACE_DELIMITER = ' ';
const char DASH_DELIMITER = '-';
const char SLASH_DELIMITER = '/';
const string QUESTION_MARK = "?";
const string PERMISSION_DENIED_ERROR = "Permission Denied";
const string NOT_FOUND_ERROR = "Not Found";
const string EMPTY_ERROR = "Empty";
const string BAD_REQUEST_ERROR = "Bad Request";
const string OK = "OK";
const string ERROR = "erorr";
const string POST_ORDER = "POST";
const string GET_ORDER = "GET";
const string PUT_ORDER = "PUT";
const string DELETE_ORDER = "DELETE";
const string MY_COURSES_REQUEST = "my_courses";
const string NOTIFICATION_REQUEST = "notification";
const string COURSES_REQUEST = "courses";
const string POST_REQUEST = "post";
const string LOGIN_REQUEST = "login";
const string LOGOUT_REQUEST = "logout";
const string CONNECT_REQUEST = "connect";
const string COURSE_OFFER_REQUEST = "course_offer";
const string PERSONAL_PAGE_REQUEST = "personal_page";
const string PROFILE_PHOTO_REQUEST = "profile_photo";
const string COURSE_POST_REQUEST="course_post";
const string TA_FORM_REQUEST="ta_form";
const string CLOSE_TA_FORM_REQUEST="close_ta_form";
const string TA_REQUEST="ta_request";
const string GET_POST_FIRST_OUTPUT="TA form for ";
const string GET_POST_SECOND_OUTPUT=" course";
const string COURSE_CHANEL_REQUEST="course_channel";
const string UT_ACCOUNT_PASSWORD_REQUEST = "UT_account";
const string UT_ACCOUNT_ID_REQUEST = "0";
const string NEW_POST_MESSAGE = "New Post";
const string UT_ACCOUNT_NOTIF = "0 UT_account: New Post";
const string NEW_COURSE_OFFERING_MESSAGE = ": New Course Offering";
const string GET_COURSE_MESSAGE = "Get Course";
const string DELETE_COURSE_MESSAGE = ": Delete Course";
const string ID = "id";
const string PASSWORD = "password";
const string STUDENT_ID = "sid";
const string PROFESSOR_ID = "pid";
const string COURSE_ID = "cid";
const string MAJOR_ID = "mid";
const int NATURAL_NUMBER = 0;
const string NULL_STRING = "";
const int INVALID_SIZE = 1;
const string MESSAGE  = "message";
const string TITLE = "title";
const string IMAGE = "image";
const string PHOTO = "photo";
const string POST_COURSE_POST_NOTIF = ": New Course Post";
const string POST_TA_FORM_NOTIF = ": New Form";
const string POST_CLOSE_TA_FORM_FIRST_OUTPUT = "We have recived ";
const string POST_CLOSE_TA_FORM_SECOND_OUTPUT=" requests for the teaching assistant position";
const string POST_ID = "post_id";

struct Posts
{
    string title;
    string message;
    int id;
    string image_address;
    string author_id;
    int course_offer_id;
};

struct Time
{
    string day;
    string from;
    string to;
};

struct Exam_date
{
    string day;
    string month;
    string year;
};

struct course_offer
{
    int course_id;
    int professsor_id;
    int capacity;
    Time time;
    Exam_date exam_date;
    int class_number;
    int course_offer_id;
    vector<Posts> posts;
    vector<int> ta_id;
    vector<string> TA_id_request;
};

#endif