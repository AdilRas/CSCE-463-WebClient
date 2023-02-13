//
// Created by Adil Rasiyani on 2/8/23.
//

#ifndef DRAGONOV_URLUTIL_H
#define DRAGONOV_URLUTIL_H


#include <string>
#include <iostream>

struct UrlParts {
    std::string scheme;
    std::string host;
    std::string port;
    std::string path;
    std::string query;
    std::string fragment;

    UrlParts() = default;

    UrlParts(
            std::string _scheme,
            std::string _host,
            std::string _port,
            std::string _path,
            std::string _query,
            std::string _fragment
            ) :
            scheme(std::move(_scheme)),
            host(std::move(_host)),
            port(std::move(_port)),
            path(std::move(_path)),
            query(std::move(_query)),
            fragment(std::move(_fragment)
    ) {}

    bool operator==(UrlParts& rhs) const {
        return (
                this->scheme == rhs.scheme &&
                this->host == rhs.host &&
                this->port == rhs.port &&
                this->path == rhs.path &&
                this->query == rhs.query &&
                this->fragment == rhs.fragment
            );
    }

    friend std::ostream& operator<<(std::ostream& oss, const UrlParts& rhs) {
        oss
            << "{"
            << "scheme={" << rhs.scheme
            << "}, host={" << rhs.host
            << "}, port={" << rhs.port
            << "}, path={" << rhs.path
            << "}, query={" << rhs.query
            << "}, fragment={" << rhs.fragment << "}"
            << "}";
        return oss;
    }
};

class UrlUtil {
public:

    // Returns the scheme of the URL if present, and empty string if not.
    static std::string getScheme(std::string& url);
    // Returns a new string containing the host portion of the URL, assuming a valid scheme is present.
    static std::string getHost(std::string& url, size_t known_scheme_length=0);
    // Returns the port, if it exists. Empty string if not.
    static std::string getPort(std::string& url, size_t known_colon_index=0);
    static std::string getPath(std::string& url, size_t known_path_divider_index=0);
    static std::string getQuery(std::string& url);
    static std::string getFragment(std::string& url);
    // assumes valid baseUrl and valid relativeUrl
    static std::string buildAbsoluteUrl(char* baseUrl, int baseLen, char* relativeUrl, int relPathLen);

    static UrlParts parseUrl(std::string&);
    // checks for valid string format
    static bool isHttpUrl(std::string &url);
};


#endif //DRAGONOV_URLUTIL_H
