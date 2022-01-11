#include <chrono>
#include <cassert>
#include <iostream>
#include <thread>

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

  bool operator>(const node& other) const {
    return this->timestamp > other.timestamp;
  }

	bool operator==(const node& other) {
				return (this->name == other.name && this->timestamp == other.timestamp);
	}
};

int main() { 
	using namespace std::literals;

	extended_queue::queue_t<node> element = extended_queue::queue_t<node>();
	auto now = timestamp_clock::now();

	struct node my_node = node("bar.baz", now);
	struct node other_node = node("foo.bar", now + 1000ms);
	struct node last_node = node("foo.bar", now + 2000ms);
	struct node duplicate_last_node = node("foo.bar", now - 2000ms);

	element.conditional_add(my_node, now);
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	element.conditional_add(other_node, now + 1000ms);
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	element.conditional_add(last_node, now + 2000ms);
	element.conditional_add(duplicate_last_node, now - 2000ms);

	std::cout << element.size() << std::endl;

	assert(element.size() == 2);
	assert(element.top().name == "foo.bar");

	return 0; 
}
