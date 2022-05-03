#include <atomic>
#include <mutex> // std::mutex

using namespace std;
void show_queue();
std::mutex mtx; // mutex for critical section
int count = 0;

class qnode
{
public:
	int value;
	atomic<qnode *> next;
	qnode(int val)
	{
		this->value = val;
		this->next = nullptr;
	}
};

class WaitFreeQueue
{
public:
	atomic<qnode *> head;
	atomic<qnode *> tail;
	WaitFreeQueue()
	{
		head = nullptr;
		tail = nullptr;
	}
};
void enqueue(WaitFreeQueue *q, int val)
{
	qnode *node = new qnode(val);
	// qnode * predecessor = fetch_and_store(q -> tail, node);
	qnode *predecessor = q->tail.exchange(node, memory_order_relaxed);
	if (predecessor != nullptr)
		predecessor->next = node;
	else
	{
		q->head = node;
	}
}

qnode *dequeue_wait_free(WaitFreeQueue *q)
{
	qnode *old;
	old = q->head;
	// if queue is empty, we directly return nullptr
	if (old == nullptr)
	{
		// cout << "OMG, the head is NULL, so we must return NULL" << endl;
		return nullptr;
	}
	qnode *next = old->next;
	// if next is not nullptr, we can be sure that old is not the only node left, we directly return old
	if (next != nullptr)
	{
		q->head = next;
		return old;
	}
	// otherwise, old is the only node left
	if (q->tail == old)
	{
		// if q -> tail equals with old, we would assign nullptr to head and return old
		if (q->tail.compare_exchange_weak(old, nullptr, std::memory_order_release, std:: memory_order_relaxed) == true)
		{
			return old;
		}
	}
	// it means that other nodes enqueue at the same time, we directly return nullptr and dequeue next time
	return nullptr;
}

qnode *dequeue_blocking(WaitFreeQueue *q)
{
	qnode *old;
	old = q->head;
	// if queue is empty, we directly return nullptr
	if (old == nullptr)
	{
		// cout << "OMG, the head is NULL, so we must return NULL" << endl;
		return nullptr;
	}
	qnode *next = old->next;
	// if next is not nullptr, we can be sure that old is not the only node left, we directly return old
	if (next != nullptr)
	{
		q->head = next;
		return old;
	}
	// otherwise, old is the only node left
	if (q->tail == old)
	{
		// if q -> tail equals with old, we would assign nullptr to head and return old
		if (q->tail.compare_exchange_strong(old, nullptr, std::memory_order_release, std:: memory_order_relaxed) == true)
		{
			return old;
		}
	}
	// it means that other nodes enqueue at the same time, we wait until other nodes finish linking
	while (1)
	{
		qnode *result = dequeue_wait_free(q);
		if (result != nullptr)
			return result;
	}
}
