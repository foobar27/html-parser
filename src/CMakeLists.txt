cmake_minimum_required(VERSION 2.8.11.2)
find_package(Gumbo REQUIRED)
find_package(Boost COMPONENTS system serialization REQUIRED)

add_library(htmlparser STATIC HtmlDocument.cpp GumboWrapper.cpp HtmlUtils.cpp)

add_executable(html2text main.cpp)
target_link_libraries(html2text ${GUMBO_LIBRARIES} ${Boost_LIBRARIES} htmlparser)
