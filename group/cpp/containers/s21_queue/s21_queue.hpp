#pragma once
#include <type_traits>

#include "../s21_list/s21_list.hpp"
#include "../s21_vector/s21_vector.hpp"

namespace s21 {

template <typename T1, typename T2>
class queue;

template <typename T1, typename T2>
struct is_valid_container_queue {
  static constexpr bool value = false;
};

template <typename T1>
struct is_valid_container_queue<T1, vector<T1>> {
  static constexpr bool value = true;
};

template <typename T1>
struct is_valid_container_queue<T1, list<T1>> {
  static constexpr bool value = true;
};

template <typename T1, typename T2 = vector<T1>>
class queue : protected T2 {
 private:
  using value_type = T1;
  using container_type = T2;
  using reference = T1 &;
  using const_reference = const T1 &;
  using size_type = size_t;

 public:
  queue() {
    static_assert(is_valid_container_queue<T1, T2>::value,
                  "Invalid container type for queue");
  }

  using T2::T2;
  using T2::operator=;

  void pop();
  void push(const T1 &value);
  const_reference front() const;
  const_reference back() const;
  bool empty() const;
  size_type size() const;
  container_type &_Get_container();
  const container_type &_Get_container() const;
  void swap(queue &other);
  template <typename... Args>
  void insert_many_back(Args &&...args);
};

}  // namespace s21

#include "s21_queue.tpp"
