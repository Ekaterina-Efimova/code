#include "tests.hpp"

TEST(ListTest, DefaultConstructor) {
  s21::list<int> lst;
  EXPECT_TRUE(lst.empty());
  EXPECT_EQ(lst.size(), 0);
}

TEST(ListTest, InitializerListConstructor) {
  s21::list<int> lst{1, 2, 3, 4, 5};
  EXPECT_FALSE(lst.empty());
  EXPECT_EQ(lst.size(), 5);
  EXPECT_EQ(lst.front(), 1);
  EXPECT_EQ(lst.back(), 5);
}

TEST(ListTest, MoveConstructor) {
  s21::list<int> lst1{1, 2, 3};
  s21::list<int> lst2(std::move(lst1));
  EXPECT_EQ(lst2.size(), 3);
  EXPECT_EQ(lst2.front(), 1);
  EXPECT_EQ(lst2.back(), 3);
  EXPECT_TRUE(lst1.empty());
}

TEST(ListTest, SizeConstructor) {
  s21::list<int> lst(5);
  EXPECT_FALSE(lst.empty());
  EXPECT_EQ(lst.size(), 5);
}

TEST(ListTest, CopyConstructor) {
  s21::list<int> lst1{1, 2, 3};
  s21::list<int> lst2(lst1);
  EXPECT_EQ(lst2.size(), 3);
  EXPECT_EQ(lst2.front(), 1);
  EXPECT_EQ(lst2.back(), 3);
}

TEST(ListTest, Operator) {
  s21::list<int> lst1{1, 2, 3};
  s21::list<int> lst2;
  lst2 = lst1;
  EXPECT_EQ(lst2.size(), 3);
  EXPECT_EQ(lst2.front(), 1);
  EXPECT_EQ(lst2.back(), 3);
}

TEST(ListTest, Operator2) {
  const s21::list<int> lst1{1, 2, 3};
  s21::list<int> lst2;
  lst2 = lst1;
  EXPECT_EQ(lst2.size(), 3);
  EXPECT_EQ(lst2.front(), 1);
  EXPECT_EQ(lst2.back(), 3);
}

TEST(ListTest, Front) {
  s21::list<int> lst1{1, 2, 3};
  EXPECT_EQ(lst1.front(), 1);
}

TEST(ListTest, Back) {
  s21::list<int> lst1{1, 2, 3};
  EXPECT_EQ(lst1.back(), 3);
}

TEST(ListTest, Begin) {
  s21::list<int> lst1{1, 2, 3};
  s21::list<int>::iterator a = lst1.begin();
  EXPECT_EQ(*a, 1);
}

TEST(ListTest, Begin2) {
  const s21::list<int> lst1{1, 2, 3};
  s21::list<int>::iterator a = lst1.begin();
  EXPECT_EQ(*a, 1);
}

TEST(ListTest, End) {
  s21::list<int> lst1{1, 2, 3};
  s21::list<int>::iterator a = lst1.end();
  EXPECT_EQ(*a, 3);
}

TEST(ListTest, End2) {
  const s21::list<int> lst1{1, 2, 3};
  s21::list<int>::iterator a = lst1.end();
  EXPECT_EQ(*a, 3);
}

TEST(ListTest, Empty) {
  s21::list<int> lst1{1, 2, 3};
  EXPECT_EQ(lst1.empty(), false);
}

TEST(ListTest, Empty2) {
  s21::list<int> lst1;
  EXPECT_EQ(lst1.empty(), true);
}

TEST(ListTest, size) {
  s21::list<int> lst1;
  EXPECT_EQ(lst1.size(), 0);
}

TEST(ListTest, Clear) {
  s21::list<int> lst1{1, 2, 3};
  lst1.clear();
  EXPECT_EQ(lst1.empty(), true);
}

TEST(ListTest, PushBackAndPushFront) {
  s21::list<int> lst;
  lst.push_back(1);
  lst.push_back(2);
  lst.push_front(3);
  EXPECT_EQ(lst.front(), 3);
  EXPECT_EQ(lst.back(), 2);
  EXPECT_EQ(lst.size(), 3);
}

TEST(ListTest, Insert) {
  s21::list<int> lst{1, 2, 3, 4, 5};
  auto it = lst.begin();
  std::advance(it, 2);
  lst.insert(it, 10);
  EXPECT_EQ(lst.size(), 6);
}

