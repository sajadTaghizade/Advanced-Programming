#include "UTaccount.hpp"
UTaccount ::UTaccount()
{
    previous = 0;
    previous_course_offer=0;
    id = UT_ACCOUNT_ID_REQUEST;
    password = UT_ACCOUNT_PASSWORD_REQUEST;
}

void UTaccount ::add_post(Posts p)
{
    posts.push_back(p);
}

void UTaccount ::delete_post(string id)
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

void UTaccount::add_profile(string address)
{
    profile_photo_address.push_back(address);
}