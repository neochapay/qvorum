#include "usercontroller.h"

#include "models/user.h"

#include "tcp/tcpmultithreadedserver.h"
#include "http/httpwebengine.h"
#include "http/httpresource.h"

using namespace QtWebServer;

userController::userController():Http::Resource("/user")
{

}

userController::~userController()
{

}

void userController::deliver(const Http::Request &request, Http::Response& response) {

    response.setHeader(Http::ContentType, "text/html");

    QString body;
    QString user_id = request.getParameters().value("userId");
    if(user_id.length() > 0)
    {
        User* user = User::fromId(user_id.toInt());
        if(user == 0)
        {
            response.setStatusCode(Http::NotFound);
            body += "Not found user "+user_id;
        }
        else
        {
            response.setStatusCode(Http::Ok);
            body += user->nickName();
        }
    }

    body += " HELLO USER";
    response.setBody(body.toUtf8());
}
