#pragma once

#include "queue_t.hpp"

namespace access {

template <typename T>
class accessor_t {
  /*
   * Provides an interface to reorder
   * the queue based on an event
   */

 public:
  accessor_t(extended_queue::queue_t<T>);
  static void reorderQueue() { _queue.reorder(); }
  bool isQueueEmpty() const;
  void interceptRequest();  // TODO

 private:
  inline static extended_queue::queue_t<T> _queue;
};
};  // namespace access
#include "accessor_t.tcc"
