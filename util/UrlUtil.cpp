//
// Created by Adil Rasiyani on 2/8/23.
//
#include "UrlUtil.h"
#include <string>

std::string UrlUtil::buildAbsoluteUrl(char* baseUrl, int urlLen, char* relPath, int relPathLen) {
    std::string base(baseUrl);
    if (not ((base.back() == '/') ^ (relPath[0] == '/'))) {
        if (base.back() == '/') base.pop_back();
        else base.push_back('/');
    }
    base += relPath;
    return base;
}

std::string UrlUtil::getScheme(std::string& url) {
    if (url.find("://") == std::string::npos) {
        return "";
    }
    std::string scheme;
    for (char i : url) {
        if (i == ':') {
            break;
        }
        scheme.push_back(i);
    }
    return scheme;
}

std::string UrlUtil::getHost(std::string& url, size_t known_scheme_length) {
    if (known_scheme_length == 0) {
        known_scheme_length = UrlUtil::getScheme(url).size();
    }
    // no scheme found. will not search for a host.
    if (known_scheme_length == 0) {
        return "";
    }

    std::string host;

    for (size_t i = known_scheme_length + std::string("://").size(); i < url.size(); i++) {
        if (url[i] == ':' or url[i] == '/' or url[i] == '?') {
            break;
        }
        host.push_back(url[i]);
    }

    return host;
}

std::string UrlUtil::getPort(std::string& url, size_t known_colon_index) {
    std::string port;

    if (known_colon_index == 0) {
        // find the colon
        std::string scheme = UrlUtil::getScheme(url);
        std::string host = UrlUtil::getHost(url, scheme.size());
        known_colon_index = scheme.size() + std::string("://").size() + host.size();
        if (known_colon_index >= url.size() or url[known_colon_index] != ':') {
            return "";
        }
    }

    for (size_t i = known_colon_index + 1; i < url.size(); i++) {
        if (url[i] == '?' or url[i] == '/') {
            break;
        }
        port.push_back(url[i]);
    }

    return port;
}

std::string UrlUtil::getPath(std::string& url, size_t known_path_divider_index) {
    if (known_path_divider_index == 0) {
        // TODO: find the divider (scheme, then host, optional port, divider)
    }

    std::string path;

    for (size_t i = known_path_divider_index + 1; i < url.size(); i++) {
        if (url[i] == '#' or url[i] == '?') {
            break;
        }
        path.push_back(url[i]);
    }

    return path;
}

std::string UrlUtil::getQuery(std::string& url) {
    size_t query_divider = 0;
    for(size_t i = 0; i < url.size(); i++) {
        if (url[i] == '?') {
            query_divider = i;
            break;
        }
    }
    std::string query;
    if (url[query_divider] == '?') {
        for (size_t i = query_divider + 1; i < url.size(); i++) {
            if (url[i] == '#') {
                break;
            }
            query.push_back(url[i]);
        }
    }
    return query;
}

std::string UrlUtil::getFragment(std::string& url) {
    size_t fragment_divider = 0;
    for (size_t i = 0; i < url.size(); i++) {
        if (url[i] == '#') {
            fragment_divider = i;
            break;
        }
    }

    std::string fragment;
    if (url[fragment_divider] == '#') {
        for (size_t i = fragment_divider + 1; i < url.size(); i++) {
            fragment.push_back(url[i]);
        }
    }
    return fragment;
}

bool UrlUtil::isHttpUrl(std::string& url) {
    std::string scheme = UrlUtil::getScheme(url);
    if (scheme != "http") {
        return false;
    }
    return true;
}

UrlParts UrlUtil::parseUrl(std::string& url) {
    UrlParts parsedUrl;

    // --- SCHEME --- //
    parsedUrl.scheme = UrlUtil::getScheme(url);

    // --- HOST --- //
    parsedUrl.host = UrlUtil::getHost(url, parsedUrl.scheme.size());

    // --- PORT --- //
    size_t port_divider = parsedUrl.scheme.size() + std::string("://").size() + parsedUrl.host.size();
    if (port_divider < url.size() and url[port_divider] == ':') {
        parsedUrl.port = UrlUtil::getPort(url, port_divider);
    }

    // --- PATH --- //
    size_t path_divider = port_divider + (!parsedUrl.port.empty() ? parsedUrl.port.size() + 1 : 0);
    if (path_divider < url.size() and url[path_divider] == '/') {
        parsedUrl.path = UrlUtil::getPath(url, path_divider);
    }

    // --- QUERY --- //
    parsedUrl.query = UrlUtil::getQuery(url);

    // --- FRAGMENT --- //
    parsedUrl.fragment = UrlUtil::getFragment(url);

    return parsedUrl;
}