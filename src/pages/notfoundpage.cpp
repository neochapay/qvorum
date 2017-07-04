#include "notfoundpage.h"

#include "tcp/tcpmultithreadedserver.h"
#include "http/httpwebengine.h"
#include "http/httpresource.h"

using namespace QtWebServer;

notFoundPage::notFoundPage(): Http::Resource("404")
{

}


notFoundPage::~notFoundPage()
{

}

void notFoundPage::deliver(const Http::Request&, Http::Response& response) {
    response.setStatusCode(Http::NotFound);
    response.setHeader(Http::ContentType, "text/html");
    response.setBody("<h1>Page not found!</h1>");
}
