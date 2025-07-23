#include "UTMS.hpp"
#include "Orders.hpp"
#include "/home/sajjad/AP_A6/finish/server/server.hpp"
#include "/home/sajjad/AP_A6/finish/examples/handlers.hpp"
#include "/home/sajjad/AP_A6/finish/globalStuff.hpp"

void mapServerPaths(Server &server, Orders *orders)
{
    server.setNotFoundErrPage("static/404.html");

    server.get("/", new ShowPage("static/logincss.html"));
    server.post("/login", new LoginHandler(orders));

    server.get("/logout",new LogoutHandler(orders));

    server.get("/home", new ShowPage("static/home.html"));
    server.get("/home.png", new ShowPage("static/home.png"));
}

int main(int argc, char **argv)
{

    if (argc != 5)
    {
        cout << ERROR << endl;
        return 0;
    }
    vector<string> pathes;
    for (int i = 1; i < 5; i++)
    {
        pathes.push_back(argv[i]);
    }
    UTMS *utms = new UTMS(pathes);
    Orders *orders = new Orders(utms);
    try
    {
        int port = 5000;
        Server server(port);

        mapServerPaths(server, orders);

        cout << "Server running on port: " << port << endl;
        server.run();
    }
    catch (const invalid_argument &e)
    {
        cerr << e.what() << endl;
        delete orders;
        delete utms;
    }
    catch (const Server::Exception &e)
    {
        cerr << e.getMessage() << endl;
        delete orders;
        delete utms;
    }
    delete orders;
    delete utms;
    return 0;
}
