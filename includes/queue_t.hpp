#pragma once
#include <chrono>
#include <queue>
#include <string>
#include <vector>

// struct node {
// std::string topic;
// int timestamp;

// bool operator>(const node& other) const;
//};

//// FIXME
// bool node::operator>(const node& other) const {
// return this->timestamp > other.timestamp;
//}

namespace extended_queue {

  using timestamp_clock = std::chrono::system_clock;
  using timestamp_type = timestamp_clock::time_point;

  struct comparator {
    /*
     * Predicate that ensures all elements in
     * the queue are properly sorted
     */

    template <class A>
    bool operator()(const A& lhs, const A& rhs) const {
      return lhs > rhs;
    }
  };

  template <class T>
  struct queue_t_traits {
    using container_type = std::vector<T>;
    using predicate_type = comparator;
    using type = std::priority_queue<T, container_type, predicate_type>;
  };

  template <class T>
  class queue_t : private queue_t_traits<T>::type {
    using traits_type = queue_t_traits<T>;
    using base_class = typename traits_type::
        type;  // http://www.cplusplus.com/forum/general/224845/

   public:
    // export the constructor
    using base_class::base_class;

    // and any other members our clients will need
    using base_class::pop;
    using base_class::size;
    using base_class::top;

    bool conditional_add(T, timestamp_type timestamp);

    friend class Accessor;

   private:
    void reorder();
  };
};  // namespace extended_queue

#include "queue_t.tcc"
