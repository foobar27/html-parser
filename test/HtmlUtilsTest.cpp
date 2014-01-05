#define BOOST_TEST_MODULE "HtmlParser_test"
#include "TestFramework.hpp"
#include "HtmlUtils.hpp"

using namespace std;

BOOST_AUTO_TEST_CASE(getText_test) {
  string input("<html><head><title>The title</title></head><body><p>Paragraph 1<p>Paragraph 2<ul><li>1<li>2<li>3</ul></body></html>");
  string expectedText("Paragraph 1 Paragraph 2 1 2 3");
  HtmlDocument doc(input);
  BOOST_CHECK_EQUAL(getText(doc), expectedText);
}
