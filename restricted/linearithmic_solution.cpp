#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <vector>
#include <string>

using timestamp_clock = std::chrono::system_clock;
using timestamp_type = timestamp_clock::time_point;

struct node {
  std::string name;
  timestamp_type timestamp;
};

template <typename T>
class accessor_t;

template <typename T>
class queue_t {
 public:
  queue_t();
  queue_t(std::vector<T>);
  void pop();
  T top() const;

  typename std::vector<T>::iterator begin();
  typename std::vector<T>::const_iterator begin() const;

  typename std::vector<T>::iterator end();
  typename std::vector<T>::const_iterator end() const;

  size_t size() const;
  bool empty() const;
  friend accessor_t<T>;

 private:
  std::vector<T> container;
  void reorder();
};

// BEGIN QUEUE_T

template <typename T>
queue_t<T>::queue_t() {
  this->container = std::vector<T>();
}

template <typename T>
queue_t<T>::queue_t(std::vector<T> _vector) {
  this->container = _vector;
}
template <typename T>
void queue_t<T>::pop() {
  this->container.pop_back();
}
template <typename T>
T queue_t<T>::top() const {
  return this->container.front();
}

template <typename T>
bool queue_t<T>::empty() const {
  return this->container.empty();
}

template <typename T>
size_t queue_t<T>::size() const {
  return this->container.size();
}

template <typename T>
typename std::vector<T>::iterator queue_t<T>::begin() {
  return this->container.begin();
}

template <typename T>
typename std::vector<T>::const_iterator queue_t<T>::begin() const {
  return this->container.begin();
}

template <typename T>
typename std::vector<T>::iterator queue_t<T>::end() {
  return this->container.end();
}

template <typename T>
typename std::vector<T>::const_iterator queue_t<T>::end() const {
  return this->container.end();
}

// END QUEUE_T

template <typename T>
class accessor_t {
 public:
  accessor_t(queue_t<T>);
  void reorder();

  queue_t<T> _queue;
 private:
};

template <typename T>
accessor_t<T>::accessor_t(queue_t<T> _q) {
  this->_queue = std::move(_q);
}

template <typename T>
void accessor_t<T>::reorder() {
	std::sort(this->_queue.begin(), this->_queue.end(), std::greater<int>());
  //std::sort(this->_queue.begin(), this->_queue.end());
}

int main() {
  // std::vector<int> my_vector = {1, 2, 3};
  queue_t<int> _queue = queue_t<int>({1, 2, 3});
  accessor_t<int> access = accessor_t<int>(_queue);

  for (auto& element : access._queue) {
    std::cout << element << std::endl;
  }
  access.reorder();

  for (auto& element : access._queue) {
    std::cout << element << std::endl;
  }
  return 0;
}

