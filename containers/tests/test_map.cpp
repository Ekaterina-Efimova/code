#include "tests.hpp"

TEST(MapConstructor, default) {
  map<int, std::string> test;

  EXPECT_EQ(test.size(), 0);
  EXPECT_TRUE(test.empty());
}

TEST(MapConstructor, copy1) {
  map<int, std::string> test1{{1, "A"}, {2, "B"}, {3, "C"}};
  map<int, std::string> test2(test1);

  EXPECT_EQ(test2.size(), 3);
  EXPECT_TRUE(test2.contains(2));
}

TEST(MapConstructor, copy2) {
  map<int, std::string> test1;
  map<int, std::string> test2(test1);

  EXPECT_EQ(test2.size(), 0);
  EXPECT_TRUE(test2.empty());
}

TEST(MapMethod, copy_operator) {
  map<int, std::string> test1;
  map<int, std::string> test2{{1, "A"}, {2, "B"}, {3, "C"}};

  test1 = test2;

  EXPECT_EQ(test1.size(), 3);
  EXPECT_FALSE(test1.empty());
}

TEST(MapMethod, operator_move) {
  map<int, std::string> test1;
  map<int, std::string> test2{{1, "A"}, {2, "B"}, {3, "C"}};

  test1 = std::move(test2);

  EXPECT_TRUE(test2.empty());
  EXPECT_EQ(test1.size(), 3);
  EXPECT_FALSE(test1.empty());
}

TEST(MapMethod, clear_1) {
  map<int, std::string> test{{1, "A"}, {2, "B"}, {3, "C"}};
  test.clear();

  // EXPECT_EQ(test.contains(2));
  EXPECT_EQ(test.size(), 0);
  EXPECT_TRUE(test.empty());
}

TEST(MapMethod, clear_2) {
  map<int, std::string> test;
  test.clear();

  EXPECT_EQ(test.size(), 0);
  EXPECT_TRUE(test.empty());
}

TEST(MapMethod, insert1) {
  map<int, std::string> test;
  pair<int, std::string> element{2, "B"};

  test.insert({1, "A"});
  pair<map<int, std::string>::iterator, bool> pair = test.insert({2, "B"});
  test.insert({3, "C"});

  EXPECT_EQ(test.size(), 3);
  EXPECT_EQ((*pair.first).first, element.first);
  EXPECT_EQ((*pair.first).second, element.second);
  EXPECT_TRUE(pair.second);
}

TEST(MapMethod, insert2) {
  map<int, std::string> test{{1, "A"}, {2, "B"}, {3, "C"}};
  pair<int, std::string> element{4, "D"};

  pair<map<int, std::string>::iterator, bool> pair = test.insert({4, "D"});

  EXPECT_EQ(test.size(), 4);
  EXPECT_EQ((*pair.first).first, element.first);
  EXPECT_EQ((*pair.first).second, element.second);
  EXPECT_TRUE(pair.second);
}

TEST(MapMethod, insert3) {
  map<int, std::string> test{{1, "A"}, {2, "B"}, {3, "C"}};
  pair<int, std::string> element{2, "B"};

  pair<map<int, std::string>::iterator, bool> pair = test.insert({2, "F"});

  EXPECT_EQ(test.size(), 3);
  EXPECT_EQ((*pair.first).first, element.first);
  EXPECT_EQ((*pair.first).second, element.second);
  EXPECT_FALSE(pair.second);
}

TEST(MapMethod, erase1) {
  map<int, std::string> test{{1, "A"}, {2, "B"}, {3, "C"}};
  test.erase(2);

  EXPECT_EQ(test.size(), 2);
  EXPECT_FALSE(test.contains(2));
}

TEST(MapMethod, erase2) {
  map<int, std::string> test{
      {1, "A"},  {2, "B"},  {3, "C"},  {4, "D"},  {5, "E"},  {6, "F"},
      {7, "G"},  {8, "H"},  {9, "I"},  {10, "J"}, {11, "K"}, {12, "L"},
      {13, "M"}, {14, "N"}, {15, "O"}, {16, "P"}, {17, "Q"}, {18, "R"},
      {19, "S"}, {20, "T"}, {21, "U"}, {22, "V"}, {23, "W"}, {24, "X"},
      {25, "Y"}, {26, "Z"}, {27, "a"}, {28, "b"}, {29, "c"}, {30, "d"}};
  test.erase(11);
  test.erase(6);
  test.erase(12);
  test.erase(22);
  test.erase(1);
  test.erase(26);
  test.erase(30);
  test.erase(19);
  test.erase(9);
  test.erase(18);
  test.erase(4);
  test.erase(2);
  test.erase(15);
  test.erase(23);
  test.erase(27);
  test.erase(24);
  test.erase(7);
  test.erase(14);
  test.erase(21);
  test.erase(8);
  test.erase(29);
  test.erase(5);
  test.erase(28);
  test.erase(10);
  test.erase(13);
  test.erase(25);
  test.erase(3);
  test.erase(17);
  test.erase(16);
  test.erase(20);

  EXPECT_EQ(test.size(), 0);
  EXPECT_TRUE(test.empty());
}

// TEST(MapMethod, erase_ptr) {
//   map<int, std::string> test{{1, "A"}, {2, "B"}, {3, "C"}};
//   test.erase(test.find(2));

