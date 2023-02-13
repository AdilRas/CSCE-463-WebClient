//
// Created by Adil Rasiyani on 2/9/23.
//

#ifndef DRAGONOV_HTMLPARSER_H
#define DRAGONOV_HTMLPARSER_H

#define MAX_HOST_LEN		256
#define MAX_URL_LEN			2048
#define MAX_REQUEST_LEN		2048

class HtmlParser {
public:
    HtmlParser();
    ~HtmlParser();
    // Returns nLinks many null-separated cstrings.
    char* Parse(char* htmlCode, int codeSize, char* baseUrl, int urlLen, int *nLinks);
private:
    char* linkBuffer;
};


#endif //DRAGONOV_HTMLPARSER_H
