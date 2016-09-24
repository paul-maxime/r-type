#include <functional>
#include <chrono>

#include "RType/Server/ThreadPool.hpp"
#include "RType/System/Chrono.hpp"

namespace rtype
{
	namespace server
	{
		ThreadPool::ThreadPool(unsigned int size)
			: _running(true),
			  _activeCount(size)
		{
			resize(size);
		}

		ThreadPool::~ThreadPool()
		{
			quit();
		}

		void ThreadPool::add(const std::function<void ()>& task)
		{
			std::lock_guard<std::mutex> lock(_mutex);

			_tasks.push(task);
		}

		void ThreadPool::resize(size_t size)
		{
			std::lock_guard<std::mutex> lock(_mutex);

			_size = size;
			while (_threads.size() < _size)
			{
				std::thread* thread = new std::thread(std::bind(&ThreadPool::run, this));
				_threads.push_back(std::unique_ptr<std::thread>(thread));
			}
		}

		void ThreadPool::join()
		{
			bool is_empty = false;
			while (_running && !is_empty)
			{
				_mutex.lock();
				is_empty = (_activeCount == 0 && _tasks.size() == 0);
				_mutex.unlock();
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
			quit();
		}

		void ThreadPool::quit()
		{
			if (!_running) return;
			_running = false;
			for (auto& thread : _threads)
			{
				thread->join();
			}
		}

		size_t ThreadPool::size()
		{
			return _size;
		}

		void ThreadPool::run()
		{
			bool active = true;
			while (_running)
			{
				std::function<void ()> fct;

				bool is_empty = pickTask(fct, active);
				if (!is_empty)
					callSafe(fct);

				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
		}

		void ThreadPool::callSafe(const std::function<void ()>& fct) const
		{
			try
			{
				fct();
			}
			catch (const std::exception& e)
			{
				std::cerr << "[" << std::chrono::system_clock::now() << "] "
						  << "error in thread " << std::this_thread::get_id()
						  << ":" << std::endl
						  << "	" << e.what() << std::endl;
			}
		}

		bool ThreadPool::pickTask(std::function<void ()>& fct, bool& active)
		{
			std::lock_guard<std::mutex> lock(_mutex);

			bool is_empty = _tasks.empty();
			if (!is_empty)
			{
				fct = _tasks.front();
				_tasks.pop();
				if (!active)
				{
					active = true;
					_activeCount += 1;
				}
			}
			else if (active)
			{
				active = false;
				_activeCount -= 1;
			}
			return is_empty;
		}
	} // namespace server
} // namespace rtype
