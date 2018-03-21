/*************************************************************************
	> File Name: lock.cc
	> Author: wuxiangwei
	> Mail: wuxiangwei@corp.netease.com
	> Created Time: 二  2/27 14:31:37 2018
 ************************************************************************/

#include<iostream>
#include<queue>
#include<mutex>
#include<thread>

std::queue<int> g_queue;
std::mutex g_qlock;
std::condition_variable g_cv;
int g_data = 0;

void producer_entry(void) {
    while(true) {
        std::unique_lock<std::mutex> ulk(g_qlock);

        g_queue.push(g_data);
        ++g_data;
        ulk.unlock();
        g_cv.notify_all();

        std::chrono::milliseconds dura(1000);
        std::this_thread::sleep_for(dura);
    }
}

void consume_entry(void) {
    while(true) {
        std::unique_lock<std::mutex> ulk(g_qlock);
        while (g_queue.empty()) {
            g_cv.wait(ulk);
        }

        int data = g_queue.front();
        g_queue.pop();
        ulk.unlock();

        std::cout << std::this_thread::get_id()  << " "  << data << std::endl;

        std::chrono::milliseconds dura(2000);
        std::this_thread::sleep_for(dura);
    }
}


int main(int argc, char *argv[]) {
    std::vector<std::thread> threads;
    threads.clear();

    // create producers
    for (int i=0; i<1; ++i) {
        threads.push_back(std::thread(producer_entry));
    }

    for (int i=0; i<2; ++i) {
        threads.push_back(std::thread(consume_entry));
    }

    for (auto &th: threads) {
        th.join();
    }

    return 0;
}
