//
// Created by Adil Rasiyani on 2/13/23.
//

#include "../util/HtmlParser.h"
#include <gtest/gtest.h>

std::string TEST_BASE_URL = "http://www.tamu.edu";
std::string TEST_REL_URL = "test-rel-url";
std::string TEST_FULL_URL = TEST_BASE_URL + "/" + TEST_REL_URL;
std::string TEST_HTML_RELATIVE_LINK = R"(<a href="/)" + TEST_REL_URL + R"(">Link</a>)";

TEST(ParserTests, RelativeUrl) {
    HtmlParser parser;
    int nLinks = 0;
    char* result = parser.Parse(
            (char*)TEST_HTML_RELATIVE_LINK.c_str(),
            (int)TEST_HTML_RELATIVE_LINK.size(),
            (char*)TEST_BASE_URL.c_str(),
            (int)TEST_BASE_URL.size(),
            &nLinks
            );
    std::string resultStr(result);
    ASSERT_EQ(resultStr, TEST_FULL_URL);
}