#include "tests.hpp"

TEST(Constructor, set_default) {
  set<int> test;

  EXPECT_EQ(test.size(), 0);
  EXPECT_EQ(test.empty(), true);
}

TEST(Constructor, set_param_1) {
  set<int> test1{1, 2, 3};
  set<int> test2(test1);

  EXPECT_EQ(test2.size(), 3);
  EXPECT_EQ(test2.contains(2), true);
}

TEST(Constructor, set_param_2) {
  set<int> test1;
  set<int> test2(test1);

  EXPECT_EQ(test2.size(), 0);
  EXPECT_EQ(test2.empty(), true);
}

TEST(Method, set_copy) {
  set<int> test1{1, 2, 3};
  set<int> test2;

  test2 = test1;

  EXPECT_EQ(test2.size(), 3);
  EXPECT_EQ(test2.empty(), false);
}

TEST(Method, set_move) {
  set<int> test1{1, 2, 3};
  set<int> test2;

  test2 = std::move(test1);

  EXPECT_EQ(test1.empty(), true);
  EXPECT_EQ(test2.size(), 3);
  EXPECT_EQ(test2.empty(), false);
}

TEST(Method, set_clear_1) {
  set<int> test1{1, 2, 3};
  test1.clear();

  EXPECT_EQ(test1.size(), 0);
  EXPECT_EQ(test1.empty(), true);
}

TEST(Method, set_clear_2) {
  set<int> test1;
  test1.clear();

  EXPECT_EQ(test1.size(), 0);
  EXPECT_EQ(test1.empty(), true);
}

TEST(Method, set_insert) {
  set<int> test1;

  test1.insert(1);
  s21::pair<set<int>::iterator, bool> pair = test1.insert(2);
  test1.insert(3);

  EXPECT_EQ(test1.size(), 3);
  EXPECT_EQ(pair.second, true);
  EXPECT_EQ(*pair.first, 2);  // скобки?
}

TEST(Method, set_erase_1) {
  set<int> test1{1, 2, 3};
  test1.erase(2);

  EXPECT_EQ(test1.size(), 2);
  EXPECT_EQ(test1.contains(2), false);
}

TEST(Method, set_erase_2) {
  set<int> test1{1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15,
                 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};
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

TEST(Method, set_erase_ptr) {
  set<int> test1{1, 2, 3};
  test1.erase(test1.find(2));

  EXPECT_EQ(test1.size(), 2);
  EXPECT_EQ(test1.contains(2), false);
}

TEST(Method, set_swap) {
  set<int> test1{1, 2, 3};
  set<int> test2{4, 5, 6, 7, 8, 9};

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

TEST(Method, set_merge) {
  set<int> test1{1, 2, 3};
  set<int> test2{4, 5, 6, 7, 8, 9};

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

TEST(Method, set_find) {
  set<int> test1{1, 2, 3};
  set<int>::iterator it = test1.find(2);

  EXPECT_EQ(*it, 2);

  it = test1.find(10);

  EXPECT_EQ(it == test1.end(), true);
}

TEST(Method, set_begin) {
  set<int> test1{1, 2, 3};
  set<int> test2{3, 2, 1};
  set<int> test3{10, 15, 5, 6, 7, 8, 9, 11, 12, 13, 14};

  EXPECT_EQ(*test1.begin(), 1);
  EXPECT_EQ(*test1.begin(), 1);
  EXPECT_EQ(*test3.begin(), 5);
}

TEST(Method, set_end) {
  set<int> test1{1, 2, 3};
  set<int> test2{3, 2, 1};
  set<int> test3{10, 15, 5, 6, 7, 8, 9, 11, 12, 13, 14};

  set<int>::iterator result = (set<int>::iterator) nullptr;

  EXPECT_EQ(test1.end(), result);
  EXPECT_EQ(test1.end(), result);
  EXPECT_EQ(test3.end(), result);
}

TEST(Method, set_max_size) {
  set<int> test1{1, 2, 3};

  EXPECT_GT(test1.max_size(), 1000);
}