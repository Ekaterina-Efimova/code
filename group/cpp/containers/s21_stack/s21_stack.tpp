namespace s21 {

/**
 * Удаляет последний элемент в контейнере
 */
template <typename T1, typename T2>
void stack<T1, T2>::pop() {
  _Get_container().pop_back();
}

/**
 * Добавляет элемент в контейнер
 * @param value значение, которое нужно добавить
 */
template <typename T1, typename T2>
void stack<T1, T2>::push(const T1 &value) {
  _Get_container().push_back(value);
}

/**
 * Указывает на последний элемент в контейнере
 * @return ссылка на последний элемент в контейнере
 */
template <typename T1, typename T2>
typename stack<T1, T2>::const_reference stack<T1, T2>::top() const {
  return _Get_container().back();
}

/**
 * Проверяет контейнер на пустоту
 * @return true - если контейнер пуст, false - если контейнер не пуст
 */
template <typename T1, typename T2>
bool stack<T1, T2>::empty() const {
  return _Get_container().empty();
}

/**
 * Возвращает размер контейнера
 * @return размер контейнера
 */
template <typename T1, typename T2>
typename stack<T1, T2>::size_type stack<T1, T2>::size() const {
  return _Get_container().size();
}

/**
 * Возвращает ссылку на контейнер
 * @return тип контейнера
 */
template <typename T1, typename T2>
typename stack<T1, T2>::container_type &stack<T1, T2>::_Get_container() {
  return *this;
}

/**
 * Возвращает const ссылку на контейнер
 * @return тип контейнера
 */
template <typename T1, typename T2>
const typename stack<T1, T2>::container_type &stack<T1, T2>::_Get_container()
    const {
  return *this;
}

/**
 * Добавляет новые элементы в верхнюю часть контейнера
 * @param args - переменное число аргументов
 */
template <typename T1, typename T2>
template <typename... Args>
void stack<T1, T2>::insert_many_front(Args &&...args) {
  _Get_container().insert_many_front(std::forward<Args>(args)...);
}

}  // namespace s21