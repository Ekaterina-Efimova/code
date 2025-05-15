#ifndef S21_VECTOR_H_
#define S21_VECTOR_H_

#include <initializer_list>
#include <limits>
#include <memory>

namespace s21 {

template <typename T>
class v_iterator {
 public:
  using value_type = T;
  using reference = T&;
  using iterator = v_iterator;
  using size_type = size_t;

  v_iterator(value_type* ptr);

  reference operator*() const;

  iterator& operator++();
  iterator operator++(int);
  iterator& operator--();
  iterator operator--(int);
  iterator& operator+=(const int n);
  iterator operator+(const int n);
  iterator& operator-=(const int n);
  iterator operator-(const int n);
  size_type operator-(iterator other);

  bool operator==(const iterator& other) const;
  bool operator!=(const iterator& other) const;
  bool operator<(const iterator& other) const;
  bool operator>(const iterator& other) const;
  bool operator<=(const iterator& other) const;
  bool operator>=(const iterator& other) const;

 private:
  value_type* iter;
};

template <typename T>
class v_const_iterator {
 public:
  using value_type = T;
  using const_reference = const T&;
  using const_iterator = v_const_iterator;
  using size_type = size_t;

  v_const_iterator(const value_type* ptr);

  const_reference operator*() const;

  const_iterator& operator++();
  const_iterator operator++(int);
  const_iterator& operator--();
  const_iterator operator--(int);
  const_iterator operator+(const int n) const;
  const_iterator operator-(const int n) const;
  size_type operator-(const const_iterator other);

  bool operator==(const const_iterator& other) const;
  bool operator!=(const const_iterator& other) const;
  bool operator<(const const_iterator& other) const;
  bool operator>(const const_iterator& other) const;
  bool operator<=(const const_iterator& other) const;
  bool operator>=(const const_iterator& other) const;

 private:
  const value_type* iter;
};

template <typename T>
class vector {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = v_iterator<T>;
  using const_iterator = v_const_iterator<T>;
  using size_type = size_t;

  vector();                      // default constructor
  explicit vector(size_type n);  // parametrized constructor
  vector(std::initializer_list<value_type> const& items);  // initializer list
  vector(const vector& v);                                 // copy constructor
  vector(vector&& v) noexcept;                             // move constructor
  ~vector();                                               // destructor

  // operator overload method
  vector& operator=(vector&& v) noexcept;

  // access methods
  reference at(size_type pos);
  const_reference at(size_type pos) const;
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  const_reference front() const;
  const_reference back() const;
  iterator data() noexcept;

  // iterator methods
  iterator begin();
  const_iterator cbegin() const;
  iterator end();
  const_iterator cend() const;

  // capacity methods
  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  void reserve(size_type size);
  size_type capacity() const;
  void shrink_to_fit();

  // modifier methods
  void clear() noexcept;
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector& other);

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);
  template <typename... Args>
  void insert_many_back(Args&&... args);

 private:
  size_type size_;
  size_type capacity_;
  value_type* data_;

  void reallocate(size_type size);
};
}  // namespace s21

#include "s21_vector.tpp"

#endif