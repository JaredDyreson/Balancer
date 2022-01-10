#include <chrono>
#include <queue>
#include <string>
#include <vector>

using timestamp_clock = std::chrono::system_clock;
using timestamp_type = timestamp_clock::time_point;

struct node {
  std::string topic;
  int timestamp;

  bool operator>(const node& other) const;
};

// FIXME
bool node::operator>(const node& other) const {
  return this->timestamp > other.timestamp;
}

struct comparator {
  /*
   * Predicate that ensures all elements in
   * the queue are properly sorted
   */

  template <class A, class B>
  bool operator()(const A& lhs, const B& rhs) {
    return lhs > rhs;
  }
};

template <class T>
struct queue_t_traits;

template <>
struct queue_t_traits<node> {
  using container_type = std::vector<node>;
  using predicate_type = comparator;
  using type = std::priority_queue<node, container_type, predicate_type>;
};

class pending_node_queue : private queue_t_traits<node>::type {
  using traits_type = queue_t_traits<node>;
  using base_class = traits_type::type;

 public:
  // export the constructor
  using base_class::base_class;

  // and any other members our clients will need
  using base_class::pop;
  using base_class::size;
  using base_class::top;

  bool conditional_add(node _node,
                       timestamp_type timestamp = timestamp_clock::now());

  friend class Accessor;

 private:
  void reorder();
};
