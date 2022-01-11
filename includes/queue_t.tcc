#include <algorithm>
#include <chrono>

namespace extended_queue {
template <typename U>

bool extended_queue::queue_t<U>::conditional_add(U element,
                                                 timestamp_type timestamp) {
    auto contains_element = [&element](auto& x) { return element == x; };

    auto i =
        std::find_if(std::begin(this->c), std::end(this->c), contains_element);

    if (i == std::end(this->c)) {
        // If there is not an element in the container
        this->push(std::move(element));
        return true;
    } else {
        if (timestamp < i->timestamp) {
            i->timestamp = std::move(timestamp);
            reorder();
            return true;
        }
    }
    return false;
}

template <typename U>
void extended_queue::queue_t<U>::reorder() {
    std::make_heap(std::begin(this->c), std::end(this->c), this->comp);
}

};  // namespace extended_queue
