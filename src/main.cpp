#include <QCoreApplication>

// QtWebServer includes
#include "tcp/tcpmultithreadedserver.h"
#include "http/httpwebengine.h"
#include "http/httpresource.h"

#include "controllers/usercontroller.h"
#include "pages/notfoundpage.h"

using namespace QtWebServer;

class RootPage : public Http::Resource {
public:
    RootPage() : Http::Resource("/") { }
    ~RootPage() { }

    void deliver(const Http::Request&, Http::Response& response) {
        // In a real world application, one would interpret the request
        // and deliver a proper response.
        response.setStatusCode(Http::Ok);
        response.setHeader(Http::ContentType, "text/html");

        response.setBody("<h1>Page found!</h1><form action='' method='post'><input type='file' name='one' value='1'><input type='hidden' name='two' value='2'><input type='submit'></form>");
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Log::instance()->setLoggingMode(Log::LoggingModeConsole);

    Http::WebEngine webEngine;

    webEngine.addResource(new userController());
    webEngine.addNotFoundPage(new notFoundPage());
    webEngine.addResource(new RootPage());

    Tcp::MultithreadedServer tcpServer;
    tcpServer.setResponder(&webEngine);
    tcpServer.listen(QHostAddress::Any, 8080, 16);
    if(!tcpServer.isListening()) {
        return 1;
    }

    return a.exec();
}
