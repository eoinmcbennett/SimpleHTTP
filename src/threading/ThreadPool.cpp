#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t poolSize) {
	//If 0 was passed create at least 2 threads
	if (poolSize == 0)
		poolSize = 2;

	for (size_t i = 0; i < poolSize; i++)
		workers.emplace_back(std::thread(&ThreadPool::listen, this));
}

ThreadPool::~ThreadPool() {
	shutdown = true;
	for (std::thread& thread : workers) {
		thread.join();
	}
}

//Function for each thread to listen for work on the queue and process it
void ThreadPool::listen() {
	while (true) {
		std::function<void()> workToBeDone;

		{
			std::unique_lock<std::mutex> ul(mx);
			cv.wait(ul, [this] { return !work.empty(); });
			workToBeDone = work.front();
			work.pop();
		}
		std::cout << "Job started on thread: " << std::this_thread::get_id() << std::endl;

		workToBeDone();

		//Return from the loop if the pool is shutting down
		if (shutdown) {
			return;
		}
	}
}



