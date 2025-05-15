#pragma once
#include <initializer_list>
#include <limits>
#include <memory>

namespace s21 {

template <class T>
class list {
 public:
  class ListIterator;

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = ListIterator;
  using const_iterator = const ListIterator;
  using size_type = size_t;

  list();
  explicit list(size_type n);
  list(std::initializer_list<value_type> const &items);
  list(const list &l);
  list(list &&l) noexcept;
  ~list();

  list &operator=(const list &other);
  list &operator=(list &&other) noexcept;

  const_reference front() const;
  const_reference back() const;

  const_iterator begin() const;
  const_iterator end() const;
  iterator begin();
  iterator end();

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void clear() noexcept;
  void erase(iterator pos);
  void push_back(const_reference value);
  void push_front(const_reference value);
  void pop_front();
  void pop_back();

  void reverse();
  void swap(list &other);
  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void unique();
  void sort();

  iterator insert(iterator pos, const_reference value);
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);
  template <typename... Args>
  void insert_many_front(Args &&...args);

 private:
  struct Node {
    value_type value;
    Node *next = nullptr;
    Node *prev = nullptr;
    Node(value_type val = value_type(), Node *next_ = nullptr,
         Node *prev_ = nullptr)
        : value(val), next(next_), prev(prev_) {}
  };

  struct List {
    size_type size_list = 0;
    Node *head = nullptr;
    Node *tail = nullptr;
  };

  List list_;
};
template <typename T>
class list<T>::ListIterator {
  friend class list<T>;

 public:
  using iterator = ListIterator;
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using pointer = T *;
  using reference = T &;

  ListIterator(typename list<T>::Node *node_ = nullptr,
               typename list<T>::Node *last_node_ = nullptr)
      : node(node_), last_node(last_node_) {};

  ListIterator(const list<T>::Node *node_) : node(node_) {}

  iterator &operator++();
  iterator operator++(int);
  iterator &operator--();
  iterator operator--(int);
  bool operator==(const iterator &other) const;
  bool operator!=(const iterator &other) const;
  reference operator*() const;

 protected:
  list<T>::Node *node;
  list<T>::Node *last_node;
};
}  // namespace s21

#include "s21_list.tpp"
