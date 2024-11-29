#include "tests.hpp"

TEST(VectorTest, DefaultConstructor_Int) {
  vector<int> v;
  EXPECT_EQ(v.size(), 0U);
  EXPECT_EQ(v.capacity(), 0U);
  EXPECT_EQ(v.data(), nullptr);
}

TEST(VectorTest, DefaultConstructor_Double) {
  vector<double> v;
  EXPECT_EQ(v.size(), 0U);
  EXPECT_EQ(v.capacity(), 0U);
  EXPECT_EQ(v.data(), nullptr);
}

TEST(VectorTest, ParameterizedConstructor_Int) {
  vector<int> v(6);
  EXPECT_EQ(v.size(), 6U);
  EXPECT_EQ(v.capacity(), 6U);
  EXPECT_NE(v.data(), nullptr);
}

TEST(VectorTest, ParameterizedConstructor_InvalidSize) {
  vector<int>::size_type invalid_size =
      std::numeric_limits<vector<int>::size_type>::max() / sizeof(int) + 1;
  EXPECT_THROW(vector<int> v(invalid_size), std::invalid_argument);
}

TEST(VectorTest, InitConstructor) {
  vector<int> v = {1, 2, 3};

  EXPECT_EQ(v.size(), 3U);
  EXPECT_EQ(v.capacity(), 3U);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, CopyConstructor) {
  vector<int> v = {1, 2, 3};
  vector<int> other(v);

  EXPECT_EQ(v.size(), other.size());
  EXPECT_EQ(v.capacity(), other.capacity());
  EXPECT_EQ(v[0], other[0]);
  EXPECT_EQ(v[1], other[1]);
  EXPECT_EQ(v[2], other[2]);
}

TEST(VectorTest, MoveConstructor) {
  vector<int> v = {1, 2, 3};
  vector<int> other(std::move(v));

  EXPECT_EQ(other.size(), 3U);
  EXPECT_EQ(other.capacity(), 3U);
  EXPECT_EQ(other[0], 1);
  EXPECT_EQ(other[1], 2);
  EXPECT_EQ(other[2], 3);
  EXPECT_EQ(v.data(), nullptr);
}

TEST(VectorTest, OperatorEqual) {
  vector<int> v{1, 2, 3};
  vector<int> other;
  other = std::move(v);

  EXPECT_EQ(other.size(), 3U);
  EXPECT_EQ(other.capacity(), 3U);
  EXPECT_EQ(other[0], 1);
  EXPECT_EQ(other[1], 2);
  EXPECT_EQ(other[2], 3);

  EXPECT_EQ(v.size(), 0U);
  EXPECT_EQ(v.capacity(), 0U);
  EXPECT_EQ(v.data(), nullptr);
}

TEST(VectorTest, AtMethod) {
  vector<int> v = {1, 2, 3};
  EXPECT_EQ(v.at(0), 1);
  EXPECT_EQ(v.at(1), 2);
  EXPECT_EQ(v.at(2), 3);
}

TEST(VectorTest, AtMethod_EmptyContainer) {
  vector<int> v;
  EXPECT_THROW(v.at(0), std::out_of_range);
}

TEST(VectorTest, AtMethod_OutOfBounds) {
  vector<int> v = {1, 2, 3};
  EXPECT_THROW(v.at(3), std::out_of_range);
}

TEST(VectorTest, AtConstMethod) {
  const vector<int> v = {1, 2, 3};
  EXPECT_EQ(v.at(0), 1);
  EXPECT_EQ(v.at(1), 2);
  EXPECT_EQ(v.at(2), 3);
}

TEST(VectorTest, AtConstMethod_OutOfRange) {
  const vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_THROW(v.at(5), std::out_of_range);
}

TEST(VectorTest, AtConstMethod_OutOfRangeEmpty) {
  const vector<int> v;
  EXPECT_THROW(v.at(0), std::out_of_range);
}

