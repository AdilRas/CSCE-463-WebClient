#include <iostream>
#include <vector>
#include "util/UrlUtil.h"
#include "util/HtmlParser.h"

int main(int argc, char** argv) {
    std::string buf = R"(<a href="http://www.google.com/">Link</a><a href="http://www.yahoo.com/">Link</a><a href="/poop">Link</a>)";
    HtmlParser parser;
    int nLinks = 0;
    char* links = parser.Parse((char*)buf.c_str(), (int)buf.size(), nullptr, 0, &nLinks);
    for(int i = 0; i < nLinks; i++) {
        printf("Found link: %s\n", links);
        links += strlen(links) + 1;
    }

    if (argc != 2) {
        std::cout << "Expected 1 argument, received " << argc-1 << "." << std::endl;
    } else {
        std::string url = argv[1];
    }
    return 0;
}