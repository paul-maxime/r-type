#ifndef RTYPE_SERVER_THREADPOOL_HPP_
#define RTYPE_SERVER_THREADPOOL_HPP_

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <memory>

namespace rtype
{
	namespace server
	{
		class ThreadPool
		{
		private:
			std::vector<std::unique_ptr<std::thread>> _threads;
			std::queue<std::function<void ()>> _tasks;
			std::mutex _mutex;
			bool _running;
			size_t _size;
			size_t _activeCount;

		public:
			ThreadPool(unsigned int size);
			virtual ~ThreadPool();

			void add(const std::function<void ()>& task);
			void resize(size_t size);
			void join();
			void quit();

			size_t size();

		private:
			void run();
			void callSafe(const std::function<void ()>& fct) const;
			bool pickTask(std::function<void ()>& fct, bool& active);
		};
	} // namespace server
} // namespace rtype

#endif // RTYPE_SERVER_THREADPOOL_HPP_
