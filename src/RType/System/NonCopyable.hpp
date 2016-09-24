#ifndef RTYPE_SYSTEM_NONCOPYABLE_HPP_
#define RTYPE_SYSTEM_NONCOPYABLE_HPP_

namespace rtype
{
	namespace system
	{
		class NonCopyable
		{
		protected:
			NonCopyable() {}
		public:
			NonCopyable(const NonCopyable&) = delete;
			NonCopyable& operator=(const NonCopyable&) = delete;
		};
	} // namespace system
} // namespace rtype

#endif // RTYPE_SYSTEM_NONCOPYABLE_HPP_