//   EXPECT_EQ(test.size(), 2);
//   EXPECT_FALSE(test.contains(2));
// }

TEST(MapMethod, swap) {
  map<int, std::string> test1{{1, "A"}, {2, "B"}, {3, "C"}};
  map<int, std::string> test2{{4, "D"}, {5, "E"}, {6, "F"},
                              {7, "G"}, {8, "H"}, {9, "I"}};

  test1.swap(test2);

  EXPECT_EQ(test1.size(), 6);
  EXPECT_EQ(test2.size(), 3);

  EXPECT_TRUE(test1.contains(4));
  EXPECT_TRUE(test1.contains(5));
  EXPECT_TRUE(test1.contains(6));
  EXPECT_TRUE(test1.contains(7));
  EXPECT_TRUE(test1.contains(8));
  EXPECT_TRUE(test1.contains(9));

  EXPECT_TRUE(test2.contains(1));
  EXPECT_TRUE(test2.contains(2));
  EXPECT_TRUE(test2.contains(3));
}

TEST(MapMethod, merge) {
  map<int, std::string> test1{{1, "A"}, {2, "B"}, {3, "C"}};
  map<int, std::string> test2{{4, "D"}, {5, "E"}, {6, "F"},
                              {7, "G"}, {8, "H"}, {9, "I"}};

  test1.merge(test2);

  EXPECT_EQ(test1.size(), 9);
  EXPECT_EQ(test2.size(), 6);

  EXPECT_TRUE(test1.contains(4));
  EXPECT_TRUE(test1.contains(5));
  EXPECT_TRUE(test1.contains(6));
  EXPECT_TRUE(test1.contains(7));
  EXPECT_TRUE(test1.contains(8));
  EXPECT_TRUE(test1.contains(9));
}

TEST(MapMethod, find) {
  map<int, std::string> test{{1, "A"}, {2, "B"}, {3, "C"}};
  pair<int, std::string> element(2, "B");
  map<int, std::string>::iterator it = test.find(2);

  EXPECT_EQ(*it, element);

  it = test.find(10);

  EXPECT_TRUE(it == test.end());
}

TEST(MapMethod, begin1) {
  map<int, std::string> test{{1, "A"}, {2, "B"}, {3, "C"}};

  pair<int, std::string> element{1, "A"};

  pair<int, std::string> begin = *(test.begin());

  EXPECT_EQ(begin.first, element.first);
  EXPECT_EQ(begin.second, element.second);
}

TEST(MapMethod, begin2) {
  map<int, std::string> test{{3, "C"}, {2, "B"}, {1, "A"}};

  pair<int, std::string> element{1, "A"};

  pair<int, std::string> begin = *(test.begin());

  EXPECT_EQ(begin.first, element.first);
  EXPECT_EQ(begin.second, element.second);
}

TEST(MapMethod, begin3) {
  map<int, std::string> test{{10, "J"}, {15, "K"}, {5, "I"}, {6, "H"},
                             {7, "G"},  {8, "F"},  {9, "E"}, {11, "D"},
                             {12, "C"}, {13, "B"}, {14, "A"}};

  pair<int, std::string> element{5, "I"};

  pair<int, std::string> begin = *(test.begin());

  EXPECT_EQ(begin.first, element.first);
  EXPECT_EQ(begin.second, element.second);
}

TEST(MapMethod, end1) {
  map<int, std::string> test{{1, "A"}, {2, "B"}, {3, "C"}};

  map<int, std::string>::iterator result =
      (map<int, std::string>::iterator) nullptr;

  EXPECT_EQ(test.end(), result);
}

TEST(MapMethod, end2) {
  map<int, std::string> test{{3, "C"}, {2, "B"}, {1, "A"}};

  map<int, std::string>::iterator result =
      (map<int, std::string>::iterator) nullptr;

  EXPECT_EQ(test.end(), result);
}

TEST(MapMethod, end3) {
  map<int, std::string> test{{10, "J"}, {15, "K"}, {5, "I"}, {6, "H"},
                             {7, "G"},  {8, "F"},  {9, "E"}, {11, "D"},
                             {12, "C"}, {13, "B"}, {14, "A"}};

  map<int, std::string>::iterator result =
      (map<int, std::string>::iterator) nullptr;

  EXPECT_EQ(test.end(), result);
}

TEST(MapMethod, max_size) {
  map<int, std::string> test{{1, "A"}, {2, "B"}, {3, "C"}};

  EXPECT_GT(test.max_size(), 1000);
}

TEST(MapOperator, indexing1) {
  map<int, std::string> test{{1, "A"}, {2, "B"}, {3, "C"}};

  EXPECT_EQ(test[1], "A");
  EXPECT_EQ(test[2], "B");
  EXPECT_EQ(test[3], "C");
}

TEST(MapOperator, indexing2) {
  map<std::string, int> test{{"A", 1}, {"B", 2}, {"C", 3}};

  EXPECT_EQ(test["A"], 1);
  EXPECT_EQ(test["B"], 2);
  EXPECT_EQ(test["C"], 3);
}

TEST(MapOperator, indexing_insert1) {
  map<int, std::string> test{{1, "A"}, {2, "B"}, {3, "C"}};

  test[4] = "D";

  EXPECT_EQ(test.size(), 4);
  EXPECT_EQ(test[4], "D");
}