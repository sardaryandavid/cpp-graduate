#include <cassert>
#include <iostream>

#include "cache.h"

int main() {
  int n;
  size_t m;

  std::cin >> m >> n;
  assert(std::cin.good());
  caches::lfu::cache_t<int> c{m};
  std::vector<int> data;

  for (int i = 0; i < n; ++i) {
    int q;
    std::cin >> q;
    assert(std::cin.good());
    data.push_back(q);
  }
  
  std::cout << caches::lfu::count_hits(m, n, data) << std::endl;
}