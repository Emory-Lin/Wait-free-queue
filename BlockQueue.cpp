#include <atomic>
#include <mutex>
using namespace std;
void show_queue_block();
class Block
{
public:
    qnode * head;
	qnode * tail;
	Block()
	{
		head = nullptr;
		tail = nullptr;
	}
};
Block * b;

void BlockEnqueue(int val)
{
	qnode * node = new qnode(val);
    mtx.lock();
    if(b -> head == nullptr)
    {
        b -> head = node;
        b -> tail = node;
    }
    else
    {
        b -> tail -> next = node; 
        b -> tail = node;
    }
    mtx.unlock();
}

qnode *BlockDequeue()
{
    mtx.lock();
    if(b -> head == nullptr)
    {
        mtx.unlock();
        return nullptr;
    }
    qnode* result = b -> head;
    if(result -> next == nullptr)
        b -> tail = nullptr;
    b -> head = result -> next; 
    mtx.unlock();
    return result; 
}
void show_queue_block()
{
	qnode *temp = b -> head;
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


