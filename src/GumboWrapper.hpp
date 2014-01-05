#pragma once

#include <boost/iterator/iterator_facade.hpp>
#include <boost/variant.hpp>
#include <boost/optional.hpp>
#include <gumbo.h>

template<typename T, typename W>
class GumboVectorWrapper_iter : public boost::iterator_facade<
  GumboVectorWrapper_iter<T, W>,
  W,
  boost::random_access_traversal_tag,
  W> {
public:
  using Derived = GumboVectorWrapper_iter<T, W>;
  // REFACTOR make ctors private/friend?
  GumboVectorWrapper_iter() : m_node(0) {}
  explicit GumboVectorWrapper_iter(const GumboVector & vector, unsigned int index)
    : m_node(reinterpret_cast<T**>(vector.data) + index)
  {}
private:
  friend class boost::iterator_core_access;

  void increment() {
    m_node++;
  }

  void decrement() {
    m_node--;
  }

  ptrdiff_t distance_to(const Derived & other) const {
    return other.m_node - m_node;
  }

  void advance(ptrdiff_t n) {
    m_node += n;
  }

  bool equal(GumboVectorWrapper_iter<T, W> const& other) const {
    return this->m_node == other.m_node;
  }

  W dereference() const {
    return W(**m_node);
  }

  T** m_node;
};

template<typename T, typename W>
class GumboVectorWrapper {
public:

  // typedef GumboVectorWrapper_iter<T, W> iterator;
  typedef GumboVectorWrapper_iter<T, const W> const_iterator;

  GumboVectorWrapper(const GumboVector & vector)
    : m_vector(vector)
  {}
  // iterator begin() {
  //   return iterator(m_vector, 0);
  // }
  const_iterator begin() const {
    return const_iterator(m_vector, 0);
  }
  // iterator end() {
  //   return iterator(m_vector, m_vector.length);
  // }
  const_iterator end() const {
    return const_iterator(m_vector, m_vector.length);
  }
private:
  const GumboVector & m_vector;
};

class GumboDocumentWrapper {
public:
  GumboDocumentWrapper(const GumboDocument & document);
private:
  const GumboDocument & m_document;
};

class GumboTextWrapper {
public:
  GumboTextWrapper(const GumboText & text);
private:
  const GumboText & m_text;
  friend std::ostream& operator<<(std::ostream& os, const GumboTextWrapper & text);
};

std::ostream& operator<<(std::ostream& os, const GumboTextWrapper & text);

class GumboNodeWrapper;
class GumboElementWrapper {
public:
  GumboElementWrapper(const GumboElement & element);
  GumboVectorWrapper<GumboNode, GumboNodeWrapper> children() const;
  GumboTag tag() const;
private:
  const GumboElement & m_element;
};

class GumboNodeWrapper {
public:
  using VariantType = boost::variant<GumboDocumentWrapper, GumboElementWrapper, GumboTextWrapper>;
  GumboNodeWrapper(const GumboNode & node);
  boost::optional<GumboNodeWrapper> parent() const;
  size_t indexWithinParent() const;
  GumboNodeType type() const;
  VariantType v() const;

private:
  const GumboNode& m_node;
};
