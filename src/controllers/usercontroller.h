#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include <QObject>

#include "http/httpresource.h"

using namespace QtWebServer;

class userController : public Http::Resource
{
    Q_OBJECT
public:
    explicit userController();
    ~userController();

    void deliver(const Http::Request &request, Http::Response& response);
};

#endif // USERCONTROLLER_H
