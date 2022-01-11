template <typename T>
access::accessor_t<T>::accessor_t(extended_queue::queue_t<T> _queue) {
	this->myQueue = _queue;
}


template <typename T>
bool access::accessor_t<T>::isQueueEmpty() const {
	return this->myQueue.empty();
}
