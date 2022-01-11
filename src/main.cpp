#include <chrono>

#include "../includes/accessor_t.hpp"
#include "../includes/queue_t.hpp"

using timestamp_clock = std::chrono::system_clock;
using timestamp_type = timestamp_clock::time_point;

struct node {
	node(std::string _name, timestamp_type _timestamp) {
		this->name = _name;
		this->timestamp = _timestamp;
	}
  std::string name;
  timestamp_type timestamp;

  bool operator>(const node& other) {
    return this->timestamp > other.timestamp;
  }

	bool operator==(const node& other) {
				return (this->name == other.name && this->timestamp == other.timestamp);
	}
};

int main() { 
	extended_queue::queue_t<node> element = extended_queue::queue_t<node>();
	auto now = timestamp_clock::now();
	struct node my_node = node("bar.baz", now);
	element.conditional_add(my_node, now);

	return 0; 
}
