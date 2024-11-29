#pragma once

#include "../s21_pair.hpp"

namespace s21 {

template <typename T>
class sorted_container {
 public:
  struct Node {
    T data;
    Node *left, *right, *parent;
    bool is_red;  // поменять на int black?

    Node(T data = 0)
        : data(data),
          left(nullptr),
          right(nullptr),
          parent(nullptr),
          is_red(true) {}
  };

  class iterator {
   private:
    using value_type = T;
    using pointer = T *;
    using reference = T &;

    Node *node_;

    Node *next_node(Node *node) const;

   public:
    iterator() : node_(nullptr) {};
    iterator(Node *node) : node_(node) {};
    ~iterator() {};

    bool operator==(const iterator &s) const { return (node_ == s.node_); };
    bool operator!=(const iterator &s) const { return (node_ != s.node_); };
    reference operator*() const { return node_->data; };
    iterator &operator++() {
      node_ = next_node(node_);
      return *this;
    };
  };

  /**
   * @brief Класс, представляющий красно-черное дерево для реализации
   * упорядоченного контейнера.
   *
   * @tparam T Тип данных, которые хранятся в узлах дерева.
   */
  class rb_tree {
   private:
    /// Корень дерева.
    Node *root;

    Node *copy_node(Node *);
    void remove_node(Node *);
    void delete_tree(Node *);
    void rotate_left(Node *&);
    void rotate_right(Node *&);

    void fix_2_red(Node *&);
    void fix_2_black(Node *&);
    std::size_t count_elements(Node *node, const T &data) const;
    pair<Node *, Node *> element_range(Node *node, const T &data);

   public:
    rb_tree() : root(nullptr) {}
    rb_tree(const rb_tree *other) { copy_tree(other); }
    ~rb_tree() { delete_tree(); }

    void delete_tree() { delete_tree(root), root = nullptr; }

    void copy_tree(const rb_tree *);
    Node *insert(const T &);
    void remove(const T &);
    Node *min() const;
    Node *search(const T &) const;
    bool empty() const { return (this == nullptr) || root == nullptr; };

    std::size_t count(const T &) const;
    pair<Node *, Node *> equal_range(const T &);
    iterator make_iterator(Node *node) { return iterator(node); }
  };

  virtual size_t size() const = 0;
  virtual bool empty() const = 0;
};

template <typename T>
typename sorted_container<T>::Node *sorted_container<T>::iterator::next_node(
    sorted_container<T>::Node *node) const {
  if (node == nullptr) return nullptr;

  Node *next = nullptr;

  if (node->right) {
    next = node->right;
    while (next->left) next = next->left;

  } else {
    next = node->parent;
    while (next && node == next->right) {
      node = next;
      next = next->parent;
    }
  }

  return next;
};

}  // namespace s21

#include "s21_rb_tree.tpp"