TEST(VectorTest, OperatorBracket) {
  const vector<int> v = {10, 20, 30, 40, 50};
  EXPECT_EQ(v[0], 10);
  EXPECT_EQ(v[1], 20);
  EXPECT_EQ(v[2], 30);
  EXPECT_EQ(v[3], 40);
  EXPECT_EQ(v[4], 50);
}

TEST(VectorTest, OperatorBracket_EmptyContainer) {
  vector<int> v;
  EXPECT_THROW(v[0], std::out_of_range);
}

TEST(VectorTest, OperatorBracket_OutOfBounds) {
  vector<int> v = {1, 2, 3};
  EXPECT_THROW(v[3], std::out_of_range);
}

TEST(VectorTest, FrontMethod) {
  vector<int> v = {1, 2, 3};
  EXPECT_EQ(v.front(), 1);
}

TEST(VectorTest, FrontMethod_EmptyContainer) {
  vector<int> v;
  EXPECT_THROW(v.front(), std::out_of_range);
}

TEST(VectorTest, BackMethod) {
  vector<int> v = {1, 2, 3};
  EXPECT_EQ(v.back(), 3);
}

TEST(VectorTest, BackMethod_EmptyContainer) {
  vector<int> v;
  EXPECT_THROW(v.back(), std::out_of_range);
}

TEST(VectorTest, DataMethod) {
  vector<int> v = {1, 2, 3};
  int* ptr = &(*v.data());

  EXPECT_EQ(*ptr, 1);
  EXPECT_EQ(ptr[0], 1);
  EXPECT_EQ(ptr[1], 2);
  EXPECT_EQ(ptr[2], 3);
}

TEST(VectorTest, BeginMethod) {
  vector<int> v = {1, 2, 3};
  auto it = v.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
}

TEST(VectorTest, CBeginMethod) {
  vector<int> v = {1, 2, 3};
  auto it = v.cbegin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
}

TEST(VectorTest, EndMethod) {
  vector<int> v = {1, 2, 3};
  auto it = v.end();
  --it;
  EXPECT_EQ(*it, 3);
}

TEST(VectorTest, CEndMethod) {
  const vector<int> v = {1, 2, 3};
  auto it = v.cend();
  --it;
  EXPECT_EQ(*it, 3);
}

TEST(VectorTest, EmptyMethod) {
  vector<int> v;
  EXPECT_EQ(v.empty(), 1);
}

TEST(VectorTest, MaxSizeMethod) {
  vector<int> v = {1, 2, 3};
  auto size = std::numeric_limits<vector<int>::size_type>::max() / sizeof(int);
  EXPECT_EQ(v.max_size(), size);
}

TEST(VectorTest, ReserveMethod) {
  vector<int> v = {1, 2, 3};
  v.reserve(6);
  EXPECT_EQ(v.capacity(), 6U);
}

TEST(VectorTest, ReserveMethod_InvalidSize) {
  vector<int> v;
  vector<int>::size_type invalid_size =
      std::numeric_limits<vector<int>::size_type>::max() / sizeof(int) + 1;
  EXPECT_THROW(v.reserve(invalid_size), std::invalid_argument);
}

TEST(VectorTest, CapacityMethod) {
  vector<int> v;
  EXPECT_EQ(v.capacity(), 0U);
}

TEST(VectorTest, ShrinkToFitMethod) {
  vector<int> v = {1, 2, 3};

  v.push_back(4);
  EXPECT_EQ(v.capacity(), 6U);
  v.shrink_to_fit();
  EXPECT_EQ(v.capacity(), 4U);
}

TEST(VectorTest, ClearMethod) {
  vector<int> v = {1, 2, 3};
  v.clear();
  EXPECT_EQ(v.size(), 0U);
}

TEST(VectorTest, InsertMethod) {
  vector<int> v = {1, 2, 3};
  v.insert(v.end(), 4);
  EXPECT_EQ(v.size(), 4U);
  EXPECT_EQ(v[3], 4);
}

