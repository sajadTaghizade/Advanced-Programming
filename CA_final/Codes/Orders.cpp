#include "Orders.hpp"

Orders::Orders(UTMS *_utms)
{
    utms = _utms;
    post_course_offer_id = 0;
    for (int i = 0; i < utms->get_student().size(); i++)
    {
        utms->get_utaccount()->conected_student_id.push_back(utms->get_student()[i]->get_sid());
    }
    for (int i = 0; i < utms->get_professor().size(); i++)
    {
        utms->get_utaccount()->conected_professor_id.push_back(utms->get_professor()[i]->get_pid());
    }
}

vector<string> divider_order(string inputVector, char delimiter)
{
    vector<string> outputVector;

    stringstream ss(inputVector);

    string token;
    while (getline(ss, token, delimiter))
    {
        outputVector.push_back(token);
    }

    return outputVector;
}

vector<string> splitString(const string &str, const string &delimiter)
{
    vector<string> tokens;
    size_t start = 0;
    size_t end = str.find(delimiter);

    while (end != string::npos)
    {
        tokens.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }

    tokens.push_back(str.substr(start, end));
    return tokens;
}

bool is_int(string command)
{
    istringstream c4(command);
    int num;
    if (c4 >> num && c4.eof())
    {
        return true;
    }
    return false;
}

bool Orders::is_not_professor(string id, UTMS *utms)
{
    for (int i = 0; i < utms->get_student().size(); i++)
    {
        if (id == utms->get_student()[i]->get_sid())
        {
            return true;
        }
    }
    if (utms->get_utaccount()->get_id() == id)
    {
        return true;
    }
    return false;
}

Course *Orders::find_course_by_id(string id)
{
    for (int i = 0; i < utms->get_course().size(); i++)
    {
        if (id == utms->get_course()[i]->get_cid())
        {
            return utms->get_course()[i];
        }
    }
}

Student *Orders ::find_student_by_id(string id)
{
    for (int i = 0; i < utms->get_student().size(); i++)
    {
        if (id == utms->get_student()[i]->get_sid())
        {
            return utms->get_student()[i];
        }
    }
    throw runtime_error(NOT_FOUND_ERROR);
}

Professors *Orders ::find_professor_by_id_(string id)
{
    for (int i = 0; i < utms->get_professor().size(); i++)
    {
        if (id == utms->get_professor()[i]->get_pid())
        {
            return utms->get_professor()[i];
        }
    }
}

void ok_login(string &id, string &password, string line)
{
    string temp = splitString(line, PASSWORD)[1];
    password = divider_order(temp, SPACE_DELIMITER)[1];
    string temp2 = splitString(line, ID)[1];
    id = divider_order(temp2, SPACE_DELIMITER)[1];
}

void Orders::Post_login(UTMS *utms, string username, string _password)
{
  
    bool flag = false;
    string id = username;
    string password = _password;
    // ok_login(id, password, line);
    for (int i = 0; i < utms->get_student().size(); i++)
    {
        if (utms->get_student()[i]->get_sid() == id && utms->get_student()[i]->get_password() == password)
        {
            cout << OK << endl;
            utms->is_logined = true;
            utms->is_student_logined = true;
            utms->student_logined = utms->get_student()[i];
            utms->student_id_loged = id;
            utms->id_loged = id;

            flag = true;
        }
        if (utms->get_student()[i]->get_sid() == id && utms->get_student()[i]->get_password() != password)
            throw runtime_error(PERMISSION_DENIED_ERROR);
    }

    for (int i = 0; i < utms->get_professor().size(); i++)
    {
        if (utms->get_professor()[i]->get_pid() == id && utms->get_professor()[i]->get_password() == password)
        {
            cout << OK << endl;
            utms->is_logined = true;
            utms->is_professor_logined = true;
            utms->professor_logined = utms->get_professor()[i];
            utms->professor_id_loged = id;
            utms->id_loged = id;
            flag = true;
        }
        if (utms->get_professor()[i]->get_pid() == id && utms->get_professor()[i]->get_password() != password)
            throw runtime_error(PERMISSION_DENIED_ERROR);
    }

    if (utms->get_utaccount()->get_id() == id && utms->get_utaccount()->get_password() == password)
    {
        cout << OK << endl;
        utms->is_logined = true;
        utms->is_ut_account_logined = true;
        utms->ut_account_logined = utms->get_utaccount();
        utms->ut_account_id_loged = id;
        flag = true;
    }

    if (utms->get_utaccount()->get_id() == id && utms->get_utaccount()->get_password() != password)
        throw runtime_error(PERMISSION_DENIED_ERROR);

    if (!flag)
        throw runtime_error(NOT_FOUND_ERROR);
}

void Orders::Post_logout(UTMS *utms)
{
    
    if (utms->is_logined)
    {
        utms->is_logined = false;
        utms->is_professor_logined = false;
        utms->is_student_logined = false;
        utms->is_ut_account_logined = false;
        cout << OK << endl;
    }
    else
    {
        throw runtime_error(PERMISSION_DENIED_ERROR);
    }
}

bool Orders::send_notification_to_student(UTMS *utms, string notif)
{
    if (utms->is_student_logined)
    {
        Student *logined = utms->student_logined;

        for (int i = 0; i < logined->get_connected_id().size(); i++)
        {
            if (is_student(logined->get_connected_id()[i]))
            {
                Student *connected_student = find_student_by_id_(logined->get_connected_id()[i]);
                connected_student->recieve_notif(notif);
            }
        }
        return true;
    }
    else if (utms->is_professor_logined)
    {
        Professors *logined = find_professor_by_id_(utms->professor_id_loged);

        for (int i = 0; i < logined->conected_id.size(); i++)
        {
            if (is_student(logined->conected_id[i]))
            {
                Student *connected_student = find_student_by_id_(logined->conected_id[i]);
                connected_student->recieve_notif(notif);
            }
        }
        return true;
    }
    else if (utms->is_ut_account_logined)
    {
        for (int i = 0; i < utms->get_utaccount()->conected_student_id.size(); i++)
        {
            Student *connected_student = find_student_by_id_(utms->get_utaccount()->conected_student_id[i]);
            connected_student->recieve_notif(notif);
        }
        return true;
    }
    return false;
}

