#pragma once

#include "pending_node_queue.hpp"

class accessor_t {
  /*
   * Provides an interface to reorder
   * the queue based on an event
   */

	public:
		accessor_t(pending_node_queue);
		void reorderQueue(pending_node_queue);
		bool isQueueEmpty() const;
		void interceptRequest(); // TODO

	private:
		inline static pending_node_queue _queue;
};
