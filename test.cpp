#include <omp.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "WaitFreeQueue.cpp"
#include <chrono>
#include <atomic>
#include <vector>

#include "MSQueue.cpp"
#include "TreiberStack.cpp"

using namespace std;
WaitFreeQueue *Q;
MSQueue *M;
Treiber *T;
double enqueue_dequeue_wait_free(int round, int thread_cnt)
{
    thread_cnt--;
    int num = round / thread_cnt;
    auto start = std::chrono::steady_clock::now();
#pragma omp parallel num_threads(thread_cnt + 1)
    {
        int thread_number = omp_get_thread_num();
        if (thread_number == 0)
        {
            int number = 0;
            while (number < round)
            {
                qnode *q = dequeue_wait_free(Q);
                if (q != nullptr)
                {
                    number++;
                }
            }
        }
        else
        {
            // cout << thread_number << endl;
            if (thread_number != thread_cnt)
            {
                for (int i = (thread_cnt - 1) * num; i < thread_cnt * num; i++)
                    enqueue(Q, i);
            }
            else
            {
                for (int i = (thread_cnt - 1) * num; i < round; i++)
                    enqueue(Q, i);
            }
        }
    }
    // cout << "Finsh" << endl;
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    // std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    return elapsed_seconds.count();
}
double enqueue_dequeue_treiber(int round, int thread_cnt)
{
    thread_cnt--;
    int num = round / thread_cnt;
    auto start = std::chrono::steady_clock::now();
#pragma omp parallel num_threads(thread_cnt + 1)
    {
        int thread_number = omp_get_thread_num();
        if (thread_number == 0)
        {
            int number = 0;
            while (number < round)
            {
                qnode *q = TreiberDequeue(T);
                if (q != nullptr)
                {
                    number++;
                }
            }
        }
        else
        {
            if (thread_number != thread_cnt)
            {
                for (int i = (thread_cnt - 1) * num; i < thread_cnt * num; i++)
                    TreiberEnqueue(T, i);
            }
            else
            {
                for (int i = (thread_cnt - 1) * num; i < round; i++)
                    TreiberEnqueue(T, i);
            }
        }
    }
    // cout << "Finsh" << endl;
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    // std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    return elapsed_seconds.count();
}
double enqueue_dequeue_MS(int round, int thread_cnt)
{
    thread_cnt--;
    int num = round / thread_cnt;
    auto start = std::chrono::steady_clock::now();
#pragma omp parallel num_threads(thread_cnt + 1)
    {
        int thread_number = omp_get_thread_num();
        if (thread_number == 0)
        {
            int number = 0;
            while (number < round)
            {
                int temp;
                msnode *q = MSDequeue(M, temp);
                if (q != nullptr)
                {
                    number++;
                }
            }
        }
        else
        {
            if (thread_number != thread_cnt)
            {
                for (int i = (thread_cnt - 1) * num; i < thread_cnt * num; i++)
                    MSEnqueue(M, i);
            }
            else
            {
                for (int i = (thread_cnt - 1) * num; i < round; i++)
                    MSEnqueue(M, i);
            }
        }
    }
    // cout << "Finsh" << endl;
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    // std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    return elapsed_seconds.count();
}
int main()
{
    Q = new WaitFreeQueue();
    T = new Treiber();
    M = new MSQueue();
    msnode *node_temp = new msnode(-1);
    pointer *temp = new pointer(node_temp, 0);
    M->head = M->tail = temp;
    // cout << "wait-free use " << enqueue_dequeue_wait_free(50000000, 2) << endl;

    // cout << "treiber use " << enqueue_dequeue_treiber(50000000, 90) << endl;
    for (int i = 2; i <= 128; i *= 2)
    {
        count = 0;
        cout << enqueue_dequeue_wait_free(50000000, i) << ",";
        cout << "count" << count / (double)50000000 << endl; 
    }
    cout << endl;

    // enqueue_dequeue_wait_free(1000, 4);
}
