#include<iostream>
#include<thread>
#include<thread>
#include<mutex>
#include<queue>
#include<condition_variable>
#include<unistd.h>
#include<sys/syscall.h>

std::queue<int> mission;
std::mutex mtx;
std::condition_variable c_v;

void provider()
{
    int i = syscall(SYS_gettid);
    std::unique_lock<std::mutex> lock(mtx);
    mission.push(i);
    std::cout << "PROVIDER add task : " <<  i  << std::endl;
    lock.unlock();
    c_v.notify_one();
    sleep(100);
}


void consumer()
{
    int id = syscall(SYS_gettid);
    while(true)
    {
        std::unique_lock<std::mutex> lock(mtx);
        c_v.wait(lock, [](){
            return !mission.empty();
        });
        int temp = mission.front();
        std::cout << "               Thread " << id <<" execute : " << temp << std::endl;
        mission.pop();  
    }
}

int main()
{
    std::thread t2(consumer);
    for(int i=0; i < 10; i++)
    {
        std::thread t1(provider);
        t1.detach();
    }

    t2.join();

    return 0;
}
