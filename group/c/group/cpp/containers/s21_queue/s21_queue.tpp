namespace s21 {

/**
 * Удаляет первый элемент в контейнере
 */
template <typename T1, typename T2>
void queue<T1, T2>::pop() {
  _Get_container().erase(_Get_container().begin());
}

/**
 * Добавляет элемент в контейнер
 * @param value значение, которое нужно добавить
 */
template <typename T1, typename T2>
void queue<T1, T2>::push(const T1 &value) {
  _Get_container().push_back(value);
}

/**
 * Указывает на первый элемент в контейнере
 * @return ссылка на последний элемент в контейнере
 */
template <typename T1, typename T2>
typename queue<T1, T2>::const_reference queue<T1, T2>::front() const {
  return _Get_container().front();
}

/**
 * Указывает на последний элемент в контейнере
 * @return ссылка на последний элемент в контейнере
 */
template <typename T1, typename T2>
typename queue<T1, T2>::const_reference queue<T1, T2>::back() const {
  return _Get_container().back();
}

/**
 * Проверяет контейнер на пустоту
 * @return true - если контейнер пуст, false - если контейнер не пуст
 */
template <typename T1, typename T2>
bool queue<T1, T2>::empty() const {
  return _Get_container().empty();
}

/**
 * Возвращает размер контейнера
 * @return размер контейнера
 */
template <typename T1, typename T2>
typename queue<T1, T2>::size_type queue<T1, T2>::size() const {
  return _Get_container().size();
}

/**
 * Возвращает ссылку на контейнер
 * @return тип контейнера
 */
template <typename T1, typename T2>
typename queue<T1, T2>::container_type &queue<T1, T2>::_Get_container() {
  return *this;
}

/**
 * Возвращает const ссылку на контейнер
 * @return тип контейнера
 */
template <typename T1, typename T2>
const typename queue<T1, T2>::container_type &queue<T1, T2>::_Get_container()
    const {
  return *this;
}

/**
 * Меняет местами содержимое текущего и другого объекта
 * @param other - ссылка на другой объект
 */
template <typename T1, typename T2>
void queue<T1, T2>::swap(queue &other) {
  _Get_container().swap(other._Get_container());
}

/**
 * Добавляет новые элементы в конец контейнера.
 * @param args - переменное число аргументов
 */
template <typename T1, typename T2>
template <typename... Args>
void queue<T1, T2>::insert_many_back(Args &&...args) {
  _Get_container().insert_many_back(std::forward<Args>(args)...);
}

}  // namespace s21