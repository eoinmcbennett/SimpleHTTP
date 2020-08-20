//
// Created by Eoin on 20/08/2020.
//

#ifndef SERVERTEST_THREADPOOL_H
#define SERVERTEST_THREADPOOL_H

#include <thread>
#include <future>
#include <vector>
#include <queue>
#include <mutex>
#include <map>
#include <condition_variable>

#include "../Response.h"
#include "../Request.h"
#include "Job.h"

class ThreadPool {
private:
    unsigned int maxThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> workers;
    std::queue<Job*> workQueue;
    std::mutex queueMutex;
    std::condition_variable condVar;

public:
    ThreadPool() = delete;
    ThreadPool(unsigned int maxThreads);

    std::future<Response> enqueueWork(std::promise<Response> responsePromise, Request reqToHandle);

private:
    [[noreturn]] void listen();
    void processRequest(std::promise<Response>,Request);



};


#endif //SERVERTEST_THREADPOOL_H
