#pragma once
#ifndef __POOL_THREAD_H__
#define __POOL_THREAD_H__

#include <future>
#include <type_traits>

#include <thread>
#include <condition_variable>
#include <mutex>

#include <vector>
#include <queue>
#include <memory>

#include <functional>

class CPool_Thread
{
public:
	CPool_Thread(const size_t num_threads);
	~CPool_Thread();


public:
	template<typename T, typename... Args>
	inline std::future<typename std::result_of<T(Args...)>::type>	Enqueue(T&& f, Args&&... args) {

		if (stop_all_)
		{
			throw std::runtime_error("Pool Stop");
		}

		using return_type = typename std::result_of<T(Args...)>::type;

		auto job = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<T>(f), std::forward<Args>(args)...));

		std::future<return_type> job_result_future = job->get_future();

		{
			std::lock_guard<std::mutex> lock(m_job_q_);
			q_jobs_.push([job]() {
				(*job)();
			});
		}
		cv_job_q_.notify_one();

		return job_result_future;
	}

public:
	void								Work();



private:
	size_t								num_threads_;
	std::vector<std::thread>			vec_workers_threads_;	// 
	std::queue<std::function<void()>>	q_jobs_;				// for storing functions to pass to Thread; 

	std::condition_variable				cv_job_q_;				// race condition;
	std::mutex							m_job_q_;				// producer - consumer pattern;

	bool								stop_all_;
};


#endif // !__POOL_THREAD_H__

