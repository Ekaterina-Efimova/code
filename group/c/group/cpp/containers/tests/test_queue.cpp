#include "tests.hpp"

TEST(QueueTest, queue_constructor) {
  queue<int> v;

  EXPECT_EQ(v.size(), 0);
}

TEST(QueueTest, queue_equal) {
  queue<int> v;
  v.push(1);
  queue<int> v2 = v;

  EXPECT_EQ(v2.front(), v.front());
}

TEST(QueueTest, queue_push) {
  queue<int> v;
  v.push(1);

  EXPECT_EQ(v.front(), 1);
}

TEST(QueueTest, queue_front) {
  queue<int> v;
  v.push(1);

  EXPECT_EQ(v.front(), 1);
}

TEST(QueueTest, queue_back) {
  queue<int> v;
  v.push(1);

  EXPECT_EQ(v.back(), 1);
}

TEST(QueueTest, queue_pop) {
  queue<int> v;
  v.push(1);
  v.push(2);

  v.pop();

  EXPECT_EQ(v.front(), 2);
  EXPECT_EQ(v.size(), 1);
}

TEST(QueueTest, queue_empty) {
  queue<int> v;
  v.push(1);

  EXPECT_EQ(v.empty(), false);
}

TEST(QueueTest, queue_empty2) {
  queue<int> v;

  EXPECT_EQ(v.empty(), true);
}

TEST(QueueTest, PushAndPop) {
  s21::queue<int> q;
  q.push(1);
  q.push(2);
  q.push(3);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 3);
  q.pop();
  EXPECT_EQ(q.front(), 2);
  EXPECT_EQ(q.back(), 3);
}

TEST(QueueTest, DefaultConstructor) {
  s21::queue<int> q;
  EXPECT_TRUE(q.empty());
  EXPECT_EQ(q.size(), 0);
}

TEST(QueueTest, InitializerListConstructor) {
  s21::queue<int> q{1, 2, 3, 4, 5};
  EXPECT_FALSE(q.empty());
  EXPECT_EQ(q.size(), 5);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 5);
}

TEST(QueueTest, CopyConstructor) {
  s21::queue<int> q1{1, 2, 3};
  s21::queue<int> q2(q1);
  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q2.back(), 3);
}

TEST(QueueTest, swap) {
  s21::queue<int> q1{1, 2, 3};
  s21::queue<int> q2{4, 5, 6};

  q1.swap(q2);

  EXPECT_EQ(q1.size(), 3);
  EXPECT_EQ(q1.front(), 4);
  EXPECT_EQ(q1.back(), 6);
  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q2.back(), 3);
}

TEST(QueueTest, insert_many) {
  s21::queue<int> q1{1, 2, 3};

  q1.insert_many_back();

  EXPECT_EQ(q1.size(), 3);
  EXPECT_EQ(q1.front(), 1);
  EXPECT_EQ(q1.back(), 3);
}
TEST(QueueTest, insert_many2) {
  s21::queue<int> q1{1, 2, 3};

  q1.insert_many_back(4);

  EXPECT_EQ(q1.size(), 4);
  EXPECT_EQ(q1.front(), 1);
  EXPECT_EQ(q1.back(), 4);
}

TEST(QueueTest, insert_many3) {
  s21::queue<int> q1{1, 2, 3};

  q1.insert_many_back(4, 5, 6);

  EXPECT_EQ(q1.size(), 6);
  EXPECT_EQ(q1.front(), 1);
  EXPECT_EQ(q1.back(), 6);
}

TEST(QueueTest, insert_many4) {
  s21::queue<int> q1{1, 2, 3};

  q1.insert_many_back(4, 5, 6, 7 , 8 );

  EXPECT_EQ(q1.size(), 8);
  EXPECT_EQ(q1.front(), 1);
  EXPECT_EQ(q1.back(), 8);
}