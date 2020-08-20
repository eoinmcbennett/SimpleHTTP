//
// Created by Eoin on 20/08/2020.
//

#include "ThreadPool.h"
#include

ThreadPool::ThreadPool(unsigned int maxThreads) {
    if(maxThreads > 0){
        this->maxThreads = maxThreads;
    }

    for(int i = 0; i < maxThreads; i++){
        workers.emplace_back(&ThreadPool::listen,this);
    }
}

std::future<Response> ThreadPool::enqueueWork(std::promise<Response> promise, Request req) {
    auto response = promise.get_future();
    Job* job = new Job();
    job->responsePromise = std::forward<std::promise<Response>>(promise);
    job->requestToProcess = std::move(req);

    queueMutex.lock();
    workQueue.push(job);
    queueMutex.unlock();
    condVar.notify_one();
}

[[noreturn]] void ThreadPool::listen() {
    //Lock the queue mutex
    //Get the next job
    //Unlock queue mutex
    //Run the job
    //Repeat
    while(true){
        std::unique_lock<std::mutex> lg(queueMutex);
        condVar.wait(lg,[this]{ return !workQueue.empty(); });

        processRequest(std::move(workQueue.front()->responsePromise),workQueue.front()->requestToProcess);

    }
}

void ThreadPool::processRequest(std::promise<Response> response, Request request) {

}

