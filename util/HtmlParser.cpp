//
// Created by Adil Rasiyani on 2/9/23.
//

#include "HtmlParser.h"
#include "UrlUtil.h"
#include <gumbo.h>
#include <string>

// helper function from https://github.com/google/gumbo-parser/blob/master/examples/find_links.cc
void search_for_links(GumboNode* node, std::string& links, int& nLinks, std::string& baseUrl) {
    if (node == nullptr or node->type != GUMBO_NODE_ELEMENT) {
        return;
    }

    GumboAttribute* href;
    if (node->v.element.tag == GUMBO_TAG_A and
            (href = gumbo_get_attribute(&node->v.element.attributes, "href"))) {
        std::string currLink = href->value;
        if (UrlUtil::getScheme(currLink).empty()) {
            currLink = UrlUtil::buildAbsoluteUrl((char*)baseUrl.c_str(), baseUrl.size(), (char*)currLink.c_str(), currLink.size());
        }
        links += currLink;
        links.push_back('\0');
        nLinks++;
    }

    const GumboVector* children = &node->v.element.children;
    for (int i = 0; i < children->length; i++) {
        search_for_links(static_cast<GumboNode*>(children->data[i]), links, nLinks, baseUrl);
    }
}

char* HtmlParser::Parse(char *htmlCode, int codeSize, char *baseUrl, int urlLen, int *nLinks) {
    GumboInternalOutput* output = gumbo_parse(htmlCode);
    std::string baseUrlStr;
    if (baseUrl != nullptr) {
        baseUrlStr = std::string(baseUrl);
    }
    std::string links;
    int count = 0;
    search_for_links(output->root, links, count, baseUrlStr);
    *nLinks = count;

    // clear buffer if it exists
    delete linkBuffer;

    linkBuffer = new char[links.size()];
    for(int i = 0; i < links.size(); i++) {
        linkBuffer[i] = links[i];
    }
    return linkBuffer;
}

HtmlParser::HtmlParser() {
    linkBuffer = nullptr;
}


HtmlParser::~HtmlParser() {
    delete linkBuffer;
}
