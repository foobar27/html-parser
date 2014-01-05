#include "GumboWrapper.hpp"

#include <cassert>

using namespace std;
using namespace boost;

using VariantType = boost::variant<GumboDocumentWrapper, GumboElementWrapper, GumboTextWrapper>;

GumboDocumentWrapper::GumboDocumentWrapper(const GumboDocument & document)
  : m_document(document)
{}

GumboTextWrapper::GumboTextWrapper(const GumboText & text)
  : m_text(text)
{}

ostream& operator<<(ostream& os, const GumboTextWrapper & text) {
  os << text.m_text.text;
  return os;
}

GumboElementWrapper::GumboElementWrapper(const GumboElement & element)
  : m_element(element)
{}

GumboVectorWrapper<GumboNode, GumboNodeWrapper> GumboElementWrapper::children() const {
  return GumboVectorWrapper<GumboNode, GumboNodeWrapper>(m_element.children);
}

GumboTag GumboElementWrapper::tag() const {
  return m_element.tag;
}

GumboNodeWrapper::GumboNodeWrapper(const GumboNode & node)
  : m_node(node)
{}

optional<GumboNodeWrapper> GumboNodeWrapper::parent() const {
  if (m_node.parent)
    return { GumboNodeWrapper(*m_node.parent) };
  return {};
}

size_t GumboNodeWrapper::indexWithinParent() const {
  return m_node.index_within_parent;
}

GumboNodeType GumboNodeWrapper::type() const {
  return m_node.type;
}

VariantType GumboNodeWrapper::v() const {
  switch (m_node.type) {
  case GUMBO_NODE_DOCUMENT:
    return VariantType(GumboDocumentWrapper(m_node.v.document));
  case GUMBO_NODE_ELEMENT:
    return VariantType(GumboElementWrapper(m_node.v.element));
  case GUMBO_NODE_TEXT:
  case GUMBO_NODE_CDATA:
  case GUMBO_NODE_COMMENT:
  case GUMBO_NODE_WHITESPACE:
    return VariantType(GumboTextWrapper(m_node.v.text));
  }
  assert(0);
}
