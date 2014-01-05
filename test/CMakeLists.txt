find_package(Boost COMPONENTS system program_options unit_test_framework serialization REQUIRED)

include_directories("${CMAKE_SOURCE_DIR}/src")

add_executable(GumboWrapperTest GumboWrapperTest.cpp)
target_link_libraries(GumboWrapperTest ${GUMBO_LIBRARIES} ${Boost_LIBRARIES} htmlparser)
add_test(GumboWrapperTest GumboWrapperTest)

add_executable(HtmlUtilsTest HtmlUtilsTest.cpp)
target_link_libraries(HtmlUtilsTest ${GUMBO_LIBRARIES} ${Boost_LIBRARIES} htmlparser)
add_test(HtmlUtilsTest HtmlUtilsTest)