bool Orders::send_notification_to_professor(UTMS *utms, string notif)
{
    if (utms->is_student_logined)
    {
        Student *logined = find_student_by_id(utms->student_id_loged);

        for (int i = 0; i < logined->get_connected_id().size(); i++)
        {
            if (is_professor(logined->get_connected_id()[i]))
            {
                Professors *connected_professor = find_professor_by_id_(logined->get_connected_id()[i]);
                connected_professor->notifications.push_back(notif);
            }
        }
        return true;
    }
    else if (utms->is_professor_logined)
    {
        Professors *logined = find_professor_by_id(utms->professor_id_loged);

        for (int i = 0; i < logined->conected_id.size(); i++)
        {
            if (is_professor(logined->conected_id[i]))
            {
                Professors *connected_professor = find_professor_by_id_(logined->conected_id[i]);
                connected_professor->notifications.push_back(notif);
            }
        }
        return true;
    }
    else if (utms->is_ut_account_logined)
    {
        for (int i = 0; i < utms->get_utaccount()->conected_professor_id.size(); i++)
        {
            Professors *connected_professsor = find_professor_by_id_(utms->get_utaccount()->conected_professor_id[i]);
            connected_professsor->notifications.push_back(notif);
        }
        return true;
    }
    return false;
}

void Orders::Post_post(string title, string message, string image, vector<string> command, UTMS *utms)
{
    if (!utms->is_logined)
        throw runtime_error(PERMISSION_DENIED_ERROR);
    if (utms->is_student_logined)
    {
        Student *s = find_student_by_id_(utms->student_id_loged);
        Posts p;
        p.message = message;
        p.title = title;
        p.id = s->get_previous() + 1;
        p.image_address = image;
        s->increase_previous();
        s->add_post(p);
        cout << OK << endl;
        string post_notif = s->get_sid() + SPACE_DELIMITER + s->get_name() + COLON_DELIMITER + SPACE_DELIMITER + "New Post";
        if (send_notification_to_student(utms, post_notif))
            return;
        else if (send_notification_to_professor(utms, post_notif))
            return;
    }
    else if (utms->is_professor_logined)
    {
        Professors *pro = utms->professor_logined;
        Posts p;
        p.message = message;
        p.title = title;
        p.id = pro->get_previous() + 1;
        p.image_address = image;
        pro->increase_previous();
        pro->add_post(p);
        cout << OK << endl;
        string post_notif = pro->get_pid() + SPACE_DELIMITER + pro->get_name() + COLON_DELIMITER + SPACE_DELIMITER + NEW_POST_MESSAGE;
        if (send_notification_to_student(utms, post_notif))
            return;
        else if (send_notification_to_professor(utms, post_notif))
            return;
    }
    else if (utms->is_ut_account_logined)
    {
        Posts p;
        p.message = message;
        p.title = title;
        p.id = utms->get_utaccount()->get_previous() + 1;
        p.image_address = image;
        utms->get_utaccount()->increase_previous();
        utms->get_utaccount()->add_post(p);
        cout << OK << endl;
        string post_notif = UT_ACCOUNT_NOTIF;
        if (send_notification_to_student(utms, post_notif))
            return;
        else if (send_notification_to_professor(utms, post_notif))
            return;
    }
}

bool Orders::connected_search(string id, UTMS *utms)
{
    for (int i = 0; i < utms->get_student().size(); i++)
    {
        if (utms->get_student()[i]->get_sid() == id)
        {
            return true;
        }
    }
    for (int i = 0; i < utms->get_professor().size(); i++)
    {
        if (utms->get_professor()[i]->get_pid() == id)
        {
            return true;
        }
    }
    if (utms->get_utaccount()->get_id() == id)
    {
        return true;
    }
    return false;
}

