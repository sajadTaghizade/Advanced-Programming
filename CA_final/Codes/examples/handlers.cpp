#include "handlers.hpp"

#include <cstdlib>
#include <iostream>

using namespace std;

LoginHandler::LoginHandler(Orders *orders)
{
    MY_orders = orders;
}
LogoutHandler::LogoutHandler(Orders *orders)
{
    MY_orders = orders;
}

Response *RandomNumberHandler::callback(Request *req)
{
    Response *res = new Response();
    res->setHeader("Content-Type", "text/html");

    string randomNumber = to_string(rand() % 10 + 1);
    string body;

    body += "<!DOCTYPE html>";
    body += "<html lang=\"en\">";

    body += "<head>";
    body += "  <title>Random Number Page</title>";
    body += "</head>";

    body += "<body style=\"text-align: center;\">";
    body += "  <h1>AP HTTP</h1>";
    body += "  <p>A random number in [1, 10] is: " + randomNumber + "</p>";
    body += "  <p>SessionId: " + req->getSessionId() + "</p>";
    body += "</body>";

    body += "</html>";
    res->setBody(body);
    return res;
}

Response *LoginHandler::callback(Request *req)
{

    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");
    if (username == "root")
    {
        throw Server::Exception("Remote root access has been disabled.");
    }
    try
    {

        MY_orders->Post_login(MY_orders->get_info(), username, password);
        Response *res = Response::redirect("/home");
        res->setSessionId("SID");
        return res;
    }
    catch (const runtime_error &e)
    {
        cerr << e.what() << endl;
    }
    Response *res = Response::redirect("/");
    return res;
}

Response *LogoutHandler::callback(Request *req)
{

    try
    {

        MY_orders->Post_logout(MY_orders->get_info());
        Response *res = Response::redirect("/");
        return res;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
            Response *res = Response::redirect("/home");
            return res;

}

Response *UploadHandler::callback(Request *req)
{
    string name = req->getBodyParam("file_name");
    string file = req->getBodyParam("file");
    utils::writeToFile(file, name);
    Response *res = Response::redirect("/");
    return res;
}

ColorHandler::ColorHandler(const string &filePath)
    : TemplateHandler(filePath) {}

map<string, string> ColorHandler::handle(Request *req)
{
    string newName = "I am " + req->getQueryParam("name");
    map<string, string> context;
    context["name"] = newName;
    context["color"] = req->getQueryParam("color");
    return context;
}
