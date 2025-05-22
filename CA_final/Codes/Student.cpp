#include "Student.hpp"

Student::Student(std::string _sid, std::string _name, std::string _major_id, std::string _semester, std::string _password)
{
    previous = 0;
    sid = _sid;
    name = _name;
    major_id = _major_id;
    semester = _semester;
    password = _password;
}

void Student ::add_post(Posts p)
{
    posts.push_back(p);
}

void Student ::delete_post(string id)
{
    if(stoi(id)<=0)
        throw runtime_error(BAD_REQUEST_ERROR);

    for (int i = 0; i < posts.size(); i++)
    {
        if (stoi(id) == posts[i].id)
        {
            posts.erase(posts.begin() + i);
            cout << OK << endl;
            return;
        }
    }
    throw runtime_error(NOT_FOUND_ERROR);
}

void Student ::delete_my_course(string id)
{
    for (int i = 0; i < my_coursrs.size(); i++)
    {
        if (stoi(id) == my_coursrs[i].course_offer_id)
        {
            my_coursrs.erase(my_coursrs.begin() + i);
            cout << OK << endl;
            return;
        }
    }
    throw runtime_error(NOT_FOUND_ERROR);
}

bool Student::check_time(Time t)
{
    for (int i = 0; i < time.size(); i++)
    {
        if (t.day == time[i].day and ((time[i].to > t.from and t.to > time[i].from) or (t.to > time[i].from && t.from > time[i].to) or (time[i].to < t.to and t.from < time[i].to) or (t.from < time[i].from and t.to > time[i].from)))
        {
            return false;
        }
    }
    time.push_back(t);
    return true;
}

void Student::add_connection(string id)
{
    conected_id.push_back(id);
}

void Student::add_my_courses(course_offer co)
{
    my_coursrs.push_back(co);
}

void Student::recieve_notif(string notif)
{
    notifications.push_back(notif);
}

void Student::view_notif()
{
    if (notifications.size() > NATURAL_NUMBER)
    {
        for (int i = notifications.size() - 1; i >= 0; i--)
        {

            cout << notifications[i] << endl;
        }
    }

    else
    {
        throw runtime_error(EMPTY_ERROR);
    }
    notifications.clear();
}

void Student::add_profile(string address)
{
    profile_photo_address.push_back(address);
}