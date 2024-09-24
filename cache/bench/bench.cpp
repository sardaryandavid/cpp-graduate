#include <cassert>
#include <iostream>
#include <vector>

#include "cache.h"

int main() {
  int lfu_hits = 0, belady_hits = 0;
  int n;
  size_t m;

  std::cin >> m >> n;
  assert(std::cin.good());
  caches::belady::cache_t<int> belady{m};
  caches::lfu::cache_t<int> lfu{m};
  std::vector<int> data;

  for (int i = 0; i < n; ++i) {
    int q;
    std::cin >> q;
    assert(std::cin.good());
    data.push_back(q);
  }

  lfu_hits = caches::lfu::count_hits(m, n, data);
  belady_hits = caches::belady::count_hits(m, n, data);

  std::cout << static_cast<double>(lfu_hits) / belady_hits << std::endl;
}