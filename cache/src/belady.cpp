#include <cassert>
#include <iostream>
#include <vector>

#include "cache.h"

int main() {
  int belady_hits = 0;
  int n;
  size_t m;

  std::cin >> m >> n;
  assert(std::cin.good());
  caches::belady::cache_t<int> belady{m};
  std::vector<int> data;

  for (int i = 0; i < n; ++i) {
    int q;
    std::cin >> q;
    assert(std::cin.good());
    data.push_back(q);
  }

  belady_hits = caches::belady::count_hits(m, n, data);

  std::cout << belady_hits << std::endl;
}