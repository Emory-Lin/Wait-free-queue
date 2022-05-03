#include <atomic>

using namespace std;

class msnode; 
class pointer
{
    public:
        msnode * ptr;
        int count;
    pointer(msnode* temp, int cnt)
    {
        ptr = temp;
        count = cnt;
    }
};
class msnode
{
public:
	int value;
    atomic<pointer*> next;
	msnode(int val)
	{
		this->value = val;
		this->next = new pointer(nullptr, -1);
	}
};
 
class MSQueue
{
public:
	atomic<pointer*> head;
	atomic<pointer*> tail;
	MSQueue()
	{
		head = nullptr;
		tail = nullptr;
	}
};
void MSEnqueue(MSQueue* M, int val)
{
	msnode * node = new msnode(val);
    pointer * oldtail; 

	while(1)
	{
        oldtail = M -> tail;
        pointer* nxt = oldtail -> ptr -> next;
        if(oldtail == M -> tail)
        {
            if(nxt -> ptr == nullptr)
            {
                if(oldtail -> ptr -> next.compare_exchange_strong(nxt, new pointer(node, nxt -> count + 1), std::memory_order_release, std::memory_order_relaxed) == true)
                    break; 
            }
            else
                M -> tail.compare_exchange_strong(oldtail, new pointer(nxt -> ptr, oldtail -> count + 1), std::memory_order_release, std::memory_order_relaxed);
        }
	} 
    M -> tail.compare_exchange_strong(oldtail, new pointer(node, oldtail -> count + 1), std::memory_order_release, std::memory_order_relaxed); 
}

msnode * MSDequeue(MSQueue* M, int& result)
{
    pointer * oldhead, *oldtail, *nxt; 
	while(1)
	{
        oldhead = M -> head;
        oldtail = M -> tail;
        nxt = oldhead -> ptr -> next;
        if(oldhead == M -> head)
        {
            if(oldhead -> ptr == oldtail -> ptr)
            {
                if(nxt -> ptr == nullptr)
                    return nullptr;
                M -> tail.compare_exchange_strong(oldtail, new pointer(nxt -> ptr, oldtail -> count + 1), std::memory_order_release, std::memory_order_relaxed);
            }
            else
            {
                result = nxt -> ptr -> value;
                if(M -> head.compare_exchange_strong(oldhead, new pointer(nxt -> ptr, oldhead -> count + 1), std::memory_order_release, std::memory_order_relaxed))
                    break;
            }
        }
	} 
    return oldhead -> ptr;
}

// void showMS()
// {
// 	qnode *temp = M -> head;
// 	int number = 0;
// 	while (temp)
// 	{
// 		number++;
// 		cout << temp->value << "->";
// 		temp = temp->next;
// 	}
// 	cout << endl;
// 	cout << "we have total " << number << " items in the queue" << endl;
// }



