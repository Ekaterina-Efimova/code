#include "tests.hpp"

TEST(Constructor, multiset_default) {
  multiset<int> test;

  EXPECT_EQ(test.size(), 0);
  EXPECT_EQ(test.empty(), true);
}

TEST(Constructor, multiset_param_1) {
  multiset<int> test1{1, 2, 3};
  multiset<int> test2(test1);

  EXPECT_EQ(test2.size(), 3);
  EXPECT_EQ(test2.contains(2), true);
}

TEST(Constructor, multiset_param_2) {
  multiset<int> test1;
  multiset<int> test2(test1);

  EXPECT_EQ(test2.size(), 0);
  EXPECT_EQ(test2.empty(), true);
}

TEST(Method, multiset_clear_1) {
  multiset<int> test1{1, 2, 3};
  test1.clear();

  EXPECT_EQ(test1.size(), 0);
  EXPECT_EQ(test1.empty(), true);
}

TEST(Method, multiset_clear_2) {
  multiset<int> test1;
  test1.clear();

  EXPECT_EQ(test1.size(), 0);
  EXPECT_EQ(test1.empty(), true);
}

TEST(Method, multiset_insert) {
  multiset<int> test1;

  test1.insert(1);
  s21::pair<multiset<int>::iterator, bool> pair = test1.insert(2);
  test1.insert(3);

  EXPECT_EQ(test1.size(), 3);
  EXPECT_EQ(pair.second, true);
  EXPECT_EQ(*pair.first, 2);  // скобки?
}

TEST(Method, multiset_erase_1) {
  multiset<int> test1{1, 2, 3};
  test1.erase(2);

  EXPECT_EQ(test1.size(), 2);
  EXPECT_EQ(test1.contains(2), false);
}

TEST(Method, multiset_erase_2) {
  multiset<int> test1{1,  2,  3,  4,  5,  6,  7,  8,  9,  10,
                      11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
                      21, 22, 23, 24, 25, 26, 27, 28, 29, 30};
  test1.erase(11);
  test1.erase(6);
  test1.erase(12);
  test1.erase(22);
  test1.erase(1);
  test1.erase(26);
  test1.erase(30);
  test1.erase(19);
  test1.erase(9);
  test1.erase(18);
  test1.erase(4);
  test1.erase(2);
  test1.erase(15);
  test1.erase(23);
  test1.erase(27);
  test1.erase(24);
  test1.erase(7);
  test1.erase(14);
  test1.erase(21);
  test1.erase(8);
  test1.erase(29);
  test1.erase(5);
  test1.erase(28);
  test1.erase(10);
  test1.erase(13);
  test1.erase(25);
  test1.erase(3);
  test1.erase(17);
  test1.erase(16);
  test1.erase(20);

  EXPECT_EQ(test1.size(), 0);
  EXPECT_EQ(test1.empty(), true);
}

TEST(Method, multiset_swap) {
  multiset<int> test1{1, 2, 3};
  multiset<int> test2{4, 5, 6, 7, 8, 9};

  test1.swap(test2);

  EXPECT_EQ(test1.size(), 6);
  EXPECT_EQ(test2.size(), 3);

  EXPECT_EQ(test1.contains(4), true);
  EXPECT_EQ(test1.contains(5), true);
  EXPECT_EQ(test1.contains(6), true);
  EXPECT_EQ(test1.contains(7), true);
  EXPECT_EQ(test1.contains(8), true);
  EXPECT_EQ(test1.contains(9), true);

  EXPECT_EQ(test2.contains(1), true);
  EXPECT_EQ(test2.contains(2), true);
  EXPECT_EQ(test2.contains(3), true);
}

TEST(Method, multiset_merge) {
  multiset<int> test1{1, 2, 3};
  multiset<int> test2{4, 5, 6, 7, 8, 9};

  test1.merge(test2);

  EXPECT_EQ(test1.size(), 9);
  EXPECT_EQ(test2.size(), 6);

  EXPECT_EQ(test1.contains(4), true);
  EXPECT_EQ(test1.contains(5), true);
  EXPECT_EQ(test1.contains(6), true);
  EXPECT_EQ(test1.contains(7), true);
  EXPECT_EQ(test1.contains(8), true);
  EXPECT_EQ(test1.contains(9), true);
}

TEST(Method, multiset_find) {
  multiset<int> test1{1, 2, 3};
  multiset<int>::iterator it = test1.find(2);

  EXPECT_EQ(*it, 2);

  it = test1.find(10);

  EXPECT_EQ(it == test1.end(), true);
}

TEST(Method, multiset_begin) {
  multiset<int> test1{1, 2, 3};
  multiset<int> test2{3, 2, 1};
  multiset<int> test3{10, 15, 5, 6, 7, 8, 9, 11, 12, 13, 14};

  EXPECT_EQ(*test1.begin(), 1);
  EXPECT_EQ(*test1.begin(), 1);
  EXPECT_EQ(*test3.begin(), 5);
}

TEST(Method, multiset_end) {
  multiset<int> test1{1, 2, 3};
  multiset<int> test2{3, 2, 1};
  multiset<int> test3{10, 15, 5, 6, 7, 8, 9, 11, 12, 13, 14};

  multiset<int>::iterator result = (multiset<int>::iterator) nullptr;

  EXPECT_EQ(test1.end(), result);
  EXPECT_EQ(test1.end(), result);
  EXPECT_EQ(test3.end(), result);
}

TEST(Method, multiset_max_size) {
  multiset<int> test1{1, 2, 3};

  EXPECT_GT(test1.max_size(), 1000);
}

TEST(Method, multiset_count) {
  multiset<int> test1{1, 2, 3, 1, 2, 3, 2};

  EXPECT_EQ(test1.count(1), 2);
  EXPECT_EQ(test1.count(2), 3);
  EXPECT_EQ(test1.count(3), 2);
}

TEST(Method, multiset_equal_range) {
  multiset<int> test1{1, 2, 3, 1, 2, 3, 2};
  multiset<int>::iterator left = test1.begin();
  ++left;
  ++left;
  multiset<int>::iterator right = left;
  ++right;
  ++right;

  EXPECT_EQ(test1.count(2), 3);
  EXPECT_EQ(test1.equal_range(2).first, left);
  EXPECT_EQ(test1.equal_range(2).second, right);
}

TEST(Method, multiset_lower_bound) {
  multiset<int> test1{1, 2, 3, 1, 2, 3, 2};
  multiset<int>::iterator left = test1.begin();
  ++left;
  ++left;

  EXPECT_EQ(test1.lower_bound(2), left);
}

TEST(Method, multiset_upper_bound) {
  multiset<int> test1{1, 2, 3, 1, 2, 3, 2};
  multiset<int>::iterator left = test1.begin();
  ++left;
  ++left;
  ++left;
  ++left;
  ++left;

  EXPECT_EQ(test1.upper_bound(2), left);
}