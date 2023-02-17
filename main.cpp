#include <iostream>
#include <sstream>
#include <vector>
#include "util/UrlUtil.h"

#define HOMEWORK_VERSION 1.0

std::string buildGetRequest(const UrlParts& urlParts, const std::string& userAgent, const std::string& http_protocol="HTTP/1.0") {
    std::ostringstream out;
    out << "GET " << urlParts.request << "HTTP/1.0\n";
    out << "Host: " << urlParts.host << "\n";
    out << "Connection: close";
    return out.str();
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Expected 1 argument, received " << argc-1 << "." << std::endl;
    } else {
        std::string url = argv[1];

        int urlValidity = UrlUtil::testUrlValidity(url);
        if (not UrlUtil::isHttpUrl(url)) {
            // invalid scheme
        }
        if (urlValidity == UNACCEPTABLE_SCHEME) {
            // error
        } else if (urlValidity == INVALID_PORT) {
            // error
        }
        // proceed
        UrlParts urlParts = UrlUtil::parseUrl(url);
        const std::string userAgent = "adilCrawler" + std::to_string(HOMEWORK_VERSION);
        std::string httpRequestString = buildGetRequest(urlParts, userAgent);
        std::cout << httpRequestString << "\n";
    }
    return 0;
}