#pragma once

#include <limits>
#include <utility>

#include "../s21_sorted_containers/s21_sorted_containers.hpp"

namespace s21 {

template <typename T1, typename T2>
class associative_container {
 private:
  using key_type = T1;
  using data_type = T2;
  using value_type = pair<key_type, data_type>;
  using tree_type = typename sorted_container<value_type>::rb_tree;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;

  using iterator = typename sorted_container<value_type>::iterator;
  using const_iterator = const typename sorted_container<value_type>::iterator;

 public:
  virtual ~associative_container() = default;

  virtual pair<iterator, bool> insert(const value_type &) = 0;
  virtual pair<iterator, bool> insert(value_type &&) = 0;
  virtual void insert(std::initializer_list<value_type>) = 0;

  virtual void erase(const key_type &) = 0;
  virtual void erase(const iterator &) = 0;

  virtual void clear() = 0;

  virtual iterator find(const key_type &) = 0;

  virtual bool contains(const key_type &) = 0;

  virtual size_type max_size() const = 0;

  virtual iterator begin() const = 0;
  virtual iterator end() const = 0;

  virtual size_t size() const = 0;
  virtual bool empty() const = 0;
};

}  // namespace s21

// #include "s21_assotiative_container.tpp"
