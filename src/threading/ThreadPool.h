#pragma once

#include <queue>
#include <thread>
#include <vector>
#include <future>
#include <condition_variable>
#include <mutex>
#include <iostream>

class ThreadPool
{
private:
	std::mutex mx;
	std::condition_variable cv;
	std::vector<std::thread> workers;
	std::queue<std::function<void(void)>> work;

	bool shutdown = false;

public:
	ThreadPool(size_t poolSize);
	~ThreadPool();

	template<typename F, typename... Args>
	inline auto enqueueTask(F&& f, Args&&... args)->std::future<typename std::result_of<F(Args...)>::type> {

		using returnType = typename std::result_of<F(Args...)>::type;
		auto task = std::make_shared <std::packaged_task<returnType()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
		std::future<returnType> res = task->get_future();

		{
			std::lock_guard<std::mutex> lg(this->mx);
			this->work.push([task]() {(*task)(); });
			this->cv.notify_one();
		}

		return res;
	}


	ThreadPool(const ThreadPool&) = delete;
	void operator = (const ThreadPool&) = delete;

private:
	void listen();
};


