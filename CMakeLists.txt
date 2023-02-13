cmake_minimum_required(VERSION 3.23)
project(Dragonov)

# ---- COMPILER STUFF ---- #
set(CMAKE_CXX_STANDARD 20)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

# ---- GTEST FETCH ---- #
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

# ---- GUMBO PARSER ---- #
file(GLOB_RECURSE source-gumbo-parser "lib/gumbo-parser/src/*.c")
add_library(gumbo-parser ${source-gumbo-parser})

file(GLOB_RECURSE source-gumbo-query "lib/gumbo-query/src/*.cpp")
add_library(gumbo-query ${source-gumbo-query})
target_include_directories(gumbo-query PUBLIC "lib/gumbo-parser/src")

include_directories("lib")

# ---- FILES FOR MAIN EXECUTABLE ---- #
add_executable(Dragonov main.cpp util/UrlUtil.cpp util/UrlUtil.h bits/stdc++.h util/Socket.cpp util/Socket.h util/HtmlParser.cpp util/HtmlParser.h)

target_link_libraries(Dragonov PUBLIC
        ${CURL_LIBRARIES}
        gumbo-query
        gumbo-parser
        )

# ---- TESTING EXECUTABLE ---- #
enable_testing()

add_executable(
        test_suite
        test/util/UrlUtil.cpp
        util/UrlUtil.cpp
        test/util/HtmlParser.cpp
        util/HtmlParser.cpp
        util/Socket.cpp
)
target_link_libraries(
        test_suite PUBLIC
        GTest::gtest_main
        ${CURL_LIBRARIES}
        gumbo-query
        gumbo-parser
)

include(GoogleTest)
gtest_discover_tests(test_suite)
