#include "HtmlUtils.hpp"

#include <stack>
#include <sstream>
#include <boost/range/adaptor/reversed.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/assign/list_inserter.hpp>

using namespace std;

string getText(const HtmlDocument & doc) {
  stringstream ss;
  stack<GumboNodeWrapper> stack;
  stack.push(doc.root());
  bool first = true;
  while (!stack.empty()) {
    auto node = stack.top();
    stack.pop();
    if (node.type() == GUMBO_NODE_TEXT) {
      if (first)
        first = false;
      else
        ss << " ";
      ss << boost::get<const GumboTextWrapper>(node.v());
    } else if (node.type() == GUMBO_NODE_ELEMENT) {
      auto element = boost::get<GumboElementWrapper>(node.v());
      if (element.tag() != GUMBO_TAG_SCRIPT &&
          element.tag() != GUMBO_TAG_STYLE &&
          element.tag() != GUMBO_TAG_HEAD) {
        for (const auto & child : element.children() | boost::adaptors::reversed)
          stack.push(child);
      }
    }
  }
  return ss.str();
}
