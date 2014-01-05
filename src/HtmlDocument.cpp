#include <gumbo.h>

#include "HtmlDocument.hpp"
#include "GumboWrapper.hpp"

using namespace std;

HtmlDocument::Options::Options()
  : tabStop(kGumboDefaultOptions.tab_stop)
  , stopOnFirstParseError(kGumboDefaultOptions.stop_on_first_error)
  , maxParseErrors(kGumboDefaultOptions.max_errors)
{}

HtmlDocument::Options::operator GumboOptions() const {
  GumboOptions result = kGumboDefaultOptions;
  result.tab_stop = tabStop;
  result.stop_on_first_error = stopOnFirstParseError;
  result.max_errors = maxParseErrors;
  return result;
}

HtmlDocument::HtmlDocument(const string & input)
  : HtmlDocument({}, input)
{}

HtmlDocument::HtmlDocument(const HtmlDocument::Options & options, const string & input)
    : m_options(options)
    , m_gumboOptions(options.operator GumboOptions())
    , m_originalInput(input)
    , m_tree(gumbo_parse_with_options(&m_gumboOptions, m_originalInput.c_str(), m_originalInput.length()))
{}

HtmlDocument::~HtmlDocument() {
  gumbo_destroy_output(&m_gumboOptions, m_tree);
}

GumboNodeWrapper HtmlDocument::root() const {
  return { *m_tree->root };
}
