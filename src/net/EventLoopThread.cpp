#include "net/EventLoopThread.h"
#include "net/EventLoop.h"
#include <cassert>

namespace Net
{
	EventLoopThread::EventLoopThread() 
	{

	}


	EventLoopThread::~EventLoopThread()
	{

	}


	void EventLoopThread::Run()
	{
		EventLoop loop;
		loopOfThisThread_ = &loop;
		loopCond_.notify_one();
		loop.Loop();
		loopOfThisThread_ = nullptr;
	}


	EventLoop* EventLoopThread::StartLoopThread()
	{
		this->Start();
		std::unique_lock<std::mutex> lk(mutex_);
		while (loopOfThisThread_ == nullptr)
		{
			loopCond_.wait(lk);
		}
		assert(loopOfThisThread_);
		return loopOfThisThread_;
	}
}

