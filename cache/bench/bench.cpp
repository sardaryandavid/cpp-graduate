#include <cassert>
#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>

#include "cache.h"

namespace {
  size_t PRECISION = 3;
  size_t MCS_IN_MS = 1000;
}

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

  auto start_lfu = std::chrono::high_resolution_clock::now();
  lfu_hits = caches::lfu::count_hits(m, n, data);
  auto stop_lfu = std::chrono::high_resolution_clock::now();

  auto start_belady = std::chrono::high_resolution_clock::now();
  belady_hits = caches::belady::count_hits(m, n, data);
  auto stop_belady = std::chrono::high_resolution_clock::now();

  auto duration_lfu = std::chrono::duration_cast<std::chrono::microseconds>(stop_lfu - start_lfu);
  auto duration_belady = std::chrono::duration_cast<std::chrono::microseconds>(stop_belady - start_belady);

  std::cout << "lfu_hits / belady_hits: " << static_cast<double>(lfu_hits) / belady_hits << std::endl;
  std::cout << std::setprecision(PRECISION) << "lfu_time: " << static_cast<double>(duration_lfu.count()) / MCS_IN_MS << " ms\n";
  std::cout << "belady_time: " << static_cast<double>(duration_belady.count()) / MCS_IN_MS << " ms\n";
}