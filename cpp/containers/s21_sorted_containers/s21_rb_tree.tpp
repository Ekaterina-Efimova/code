#define MY_BRO_HAS_RED_SON                   \
  ((my_bro->left && my_bro->left->is_red) || \
   (my_bro->right && my_bro->right->is_red))

#define RED_GOES_UP         \
  grand_parent->is_red = 1; \
  parent->is_red = 0;       \
  uncle->is_red = 0;

namespace s21 {

template <typename T>
typename sorted_container<T>::Node *sorted_container<T>::rb_tree::copy_node(
    Node *node) {
  Node *new_node = new Node(node->data);
  new_node->is_red = node->is_red;

  if (node->left) {
    new_node->left = copy_node(node->left);
    new_node->left->parent = new_node;
  }

  if (node->right) {
    new_node->right = copy_node(node->right);
    new_node->right->parent = new_node;
  }

  return new_node;
}

template <typename T>
void sorted_container<T>::rb_tree::remove_node(Node *target) {
  Node *target_parent = target->parent;
  Node *placeholder = nullptr;
  if (target->left && target->right) {
    placeholder = target->left;
    while (placeholder->right != nullptr) {
      placeholder = placeholder->right;
    }
  } else if (target->left == nullptr && target->right == nullptr) {
    placeholder = nullptr;
  } else {
    placeholder = (target->left) ? target->left : target->right;
  }

  if (placeholder == nullptr) {
    if (target == root) {
      root = nullptr;

    } else {
      if (target->is_red == 0) {
        fix_2_black(target);
      }

      if (target_parent && target == target_parent->left) {
        target_parent->left = nullptr;
      } else if (target_parent) {
        target_parent->right = nullptr;
      }
    }
    delete target;

  } else {
    bool need_fix = 0;
    if (placeholder->is_red == 0) {
      if (placeholder->left) {
        if (placeholder->left->is_red) {
          placeholder->left->is_red = 0;
        } else {
          need_fix = 1;
        }
      } else {
        fix_2_black(placeholder);
      }
    }

    Node *ph_parent = placeholder->parent;
    if (ph_parent->left == placeholder) {
      ph_parent->left = placeholder->left;
    } else {
      ph_parent->right = placeholder->left;
    }
    if (placeholder->left) placeholder->left->parent = ph_parent;

    if (need_fix) fix_2_red(placeholder->left);

    target->data = placeholder->data;
    delete placeholder;
  }
}

template <typename T>
void sorted_container<T>::rb_tree::delete_tree(Node *node) {
  if (node) {
    delete_tree(node->left);
    delete_tree(node->right);

    delete node;
  }
}

template <typename T>
void sorted_container<T>::rb_tree::rotate_left(Node *&node) {
  Node *right_child = node->right;
  node->right = right_child->left;

  if (node->right) {
    node->right->parent = node;
  }

  right_child->parent = node->parent;

  if (node->parent == nullptr) {
    root = right_child;
  } else if (node == node->parent->left) {
    node->parent->left = right_child;
  } else {
    node->parent->right = right_child;
  }

  right_child->left = node;
  node->parent = right_child;
}

template <typename T>
void sorted_container<T>::rb_tree::rotate_right(Node *&node) {
  Node *left_child = node->left;
  node->left = left_child->right;

  if (node->left) {
    node->left->parent = node;
  }

  left_child->parent = node->parent;

  if (node->parent == nullptr) {
    root = left_child;
  } else if (node == node->parent->left) {
    node->parent->left = left_child;
  } else {
    node->parent->right = left_child;
  }

  left_child->right = node;
  node->parent = left_child;
}

template <typename T>
void sorted_container<T>::rb_tree::fix_2_red(Node *&node) {
  while ((node != root) && (node->is_red) && (node->parent->is_red)) {
    Node *parent = node->parent;
    Node *grand_parent = node->parent->parent;

    if (parent == grand_parent->left) {
      Node *uncle = grand_parent->right;

      if ((uncle) && (uncle->is_red)) {
        RED_GOES_UP;
        node = grand_parent;

      } else {
        if (node == parent->right) {
          rotate_left(parent);
          node = parent;
          parent = node->parent;
        }
        rotate_right(grand_parent);
        std::swap(parent->is_red, grand_parent->is_red);
        node = parent;
      }

    } else {
      Node *uncle = grand_parent->left;
      if ((uncle) && (uncle->is_red)) {
        RED_GOES_UP;
        node = grand_parent;

      } else {
        if (node == parent->left) {
          rotate_right(parent);
          node = parent;
          parent = node->parent;
        }
        rotate_left(grand_parent);
        std::swap(parent->is_red, grand_parent->is_red);
        node = parent;
      }
    }
  }

  root->is_red = 0;
}
template <typename T>

void sorted_container<T>::rb_tree::fix_2_black(Node *&node) {
  if (node == root) return;

  Node *parent = node->parent;
  bool left_child = (node == parent->left);
  Node *my_bro = (left_child) ? parent->right : parent->left;

  if (my_bro->is_red) {
    parent->is_red = 1;
    my_bro->is_red = 0;

    if (left_child) {
      rotate_left(parent);
    } else {
      rotate_right(parent);
    }
    fix_2_black(node);

  } else if MY_BRO_HAS_RED_SON {
    if (my_bro->left && my_bro->left->is_red) {
      if (left_child) {
        std::swap(my_bro->left->is_red, my_bro->is_red);
        rotate_right(my_bro);
        fix_2_black(node);
      } else {
        my_bro->left->is_red = my_bro->is_red;
        my_bro->is_red = parent->is_red;
        rotate_right(parent);
      }
    } else {
      if (left_child) {
        my_bro->right->is_red = my_bro->is_red;
        my_bro->is_red = parent->is_red;
        rotate_left(parent);
      } else {
        std::swap(my_bro->right->is_red, my_bro->is_red);
        rotate_left(my_bro);
        fix_2_black(node);
      }
    }
    parent->is_red = 0;

  } else {
    my_bro->is_red = 1;
    if (parent->is_red == 0)
      fix_2_black(parent);
    else
      parent->is_red = 0;
  }
}

template <typename T>
std::size_t sorted_container<T>::rb_tree::count_elements(Node *node,
                                                         const T &data) const {
  std::size_t result = 0;
  if (node->data == data) result++;

  if (node->data >= data && node->left) {
    result += count_elements(node->left, data);
  }

  if (node->data <= data && node->right) {
    result += count_elements(node->right, data);
  }

  return result;
}

template <typename T>
pair<typename sorted_container<T>::Node *, typename sorted_container<T>::Node *>
sorted_container<T>::rb_tree::element_range(Node *node, const T &data) {
  pair<Node *, Node *> range = {nullptr, nullptr};
  if (node->data >= data && node->left) {
    if (node->data == data) {
      range.first = element_range(node->left, data).first;
    } else {
      range = element_range(node->left, data);
    }
  }

  if (node->data <= data && node->right) {
    if (range.first || node->data == data) {
      range.second = element_range(node->right, data).second;
    } else {
      range = element_range(node->right, data);
    }
  }

  if (range.first == nullptr) {
    range.first = ((node->data == data) ? node : range.second);
  }

  if (range.second == nullptr) {
    range.second = ((node->data == data) ? node : range.first);
  }

  return range;
}

template <typename T>
void sorted_container<T>::rb_tree::copy_tree(const rb_tree *other) {
  root = ((other->root) ? copy_node(other->root) : nullptr);
}

template <typename T>
typename sorted_container<T>::Node *sorted_container<T>::rb_tree::insert(
    const T &data) {
  Node *new_node = new Node(data);
  Node *current = root;
  Node *parent = nullptr;

  while (current != nullptr) {
    parent = current;
    current = ((data < current->data) ? current->left : current->right);
  }

  new_node->parent = parent;

  if (parent == nullptr) {
    root = new_node;
  } else if (data < parent->data) {
    parent->left = new_node;
  } else {
    parent->right = new_node;
  }

  fix_2_red(new_node);

  return new_node;
}

template <typename T>
void sorted_container<T>::rb_tree::remove(const T &data) {
  if (Node *target = search(data)) remove_node(target);
}

template <typename T>
typename sorted_container<T>::Node *sorted_container<T>::rb_tree::min() const {
  Node *current = root;
  if (current)
    while (current->left) current = current->left;

  return current;
}

template <typename T>
typename sorted_container<T>::Node *sorted_container<T>::rb_tree::search(
    const T &data) const {
  Node *temp = root;

  while (temp != nullptr && temp->data != data) {
    temp = ((data < temp->data) ? temp->left : temp->right);
  }

  return temp;
}

template <typename T>
std::size_t sorted_container<T>::rb_tree::count(const T &data) const {
  Node *target = search(data);

  return ((target) ? count_elements(target, data) : 0);
}

template <typename T>
pair<typename sorted_container<T>::Node *, typename sorted_container<T>::Node *>
sorted_container<T>::rb_tree::equal_range(const T &data) {
  pair<Node *, Node *> range;
  Node *target = search(data);

  if (target) range = element_range(target, data);

  return range;
}

}  // namespace s21
