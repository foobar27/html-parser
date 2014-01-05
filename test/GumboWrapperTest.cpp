#define BOOST_TEST_MODULE "GumboWrapper_test"
#include "TestFramework.hpp"
#include "GumboWrapper.hpp"

#include <cstdlib>
#include <utility>
#include <iostream>

using namespace std;

class IntWrapper {
public:
  IntWrapper(int value) : m_value(value) {}
  operator int() const{
    return m_value;
  }
private:
  int m_value;
};

ostream& operator<<(ostream& os, const IntWrapper & iw) {
  os << iw.operator int();
  return os;
}

class IntVector {
public:
  IntVector(initializer_list<int> data) {
    size_t sz = sizeof(void*) * data.size();
    m_vector.data = (void**)malloc(sz);
    m_vector.length = data.size();
    m_vector.capacity = data.size();
    auto p = reinterpret_cast<int**>(m_vector.data);
    for (auto it = data.begin(); it != data.end(); ++it, ++p) {
      *p = new int {*it};
    }
  }

  ~IntVector() {
    auto p = reinterpret_cast<int**>(m_vector.data);
    for (int i=0; i<m_vector.capacity; ++i, ++p)
      delete *p;
    free(m_vector.data);
  }

  GumboVector& vector() {
    return m_vector;
  }

  GumboVectorWrapper<int, IntWrapper> wrapper() {
    return {m_vector};
  }
  GumboVector m_vector;
};

BOOST_AUTO_TEST_CASE(GumboVectorWrapper_test) {
  IntVector v {1, 2, 3};
  auto wrapper = v.wrapper();
  auto begin = wrapper.begin();
  auto end = wrapper.end();
  BOOST_CHECK(begin == begin);
  BOOST_CHECK(end == end);

  auto it = begin;
  BOOST_CHECK_EQUAL(*it, 1);
  ++it;
  BOOST_CHECK(it != begin);
  BOOST_CHECK(it != end);
  BOOST_CHECK_EQUAL(*it, 2);
  ++it;
  BOOST_CHECK(it != begin);
  BOOST_CHECK(it != end);
  BOOST_CHECK_EQUAL(*it, 3);
  ++it;
  BOOST_CHECK(it != begin);
  BOOST_CHECK(it == end);

  // test distance_to
  BOOST_CHECK_EQUAL(3, end-begin);

  // try out advance
  it -= 2;
  BOOST_CHECK_EQUAL(*it, 2);
}
