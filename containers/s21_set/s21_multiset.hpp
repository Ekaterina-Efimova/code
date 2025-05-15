#pragma once
#include "s21_set.hpp"

namespace s21 {

template <typename T>
class multiset : public set<T> {
 private:
  using value_type = T;
  using const_reference = const T &;
  using size_type = std::size_t;

 public:
  using iterator = typename sorted_container<value_type>::iterator;

  multiset() : set<T>() {};
  multiset(std::initializer_list<T> const &);

  pair<iterator, bool> insert(const_reference);
  void merge(multiset &);
  size_type count(const_reference num) const { return this->tree->count(num); };
  pair<iterator, iterator> equal_range(const_reference);
  iterator lower_bound(const_reference);
  iterator upper_bound(const_reference);
};

}  // namespace s21

#include "s21_multiset.tpp"