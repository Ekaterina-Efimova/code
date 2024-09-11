#pragma once

#include <limits>
#include <utility>

#include "../s21_sorted_containers/s21_sorted_containers.hpp"

namespace s21 {

template <typename T1, typename T2 /*, typename comparator = std::less<T1>*/>
class map : private sorted_container<pair<T1, T2>> {
 private:
  using key_type = T1;
  using data_type = T2;
  using value_type = pair<key_type, data_type>;
  using tree_type = typename sorted_container<value_type>::rb_tree;
  using reference = value_type &;
  using const_reference = const value_type &;

  tree_type *tree_;
  std::size_t m_size_;

 public:
  using iterator = typename sorted_container<value_type>::iterator;
  using const_iterator = const typename sorted_container<value_type>::iterator;

  map() : tree_(new tree_type()), m_size_(0) {};
  map(std::initializer_list<value_type> const &);
  map(const map &);
  map(map &&);
  ~map() { delete tree_; };

  pair<iterator, bool> insert(const value_type &value);
  pair<iterator, bool> insert(value_type &&);
  void insert(std::initializer_list<value_type>);

  void erase(key_type const &);

  void clear();

  iterator find(const key_type &key);

  bool contains(const key_type &);

  std::size_t max_size() const;

  iterator begin() const;
  iterator end() const;

  std::size_t size() const;
  bool empty() const;

  void merge(map &);
  void swap(map &) noexcept;

  bool operator==(const map &);
  map &operator=(const map &);
  map &operator=(map &&) noexcept;
  data_type &operator[](const key_type &);
};

}  // namespace s21

#include "s21_map.tpp"
