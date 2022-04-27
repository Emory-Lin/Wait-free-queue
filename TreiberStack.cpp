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
Treiber * t;

void TreiberEnqueue(int val)
{
	qnode * newHead = new qnode(val);
	qnode* oldHead;
	do
	{
		oldHead = t -> head;	
		newHead -> next = oldHead; 
	} while (t -> head.compare_exchange_strong(oldHead, newHead) == false);
}

qnode *TreiberDequeue()
{
	qnode *oldHead, *newHead;
	do
	{
		oldHead = t -> head;
		if(oldHead == nullptr)
			return nullptr;
		newHead = oldHead -> next;
	} while (t -> head.compare_exchange_strong(oldHead, newHead) == false);
	// cout << "Dequeu number is " << oldHead -> value << endl; 
	return oldHead;
}

void show_treiber()
{
	qnode *temp = t -> head;
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

