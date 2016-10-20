#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <string>
#include <unordered_set>

template< typename T, 
          typename... Args, 
          template <class...> class Container>
void pp( T &os, Container<Args...> &ts) {
  std::string sep = "";
  os << "[";
  for( auto &t : ts) {
    os << sep;
    os << t;
    sep = ", ";
  }
  os << "]";
  os << std::endl;
}

template< typename T, typename... Args>
  T& operator<<( T &os, std::unordered_set<Args...> &ts) {
  pp(os, ts);
  return os;
}

template< typename T, typename... Args>
  T& operator<<( T &os, std::vector<Args...> &ts) {
  pp(os, ts);
  return os;
}
