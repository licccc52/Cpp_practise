#include<iostream>
#include<thread>
#include<mutex>
#include<string>
#include<condition_variable>
#include<queue>

std::queue<int> g_queue;
std::condition_variable g_cv;
std::mutex mtx;

void Producer()
{
    for(int i=0; i < 10; i++)
    {
        std::unique_lock<std::mutex> lock(mtx);
        g_queue.push(i);
        //通知消费者来取任务
        g_cv.notify_one();
        std::cout << "push task : " << i << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::microseconds(100));
}

int Consumer()
{//持续不断地从生产者中取出任务执行
    while(1)
    {
        std::unique_lock<std::mutex> lock(mtx);
        //如果队列为空， 需要等待
        //队列为空表示需要等待
        g_cv.wait(lock, [](){
            return !g_queue.empty();
        });
        int value = g_queue.front();
        std::cout << " g_queue.pop()  : "<<value << std::endl;
        g_queue.pop();
    }
}

int main()
{
    std::thread_t1(Producer);
    std::thread_t2(Consumer);
    t1.join();
    t2.join();

    return 0;
}