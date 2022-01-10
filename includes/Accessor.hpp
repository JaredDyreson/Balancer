#pragma once

#include "pending_node_queue.hpp"

class Accessor {
  /*
   * Provides an interface to reorder
   * the queue based on event
   */
	public:
		void reorderQueue(pending_node_queue);
};
