#include <omp.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "WaitFreeQueue.cpp"
#include <chrono>
#include <atomic>

#include "BlockQueue.cpp"
#include "TreiberStack.cpp"


using namespace std;
double enqueue_dequeue_wait_free(int round)
{
    int first = round / 3;
    int second = round / 3 * 2;
    auto start = std::chrono::steady_clock::now();
    #pragma omp parallel  num_threads(4) 
    {
        int thread_number = omp_get_thread_num();
        if(thread_number == 0)
        { 
            int number = 0;
            while(number < round)
            {
                qnode* q = dequeue_wait_free();
                if(q != nullptr)
                {
                    number++;
                }
            }
        }
        else if(thread_number == 1)
        {
            for(int i = 0; i < first; i++)
                enqueue(i);        
        }
        else if(thread_number == 2)
        {
            for(int i = first; i < second; i++)
                enqueue(i);      
        }
        else 
        {
            for(int i = second; i < round; i++)
                enqueue(i); 
        }
    }
    // cout << "Finsh" << endl;
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    // std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    return elapsed_seconds.count(); 
}
double enqueue_dequeue_treiber(int round)
{
    int first = round / 3;
    int second = round / 3 * 2;
    auto start = std::chrono::steady_clock::now();
    #pragma omp parallel  num_threads(4) 
    {
        int thread_number = omp_get_thread_num();
        if(thread_number == 0)
        { 
            int number = 0;
            while(number < round)
            {
                qnode* q = TreiberDequeue();
                if(q != nullptr)
                {
                    number++;
                }
            }
        }
        else if(thread_number == 1)
        {
            for(int i = 0; i < first; i++)
                TreiberEnqueue(i);        
        }
        else if(thread_number == 2)
        {
            for(int i = first; i < second; i++)
                TreiberEnqueue(i);      
        }
        else 
        {
            for(int i = second; i < round; i++)
                TreiberEnqueue(i); 
        }
    }
    // cout << "Finsh" << endl;
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    // std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    return elapsed_seconds.count(); 
}
double enqueue_dequeue_block(int round)
{
        int first = round / 3;
    int second = round / 3 * 2;
    auto start = std::chrono::steady_clock::now();
    #pragma omp parallel  num_threads(4) 
    {
        int thread_number = omp_get_thread_num();
        if(thread_number == 0)
        { 
            int number = 0;
            while(number < round)
            {
                qnode* q = BlockDequeue();
                if(q != nullptr)
                {
                    number++;
                }
            }
        }
        else if(thread_number == 1)
        {
            for(int i = 0; i < first; i++)
                BlockEnqueue(i);        
        }
        else if(thread_number == 2)
        {
            for(int i = first; i < second; i++)
                BlockEnqueue(i);      
        }
        else 
        {
            for(int i = second; i < round; i++)
                BlockEnqueue(i); 
        }
    }
    // cout << "Finsh" << endl;
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    // std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    return elapsed_seconds.count(); 
}
void core(int round)
{
    double first, second, third;
    for(int i = 0; i < 10; i++)
        first += enqueue_dequeue_wait_free(round);
    cout << "wait-free use " << first / 10 << endl;
    for(int i = 0; i < 10; i++)
        second += enqueue_dequeue_treiber(round);
    cout << "treiber use " << second / 10 << endl;
    for(int i = 0; i < 10; i++)
        third += enqueue_dequeue_block(round);
    cout << "block use " << third / 10 << endl;
}
int main()
{
    q = new NewQueue();
    t = new Treiber();
    b = new Block();
    // no_data_race = q -> tail; 
    // enqueue_dequeue_wait_free(400);
    for(int i = 100000; i < 1000001; i += 100000)
    {
        cout << "Round " << i << endl; 
        core(i);
    }
}