TEST(ListTest, Erase) {
  s21::list<int> lst{1, 2, 3, 4, 5};
  auto it = lst.begin();
  std::advance(it, 2);
  lst.erase(it);
  EXPECT_EQ(lst.size(), 4);
}

TEST(ListTest, Reverse) {
  s21::list<int> lst{1, 2, 3, 4, 5};
  lst.reverse();
  EXPECT_EQ(lst.front(), 5);
  EXPECT_EQ(lst.back(), 1);
}

TEST(ListTest, Sort) {
  s21::list<int> lst{5, 3, 1, 4, 2};
  lst.sort();
  EXPECT_EQ(lst.front(), 1);
  EXPECT_EQ(lst.back(), 5);
}

TEST(ListTest, Clear2) {
  s21::list<int> lst{1, 2, 3, 4, 5};
  lst.clear();
  EXPECT_TRUE(lst.empty());
  EXPECT_EQ(lst.size(), 0);
}

TEST(ListTest, Unique) {
  s21::list<int> lst{1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
  lst.unique();
  EXPECT_EQ(lst.size(), 4);
  EXPECT_EQ(lst.front(), 1);
  EXPECT_EQ(lst.back(), 4);
}

TEST(ListTest, Merge) {
  s21::list<int> lst1{1, 3, 5};
  s21::list<int> lst2{2, 4, 6};
  lst1.merge(lst2);
  EXPECT_EQ(lst1.size(), 6);
  EXPECT_EQ(lst1.front(), 1);
  EXPECT_EQ(lst1.back(), 6);
}

TEST(ListTest, Splice) {
  s21::list<int> lst1{1, 3, 5};
  s21::list<int> lst2{2, 4, 6};
  lst1.splice(lst1.begin(), lst2);
  EXPECT_EQ(lst1.size(), 6);
  EXPECT_EQ(lst1.front(), 2);
  EXPECT_EQ(lst1.back(), 5);
}

TEST(ListTest, Swap) {
  s21::list<int> lst1{1, 2, 3};
  s21::list<int> lst2{4, 5, 6};
  lst1.swap(lst2);
  EXPECT_EQ(lst1.size(), 3);
  EXPECT_EQ(lst1.front(), 4);
  EXPECT_EQ(lst1.back(), 6);
  EXPECT_EQ(lst2.size(), 3);
  EXPECT_EQ(lst2.front(), 1);
  EXPECT_EQ(lst2.back(), 3);
}

TEST(ListTest, InsertMany) {
  s21::list<int> lst{1, 2, 3};
  lst.insert_many(lst.begin());
  EXPECT_EQ(lst.size(), 3);
  EXPECT_EQ(lst.front(), 1);
  EXPECT_EQ(lst.back(), 3);
}

TEST(ListTest, InsertManyBack) {
  s21::list<int> lst{1, 2, 3};
  lst.insert_many_back();
  EXPECT_EQ(lst.size(), 3);
  EXPECT_EQ(lst.front(), 1);
  EXPECT_EQ(lst.back(), 3);
}

TEST(ListTest, InsertManyFront) {
  s21::list<int> lst{1, 2, 3};
  lst.insert_many_front();
  EXPECT_EQ(lst.size(), 3);
  EXPECT_EQ(lst.front(), 1);
  EXPECT_EQ(lst.back(), 3);
}

TEST(ListTest, InsertMany2) {
  s21::list<int> lst{1, 2, 3};
  lst.insert_many(lst.begin(), 4);
  EXPECT_EQ(lst.size(), 4);
  EXPECT_EQ(lst.front(), 4);
  EXPECT_EQ(lst.back(), 3);
}

TEST(ListTest, InsertManyBack2) {
  s21::list<int> lst{1, 2, 3};
  lst.insert_many_back(4);
  EXPECT_EQ(lst.size(), 4);
  EXPECT_EQ(lst.front(), 1);
  EXPECT_EQ(lst.back(), 4);
}

TEST(ListTest, InsertManyFront2) {
  s21::list<int> lst{1, 2, 3};
  lst.insert_many_front(4);
  EXPECT_EQ(lst.size(), 4);
  EXPECT_EQ(lst.front(), 4);
  EXPECT_EQ(lst.back(), 3);
}

TEST(ListTest, InsertMany3) {
  s21::list<int> lst{1, 2, 3};
  lst.insert_many(lst.begin(), 4, 5, 6);
  EXPECT_EQ(lst.size(), 6);
  EXPECT_EQ(lst.front(), 4);
  EXPECT_EQ(lst.back(), 3);
}

TEST(ListTest, InsertManyBack3) {
  s21::list<int> lst{1, 2, 3};
  lst.insert_many_back(4, 5, 6);
  EXPECT_EQ(lst.size(), 6);
  EXPECT_EQ(lst.front(), 1);
  EXPECT_EQ(lst.back(), 6);
}

TEST(ListTest, InsertManyFront3) {
  s21::list<int> lst{1, 2, 3};
  lst.insert_many_front(4, 5, 6);
  EXPECT_EQ(lst.size(), 6);
  EXPECT_EQ(lst.front(), 6);
  EXPECT_EQ(lst.back(), 3);
}

TEST(ListTest, InsertMany4) {
  s21::list<int> lst{1, 2, 3};
  lst.insert_many(lst.begin(), 4, 5, 6, 7, 8);
  EXPECT_EQ(lst.size(), 8);
  EXPECT_EQ(lst.front(), 4);
  EXPECT_EQ(lst.back(), 3);
}

TEST(ListTest, InsertManyBack4) {
  s21::list<int> lst{1, 2, 3};
  lst.insert_many_back(4, 5, 6, 7, 8);
  EXPECT_EQ(lst.size(), 8);
  EXPECT_EQ(lst.front(), 1);
  EXPECT_EQ(lst.back(), 8);
}

TEST(ListTest, InsertManyFront4) {
  s21::list<int> lst{1, 2, 3};
  lst.insert_many_front(4, 5, 6, 7 ,8);
  EXPECT_EQ(lst.size(), 8);
  EXPECT_EQ(lst.front(), 8);
  EXPECT_EQ(lst.back(), 3);
}
TEST(ListTest, PushBack) {
  s21::list<int> lst;
  lst.push_back(1);
  lst.push_back(2);
  lst.push_back(3);
  EXPECT_EQ(lst.size(), 3);
  EXPECT_EQ(lst.front(), 1);
  EXPECT_EQ(lst.back(), 3);
}

TEST(ListTest, PushFront) {
  s21::list<int> lst;
  lst.push_front(1);
  lst.push_front(2);
  lst.push_front(3);
  EXPECT_EQ(lst.size(), 3);
  EXPECT_EQ(lst.front(), 3);
  EXPECT_EQ(lst.back(), 1);
}

TEST(ListTest, PopBack) {
  s21::list<int> lst{1, 2, 3};
  lst.pop_back();
  EXPECT_EQ(lst.size(), 2);
  EXPECT_EQ(lst.front(), 1);
  EXPECT_EQ(lst.back(), 2);
}

TEST(ListTest, PopFront) {
  s21::list<int> lst{1, 2, 3};
  lst.pop_front();
  EXPECT_EQ(lst.size(), 2);
  EXPECT_EQ(lst.front(), 2);
  EXPECT_EQ(lst.back(), 3);
}

TEST(ListTest, MaxSize) {
  s21::list<int> lst;

  EXPECT_EQ(lst.max_size(), 384307168202282325);
}

TEST(ListTest, ItOperator) {
  s21::list<int> lst{1, 2, 3};
  list<int>::ListIterator a = lst.begin();

  EXPECT_EQ(*a, 1);
}

TEST(ListTest, ItOperator5) {
  s21::list<int> lst{1, 2, 3};
  list<int>::ListIterator a = lst.end();
  --a;
  EXPECT_EQ(*a, 2);
}

TEST(ListTest, ItOperator6) {
  s21::list<int> lst{1, 2, 3};
  list<int>::ListIterator a = lst.end();
  a--;
  EXPECT_EQ(*a, 2);
}

TEST(ListTest, ItOperator7) {
  s21::list<int> lst{1, 2, 3};
  list<int>::ListIterator a = lst.begin();
  a++;
  EXPECT_EQ(*a, 2);
}

TEST(ListTest, ItOperator8) {
  s21::list<int> lst{1, 2, 3};
  list<int>::ListIterator a = lst.begin();
  ++a;
  EXPECT_EQ(*a, 2);
}

TEST(Method, list_move) {
  s21::list<int> test1{1, 2, 3};
  s21::list<int> test2;

  test2 = std::move(test1);

  EXPECT_EQ(test1.empty(), true);
  EXPECT_EQ(test2.size(), 3);
  EXPECT_EQ(test2.empty(), false);
}