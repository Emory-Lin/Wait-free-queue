#include <atomic>
#include <mutex>          // std::mutex

using namespace std;
void show_queue();
std::mutex mtx;           // mutex for critical section

class qnode
{
public:
	int value;
	qnode *next;
	qnode(int val)
	{
		this->value = val;
		this->next = nullptr;
	}
};

class NewQueue
{
public:
	atomic<qnode *> head;
	atomic<qnode *> tail;
	NewQueue()
	{
		head = nullptr;
		tail = nullptr;
	}
};
NewQueue *q;
void enqueue(int val)
{
	qnode *node = new qnode(val);
	// qnode * predecessor = fetch_and_store(q -> tail, node);
	qnode *predecessor = q -> tail.exchange(node);
	if (predecessor != nullptr)
		predecessor->next = node;
	else
	{
		q->head = node;
	}
}

qnode *dequeue_wait_free()
{
	qnode *old;
	old = q->head;
	// if queue is empty, we directly return nullptr
	if (old == nullptr)
	{
		// cout << "OMG, the head is NULL, so we must return NULL" << endl;
		return nullptr;
	}
	qnode * next = old -> next; 
	// if next is not nullptr, we can be sure that old is not the only node left, we directly return old
	if (next != nullptr)
	{
		q -> head = next; 
		return old;
	}
	// otherwise, old is the only node left
	if (q->tail == old)
	{
		// if q -> tail equals with old, we would assign nullptr to head and return old
		if (q->tail.compare_exchange_strong(old, nullptr) == true)
		{
			return old;
		}
	}
	// it means that other nodes enqueue at the same time, we directly return nullptr and dequeue next time
	return nullptr;
}

qnode *dequeue_blocking()
{
	qnode *old;
	old = q->head;
	// if queue is empty, we directly return nullptr
	if (old == nullptr)
	{
		// cout << "OMG, the head is NULL, so we must return NULL" << endl;
		return nullptr;
	}
	qnode * next = old -> next; 
	// if next is not nullptr, we can be sure that old is not the only node left, we directly return old
	if (next != nullptr)
	{
		q -> head = next; 
		return old;
	}
	// otherwise, old is the only node left
	if (q->tail == old)
	{
		// if q -> tail equals with old, we would assign nullptr to head and return old
		if (q->tail.compare_exchange_strong(old, nullptr) == true)
		{
			return old;
		}
	}
	// it means that other nodes enqueue at the same time, we wait until other nodes finish linking 
	while (1)
	{
		qnode * result = dequeue_wait_free();
		if(result != nullptr)
			return result; 
	}
}

void show_queue()
{
	qnode *temp = q->head;
	int number = 0;
	while (temp)
	{
		number++;
		cout << temp->value << "->";
		temp = temp->next;
	}
	cout << endl;
	cout << "we have total " << number << " items in the queue" << endl;
}