TEST(VectorTest, InsertMethod_ElementMove) {
  vector<int> v = {1, 2, 3};

  v.reserve(5);
  v.insert(v.begin() + 1, 99);

  EXPECT_EQ(v.size(), 4);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 99);
  EXPECT_EQ(v[2], 2);
  EXPECT_EQ(v[3], 3);
}

TEST(VectorTest, InsertMethod_OutOfRange) {
  vector<int> v = {1, 2, 3};
  EXPECT_THROW(v.insert(v.end() + 1, 4), std::out_of_range);
}

TEST(VectorTest, InsertMethod_PositionOutOfRange) {
  vector<int> v = {1, 2, 3};
  EXPECT_THROW(v.insert(v.begin() - 1, 4), std::out_of_range);
  EXPECT_THROW(v.insert(v.end() + 1, 4), std::out_of_range);
}

TEST(VectorTest, EraseMethod) {
  vector<int> v = {1, 2, 3, 4, 5};

  v.erase(v.begin() + 2);
  EXPECT_EQ(v.size(), 4U);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 4);
  EXPECT_EQ(v[3], 5);
}

TEST(VectorTest, EraseMethod_OutOfRange) {
  vector<int> v = {1, 2, 3};
  EXPECT_THROW(v.erase(v.end()), std::out_of_range);
}

TEST(VectorTest, EraseMethod_EmptyContainer) {
  vector<int> v;
  EXPECT_THROW(v.erase(v.begin()), std::out_of_range);
}

TEST(VectorTest, PushBackMethod) {
  vector<int> v = {1, 2, 3};
  v.push_back(4);
  EXPECT_EQ(v.size(), 4U);
  EXPECT_EQ(v[3], 4);
}

TEST(VectorTest, PopBackMethod) {
  vector<int> v = {1, 2, 3};
  v.pop_back();
  EXPECT_EQ(v.size(), 2U);
  EXPECT_EQ(v[1], 2);
}

TEST(VectorTest, PopBackMethod_EmptyContainer) {
  vector<int> v;
  EXPECT_THROW(v.pop_back(), std::out_of_range);
}

TEST(VectorTest, SwapMethod) {
  vector<int> v = {1, 2, 3};
  vector<int> other = {4, 5, 6};

  v.swap(other);

  EXPECT_EQ(v[0], 4);
  EXPECT_EQ(v[1], 5);
  EXPECT_EQ(v[2], 6);

  EXPECT_EQ(other[0], 1);
  EXPECT_EQ(other[1], 2);
  EXPECT_EQ(other[2], 3);
}

TEST(VectorTest, InsertManyMethod_OutOfRange) {
  vector<int> v = {1, 2, 3};
  EXPECT_THROW(v.insert_many(v.cend() + 1, 4, 5, 6), std::out_of_range);
}

TEST(VectorTest, InsertManyMethod_1) {
  vector<int> v{1, 2, 3};
  v.insert_many(v.cbegin() + 1);
  EXPECT_EQ(v.size(), 3U);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, InsertManyMethod_2) {
  vector<int> v{1, 2, 3};
  v.insert_many(v.cbegin() + 1, 4);
  EXPECT_EQ(v.size(), 4U);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 4);
  EXPECT_EQ(v[2], 2);
  EXPECT_EQ(v[3], 3);
}

TEST(VectorTest, InsertManyMethod_3) {
  vector<int> v{1, 2, 3};
  v.insert_many(v.cbegin() + 1, 4, 5, 6);
  EXPECT_EQ(v.size(), 6U);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 4);
  EXPECT_EQ(v[2], 5);
  EXPECT_EQ(v[3], 6);
  EXPECT_EQ(v[4], 2);
  EXPECT_EQ(v[5], 3);
}

