#include <algorithm>
#include <iostream>
#include <vector>

#include "triangle.h"

int main() {
  size_t N;
  std::cin >> N;

  std::vector<std::pair<geometry::triangle_t, bool>> tarr;

  for (size_t i = 0; i < N; ++i)
    tarr.push_back(std::make_pair(geometry::input_triangle(), false));
  
  std::vector<int> ans; 
  for (size_t i = 0; i < N; ++i) {
    if (tarr[i].second) {
      continue;
    }
    
    for (size_t j = 0; j < N; ++j) {
      if (i == j)
        continue;

      if (tarr[i].first.is_intersect_triangle_3d(tarr[j].first)) {
        tarr[i].second = true;
        tarr[j].second = true;
      }
    }
  }

  for (size_t i = 0; i < N; ++i)
    if (tarr[i].second)
      ans.push_back(i + 1);

  std::sort(ans.begin(), ans.end());

  for (auto elem : ans)
    std::cout << elem << std::endl;
}