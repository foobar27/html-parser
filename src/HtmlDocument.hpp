#pragma once

#include <string>
#include "GumboWrapper.hpp"
#include <gumbo.h>

class HtmlDocument {
public:
  struct Options {
    int tabStop;
    bool stopOnFirstParseError;
    int maxParseErrors;

    Options();

    operator GumboOptions() const;
  };

private:
  const Options m_options;
  const GumboOptions m_gumboOptions;
  const std::string m_originalInput;
  GumboOutput *m_tree;

public:
  HtmlDocument(const std::string & input);
  HtmlDocument(const Options & options, const std::string & input);
  ~HtmlDocument();

  GumboNodeWrapper root() const;
};
