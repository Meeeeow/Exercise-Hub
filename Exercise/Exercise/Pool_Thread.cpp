#include "Pool_Thread.h"



CPool_Thread::CPool_Thread(const size_t num_threads)
	: num_threads_(num_threads), stop_all_(false)
{
	vec_workers_threads_.reserve(num_threads_);
	for (size_t i = 0; i < num_threads_; ++i) {
		vec_workers_threads_.emplace_back([this]() { 
			this->Work(); }
		);
	}
}


CPool_Thread::~CPool_Thread()
{
	stop_all_ = true;
	cv_job_q_.notify_all();								// notify_all() is condition variable function. wake up all threads.

	for (auto& iter : vec_workers_threads_) {
		iter.join();
	}
}

void CPool_Thread::Work()
{
	while (true) {
		std::unique_lock<std::mutex> lock(m_job_q_);

		cv_job_q_.wait(lock, [this]() { 
			return !this->q_jobs_.empty() || stop_all_; }
		);

		if (stop_all_ && this->q_jobs_.empty()) {
			return;
		}
		
		std::function<void()> job = std::move(q_jobs_.front());
		q_jobs_.pop();
		lock.unlock();

		job();
	}
}
