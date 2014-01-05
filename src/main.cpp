#include <gumbo.h>
#include "HtmlUtils.hpp"

#include <iostream>
#include <iterator>
#include <sstream>

using namespace std;

int main(int argc, char** argv)
{
  std::stringstream buffer;
  buffer << cin.rdbuf();
  std::string input(buffer.str());
  HtmlDocument doc(input);
  cout << getText(doc) << endl;;
}
