#include "Professor.hpp"

Professors::Professors(std::string _pid, std::string _name, std::string _major_id, std::string _position, std::string _password)
{
    previous = 0;
    pid = _pid;
    name = _name;
    major_id = _major_id;
    position = _position;
    password = _password;
}

void Professors ::add_post(Posts p)
{
    posts.push_back(p);
}

void Professors ::delete_post(string id)
{
    if (stoi(id) <= 0)
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

void Professors::recieve_notif(string notif)
{
    notifications.push_back(notif);
}

void Professors::view_notif()
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

void Professors::add_connection(string id)
{
    conected_id.push_back(id);
}

bool Professors::check_time(Time t)
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

void Professors::add_profile(string address)
{
    profile_photo_address.push_back(address);
}

