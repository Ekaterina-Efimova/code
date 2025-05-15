#pragma once
#include <type_traits>

#include "../s21_list/s21_list.hpp"
#include "../s21_vector/s21_vector.hpp"

namespace s21 {
template <typename T1, typename T2>
class stack;

template <typename T1, typename T2>
struct is_valid_container_stack {
  static constexpr bool value = false;
};

template <typename T1>
struct is_valid_container_stack<T1, vector<T1>> {
  static constexpr bool value = true;
};

template <typename T1>
struct is_valid_container_stack<T1, list<T1>> {
  static constexpr bool value = true;
};
template <typename T1, typename T2 = vector<T1>>
class stack : protected T2 {
 private:
  using value_type = T1;
  using container_type = T2;
  using reference = T1 &;
  using const_reference = const T1 &;
  using size_type = size_t;

 public:
  stack() {
    static_assert(is_valid_container_stack<T1, T2>::value,
                  "Invalid container type for stack");
  }

  using T2::T2;
  using T2::operator=;

  void pop();
  void push(const T1 &value);
  const_reference top() const;
  bool empty() const;
  size_type size() const;
  container_type &_Get_container();
  const container_type &_Get_container() const;
  template <typename... Args>
  void insert_many_front(Args &&...args);
};

}  // namespace s21

#include "s21_stack.tpp"