bool Orders::is_connected(string id, UTMS *utms)
{
    for (int j = 0; j < utms->get_student().size(); j++)
    {
        if (utms->get_student()[j]->get_sid() == utms->student_id_loged)
        {
            Student *s = find_student_by_id_(utms->student_id_loged);
            for (int i = 0; i < s->get_connected_id().size(); i++)
            {
                if (id == s->get_connected_id()[i])
                {
                    return true;
                }
            }
        }
    }

    for (int j = 0; j < utms->get_professor().size(); j++)
    {
        if (utms->get_professor()[j]->get_pid() == utms->professor_id_loged)
        {
            Professors *p = find_professor_by_id_(utms->professor_id_loged);
            for (int i = 0; i < p->conected_id.size(); i++)
            {
                if (id == p->conected_id[i])
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void Orders::Post_connect(string id, UTMS *utms)
{
    if (!utms->is_logined)
        throw runtime_error(PERMISSION_DENIED_ERROR);

    if (utms->is_ut_account_logined)
        throw runtime_error(PERMISSION_DENIED_ERROR);

    if (!(is_int(id) && stoi(id) > NATURAL_NUMBER))
        throw runtime_error(BAD_REQUEST_ERROR);

    if (is_connected(id, utms))
        throw runtime_error(BAD_REQUEST_ERROR);

    if (!connected_search(id, utms))
        throw runtime_error(NOT_FOUND_ERROR);

    if (utms->is_student_logined)
    {
        Student *s = utms->student_logined;
        s->add_connection(id);

        for (int i = 0; i < utms->get_professor().size(); i++)
        {
            if (utms->get_professor()[i]->get_pid() == id)
            {
                Professors *p = utms->get_professor()[i];
                p->conected_id.push_back(utms->student_id_loged);
            }
        }

        for (int i = 0; i < utms->get_student().size(); i++)
        {
            if (utms->get_student()[i]->get_sid() == id)
            {
                Student *ss = utms->get_student()[i];
                ss->add_connection(utms->student_id_loged);
            }
        }
        cout << OK << endl;
    }
    else if (utms->is_professor_logined)
    {
        Professors *p = find_professor_by_id_(utms->professor_id_loged);
        p->conected_id.push_back(id);
        for (int i = 0; i < utms->get_professor().size(); i++)
        {
            if (utms->get_professor()[i]->get_pid() == id)
            {
                Professors *p = find_professor_by_id(id);
                p->conected_id.push_back(utms->professor_id_loged);
            }
        }

        for (int i = 0; i < utms->get_student().size(); i++)
        {
            if (utms->get_student()[i]->get_sid() == id)
            {
                Student *ss = find_student_by_id_(id);
                ss->add_connection(utms->professor_id_loged);
            }
        }
        cout << OK << endl;
    }
}

bool Orders::have_course(string course_id, UTMS *utms)
{
    for (int i = 0; i < utms->get_course().size(); i++)
    {
        if (course_id == utms->get_course()[i]->get_cid())
        {
            return true;
        }
    }
    return false;
}

bool Orders::have_major(string id, UTMS *utms, Professors *professor)
{
    Course *c = find_course_by_id(id);
    vector<string> majors_id = divider_order(c->get_major_id(), SEMI_COLON_DELIMITER);
    for (int i = 0; i < majors_id.size(); i++)
    {
        if (majors_id[i] == professor->get_major_id())
        {
            return true;
        }
    }
    return false;
}

bool Orders::is_conflict_professor(Time t, Professors *professor)
{
    return professor->check_time(t);
}

bool Orders::is_conflict_student(Time t, Student *s)
{
    return s->check_time(t);
}

void Orders::Post_course_offer(vector<string> command, UTMS *utms)
{
    vector<string> temp = divider_order(command[10], COLON_DELIMITER);
    vector<string> help = divider_order(temp[1], DASH_DELIMITER);

    Time t;
    t.day = temp[0];
    t.from = help[0];
    t.to = help[1];
    if (!utms->is_logined || !utms->is_ut_account_logined)
    {
        throw runtime_error(PERMISSION_DENIED_ERROR);
    }
    if (!is_int(command[4]) || !is_int(command[6]) || !is_int(command[8]) || !is_int(command[14]))
    {
        throw runtime_error(BAD_REQUEST_ERROR);
    }
    if (stoi(command[4]) <= NATURAL_NUMBER || stoi(command[6]) <= NATURAL_NUMBER || stoi(command[8]) <= NATURAL_NUMBER || stoi(command[14]) <= NATURAL_NUMBER)
    {
        throw runtime_error(BAD_REQUEST_ERROR);
    }
    if (!have_course(command[4], utms))
    {
        throw runtime_error(NOT_FOUND_ERROR);
    }
    else
    {
        if (!is_not_professor(command[6], utms))
        {
            Professors *found_pro = find_professor_by_id(command[6]);
            if (!have_major(command[4], utms, found_pro))
            {
                throw runtime_error(PERMISSION_DENIED_ERROR);
            }
            if (!is_conflict_professor(t, found_pro))
            {
                throw runtime_error(PERMISSION_DENIED_ERROR);
            }
        }
        else
        {
            throw runtime_error(PERMISSION_DENIED_ERROR);
        }
        Professors *found_pro = find_professor_by_id(command[6]);

        Exam_date e_d;
        e_d.day = divider_order(command[12], SLASH_DELIMITER)[2];
        e_d.month = divider_order(command[12], SLASH_DELIMITER)[1];
        e_d.year = divider_order(command[12], SLASH_DELIMITER)[0];

        int index_id;
        index_id = utms->get_utaccount()->get_previous_course_offer() + 1;

        course_offer c_o;
        c_o.course_id = stoi(command[4]);
        c_o.professsor_id = stoi(command[6]);
        c_o.capacity = stoi(command[8]);
        c_o.time = t;
        c_o.exam_date = e_d;
        c_o.class_number = stoi(command[14]);
        c_o.course_offer_id = index_id;
        course_offers.push_back(c_o);
        utms->get_utaccount()->increase_previous_course_offer();
        is_offer = true;
        string post_notif = found_pro->get_pid() + SPACE_DELIMITER + found_pro->get_name() + NEW_COURSE_OFFERING_MESSAGE;
        cout << OK << endl;
        send_notification_to_student(utms, post_notif);
        send_notification_to_professor(utms, post_notif);
    }
}

void ok_post(string line, string &title, string &message, string &image)
{
    vector<string> command = divider_order(line, SPACE_DELIMITER);
    bool flag = false;
    for (int i = 0; i < command.size(); i++)
    {
        if (command[i] == MESSAGE)
        {
            flag = true;
            break;
        }
    }
    if (!flag)
        throw runtime_error(BAD_REQUEST_ERROR);

    string divide_for_titile = splitString(line, TITLE)[1];
    title = divider_order(divide_for_titile, '"')[1];
    string divide_for_message = splitString(line, MESSAGE)[1];
    message = divider_order(divide_for_message, '"')[1];
    for (int i = 0; i < command.size(); i++)
    {
        if (command[i] == IMAGE)
        {
            string divide_for_image = splitString(line, IMAGE)[1];
            string my_image = divider_order(divide_for_image, SPACE_DELIMITER)[1];
            image = my_image;
            break;
        }
    }
}

void Orders::Post_profile_photo(vector<string> command, UTMS *utms)
{
    if (!utms->is_logined)
        throw runtime_error(PERMISSION_DENIED_ERROR);

    if (command[3] != PHOTO)
        throw runtime_error(BAD_REQUEST_ERROR);

    if (utms->is_student_logined)
    {
        Student *s = utms->student_logined;
        s->add_profile(command[4]);
        cout << OK << endl;
    }
    if (utms->is_professor_logined)
    {
        Professors *p = utms->professor_logined;
        p->add_profile(command[4]);
        cout << OK << endl;
    }
    if (utms->is_ut_account_logined)
    {
        UTaccount *ut = utms->ut_account_logined;
        ut->add_profile(command[4]);
        cout << OK << endl;
    }
}

void Orders::Post_course_post(vector<string> command, UTMS *utms, string line)
{
    if (!utms->is_logined)
        throw runtime_error(PERMISSION_DENIED_ERROR);
    course_offer co = find_course_offer_by_id(command[4]);
    Course *c = find_course_by_id(to_string(co.course_id));
    string name = c->get_name();
    bool flag = false;

    if (to_string(co.professsor_id) == utms->id_loged)
    {
        flag = true;
    }
    if (!flag)
    {
        for (int i = 0; i < co.ta_id.size(); i++)
        {
            if (to_string(co.ta_id[i]) == utms->id_loged)
            {
                flag = true;
            }
        }
    }
    if (!flag)
        throw runtime_error(PERMISSION_DENIED_ERROR);

    Posts p;
    string message = NULL_STRING;
    string title = NULL_STRING;
    string image = NULL_STRING;
    ok_post(line, title, message, image);
    p.title = title;
    p.message = message;
    p.id = co.posts.size() + 1;
    p.image_address = image;
    p.author_id = utms->id_loged;
    for (int i = 0; i < course_offers.size(); i++)
    {
        if (course_offers[i].course_offer_id == stoi(command[4]))
        {
            course_offers[i].posts.push_back(p);
        }
    }
    cout << OK << endl;
    string post_notif = to_string(co.course_offer_id) + SPACE_DELIMITER + name + POST_COURSE_POST_NOTIF;
}

void Orders::Post_ta_form(vector<string> command, UTMS *utms, string line)
{
    if (!utms->is_logined || utms->is_student_logined || utms->is_ut_account_logined)
        throw runtime_error(PERMISSION_DENIED_ERROR);
    course_offer co = find_course_offer_by_id(command[4]);
    Professors *pro = utms->professor_logined;
    if (utms->professor_id_loged != to_string(co.professsor_id))
        throw runtime_error(PERMISSION_DENIED_ERROR);
    string message = divider_order(line, DOUBLE_QUATATION_DELIMITER)[1];
    Posts p;
    p.course_offer_id = stoi(command[4]);
    p.id = pro->get_previous() + 1;
    pro->increase_previous();
    p.message = message;
    pro->add_post(p);
    cout << OK << endl;
    string post_notif = pro->get_pid() + SPACE_DELIMITER + pro->get_name() + SPACE_DELIMITER + POST_TA_FORM_NOTIF;
    if (send_notification_to_student(utms, post_notif))
        return;
    else if (send_notification_to_professor(utms, post_notif))
        return;
}

void Orders::Post_close_ta_form(vector<string> command, UTMS *utms, string line)
{
    if (utms->is_logined || utms->is_student_logined || utms->is_ut_account_logined)
        throw runtime_error(PERMISSION_DENIED_ERROR);
    Professors *pro = utms->professor_logined;
    bool flag = false;
    for (int i = 0; i < pro->get_posts().size(); i++)
    {
        if (command[4] == to_string(pro->get_posts()[i].id))
        {
            if (pro->get_posts()[i].title == NULL_STRING)
            {
                flag = true;
                break;
            }
        }
    }
    if (!flag)
        throw runtime_error(NOT_FOUND_ERROR);
    course_offer co = find_course_offer_by_id(to_string(pro->get_posts()[stoi(command[4]) - 1].course_offer_id));
    for (int i = 0; i < co.TA_id_request.size(); i++)
    {

        cout << POST_CLOSE_TA_FORM_FIRST_OUTPUT << co.TA_id_request.size() << POST_CLOSE_TA_FORM_SECOND_OUTPUT << endl;
    }
}

void Orders::Post_ta_request(vector<string> command, UTMS *utms, string line)
{
    if (!utms->is_logined || utms->is_professor_logined || utms->is_ut_account_logined)
        throw runtime_error(PERMISSION_DENIED_ERROR);
    Professors *pro = find_professor_by_id(command[4]);
    Student *s = utms->student_logined;

    if (pro->get_posts().size() < stoi(command[6]))
    {
        throw runtime_error(NOT_FOUND_ERROR);
    }
    course_offer c_o = find_course_offer_by_id(to_string(pro->get_posts()[stoi(command[6]) - 1].course_offer_id));

    Course *c = find_course_by_id(to_string(c_o.course_id));

    if (command[6] != to_string(pro->get_posts()[stoi(command[6]) - 1].id))
        throw runtime_error(NOT_FOUND_ERROR);

    if (s->get_semester() < c->get_prerequisite())
        throw runtime_error(PERMISSION_DENIED_ERROR);

    for (int i = 0; i < course_offers.size(); i++)
    {
        if (pro->get_posts()[stoi(command[6]) - 1].id == stoi(command[6]))
        {
            course_offers[i].TA_id_request.push_back(utms->id_loged);
        }
    }

    c_o.TA_id_request.push_back(utms->id_loged);
    cout << OK << endl;
}

void Orders ::handeling_Post(vector<string> command, string line)
{
     if (command[1] == POST_REQUEST)
    {
        string title = NULL_STRING;
        string message = NULL_STRING;
        string image = NULL_STRING;
        ok_post(line, title, message, image);
        Post_post(title, message, image, command, utms);
    }

    else if (command[1] == CONNECT_REQUEST)
    {
        Post_connect(command[4], utms);
    }
    else if (command[1] == COURSE_OFFER_REQUEST)
    {
        Post_course_offer(command, utms);
    }
    else if (command[1] == PROFILE_PHOTO_REQUEST)
    {
        Post_profile_photo(command, utms);
    }
    else if (command[1] == COURSE_POST_REQUEST)
    {
        Post_course_post(command, utms, line);
    }
    else if (command[1] == TA_FORM_REQUEST)
    {
        Post_ta_form(command, utms, line);
    }
    else if (command[1] == CLOSE_TA_FORM_REQUEST)
    {
        Post_close_ta_form(command, utms, line);
    }
    else if (command[1] == TA_REQUEST)
    {
        Post_ta_request(command, utms, line);
    }
    else
    {
        throw runtime_error(NOT_FOUND_ERROR);
    }
}

Student *Orders ::find_student_by_id_(string id)
{
    for (int i = 0; i < utms->get_student().size(); i++)
    {
        if (id == utms->get_student()[i]->get_sid())
        {
            return utms->get_student()[i];
        }
    }
}

Professors *Orders ::find_professor_by_id(string id)
{
    for (int i = 0; i < utms->get_professor().size(); i++)
    {
        if (id == utms->get_professor()[i]->get_pid())
        {
            return utms->get_professor()[i];
        }
    }
    throw runtime_error(NOT_FOUND_ERROR);
}

void Orders::Delete_post(vector<string> command)

{
    if (!utms->is_logined)
        throw runtime_error(PERMISSION_DENIED_ERROR);
    if (utms->is_ut_account_logined)
    {
        utms->get_utaccount()->delete_post(command[4]);
    }
    else if (utms->is_student_logined)
    {
        Student *s = find_student_by_id(utms->student_id_loged);
        s->delete_post(command[4]);
    }
    else if (utms->is_professor_logined)
    {
        Professors *p = find_professor_by_id(utms->professor_id_loged);
        p->delete_post(command[4]);
    }
}

void Orders::Delete_my_course(string id)
{
    if (!utms->is_logined)
        throw runtime_error(PERMISSION_DENIED_ERROR);
    if (!(is_int(id) && stoi(id) >= NATURAL_NUMBER))
        throw runtime_error(BAD_REQUEST_ERROR);
    Student *s = utms->student_logined;
    s->delete_my_course(id);
    string post_notif = s->get_sid() + SPACE_DELIMITER + s->get_name() + DELETE_COURSE_MESSAGE;
    if (send_notification_to_student(utms, post_notif))
        return;
    else if (send_notification_to_professor(utms, post_notif))
        return;
    cout << OK << endl;
}

void Orders ::handeling_Delete(vector<string> command)
{
    if (command[1] == POST_REQUEST)
    {
        Delete_post(command);
    }
    else if (command[1] == MY_COURSES_REQUEST)
    {
        Delete_my_course(command[4]);
    }
    else
        throw runtime_error(NOT_FOUND_ERROR);
}

void Orders::Get_notification(vector<string> command, UTMS *utms)
{
    if (!utms->is_logined)
    {
        throw runtime_error(PERMISSION_DENIED_ERROR);
    }
    if (utms->is_ut_account_logined)
        throw runtime_error(PERMISSION_DENIED_ERROR);
    if (utms->is_student_logined)
    {
        Student *s = utms->student_logined;
        s->view_notif();
    }
    if (utms->is_professor_logined)
    {
        Professors *p = utms->professor_logined;
        if (p->notifications.size() > NATURAL_NUMBER)
        {
            for (int i = p->notifications.size() - 1; i >= 0; i--)
            {

                cout << p->notifications[i] << endl;
            }
        }

        else
        {
            throw runtime_error(EMPTY_ERROR);
        }
        p->notifications.clear();
    }
}

course_offer Orders::find_course_offer_by_id(string id)
{
    for (int i = 0; i < course_offers.size(); i++)
    {
        if (stoi(id) == course_offers[i].course_offer_id)
        {
            return course_offers[i];
        }
    }
    throw runtime_error(NOT_FOUND_ERROR);
}

void Orders::Get_courses(string id, UTMS *utms)
{
    if (!utms->is_logined)
        throw runtime_error(PERMISSION_DENIED_ERROR);
    if (utms->is_ut_account_logined)
        throw runtime_error(PERMISSION_DENIED_ERROR);
    if (!(is_int(id) && stoi(id) >= NATURAL_NUMBER))
        throw runtime_error(BAD_REQUEST_ERROR);
    course_offer co = find_course_offer_by_id(id);
    Professors *p = find_professor_by_id_(to_string(co.professsor_id));
    Course *c = find_course_by_id(to_string(co.course_id));
    cout << co.course_offer_id << SPACE_DELIMITER << c->get_name() << SPACE_DELIMITER << co.capacity << SPACE_DELIMITER << p->get_name() << SPACE_DELIMITER << co.time.day << COLON_DELIMITER << co.time.from << DASH_DELIMITER << co.time.to
         << SPACE_DELIMITER << co.exam_date.year << SLASH_DELIMITER << co.exam_date.month << SLASH_DELIMITER << co.exam_date.day << SPACE_DELIMITER << co.class_number << endl;
}

void Orders::Get_all_courses(UTMS *utms)
{
    if (!utms->is_logined)
        throw runtime_error(PERMISSION_DENIED_ERROR);
    if (utms->is_ut_account_logined)
        throw runtime_error(PERMISSION_DENIED_ERROR);
    if (course_offers.size() == NATURAL_NUMBER)
        throw runtime_error(EMPTY_ERROR);

    for (int i = 0; i < course_offers.size(); i++)
    {
        Professors *p = find_professor_by_id_(to_string(course_offers[i].professsor_id));
        Course *c = find_course_by_id(to_string(course_offers[i].course_id));
        cout << course_offers[i].course_offer_id << SPACE_DELIMITER << c->get_name() << SPACE_DELIMITER << course_offers[i].capacity << SPACE_DELIMITER << p->get_name() << endl;
    }
}

bool Orders::is_student(string id)
{
    for (int i = 0; i < utms->get_student().size(); i++)
    {
        if (utms->get_student()[i]->get_sid() == id)
        {
            return true;
        }
    }
    return false;
}

bool Orders::is_professor(string id)
{
    for (int i = 0; i < utms->get_professor().size(); i++)
    {
        if (utms->get_professor()[i]->get_pid() == id)
        {
            return true;
        }
    }
    return false;
}

bool Orders::is_ut_account(string id)
{
    if (utms->get_utaccount()->get_id() == id)
    {
        return true;
    }
    return false;
}

Major *Orders::find_major_by_id(string id)
{
    for (int i = 0; i < utms->get_major().size(); i++)
    {
        if (id == utms->get_major()[i]->get_mid())
        {
            return utms->get_major()[i];
        }
    }
}

course_offer Orders::find_course_offer_by_pro_id(string id)
{
    for (int i = 0; i < course_offers.size(); i++)
    {
        if (stoi(id) == course_offers[i].professsor_id)
        {
            return course_offers[i];
        }
    }
    throw runtime_error(NOT_FOUND_ERROR);
}

vector<course_offer> Orders::find_course_offer_by_pro_id_(string id)
{
    vector<course_offer> co;
    for (int i = 0; i < course_offers.size(); i++)
    {
        if (stoi(id) == course_offers[i].professsor_id)
        {
            co.push_back(course_offers[i]);
        }
    }
    return co;
}

void Orders::Get_post(string id, string post_id, UTMS *utms)
{
    if (!utms->is_logined)
        throw runtime_error(PERMISSION_DENIED_ERROR);
    if (!(is_int(id) && stoi(id) >= NATURAL_NUMBER) || !(is_int(post_id) && stoi(post_id) > 0))
        throw runtime_error(BAD_REQUEST_ERROR);
    if (utms->is_ut_account_logined)
        throw runtime_error(PERMISSION_DENIED_ERROR);
    if (is_student(id))
    {
        Student *s = find_student_by_id_(id);
        bool flag = false;
        for (int i = 0; i < s->get_posts().size(); i++)
        {
            if (s->get_posts()[i].id == stoi(post_id))
                flag = true;
        }
        if (!flag)
            throw runtime_error(NOT_FOUND_ERROR);

        string title = s->get_posts()[stoi(post_id) - 1].title;
        string message = s->get_posts()[stoi(post_id) - 1].message;
        string name = s->get_name();
        string semester = s->get_semester();
        Major *m = find_major_by_id(s->get_major_id());
        string major_name = m->get_major_name();
        cout << name << SPACE_DELIMITER << major_name << SPACE_DELIMITER << semester << SPACE_DELIMITER;
        for (int i = 0; i < s->get_my_courses().size(); i++)
        {
            Course *c = find_course_by_id(to_string(s->get_my_courses()[i].course_id));
            cout << c->get_name() << COMMA_DELIMITER << endl;
        }
        cout << endl;
        cout << SPACE_DELIMITER << post_id << SPACE_DELIMITER << DOUBLE_QUATATION_DELIMITER << title << DOUBLE_QUATATION_DELIMITER << SPACE_DELIMITER << DOUBLE_QUATATION_DELIMITER << message << DOUBLE_QUATATION_DELIMITER << endl;
    }
    else if (is_professor(id))
    {
        Professors *p = find_professor_by_id_(id);
        if (p->get_posts().size() < stoi(post_id))
            throw runtime_error(NOT_FOUND_ERROR);

        string message = p->get_posts()[stoi(post_id) - 1].message;
        string name = p->get_name();
        string position = p->get_position();
        Major *m = find_major_by_id(p->get_major_id());
        string major_name = m->get_major_name();
        course_offer c_o = find_course_offer_by_pro_id(id);
        string course_id = to_string(c_o.course_id);
        Course *c = find_course_by_id(course_id);
        string courses = c->get_name();

        cout << name << SPACE_DELIMITER << major_name << SPACE_DELIMITER << position << SPACE_DELIMITER << courses << SPACE_DELIMITER << endl;
        cout << post_id;
        if (p->get_posts()[stoi(post_id) - 1].title != NULL_STRING)
        {
            string title = p->get_posts()[stoi(post_id) - 1].title;
            cout << SPACE_DELIMITER << DOUBLE_QUATATION_DELIMITER << title << DOUBLE_QUATATION_DELIMITER << SPACE_DELIMITER << DOUBLE_QUATATION_DELIMITER << message << DOUBLE_QUATATION_DELIMITER << endl;
        }
        else
        {
            course_offer co = find_course_offer_by_id(to_string(p->get_posts()[stoi(post_id) - 1].course_offer_id));
            Course *c = find_course_by_id(to_string(co.course_id));
            cout << SPACE_DELIMITER << GET_POST_FIRST_OUTPUT << c->get_name() << GET_POST_SECOND_OUTPUT << endl
                 << co.course_offer_id << SPACE_DELIMITER << c->get_name() << SPACE_DELIMITER << co.capacity << SPACE_DELIMITER << name << SPACE_DELIMITER << co.time.day << COLON_DELIMITER
                 << co.time.from << DASH_DELIMITER << co.time.to << SPACE_DELIMITER << co.exam_date.year << SLASH_DELIMITER << co.exam_date.month << SLASH_DELIMITER << co.exam_date.day << SPACE_DELIMITER << co.class_number << endl
                 << DOUBLE_QUATATION_DELIMITER << message << DOUBLE_QUATATION_DELIMITER << endl;
        }
    }
    else if (is_ut_account(id))
    {
        if (utms->get_utaccount()->get_posts().size() < stoi(post_id))
            throw runtime_error(NOT_FOUND_ERROR);

        string title = utms->get_utaccount()->get_posts()[stoi(post_id) - 1].title;
        string messages = utms->get_utaccount()->get_posts()[stoi(post_id) - 1].message;
        cout << UT_ACCOUNT_PASSWORD_REQUEST << endl;
        cout << post_id << SPACE_DELIMITER << DOUBLE_QUATATION_DELIMITER << title << DOUBLE_QUATATION_DELIMITER << SPACE_DELIMITER << DOUBLE_QUATATION_DELIMITER << messages << DOUBLE_QUATATION_DELIMITER << endl;
    }
    else
        throw runtime_error(NOT_FOUND_ERROR);
}

bool Orders::have_course_offer(string id)
{
    for (int i = 0; i < course_offers.size(); i++)
    {
        if (stoi(id) == course_offers[i].professsor_id)
        {
            return true;
        }
    }
    return false;
}

void Orders::Get_personal_page(string id, UTMS *utms)
{
    if (!utms->is_logined)
        throw runtime_error(PERMISSION_DENIED_ERROR);
    if (!(is_int(id) && stoi(id) >= NATURAL_NUMBER))
        throw runtime_error(BAD_REQUEST_ERROR);
    if (utms->is_ut_account_logined)
        throw runtime_error(PERMISSION_DENIED_ERROR);

    if (is_student(id))
    {
        Student *s = find_student_by_id_(id);
        string name = s->get_name();
        string semester = s->get_semester();
        Major *m = find_major_by_id(s->get_major_id());
        string major_name = m->get_major_name();

        cout << name << SPACE_DELIMITER << major_name << SPACE_DELIMITER << semester << SPACE_DELIMITER;
        for (int i = 0; i < s->get_my_courses().size(); i++)
        {
            Course *c = find_course_by_id(to_string(s->get_my_courses()[i].course_id));
            cout << c->get_name();
            if (i < s->get_my_courses().size() - 1)
                cout << COMMA_DELIMITER;
        }
        cout << endl;
        for (int i = s->get_posts().size() - 1; i >= 0; i--)
        {
            cout << s->get_posts()[i].id << SPACE_DELIMITER << DOUBLE_QUATATION_DELIMITER << s->get_posts()[i].title << DOUBLE_QUATATION_DELIMITER << endl;
        }
    }
    else if (is_professor(id))
    {
        Professors *p = find_professor_by_id_(id);
        string name = p->get_name();
        string position = p->get_position();
        Major *m = find_major_by_id(p->get_major_id());
        string major_name = m->get_major_name();
        if (have_course_offer(id))
        {
            vector<course_offer> c_os;
            c_os = find_course_offer_by_pro_id_(id);
            vector<Course *> c;
            for (int i = 0; i < c_os.size(); i++)
            {
                c.push_back(find_course_by_id(to_string(c_os[i].course_id)));
            }

            cout << name << SPACE_DELIMITER << major_name << SPACE_DELIMITER << position << SPACE_DELIMITER;
            for (int i = 0; i < c.size(); i++)
            {
                cout << c[i]->get_name();
                if (i < c.size() - 1)
                    cout << COMMA_DELIMITER;
            }
            cout << endl;
        }
        else
        {
            cout << name << SPACE_DELIMITER << major_name << SPACE_DELIMITER << position << SPACE_DELIMITER << endl;
        }
        for (int i = p->get_posts().size() - 1; i >= 0; i--)
        {
            cout << p->get_posts()[i].id << SPACE_DELIMITER;
            if (p->get_posts()[i].title != "")
                cout << DOUBLE_QUATATION_DELIMITER << p->get_posts()[i].title << DOUBLE_QUATATION_DELIMITER << endl;
            else
            {
                course_offer co = find_course_offer_by_id(to_string(p->get_posts()[i].course_offer_id));
                Course *c = find_course_by_id(to_string(co.course_id));
                cout << GET_POST_FIRST_OUTPUT << c->get_name() << GET_POST_SECOND_OUTPUT<< endl;
            }
        }
    }
    else if (is_ut_account(id))
    {
        cout << UT_ACCOUNT_PASSWORD_REQUEST << endl;
        for (int i = utms->get_utaccount()->get_posts().size() - 1; i >= 0; i--)
        {
            cout << utms->get_utaccount()->get_posts()[i].id << SPACE_DELIMITER << DOUBLE_QUATATION_DELIMITER << utms->get_utaccount()->get_posts()[i].title << DOUBLE_QUATATION_DELIMITER << endl;
        }
    }
    else
        throw runtime_error(NOT_FOUND_ERROR);
}

void Orders::Get_my_courses(UTMS *utms)
{
    if (utms->is_ut_account_logined)
        throw runtime_error(PERMISSION_DENIED_ERROR);
    Student *s = utms->student_logined;
    if (s->get_my_courses().size() == NATURAL_NUMBER)
        throw runtime_error(EMPTY_ERROR);
    if (utms->is_ut_account_logined)
        throw runtime_error(PERMISSION_DENIED_ERROR);
    for (int i = 0; i < s->get_my_courses().size(); i++)
    {
        int id = s->get_my_courses()[i].course_offer_id;
        Course *c = find_course_by_id(to_string(s->get_my_courses()[i].course_id));
        string name = c->get_name();
        int capacity = s->get_my_courses()[i].capacity;
        Professors *p = find_professor_by_id_(to_string(s->get_my_courses()[i].professsor_id));
        cout << id << SPACE_DELIMITER << name << SPACE_DELIMITER << capacity << SPACE_DELIMITER << p->get_name() << SPACE_DELIMITER << s->get_my_courses()[i].time.day << COLON_DELIMITER << s->get_my_courses()[i].time.from
             << DASH_DELIMITER << s->get_my_courses()[i].time.to << SPACE_DELIMITER << s->get_my_courses()[i].exam_date.year << SLASH_DELIMITER << s->get_my_courses()[i].exam_date.month << SLASH_DELIMITER << s->get_my_courses()[i].exam_date.day << SPACE_DELIMITER << s->get_my_courses()[i].class_number << endl;
    }
}

void Orders::Get_course_channel(string id, UTMS *utms)
{
    if (!utms->is_logined)
        throw runtime_error(PERMISSION_DENIED_ERROR);

    course_offer co = find_course_offer_by_id(id);
    Course *c = find_course_by_id(to_string(co.course_id));
    Professors *p = find_professor_by_id_(to_string(co.professsor_id));
    bool flag = false;
    if (to_string(co.professsor_id) == utms->id_loged)
    {
        flag = true;
    }
    if (!flag)
    {
        for (int i = 0; i < co.ta_id.size(); i++)
        {
            if (to_string(co.ta_id[i]) == utms->id_loged)
            {
                flag = true;
                break;
            }
        }
    }
    if (!flag)
    {
        if (utms->is_student_logined)
        {
            Student *s = utms->student_logined;
            for (int i = 0; i < s->get_my_courses().size(); i++)
            {
                if (s->get_my_courses()[i].course_offer_id == stoi(id))
                {
                    flag = true;
                    break;
                }
            }
        }
    }
    if (!flag)
    {
        throw runtime_error(PERMISSION_DENIED_ERROR);
    }

    cout << co.course_offer_id << SPACE_DELIMITER << c->get_name() << SPACE_DELIMITER << co.capacity << SPACE_DELIMITER << p->get_name()
         << SPACE_DELIMITER << co.time.day << COLON_DELIMITER << co.time.from << DASH_DELIMITER << co.time.to << SPACE_DELIMITER << co.exam_date.year << SLASH_DELIMITER << co.exam_date.month << SLASH_DELIMITER << co.exam_date.day << SPACE_DELIMITER << co.class_number << endl;
    for (int i = co.posts.size() - 1; i >= 0; i--)
    {
        if (is_professor(co.posts[i].author_id))
        {
            Professors *pro = find_professor_by_id_(co.posts[i].author_id);
            cout << co.posts[i].id << SPACE_DELIMITER << pro->get_name() << SPACE_DELIMITER << DOUBLE_QUATATION_DELIMITER << co.posts[i].title << DOUBLE_QUATATION_DELIMITER << endl;
        }
        else if (is_student(co.posts[i].author_id))
        {
            Student *stu = find_student_by_id_(co.posts[i].author_id);
            cout << co.posts[i].id << SPACE_DELIMITER << stu->get_name() << SPACE_DELIMITER << DOUBLE_QUATATION_DELIMITER << co.posts[i].title << DOUBLE_QUATATION_DELIMITER << endl;
        }
    }
}

void Orders::Get_course_post(string id, string post_id, UTMS *utms)
{
    if (!utms->is_logined)
        throw runtime_error(PERMISSION_DENIED_ERROR);
    course_offer co = find_course_offer_by_id(id);
    Course *c = find_course_by_id(to_string(co.course_id));
    Professors *pro = find_professor_by_id_(to_string(co.professsor_id));
    bool flag = false;
    if (to_string(co.professsor_id) == utms->professor_id_loged)
    {
        flag = true;
    }
    if (!flag)
    {
        for (int i = 0; i < co.ta_id.size(); i++)
        {
            if (to_string(co.ta_id[i]) == utms->student_id_loged)
            {
                flag = true;
                break;
            }
        }
    }
    if (!flag)
    {
        if (utms->is_student_logined)
        {
            Student *s = utms->student_logined;
            for (int i = 0; i < s->get_my_courses().size(); i++)
            {
                if (s->get_my_courses()[i].course_offer_id == stoi(id))
                {
                    flag = true;
                    break;
                }
            }
        }
    }
    if (!flag)
    {
        throw runtime_error(PERMISSION_DENIED_ERROR);
    }
    bool flag2 = false;
    for (int i = 0; i < co.posts.size(); i++)
    {
        if (co.posts[i].id == stoi(post_id))
        {
            flag2 = true;
            break;
        }
    }
    if (!flag2)
        throw runtime_error(NOT_FOUND_ERROR);

    cout << co.course_offer_id << SPACE_DELIMITER << c->get_name() << SPACE_DELIMITER << co.capacity << SPACE_DELIMITER << pro->get_name() << SPACE_DELIMITER
         << co.time.day << COLON_DELIMITER << co.time.from << DASH_DELIMITER << co.time.to << SPACE_DELIMITER << co.exam_date.year << SLASH_DELIMITER << co.exam_date.month << SLASH_DELIMITER << co.exam_date.day << SPACE_DELIMITER << co.class_number << endl;
    if (is_professor(co.posts[stoi(post_id) - 1].author_id))
    {
        Professors *pro = find_professor_by_id_(co.posts[stoi(post_id) - 1].author_id);
        cout << co.posts[stoi(post_id) - 1].id << SPACE_DELIMITER << pro->get_name() << SPACE_DELIMITER << DOUBLE_QUATATION_DELIMITER << co.posts[stoi(post_id) - 1].title << DOUBLE_QUATATION_DELIMITER << SPACE_DELIMITER << co.posts[stoi(post_id) - 1].message << endl;
    }
    else if (is_student(co.posts[stoi(post_id) - 1].author_id))
    {
        Student *stu = find_student_by_id_(co.posts[stoi(post_id) - 1].author_id);
        cout << co.posts[stoi(post_id) - 1].id << SPACE_DELIMITER << stu->get_name() << SPACE_DELIMITER << DOUBLE_QUATATION_DELIMITER << co.posts[stoi(post_id) - 1].title << DOUBLE_QUATATION_DELIMITER << endl;
    }
}

void ok_get_course_post(string &id, string &post_id, string line, vector<string> command)
{
    string temp = splitString(line, POST_ID)[1];
    post_id = divider_order(temp, SPACE_DELIMITER)[1];
    string temp2 = splitString(line, ID)[1];
    id = divider_order(temp2, SPACE_DELIMITER)[1];
}

void Orders::handeling_Get(vector<string> command, string line)
{
    if (command[1] == NOTIFICATION_REQUEST)
    {
        Get_notification(command, utms);
    }
    else if (command[1] == COURSES_REQUEST)
    {
        if (command.size() == 3)
            Get_all_courses(utms);
        else
            Get_courses(command[4], utms);
    }
    else if (command[1] == POST_REQUEST)
    {
        Get_post(command[4], command[6], utms);
    }
    else if (command[1] == PERSONAL_PAGE_REQUEST)
    {
        Get_personal_page(command[4], utms);
    }
    else if (command[1] == MY_COURSES_REQUEST)
    {
        Get_my_courses(utms);
    }
    else if (command[1] == COURSE_CHANEL_REQUEST)
    {
        Get_course_channel(command[4], utms);
    }
    else if (command[1] == COURSE_POST_REQUEST)
    {
        string id = NULL_STRING;
        string post_id = NULL_STRING;
        ok_get_course_post(id, post_id, line, command);
        Get_course_post(command[4], command[6], utms);
    }

    else
        throw runtime_error(NOT_FOUND_ERROR);
}

void Orders::Put_my_courses(string id, UTMS *utms)
{
    bool exists = false;
    if (!utms->is_logined)
        throw runtime_error(PERMISSION_DENIED_ERROR);
    if (!(is_int(id) && stoi(id) >= NATURAL_NUMBER))
        throw runtime_error(BAD_REQUEST_ERROR);
    for (int i = 0; i < course_offers.size(); i++)
    {
        if (id == to_string(course_offers[i].course_offer_id))
            exists = true;
    }
    if (!exists)
        throw runtime_error(NOT_FOUND_ERROR);

    Student *s = utms->student_logined;
    course_offer co = find_course_offer_by_id(id);
    Course *c = find_course_by_id(to_string(co.course_id));
    if (s->get_semester() < c->get_prerequisite())
        throw runtime_error(PERMISSION_DENIED_ERROR);

    vector<string> major_ids = divider_order(c->get_major_id(), SEMI_COLON_DELIMITER);
    bool flag = false;
    for (int i = 0; i < major_ids.size(); i++)
    {
        if ((major_ids[i] == s->get_major_id()))
        {
            flag = true;
            break;
        }
    }
    if (!flag)
        throw runtime_error(PERMISSION_DENIED_ERROR);

    for (int i = 0; i < s->get_my_courses().size(); i++)
    {
        if (s->get_my_courses()[i].exam_date.day == co.exam_date.day && s->get_my_courses()[i].exam_date.month == co.exam_date.month && s->get_my_courses()[i].exam_date.year == co.exam_date.year)
            throw runtime_error(PERMISSION_DENIED_ERROR);
    }
    for (int i = 0; i < s->get_my_courses().size(); i++)
    {
        if (!is_conflict_student(co.time, s))
            throw runtime_error(PERMISSION_DENIED_ERROR);
    }
    s->add_my_courses(co);
    string post_notif = s->get_sid() + SPACE_DELIMITER + s->get_name() + COLON_DELIMITER + SPACE_DELIMITER + GET_COURSE_MESSAGE;
    cout << OK << endl;
    if (send_notification_to_student(utms, post_notif))
        return;
    else if (send_notification_to_professor(utms, post_notif))
        return;
}

void Orders::handeling_Put(vector<string> command)
{
    if (command[1] == MY_COURSES_REQUEST)
    {
        Put_my_courses(command[4], utms);
    }
    else
        throw runtime_error(NOT_FOUND_ERROR);
}

void Orders::input()
{
    string line;
    while (getline(cin, line))
    {
        if (line.size() < INVALID_SIZE)
        {
            cout << BAD_REQUEST_ERROR << endl;
            continue;
        }
        vector<string> input_line = divider_order(line, SPACE_DELIMITER);
        try
        {
            if (input_line[0] == POST_ORDER)
            {
                handeling_Post(input_line, line);
            }
            else if (input_line[0] == DELETE_ORDER)
            {
                handeling_Delete(input_line);
            }
            else if (input_line[0] == GET_ORDER)
            {
                handeling_Get(input_line, line);
            }
            else if (input_line[0] == PUT_ORDER)
            {
                handeling_Put(input_line);
            }
            else
            {
                cout << BAD_REQUEST_ERROR << endl;
            }
        }
        catch (runtime_error &ex)
        {
            cout << ex.what() << endl;
        }
    }
}