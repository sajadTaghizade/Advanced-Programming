#ifndef PROFESSORS_HPP
#define PROFESSORS_HPP

#include "globalStuff.hpp"

class Professors
{
public:
    Professors(string _pid, string _name, string _major_id, string _position, string _password);
    string get_pid() { return pid; }
    string get_password() { return password; }
    string get_major_id() { return major_id; }
    vector<Posts> get_posts() { return posts; }
    vector<string> get_connected_id() { return conected_id; }
    vector<Time> time;
    vector<string> conected_id;
    int get_previous() { return previous; }
    void increase_previous() { previous++; }
    void add_post(Posts p);
    void delete_post(string id);
    string get_name() { return name; }
    string get_position() { return position; }
    void recieve_notif(string notif);
    void view_notif();
    void add_connection(string id);
    bool check_time(Time t);
    vector<string> notifications;
    void add_profile(string address);

private:
    string pid, name, major_id, position, password;
    vector<Posts> posts;
    int previous;
    vector<string> profile_photo_address;
};

#endif // PROFESSORS_HPP
