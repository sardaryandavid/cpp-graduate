#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "cache.h"

TEST(lfu_cache_test, test1) {
  std::vector<int> data {1, 1, 1, 1, 1};
  EXPECT_EQ(caches::lfu::count_hits(1, 5, data), 4);
}

TEST(lfu_cache_test, test2) {
  std::vector<int> data {1, 2, 3, 2, 5, 3, 1, 3, 4, 5, 5, 4};
  EXPECT_EQ(caches::lfu::count_hits(2, 12, data), 3);
}

TEST(lfu_cache_test, test3) {
  std::vector<int> data {12, 12, 5, 12 , 5, 5, 12, 5, 12, 4, 5, 12};
  EXPECT_EQ(caches::lfu::count_hits(3, 12, data), 9);
}

TEST(lfu_cache_test, test4) {
  std::vector<int> data {2, 3, 2, 2, 2, 3, 3, 2, 3, 2, 3, 2};
  EXPECT_EQ(caches::lfu::count_hits(1, 12, data), 3);
}

TEST(lfu_cache_test, test5) {
  std::vector<int> data {13, 52, 47, 40, 51, 47, 30, 59, 69, 100, 44, 42, 74, 74, 33, 30, 43, 74, 15, 74};
  EXPECT_EQ(caches::lfu::count_hits(3, 20, data), 3);
}

TEST(lfu_cache_test, test6) {
  std::vector<int> data {1, 2, 3, 4, 1, 2, 5, 1, 2, 4, 3, 4};
  EXPECT_EQ(caches::lfu::count_hits(4, 12, data), 6);
}

TEST(belady_cache_test, test1) {
  std::vector<int> data {1, 1, 1, 1, 1};
  EXPECT_EQ(caches::belady::count_hits(1, 5, data), 4);
}

TEST(belady_cache_test, test2) {
  std::vector<int> data {1, 2, 3, 2, 5, 3, 1, 3, 4, 5, 5, 4};
  EXPECT_EQ(caches::belady::count_hits(2, 12, data), 6);
}

TEST(belady_cache_test, test3) {
  std::vector<int> data {12, 12, 5, 12, 5, 5, 12, 5, 12, 4, 5, 12};
  EXPECT_EQ(caches::belady::count_hits(3, 12, data), 9);
}

TEST(belady_cache_test, test4) {
  std::vector<int> data {2, 3, 2, 2, 2, 3, 3, 2, 3, 2, 3, 2};
  EXPECT_EQ(caches::belady::count_hits(1, 12, data), 6);
}

TEST(belady_cache_test, test5) {
  std::vector<int> data {1, 2, 3, 4, 1, 2, 5, 1, 2, 4, 3, 4};
  EXPECT_EQ(caches::belady::count_hits(4, 12, data), 7);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::InitGoogleMock(&argc, argv);
  
  return RUN_ALL_TESTS();
}