#include "tests.hpp"

TEST(StackTest, stack_constructor) {
  stack<int> v;

  EXPECT_EQ(v.size(), 0);
}

TEST(StackTest, stack_equal) {
  stack<int> v;
  v.push(1);
  stack<int> v2 = v;

  EXPECT_EQ(v2.top(), v.top());
}

TEST(StackTest, stack_push) {
  stack<int> v;
  v.push(1);

  EXPECT_EQ(v.top(), 1);
}

TEST(StackTest, stack_top) {
  stack<int> v;
  v.push(1);

  EXPECT_EQ(v.top(), 1);
}

TEST(StackTest, stack_pop) {
  stack<int> v;
  v.push(1);
  v.push(2);

  v.pop();

  EXPECT_EQ(v.top(), 1);
  EXPECT_EQ(v.size(), 1);
}

TEST(StackTest, stack_empty) {
  stack<int> v;
  v.push(1);

  EXPECT_EQ(v.empty(), false);
}

TEST(StackTest, stack_empty2) {
  stack<int> v;

  EXPECT_EQ(v.empty(), true);
}

TEST(StackTest, PushAndPop) {
  s21::stack<int> s;
  s.push(1);
  s.push(2);
  s.push(3);
  EXPECT_EQ(s.top(), 3);
  s.pop();
  EXPECT_EQ(s.top(), 2);
}

TEST(StackTest, DefaultConstructor) {
  s21::stack<int> s;
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);
}

TEST(StackTest, InitializerListConstructor) {
  s21::stack<int> s{1, 2, 3, 4, 5};
  EXPECT_FALSE(s.empty());
  EXPECT_EQ(s.size(), 5);
  EXPECT_EQ(s.top(), 5);
}

TEST(StackTest, CopyConstructor) {
  s21::stack<int> s1{1, 2, 3};
  s21::stack<int> s2(s1);
  EXPECT_EQ(s2.size(), 3);
  EXPECT_EQ(s2.top(), 3);
}

TEST(StackTest, InsertManyFront) {
  s21::stack<int, s21::list<int>> s {1, 2, 3};
  s.insert_many_front();
  EXPECT_EQ(s.top(), 3);
  EXPECT_EQ(s.size(), 3);
}

TEST(StackTest, InsertManyFront2) {
  s21::stack<int, s21::list<int>> s;
  s.insert_many_front(1);
  EXPECT_EQ(s.top(), 1);
  EXPECT_EQ(s.size(), 1);
}

TEST(StackTest, InsertManyFront3) {
  s21::stack<int, s21::list<int>> s;
  s.insert_many_front(1, 2, 3);
  EXPECT_EQ(s.top(), 1);
  EXPECT_EQ(s.size(), 3);
}

TEST(StackTest, InsertManyFront4) {
  s21::stack<int, s21::list<int>> s;
  s.insert_many_front(1, 2, 3, 4, 5);
  EXPECT_EQ(s.top(), 1);
  EXPECT_EQ(s.size(), 5);
}