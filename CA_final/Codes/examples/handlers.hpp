#ifndef HANDLERS_HPP_INCLUDE
#define HANDLERS_HPP_INCLUDE

#include <map>
#include <string>

#include "../server/server.hpp"
#include "/home/sajjad/AP_A6/finish/Orders.hpp"
#include "/home/sajjad/AP_A6/finish/globalStuff.hpp"

using namespace std;

class RandomNumberHandler : public RequestHandler
{
public:
    Response *callback(Request *) override;
};



class LoginHandler : public RequestHandler
{
public:
    LoginHandler(Orders *orders);
    
    Response *callback(Request *) override;

private:
    Orders *MY_orders;
};

class LogoutHandler : public RequestHandler
{
public:
    LogoutHandler(Orders *orders);
    
    Response *callback(Request *) override;

private:
    Orders *MY_orders;
};

class UploadHandler : public RequestHandler
{
public:
    Response *callback(Request *) override;
};

class ColorHandler : public TemplateHandler
{
public:
    ColorHandler(const string &filePath);
    map<string, string> handle(Request *req) override;
};

#endif // HANDLERS_HPP_INCLUDE