TEST(VectorTest, InsertManyMethod_4) {
  vector<int> v{1, 2, 3};
  v.insert_many(v.cbegin() + 1, 4, 5, 6, 7, 8);
  EXPECT_EQ(v.size(), 8U);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 4);
  EXPECT_EQ(v[2], 5);
  EXPECT_EQ(v[3], 6);
  EXPECT_EQ(v[4], 7);
  EXPECT_EQ(v[5], 8);
  EXPECT_EQ(v[6], 2);
  EXPECT_EQ(v[7], 3);
}

TEST(VectorTest, InsertManyBackMethod_OutOfRange) {
  vector<int> v = {1, 2, 3};
  EXPECT_THROW(v.insert_many(v.cend() + 1, 4, 5, 6), std::out_of_range);
}

TEST(VectorTest, InsertManyBackMethod_1) {
  vector<int> v = {1, 2, 3};
  v.insert_many_back();
  EXPECT_EQ(v.size(), 3U);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, InsertManyBackMethod_2) {
  vector<int> v = {1, 2, 3};
  v.insert_many_back(4);
  EXPECT_EQ(v.size(), 4U);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[3], 4);
}

TEST(VectorTest, InsertManyBackMethod_3) {
  vector<int> v = {1, 2, 3};
  v.insert_many_back(4, 5, 6);
  EXPECT_EQ(v.size(), 6U);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[3], 4);
  EXPECT_EQ(v[4], 5);
  EXPECT_EQ(v[5], 6);
}

TEST(VectorTest, InsertManyBackMethod_4) {
  vector<int> v = {1, 2, 3};
  v.insert_many_back(4, 5, 6, 7, 8);
  EXPECT_EQ(v.size(), 8U);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[3], 4);
  EXPECT_EQ(v[4], 5);
  EXPECT_EQ(v[5], 6);
  EXPECT_EQ(v[6], 7);
  EXPECT_EQ(v[7], 8);
}

TEST(VectorTest, IteratorOperations) {
  vector<int> v = {1, 2, 3, 4, 5};
  auto it = v.begin();

  EXPECT_EQ(*it, 1);

  ++it;
  EXPECT_EQ(*it, 2);

  it++;
  EXPECT_EQ(*it, 3);

  --it;
  EXPECT_EQ(*it, 2);

  it--;
  EXPECT_EQ(*it, 1);

  it += 3;
  EXPECT_EQ(*it, 4);

  it = it + 1;
  EXPECT_EQ(*it, 5);

  it -= 2;
  EXPECT_EQ(*it, 3);

  it = it - 1;
  EXPECT_EQ(*it, 2);

  auto it2 = v.begin() + 4;
  EXPECT_EQ(it2 - it, 3);

  EXPECT_TRUE(it < it2);
  EXPECT_TRUE(it2 > it);
  EXPECT_TRUE(it <= it2);
  EXPECT_TRUE(it2 >= it);
  EXPECT_FALSE(it == it2);
  EXPECT_TRUE(it != it2);
}

TEST(VectorTest, ConstIteratorOperations) {
  const vector<int> v = {1, 2, 3, 4, 5};
  auto it = v.cbegin();

  EXPECT_EQ(*it, 1);

  ++it;
  EXPECT_EQ(*it, 2);

  it++;
  EXPECT_EQ(*it, 3);

  --it;
  EXPECT_EQ(*it, 2);

  it--;
  EXPECT_EQ(*it, 1);

  it = it + 3;
  EXPECT_EQ(*it, 4);

  it = it - 2;
  EXPECT_EQ(*it, 2);

  auto it2 = v.cbegin() + 4;
  EXPECT_TRUE(it < it2);
  EXPECT_TRUE(it2 > it);
  EXPECT_TRUE(it <= it2);
  EXPECT_TRUE(it2 >= it);
  EXPECT_FALSE(it == it2);
  EXPECT_TRUE(it != it2);
}