#include <atomic>
using namespace std;

class Treiber
{
public:
	atomic<qnode *> head;
	atomic<qnode *> tail;
	Treiber()
	{
		head = nullptr;
		tail = nullptr;
	}
};

void TreiberEnqueue(Treiber* t, int val)
{
	qnode * newHead = new qnode(val);
	qnode* oldHead;
	do
	{
		oldHead = t -> head;	
		newHead -> next = oldHead; 
	} while (t -> head.compare_exchange_weak(oldHead, newHead, std::memory_order_release, std::memory_order_relaxed) == false);
}

qnode *TreiberDequeue(Treiber* t)
{
	qnode *oldHead, *newHead;
	do
	{
		oldHead = t -> head;
		if(oldHead == nullptr)
			return nullptr;
		newHead = oldHead -> next;
	} while (t -> head.compare_exchange_weak(oldHead, newHead, std::memory_order_release, std::memory_order_relaxed) == false);
	// cout << "Dequeu number is " << oldHead -> value << endl; 
	return oldHead;
}


