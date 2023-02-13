//
// Created by Adil Rasiyani on 2/12/23.
//
#include <gtest/gtest.h>
#include "../util/UrlUtil.h"

const std::map<std::string, UrlParts> TEST_URLS {
        {"http://tamu.edu", UrlParts("http", "tamu.edu", "", "", "", "")},
        {"http://www.tamu.edu:80", UrlParts("http", "www.tamu.edu", "80", "", "", "")},
        {"http://128.194.135.72:80/courses/index.asp#location", UrlParts("http", "128.194.135.72", "80", "courses/index.asp", "", "location")},
        {"http://165.91.22.70/", UrlParts("http", "165.91.22.70", "", "", "", "")},
        {"http://s2.irl.cs.tamu.edu/IRL7", UrlParts("http", "s2.irl.cs.tamu.edu", "", "IRL7", "", "")},
        {"http://facebook.com:443?addrbook.php", UrlParts("http", "facebook.com", "443", "", "addrbook.php", "")},
        {"http://relay.tamu.edu:465/index.html", UrlParts("http", "relay.tamu.edu", "465", "index.html", "", "")},
        {"http://ftp.gnu.org:21/", UrlParts("http", "ftp.gnu.org", "21", "", "", "")},
        {"http://s22.irl.cs.tamu.edu:990/view?test=1", UrlParts("http", "s22.irl.cs.tamu.edu", "990", "view", "test=1", "")},
        {"http://128.194.135.25?viewcart.php/", UrlParts("http", "128.194.135.25", "", "", "viewcart.php/", "")}
};

const std::string TEST_BASE_URL = "https://www.test.com:80";
const std::string TEST_REL_PATH = "test/rel/path";
std::string EXPECTED_ABSOLUTE_PATH = TEST_BASE_URL + "/" + TEST_REL_PATH;

TEST(UrlParsing, ParseTestUrls) {
    for(auto [URL, EXPECTED] : TEST_URLS) {
        const UrlParts result = UrlUtil::parseUrl(const_cast<std::string&>(URL));
        EXPECT_TRUE(result == EXPECTED);
        if (HasFailure() and result != EXPECTED) {
            std::cout << "Failed to parse " << URL << ". " << "Expected: " << EXPECTED << "; Got: " << result << std::endl;
            break;
        }
    }
}

TEST(AbsolutePathBuilder, PathWithTrailingSlash) {
    std::string pathWithSlash = TEST_BASE_URL + "/";
    std::string response =
            UrlUtil::buildAbsoluteUrl(
                    (char*)pathWithSlash.c_str(),
                    (int)pathWithSlash.size(),
                    (char*)TEST_REL_PATH.c_str(),
                    (int)TEST_REL_PATH.size()
                    );

    std::string expected = TEST_BASE_URL + "/" + TEST_REL_PATH;
    ASSERT_EQ(response, EXPECTED_ABSOLUTE_PATH);
}

TEST(AbsolutePathBuilder, RelativePathWithLeadingSlash) {
    std::string pathWithSlash = "/" + TEST_REL_PATH;
    std::string response =
            UrlUtil::buildAbsoluteUrl(
                    (char*)TEST_BASE_URL.c_str(),
                    (int)TEST_BASE_URL.size(),
                    (char*)pathWithSlash.c_str(),
                    (int)pathWithSlash.size()
            );

    ASSERT_EQ(response, EXPECTED_ABSOLUTE_PATH);
}

TEST(AbsolutePathBuilder, TrailingAndLeadingSlashes) {
    std::string relWithSlash = "/" + TEST_REL_PATH;
    std::string baseWithSlash = TEST_BASE_URL + "/";
    std::string response =
            UrlUtil::buildAbsoluteUrl(
                    (char*)baseWithSlash.c_str(),
                    (int)baseWithSlash.size(),
                    (char*)relWithSlash.c_str(),
                    (int)relWithSlash.size()
            );

    ASSERT_EQ(response, EXPECTED_ABSOLUTE_PATH);
}

TEST(AbsolutePathBuilder, NoSlashes) {
    std::string response =
            UrlUtil::buildAbsoluteUrl(
                    (char*)TEST_BASE_URL.c_str(),
                    (int)TEST_BASE_URL.size(),
                    (char*)TEST_REL_PATH.c_str(),
                    (int)TEST_REL_PATH.size()
            );

    ASSERT_EQ(response, EXPECTED_ABSOLUTE_PATH);
}