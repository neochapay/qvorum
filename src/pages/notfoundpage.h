#ifndef NOTFOUNDPAGE_H
#define NOTFOUNDPAGE_H

#include <QObject>

#include "http/httpresource.h"

using namespace QtWebServer;

class notFoundPage : public Http::Resource
{
    Q_OBJECT
public:
    explicit notFoundPage();
    ~notFoundPage();

    void deliver(const Http::Request &request, Http::Response& response);
};

#endif // NOTFOUNDPAGE_H
